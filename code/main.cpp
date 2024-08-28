#include "RAM.h"

void showMenu() {
  cout << "===================================" << endl;
  cout << "                RAM                " << endl;
  cout << "===================================" << endl;
  cout << "1.  Load Program" << endl;
  cout << "2.  Execute Program" << endl;
  cout << "3.  Show Machine" << endl;
  cout << "4.  Configure Machine" << endl;
  cout << "5.  Reset Machine" << endl;
  cout << "6.  Show Registers" << endl;
  cout << "7.  Show Memory" << endl;
  cout << "8.  Show String Memory" << endl;
  cout << "9.  Help" << endl;
  cout << "10. Show Command History" << endl;
  cout << "0.  Exit" << endl;
  cout << "===================================" << endl;
  cout << "Select an option: ";
}

void showHelp() {
  cout << "===================================" << endl;
  cout << "            Help Menu              " << endl;
  cout << "===================================" << endl;
  cout << "This is a simple RAM program that can load and execute programs "
          "written "
          "in a custom assembly language."
       << endl;
  cout << "The machine has by default 32 double registers, 1024 double memory "
          "cells "
          "and 1024 string memory cells."
       << endl;
  cout << "The machine has the following " << endl;
  cout << "instructions: " << endl;
  cout << " - Halt: Stop the execution of the program" << endl;
  cout << " - Add: Sum two registers and store the result in a register"
       << endl;
  cout << " - Sub: Subtract two registers and store the result in a register"
       << endl;
  cout << " - Mul: Multiply two registers and store the result in a register"
       << endl;
  cout << " - Div: Divide two registers and store the result in a register"
       << endl;
  cout << " - Load: Put a value from memory to a register" << endl;
  cout << " - Store: Put a value from a register to memory" << endl;
  cout << " - Read: Put a value from the input to a register" << endl;
  cout << " - Write: Put a value from a register to the output" << endl;
  cout << " - Jump: Make a jump to a label" << endl;
  cout << " - Jzero: Make a jump if the register is zero" << endl;
  cout << " - Jgtz: Make a jump if the register is greater than zero" << endl;
  cout << " - Jltz: Make a jump if the register is less than zero" << endl;
  cout << "===================================" << endl;
  cout << "               Usage               " << endl;
  cout << "===================================" << endl;
  cout << "1.  Load a program: Load a program from a file by entering the "
          "filename."
       << endl;
  cout << "2.  Execute a program: Execute the loaded program. If no program is "
          "loaded, it will show an error."
       << endl;
  cout << "3.  Show Machine: Show all the registers, memory cells and string "
          "memory cells."
       << endl;
  cout << "4.  Configure Machine: Configure the machine by setting the number "
          "of registers, memory cells and string memory cells."
       << endl;
  cout << "5.  Reset Machine: Reset the machine to its initial state." << endl;
  cout << "6.  Show Registers: Show the registers that have a non-zero value. "
       << endl;
  cout << "7.  Show Memory: Show the memory cells that have a non-zero value."
       << endl;
  cout << "8.  Show String Memory: Show the string memory cells that have a "
          "non-empty string."
       << endl;
  cout << "9.  Help: Show this help menu." << endl;
  cout << "10. Show Command History: Show the history of commands entered."
       << endl;
  cout << "0.  Exit: Exit the RAM." << endl;
}

int main() {
  system("clear");
  RAM ram;
  int option;
  string filename;

  while (true) {
    showMenu();
    cin >> option;
    system("clear");

    switch (option) {
      case 1:
        cout << "Selection: Load Program" << endl;
        cout << "Enter the filename of the program to load: ";
        cin >> filename;
        ram.loadProgram(filename);
        break;

      case 2:
        cout << "Selection: Execute Program" << endl;
        ram.executeProgram();
        break;

      case 3:
        cout << "Selection: Show Machine" << endl;
        cout << "Machine state:" << endl;
        ram.printMachine();
        break;

      case 4:
        cout << "Selection: Configure Machine" << endl;
        cout << "Enter the number of registers: ";
        unsigned numRegisters;
        cin >> numRegisters;
        ram.setNumRegisters(numRegisters);
        cout << "Enter the number of memory cells: ";
        unsigned numMemory;
        cin >> numMemory;
        ram.setNumMemory(numMemory);
        cout << "Enter the number of string memory cells: ";
        unsigned numStringMemory;
        cin >> numStringMemory;
        ram.setNumStringMemory(numStringMemory);
        ram.addCommandToHistory(
            "Configure Machine: " + to_string(numRegisters) + " registers, " +
            to_string(numMemory) + " memory cells, " +
            to_string(numStringMemory) + " string memory cells");
        break;

      case 5:
        cout << "Selection: Reset Machine" << endl;
        ram.reset();
        break;

      case 6:
        cout << "Selection: Show Registers" << endl;
        ram.printRegisters();
        break;

      case 7:
        cout << "Selection: Show Memory" << endl;
        ram.printMemory();
        break;

      case 8:
        cout << "Selection: Show String Memory" << endl;
        ram.printStringMemory();
        break;

      case 9:
        showHelp();
        ram.addCommandToHistory("Show Help");
        break;

      case 10:
        cout << "Selection: Show Command History" << endl;
        ram.printCommandHistory();
        break;

      case 0:
        cout << "Selection: Exit" << endl;
        cout << "Exiting RAM..." << endl;
        return 0;

      default:
        cout << "Invalid option. Please try again." << endl;
        ram.addCommandToHistory("Invalid option: " + to_string(option));
        showHelp();
    }
  }

  return 0;
}