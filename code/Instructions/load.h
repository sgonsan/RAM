#ifndef LOAD_H
#define LOAD_H

#include "../instruction.h"

/**
 * @brief Class that represents the Load instruction. The instruction loads a
 * value from memory and stores it in a register.
 */
class Load : public Instruction {
 public:
  Load() {}
  Load(const string &line) {
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
      if (isdigit(operand[0])) {
        operands_.push_back(Operand(operand));
      } else {
        if (operand[0] != '=' && operand[0] != '*') {
          operands_.push_back(Operand(operand, true));
        } else {
          operands_.push_back(Operand(operand));
        }
      }
    }
  }

  void execute(vector<double> &memory, vector<string> &stringMemory,
               vector<double> &registers, unsigned &pc, bool &halted,
               const map<std::string, pair<unsigned, bool>> &labels_,
               ostream &out) const override {
    if (operands_.size() != 2) {
      throw invalid_argument("load instruction must have 2 operands");
      return;
    }
    double operand_1{0};

    // Get the values of the operand 1
    if (operands_[1].getTag() != "") {
      if (labels_.find(operands_[1].getTag()) == labels_.end()) {
        throw invalid_argument("label " + operands_[1].getTag() + " not found");
      }
      operand_1 = memory[labels_.at(operands_[1].getTag()).first];
    } else {
      if (operands_[1].getAddressingMode() == 2) {  // Direct addressing
        operand_1 = memory[operands_[1].getValue()];
      } else if (operands_[1].getAddressingMode() ==
                 1) {  // Indirect addressing
        operand_1 = memory[memory[operands_[1].getValue()]];
      } else {  // Immediate addressing
        operand_1 = operands_[1].getValue();
      }
    }

    // Get the values of the operand 2
    if (operands_[0].getAddressingMode() == 2) {  // Direct addressing
      if (operands_[0].getValue() >= registers.size() ||
          operands_[0].getValue() < 0) {
        throw invalid_argument(
            "register " + to_string(int(operands_[0].getValue())) + " not found");
      }
      registers[operands_[0].getValue()] = operand_1;
    } else if (operands_[0].getAddressingMode() == 1) {  // Indirect addressing
      if (operands_[0].getValue() >= registers.size() ||
          operands_[0].getValue() < 0 ||
          registers[operands_[0].getValue()] >= registers.size() ||
          registers[operands_[0].getValue()] < 0) {
        throw invalid_argument(
            "register " + to_string(int(operands_[0].getValue())) + " not found");
      }
      registers[registers[operands_[0].getValue()]] = operand_1;
    } else {  // Immediate addressing
      throw invalid_argument(
          "load instruction cannot have immediate addressing mode");
    }
  }

  string getName() const override { return "load"; }

 private:
  vector<Operand> operands_;
};

#endif  // Load_H