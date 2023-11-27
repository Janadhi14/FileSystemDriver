// store.c
#include <stdio.h>
#include <stdlib.h>
#include "fs.h"
#include "string.h"
#include "libmemdrv.h"

/*• This program should take a command-line argument, which is the name of a file that you
want to store in /dev/memdrv.
• If the length of the file is greater than 4864 bytes it should be truncated and the word
truncated printed to /stderr/.
• The program should take an optional second command-line argument -r which specifies a
random ordering of the blocks in the direct and indirect indexes
*/

// need to define device and MAX_BID
#define MAXSIZE DEVICE_SIZE - (BLOCK_SIZE * 2)

// free_list
static int8_t free_list[MAX_BID];
// store_file method that will store the file
void store_file(const char *filepath, int randomise);
void shuffle(int8_t *array, int n);
void write_inode(Inode* inode);



// main
int main(int argc, char *argv[]){

    // if the user enters the wrong number of CLI arguments 
    if (argc < 2 || argc > 3){
        fprintf(stderr, "Usage: %s [FILE] [-r]\n", argv[0]);
        return EXIT_FAILURE;
    }
    int randomise = 0;
    // if randomise is specified
    if (argc == 3){
        if (strcmp(argv[2], "-r") == 0){
            randomise = 1;
        }
        else{
            fprintf(stderr, "The argument is invalid: %s\nUsage: %s [FILE] [-r]\n", argv[2], argv[0]);
            return EXIT_FAILURE;
        }
    }

    // calling the store_file method passing in the second argument as the file name and the third argument being the randomisation
    store_file(argv[1], randomise);
    // prints message if sucessful
    printf("SUCCCCCCCCsess!! file was stored.\n");
    return EXIT_SUCCESS;
}

// implementation for storing file
void store_file(const char *filepath, int randomise){
    Inode inode = {0}; 
    FILE *file;
    size_t bytsRead;
    int block_index = 1; 
    char buf[BLOCK_SIZE];

    // need to open device
    open_device();

    // if randomise is true we need to use random ordering of blocks for direct and indirect
    if (randomise){
        for (int i = 0; i < MAX_BID; i++){
            free_list[i] = i;
        }
        shuffle(free_list + 1, MAX_BID - 1);
    }

    // if we can't open the file 
    file =fopen(filepath, "rb");
    if(!file){
        fprintf(stderr, "Could not open file:%s\n", filepath);
        close_device();
        exit(EXIT_FAILURE);
    }

    // get the size of the file and then if the size is greater we nee to truncate 
    fseek(file, 0, SEEK_END);
    inode.size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (inode.size > MAXSIZE)
    {
        fprintf(stderr, "truncated\n");
        inode.size = MAXSIZE;
    }

    // writing direct blocks 
    for(int i = 0; i< NDIRECT && (i* BLOCK_SIZE) < inode.size; i++){
        bytsRead = fread(buf, 1, BLOCK_SIZE, file);
        // if we cant read the file
        if (bytsRead < BLOCK_SIZE && !feof(file)){
            fprintf(stderr, "Error reading from file.\n");
            fclose(file);
            close_device();
            exit(EXIT_FAILURE);
        }
        if (randomise) { 
        inode.addrs[i] = free_list[block_index++];
        if (inode.addrs[i] == 0) { // if the random block is the inode
            i--; 
            continue; 
            }
        }else {
            inode.addrs[i] = block_index++;
        }
        
        write_block(inode.addrs[i], buf);
    }
    // writing NDirect blokcs (if the size is larger than NDIRECT* BLOCK_SIZE we are going to need indirect blocks)
    if(inode.size > NDIRECT * BLOCK_SIZE){
        int8_t indirect[MAX_BID];

        if(randomise)
            inode.addrs[NDIRECT] = free_list[block_index++];
        for (int i = NDIRECT * BLOCK_SIZE; i < inode.size; i += BLOCK_SIZE){
            bytsRead = fread(buf,1,BLOCK_SIZE, file);

            if(bytsRead < BLOCK_SIZE && !feof(file)){
                fprintf(stderr, "There was an error reading the file!!\n");
                fclose(file);
                close_device();
                exit(EXIT_FAILURE);
            }
            
            //  if the randomise option is selected 
            int indirect_index = (i - NDIRECT * BLOCK_SIZE) / BLOCK_SIZE;
            if (randomise)
                indirect[indirect_index] = free_list[block_index++];
            else
                indirect[indirect_index] = block_index++;
            
            write_block(indirect[indirect_index], buf);

        }
        write_block(inode.addrs[NDIRECT], (char*)indirect);

    }
    //close file 
    fclose(file);
    write_inode(&inode); 
    // need to close device
    close_device();
}
// writing inode 
void write_inode(Inode *inode){
    char buf[BLOCK_SIZE];
    memset(buf, 0, BLOCK_SIZE);
    memcpy(buf, inode, sizeof(Inode));
    write_block(0, buf);
}
// shuffle
void shuffle(int8_t *array, int n){
    for (int i = 0; i < n - 1; i++){
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        int8_t t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}