                        Assignment 1
# about
This folder contains three files A1_q1.cpp,A2_q2.cpp and readme file.

This assignment is basically used to perform actions like blockwise reversal,full file reversal,partial reversal logic namely flag0,flag1,flag2 respectively in A1_q1.cpp and verification of those actions and permissions of the files logic in A2_q2.cpp on the text files. 

The code for both cpp files is written in c++ language using system calls like read,write,lseek,stat,fflush,perror,mkdir,open,close.

A progress bar is also shown on the terminal for each flag execution.
# Question1
# flag0(blockwise reversal)
This flag reverses the file blockwise reversal where blocksize is given by user.

-**Logic** :Starting from first character of the file block is considered and the contents in the is reversed and stored in the outout file maintaining the order of the block.

-**Execution**
g++ A1_q1.cpp
./a.out <input file name> <flag> <block size>
output file:assignment1/0_<input_file_name>
Example: If A.txt contains ABCDEFGH and block size 4, output is DCBAHGFE


# flag1(full file reversal)
This flag reverses the full file and stores in a file in a directory named assignment1.

Logic:The file content is divided into blocks.starting from the last block the block content is reversed and written into a output file similarly for all the blocks process is done so the First byte becomes last, last byte becomes first.

-**Execution:**
./a.out <input file> 1
output file:Assignment 1/1_<input_file_name>
Example:Hello, World! becomes !dlroW ,olleh

# flag2(partial reversal)
This flag returns the reverse of the content from the 0th byte till before the start index and maintains same content from start to end and reverses from end+1 byte to EOF.

Logic:The content is divided into blocks and stored in buffer and that buffer is reversed and witten into output file and similarly from the end+1 to EOF.

-**Execution:**
/a.out <input file> 2 <start index> <end index>
 Output file: Assignment1/2 <input file name>
 Example: Input Hello, World!, 2 2 7 outputs eHllo, W!dlro.
 
# Question2
Verification Steps

Directory Creation Check
Prints whether assignment1 exists.
File Content Verification
Flag 0: Checks blockwise reversal correctness.
Flag 1: Checks full reversal correctness.
Flag 2: Checks partial reversal correctness.
File Size Check
Compares input and output file sizes.

Permissions Check
Displays read, write, and execute permissions for:
Original file,Output file,Directory.

-**Execution:**
g++ A2_q2.cpp
./a.out <input_file> <output_file> <directory> <flag> [block_size / start end]

Flag 0 Verification:
./a.out assignment1/0_input.txt  input.txt assignment1 0 4

Flag 1 Verification:
./a.out assignment1/1_input.txt  input.txt assignment1 1

Flag 2 Verification:
./a.out assignment1/2_input.txt  input.txt assignment1 2 2 7

-**output format:**
Directory is created: Yes
Whether file contents are correctly processed : Yes
Both Files Sizes are same :yes
User has read permissions on newfile: Yes
User has write permission on newfile: Yes
User has execute permission on newfile: Yes
Group has read permissions on newfile: Yes
Group has write permission on newfile: Yes
Group has execute permission on newfile: Yes
Others has read permissions on newfile: Yes
Others has write permission on newfile: No
Others has execute permission on newfile: Yes
User has read permissions on oldfile: Yes
User has write permission on oldfile: Yes
User has execute permission on oldfile: Yes
Group has read permissions on oldfile: Yes
Group has write permission on oldfile: Yes
Group has execute permission on oldfile: Yes
Others has read permissions on oldfile: Yes
Others has write permission on oldfile: No
Others has execute permission on oldfile: Yes
User has read permissions on directory: Yes
User has write permission on directory: Yes
User has execute permission on directory: Yes
Group has read permissions on directory: Yes
Group has write permission on directory: Yes
Group has execute permission on directory: Yes
Others has read permissions on directory: Yes
Others has write permission on directory: No
Others has execute permission on directory: Yes



