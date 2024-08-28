#ifndef ADD_H
#define ADD_H

#include "../instruction.h"

/**
 * @brief Class that represents the Add instruction. The instruction adds two
 * operands and stores the result in a register.
 */
class Add : public Instruction {
 public:
  Add() {}
  Add(const string &line) {
    // Parse the line
    istringstream iss(line);
    string firstchar;
    iss >> firstchar;
    if (firstchar == "//") {
      return;
    }
    string operand;
    while (iss >> operand) {
      if (operand == "//") {
        break;
      }
      operands_.push_back(Operand(operand));
    }
  }

  void execute(vector<double> &memory, vector<string> &stringMemory,
               vector<double> &registers, unsigned &pc, bool &halted,
               const map<std::string, pair<unsigned, bool>> &labels_,
               ostream &out) const override {
    if (operands_.size() != 3) {
      throw invalid_argument("add instruction must have 3 operands");
      return;
    }
    double operand_1{0};
    double operand_2{0};

    // Get the values of the operand 1
    if (operands_[1].getAddressingMode() == 2) {  // Direct addressing
      if (operands_[1].getValue() >= registers.size()) {
        throw invalid_argument("register " + to_string(operands_[1].getValue()) +
                               " not found");
      }
      operand_1 = registers[operands_[1].getValue()];
    } else if (operands_[1].getAddressingMode() == 1) {  // Indirect addressing
      if (operands_[1].getValue() >= registers.size() ||
          operands_[1].getValue() < 0 ||
          registers[operands_[1].getValue()] >= registers.size() ||
          registers[operands_[1].getValue()] < 0) {
        throw invalid_argument("register " + to_string(operands_[1].getValue()) +
                               " not found");
      }
      operand_1 = registers[registers[operands_[1].getValue()]];
    } else {  // Immediate addressing
      operand_1 = operands_[1].getValue();
    }

    // Get the values of the operand 2
    if (operands_[2].getAddressingMode() == 2) {  // Direct addressing
      if (operands_[2].getValue() >= registers.size()) {
        throw invalid_argument("register " + to_string(operands_[2].getValue()) +
                               " not found");
      }
      operand_2 = registers[operands_[2].getValue()];
    } else if (operands_[2].getAddressingMode() == 1) {  // Indirect addressing
      if (operands_[2].getValue() >= registers.size() ||
          operands_[2].getValue() < 0 ||
          registers[operands_[2].getValue()] >= registers.size() ||
          registers[operands_[2].getValue()] < 0) {
        throw invalid_argument("register " + to_string(operands_[2].getValue()) +
                               " not found");
      }
      operand_2 = registers[registers[operands_[2].getValue()]];
    } else {  // Immediate addressing
      operand_2 = operands_[2].getValue();
    }

    // Add the operands
    if (operands_[0].getAddressingMode() == 2) {  // Direct addressing
      if (operands_[0].getValue() >= registers.size()) {
        throw invalid_argument("register " + to_string(operands_[0].getValue()) +
                               " not found");
      }
      registers[operands_[0].getValue()] = operand_1 + operand_2;
    } else if (operands_[0].getAddressingMode() == 1) {  // Indirect addressing
      if (operands_[0].getValue() >= registers.size() ||
          operands_[0].getValue() < 0 ||
          registers[operands_[0].getValue()] >= registers.size() ||
          registers[operands_[0].getValue()] < 0) {
        throw invalid_argument("register " + to_string(operands_[0].getValue()) +
                               " not found");
      }
      registers[registers[operands_[0].getValue()]] = operand_1 + operand_2;
    } else {  // Immediate addressing
      throw invalid_argument(
          "add instruction cannot have immediate addressing mode");
    }
  }

  string getName() const override { return "add"; }

 private:
  vector<Operand> operands_;
};

#endif  // ADD_H