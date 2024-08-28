#ifndef READ_H
#define READ_H

#include "../instruction.h"

/**
 * @brief Class that represents the Read instruction. The instruction reads a
 * value from the standard input and stores it in a register.
 */
class Read : public Instruction {
 public:
  Read() {}
  Read(const string &line) {
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
    if (operands_.size() != 1) {
      throw invalid_argument("read instruction must have 1 operand");
      return;
    }

    if (operands_[0].getAddressingMode() == 0) {  // Immediate mode
      throw invalid_argument("read instruction cannot have immediate mode");
      return;
    }

    double value;
    cin >> value;

    if (operands_[0].getAddressingMode() == 2) {  // Direct addressing
      if (operands_[0].getValue() >= registers.size() ||
          operands_[0].getValue() < 0) {
        throw invalid_argument(
            "register " + to_string(operands_[0].getValue()) + " not found");
      }
      registers[operands_[0].getValue()] = value;
    } else {  // Indirect addressing
      if (operands_[0].getValue() >= registers.size() ||
          operands_[0].getValue() < 0 ||
          registers[operands_[0].getValue()] >= registers.size() ||
          registers[operands_[0].getValue()] < 0) {
        throw invalid_argument(
            "register " + to_string(operands_[0].getValue()) + " not found");
      }
      registers[registers[operands_[0].getValue()]] = value;
    }
  }

  string getName() const override { return "read"; }

 private:
  vector<Operand> operands_;
};

#endif  // READ_H