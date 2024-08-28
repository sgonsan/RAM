#ifndef JLTZ_H
#define JLTZ_H

#include "../instruction.h"

/**
 * @brief Class that represents the Jltz instruction. The instruction jumps to a
 * tag if the value in a register is less than zero.
 */
class Jltz : public Instruction {
 public:
  Jltz() {}
  Jltz(const string &line) {
    // Parse the line
    istringstream iss(line);
    string name;
    iss >> name;
    if (name == "//") {
      return;
    }
    string operand;
    for (int i = 0; i < 2; i++) {
      iss >> operand;
      if (operand == "//") {
        break;
      }
      operands_.push_back(Operand(operand, (i == 1)));
    }
  }

  void execute(vector<double> &memory, vector<string> &stringMemory,
               vector<double> &registers, unsigned &pc, bool &halted,
               const map<std::string, pair<unsigned, bool>> &labels_,
               ostream &out) const override {
    if (operands_.size() != 2) {
      throw invalid_argument("jltz instruction must have 2 operands");
      return;
    }
    if (operands_[0].getAddressingMode() == 2) {  // Direct addressing
      if (operands_[0].getValue() >= registers.size() ||
          operands_[0].getValue() < 0) {
        throw invalid_argument(
            "register " + to_string(operands_[0].getValue()) + " not found");
      }
      if (registers[operands_[0].getValue()] < 0) {
        pc = labels_.at(operands_[1].getTag()).first;
      }
    } else if (operands_[0].getAddressingMode() == 1) {  // Indirect addressing
      if (operands_[0].getValue() >= registers.size() ||
          operands_[0].getValue() < 0 ||
          registers[operands_[0].getValue()] >= registers.size() ||
          registers[operands_[0].getValue()] < 0) {
        throw invalid_argument(
            "register " + to_string(operands_[0].getValue()) + " not found");
      }
      if (registers[registers[operands_[0].getValue()]] < 0) {
        pc = labels_.at(operands_[1].getTag()).first;
      }
    } else {  // Immediate addressing
      if (operands_[0].getValue() < 0) {
        pc = labels_.at(operands_[1].getTag()).first;
      }
    }
  }

  string getName() const override { return "jltz"; }

 private:
  vector<Operand> operands_;
};

#endif  // JLTZ_H