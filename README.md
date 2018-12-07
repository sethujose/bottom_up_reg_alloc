# Bottom Up Register Allocator

This is the implementation of a bottom up register allocator. It reads the instructions from the input file 'input.txt' and writes the register allocated code to output.txt file. 

It generates the detailed information about the register allocation in btm_up_reg_alloc_report.txt file. 

The allocator allocates registers to currently used variables in a greedy fashion. If there are no more registers available for variables, then the last recently used variable is spilled to memory. 

The input instruction file to be converted and the register count should be specified as command line argument to the exectuable.

# Files
- list.c: implements the linked list to store the variables which are encountered in the input instructions
reg_alloc.c : performs the entire top down allocation

# Preqrequisites
To build the module, following tools are needed:
- gcc

This allocator was developed using gcc (7.3.0)

# Build
To clean build the bottom up allocator, the following commands can be used:

make clean
make 

# Run
Allocator can be run by executing the output file btm_up as follows:

./btm_up input.txt 10

where 10 is the number of registers to be used.

