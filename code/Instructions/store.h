#ifndef STORE_H
#define STORE_H

#include "../instruction.h"

/**
 * @brief Class that represents the Store instruction. The instruction stores a
 * value from a register in memory.
 */
class Store : public Instruction {
 public:
  Store() {}
  Store(const string &line) {
    // Parse the line
    istringstream iss(line);
    string name;
    iss >> name;
    if (name == "//") {
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
    if (operands_.size() != 2) {
      throw invalid_argument("store instruction must have 2 operands");
      return;
    }
    double operand_1{0};

    // Get the values of the operand 1
    if (operands_[1].getAddressingMode() == 2) {  // Direct addressing
      operand_1 = registers[operands_[1].getValue()];
    } else if (operands_[1].getAddressingMode() == 1) {  // Indirect addressing
      operand_1 = registers[registers[operands_[1].getValue()]];
    } else {  // Immediate addressing
      operand_1 = operands_[1].getValue();
    }

    // Get the values of the operand 2
    if (operands_[0].getAddressingMode() == 2) {  // Direct addressing
      memory[operands_[0].getValue()] = operand_1;
    } else if (operands_[0].getAddressingMode() == 1) {  // Indirect addressing
      memory[memory[operands_[0].getValue()]] = operand_1;
    } else {  // Immediate addressing
      throw invalid_argument(
          "store instruction cannot have immediate addressing mode");
    }
  }

  string getName() const override { return "store"; }

 private:
  vector<Operand> operands_;
};

#endif  // STORE_H