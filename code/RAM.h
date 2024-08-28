#ifndef RAM_H
#define RAM_H

#include <fstream>
#include <iomanip>
#include <iostream>

#include "Instructions/instructions.h"

using namespace std;

/**
 * @brief Class to represent a RAM. It contains a 1024 cell memory, a 32
 * cell register bank and a program counter. The machine can load a program from
 * a file, execute it and print the memory state.\n
 * \n
 * The machine has the following instructions: \n
 * - Halt: Stop the execution of the program \n
 * - Add: Sum two registers and store the result in a register \n
 * - Sub: Subtract two registers and store the result in a register \n
 * - Mul: Multiply two registers and store the result in a register \n
 * - Div: Divide two registers and store the result in a register \n
 * - Load: Put a value from memory to a register \n
 * - Store: Put a value from a register to memory \n
 * - Read: Put a value from the input to a register \n
 * - Write: Put a value from a register to the output \n
 * - Jump: Make a jump to a label \n
 * - Jzero: Make a jump if the register is zero \n
 * - Jgtz: Make a jump if the register is greater than zero \n
 * - Jltz: Make a jump if the register is less than zero \n
 * \n
 * The machine can also check if the memory is all zeros and print the memory
 * state.
 */
class RAM {
 public:
  // Constructor
  RAM();

  // Methods
  void reset();
  void loadProgram(const string& filename);
  void executeProgram();

  // Getters
  bool getHalted() const;
  bool getExecutable() const;
  unsigned getNumRegisters() const;
  unsigned getNumMemory() const;
  unsigned getNumStringMemory() const;

  // Setters
  void setNumRegisters(unsigned numRegisters);
  void setNumMemory(unsigned numMemory);
  void setNumStringMemory(unsigned numStringMemory);

  // I/O methods
  void addCommandToHistory(const string& command);
  ostream& writeRegisters(ostream& os = cout) const;
  void printRegisters();
  ostream& writeMemory(ostream& os = cout) const;
  void printMemory();
  ostream& writeStringMemory(ostream& os = cout) const;
  void printStringMemory();
  ostream& writeMachine(ostream& os = cout) const;
  void printMachine();
  ostream& writeCommandHistory(ostream& os = cout) const;
  void printCommandHistory() const;

 private:
  // Private methods
  void reset_(void);
  void createInstruction_(const string& line);
  void createData_(const string& line, unsigned& memory_ptr,
                   unsigned& stringMemory_ptr);
  bool allZero_(const vector<double>& vec) const;
  bool allZero_(const vector<string>& vec) const;
  void reset_(vector<double>& vec);
  void reset_(vector<string>& vec);
  void addCommandToHistory_(const std::string& command);

  // Vector of instructions
  vector<Instruction*> program_;

  // Map of labels (label, (address, isString))
  map<string, pair<unsigned, bool>> labels_;

  // Vector of registers
  vector<double> registers_;

  // Vector of memory cells
  vector<double> memory_;

  // Vector of string memory cells
  vector<string> stringMemory_;

  // Program counter
  unsigned pc_;

  // Flag to indicate if the machine is halted
  bool halted_;

  // Flag to indicate if the program is executable
  bool executable_;

  // Flag to indicate if the machine have been reset
  bool isReset_;

  // Number of registers
  unsigned numRegisters_;

  // Number of memory cells
  unsigned numMemory_;

  // Number of string memory cells
  unsigned numStringMemory_;

  // Command history
  std::vector<std::string> commandHistory_;
};

#include "RAM_/RAM.cpp"

#endif  // RAM_H