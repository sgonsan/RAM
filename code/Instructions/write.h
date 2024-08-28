#ifndef WRITE_H
#define WRITE_H

#include "../instruction.h"

/**
 * @brief Class that represents the Write instruction. The instruction writes a
 * value from a register to the output.
 */
class Write : public Instruction {
 public:
  Write() {}
  Write(const string &line) {
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
      if (!isdigit(operand[0]) && !isdigit(operand[1])) {
        operands_.push_back(Operand(operand, true));
      } else {
        operands_.push_back(Operand(operand));
      }
    }
  }

  void execute(vector<double> &memory, vector<string> &stringMemory,
               vector<double> &registers, unsigned &pc, bool &halted,
               const map<std::string, pair<unsigned, bool>> &labels_,
               ostream &out) const override {
    if (operands_.size() != 1) {
      throw invalid_argument("write instruction must have 1 operand");
      return;
    }
    if (operands_[0].getTag() == "ENDL") {
      out << endl;
      return;
    }
    if (operands_[0].getTag() == "") {
      if (operands_[0].getAddressingMode() == 2) {  // Direct addressing
        if (operands_[0].getValue() >= registers.size() ||
            operands_[0].getValue() < 0) {
          throw invalid_argument(
              "register " + to_string(operands_[0].getValue()) + " not found");
        }
        out << registers[operands_[0].getValue()];
      } else if (operands_[0].getAddressingMode() ==
                 1) {  // Indirect addressing
        if (operands_[0].getValue() >= registers.size() ||
            operands_[0].getValue() < 0 ||
            registers[operands_[0].getValue()] >= registers.size() ||
            registers[operands_[0].getValue()] < 0) {
          throw invalid_argument(
              "register " + to_string(operands_[0].getValue()) + " not found");
        }
        out << registers[registers[operands_[0].getValue()]];
      } else {  // Immediate mode
        out << operands_[0].getValue();
      }
    } else {
      if (labels_.at(operands_[0].getTag()).second) {
        out << stringMemory[labels_.at(operands_[0].getTag()).first];
      } else {
        out << memory[labels_.at(operands_[0].getTag()).first];
      }
    }
  }

  string getName() const override { return "write"; }

 private:
  vector<Operand> operands_;
};

#endif  // WRITE_H