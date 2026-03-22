DSA PROJECT INSTALLATION AND USAGE GUIDE - SORTING ALGORITHMS

1. System Requirements & Installation
The project requires the C/C++ programming language.
The source code must be compiled using the C++17 standard.

Download the .zip file and extract it.

To compile the source code into an executable file via the terminal, run the following command in the project directory:
g++ *.cpp -std=c++17 -o groupid

On macOS or Linux environments, the executable will be created as a binary file without the .exe extension. You can run the program using:
./groupid


2. Command Line Arguments
The general prototype to execute the program is:
./groupid -mode [Algorithm] [Input/Size] [Order] [Output_parameter]

-mode: Use -a for algorithm mode or -c for comparison mode.

Algorithm: Enter the algorithm name, e.g., selection-sort, insertion-sort, bubble-sort, shaker-sort, shell-sort, heap-sort, merge-sort, quick-sort, counting-sort, radix-sort, flash-sort, binary-insertion-sort.

Input_order: Data arrangements include:
-sorted (sorted), -nsorted (nearly sorted), -rev (reverse sorted), -rand (randomized).

Output_parameter: Output parameters include:
-time (running time only), -comp (comparisons only), or -both (both).

Input_size: The generated data size is limited to a maximum of 1,000,000 elements.

3. Execution Commands (Usage)

Command 1 - Run a sorting algorithm on the given input data:
./groupid -a [Algorithm] [Input_file] [Output_parameter]

Command 2 - Run a sorting algorithm on automatically generated data:
./groupid -a [Algorithm] [Input_size] [Input_order] [Output_parameter]

Command 3 - Run a sorting algorithm on all data arrangements:
./groupid -a [Algorithm] [Input_size] [Output_parameter]

Command 4 - Run two sorting algorithms on the given input:
./groupid -c [Algorithm1] [Algorithm2] [Input_file]

Command 5 - Run two sorting algorithms on automatically generated data:
./groupid -c [Algorithm1] [Algorithm2] [Input_size] [Input_order]

Note:
The program will automatically write to the output.txt file when running Command 1 and Command 2.
It will also automatically write generated input to input.txt (or input_1.txt to input_4.txt) when using the automatic data generation feature.