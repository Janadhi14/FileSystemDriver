// retrieve.c 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "fs.h"
#include "libmemdrv.h"


 // "reading from a file and storing on a device"
void read_inode(Inode* inode);

// read_inode method
void read_inode(Inode* inode) {
    char buf[BLOCK_SIZE];
    read_block(0, buf);  
    *inode = *(Inode*)buf; 
}

void read_file(Inode* inode, FILE* file);

// main method 
int main(int argc, char* argv[]){
    // need to check for correct number of arguments if not print error
    if (argc > 2){
        fprintf(stderr, "Usage: %s [FILE]\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* file = stdout;
    if (argc == 2){
        file = fopen(argv[1], "r");
        if (file != NULL){
            // the file exists so we need to ask for overwrite confrimation.
            fclose(file);
            char confirm;
            printf("The file alredy %s exists. Overwrite? (y/n): ", argv[1]);
            scanf("%c", &confirm);
            if (confirm != 'Y' && confirm != 'y'){
                printf("Aborted.\n");
                return EXIT_SUCCESS;
            }
        }

        file = fopen(argv[1], "wb");
        if (file == NULL){
            perror("Error opening the file");
            return EXIT_FAILURE;
        }
    }

    open_device();
    //declerations
    Inode inode;
    read_inode(&inode);
    // need to loop through and read from memdrv to the file we want to write to 
   
    // calling the read file method which will read the file 
    read_file(&inode, file);

     if (file != stdout){
    fclose(file);
    }
    close_device();
    return EXIT_SUCCESS;



 }
 
// read_file method
void read_file(Inode* inode, FILE* file){
        char buf[BLOCK_SIZE];
        int remainder = inode->size;

        // reading and writing to direct blocks
        for(int i = 0; i < NDIRECT && remainder > 0; i++){
            read_block(inode-> addrs[i], buf);
   // for checking if we are at the last block (setting write size to be the remanider)
            int8_t size_written = remainder < BLOCK_SIZE ? remainder : BLOCK_SIZE;
            fwrite(buf, 1, size_written, file);
            remainder -= BLOCK_SIZE;

        }
        //if there is no more data we should use read from.(when we reach the last index of the node 13th)
        if(remainder> 0 && inode->addrs[NDIRECT] !=0){

            int8_t indirect[BLOCK_SIZE/sizeof(int8_t)];
            read_block(inode->addrs[NDIRECT], (char*)indirect);
            // will loop through and write the reaminder of the file 
            for(int i = 0; i < (int8_t)(BLOCK_SIZE/sizeof(int8_t))&& remainder>0; i++){
                read_block(indirect[i], buf);
                int8_t size_written = remainder < BLOCK_SIZE ? remainder : BLOCK_SIZE;
                fwrite (buf, 1, size_written, file);
                remainder-= BLOCK_SIZE;

            }
        }
    }



    

 