# Random Access Machine

This is an implementation of a Random Access Machine (RAM) in C++. The RAM is a theoretical computer that can be used to model the execution of algorithms.

The RAM has a set of registers, a memory, a program counter, and an instruction set. The RAM is capable of executing instructions in a sequential order and can perform basic arithmetic operations.

## Instruction Set

The RAM has the following instructions:

- **halt**: Stops the execution of the program.
- **add**: Adds the values of two registers and stores the result in a register.
- **sub**: Subtracts the values of two registers and stores the result in a register.
- **mul**: Multiplies the values of two registers and stores the result in a register.
- **div**: Divides the values of two registers and stores the result in a register.
- **load**: Loads a value from memory into a register.
- **store**: Stores a value from a register into memory.
- **read**: Reads a value from the input and stores it in a register.
- **write**: Writes a value from a register to the output.
- **jump**: Jumps to a specified line in the program.
- **jzero**: Jumps to a specified line in the program if a register is zero.
- **jgtz**: Jumps to a specified line in the program if a register is greater than zero.
- **jltz**: Jumps to a specified line in the program if a register is less than zero.

## Installation

To compile the code, run the following command:

```bash
g++ -o ram main.cpp
```

To run the program, use the following command:

```bash
./ram
```

## Usage

The program will display a help menu with a list of available options:

- 1 Load a program: Load a program from a file by entering the filename.
- 2 Execute a program: Execute the loaded program. If no program is loaded, it will show an error.
- 3 Show Machine: Show all the registers, memory cells, and string memory cells.
- 4 Configure Machine: Configure the machine by setting the number of registers, memory cells, and string memory cells.
- 5 Reset Machine: Reset the machine to its initial state.
- 6 Show Registers: Show the registers that have a non-zero value.
- 7 Show Memory: Show the memory cells that have a non-zero value.
- 8 Show String Memory: Show the string memory cells that have a non-empty string.
- 9 Help: Show this help menu.
- 10 Show Command History: Show the history of commands entered.
- 0 Exit: Exit the RAM.

Here is an example of every instruction:

```ram
halt            // Stops the execution of the program
add 1 2 3       // Adds the values of registers 2 and 3 and stores the result in register 1
sub 1 2 3       // Subtracts the value of register 3 from register 2 and stores the result in register 1
mul 1 2 3       // Multiplies the values of registers 2 and 3 and stores the result in register 1
div 1 2 3       // Divides the value of register 2 by the value of register 3 and stores the result in register 1

load 1 2        // Loads the value from memory cell 2 into register 1
store 1 2       // Stores the value from register 1 into memory cell 2

read 1          // Reads a value from the input and stores it in register 1
write 1         // Writes the value from register 1 to the output

jump <tag>      // Jumps to the specified tag in the program
jzero 1 <tag>   // Jumps to the specified tag in the program if register 1 is zero
jgtz 1 <tag>    // Jumps to the specified tag in the program if register 1 is greater than zero
jltz 1 <tag>    // Jumps to the specified tag in the program if register 1 is less than zero
```

## Example

This program will prompt the user to enter a number, then it will perform addition, subtraction, multiplication, and division operations on that number and print the results:

```ram
.data // data section

welcome: .string "Welcome to the arithmetic program."
end_program: .string "End of the program."
get_input: .string "Enter a number: "
get_add: .string "10 + "
get_sub: .string "20 - "
get_mul: .string "30 * "
get_div: .string "40 / "
equals: .string " = "

operator_add: .int 10
operator_sub: .int 20
operator_mul: .int 30
operator_div: .int 40

.code // code section

write welcome         // print welcome message
write ENDL            // print new line

load 0 operator_add   // R[0] = 10
load 1 operator_sub   // R[1] = 20
load 2 operator_mul   // R[2] = 30
load 3 operator_div   // R[3] = 40

write get_input       // print get_input message
read 8                // R[8] = input
jzero 8 end           // if input is 0, jump to end

add 4 0 8             // R[4] = R[0] + R[8]
sub 5 1 8             // R[5] = R[1] - R[8]
mul 6 2 8             // R[6] = R[2] * R[8]
div 7 3 8             // R[7] = R[3] / R[8]

write get_add         // print get_add message
write 8               // print input
write equals          // print equals
write 4               // print R[4]
write ENDL            // print new line

write get_sub         // print get_sub message
write 8               // print input
write equals          // print equals
write 5               // print R[5]
write ENDL            // print new line

write get_mul         // print get_mul message
write 8               // print input
write equals          // print equals
write 6               // print R[6]
write ENDL            // print new line

write get_div         // print get_div message
write 8               // print input   
write equals          // print equals
write 7               // print R[7]
write ENDL            // print new line

write end_program     // print end_program message
write ENDL            // print new line 

end:
```

## Contributing

If you would like to contribute to this project, please open an issue or a pull request. Any contributions are welcome!
