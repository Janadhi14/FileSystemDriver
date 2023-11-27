File system driver for Linux

## Dev log 
<!-- store -->
- Initally I have added rules to the Makefile to create store-prog and retrieve-rpog from the store.c and retrieve.c source files which include the -g -W -Wall flalgs duign the compilation.
- Starting with storing files,established the CLI argument with 2 arguments and if it's not 2 then we ar exiting with failure. 
- implementing the second CLI argument so that if we have -r we are going to call the' randomise flag 
- implemented the check to see if the MAXSIZE is larger than 4864 and then print out "truncated" if it is larger.
- implemented reading a file and error handeling if we can't open the file. 
- implemented writing block directly 
- implementing indirect block writing 
- handled storing file data if there is an unfilled block at the end.(not sure if implemented properly tho)
- implemented truncation, and randomisation with NDIRECT adressing

<!-- retrieve -->
- implemented the CLI arguments for both overwriting by asking y/n and also  of the CLI argument usage is wrong 
- implemented the reading a file logic, to do this I have used the read_block to first to create a read inode method which will be used to ditermine the order of the blocks 
- Completed the direct blocks logic so we are able to read the data from the direct blocks(not truncated)If we are not in NDIRECT, i think i need to for loop through and check that we are not at the end of the inode, need to then read block by block of the direct and then write to the file, need to somehow keep track of how much of the file has been written of how much is left .
- If there is a NDIRECT (could check using the reaminder) we need to go through the NDIRECT block adn read in the block numbers and then write them into the file aswell.
- Competed working with direct addresses, need to check on NDIRECT
- not working with ndirect so debugging (there were problems with the type, using int8_t insted of int, so has been fixed , wokring properly as i should in terminal, checking if it is working with writing to the file)
- DONE! working sucessfully with writing to file




## to do list:
In libmemdrv.h update BLOCK_SIZE and MAX_BID to 64 and 78.
- [x] update block size 
- [x] max_bid 
- [x] add rules to create store-prog and retrieve prog from the store.c and  - - [x] retrieve.c source file and makeusr to include the flags -g -W -Wall during compilation 


## Store files 
- [x] accept a file name as the first arg to be stored /dev/memdrv
- [x] accept a second argument -r to specify random block ordering
- [x] check if the file length exceeds 4864 bytes.
- [x] if exceeded, truncate the file and print “truncated” to /stderr/
- [x] store the file data in /dev/memdrv
- [x] if -r is provided, ensure the blocks are stored in a random order

- [x] testing (works accordingly)

## Retrieve files
- [x] handles CL arguments 
- [x] if no argument is provided output the retireved file 
- [x] if an arg is provided, it should be considered as the output file name 
- [x] if the file name exists promt the uer to confirm overwriting 
- [x] data retrieval to ensure no assumption of data block seq
- [x] retrieve the dat  blocs even if stored in a random order on the RAM
- [x] ensure file is identical to the origional
- [x] use a command like ./store-prog myfile.txt to store fiels according to indexed allocation
- [x] use diff to compare teh origional and retrieved files to check they are the same


- [x] testing 
- [x] debugging 

## final
- [x] error handelling 
- [x] final check

