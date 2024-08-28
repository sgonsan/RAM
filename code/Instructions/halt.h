#ifndef HALT_H
#define HALT_H

#include "../instruction.h"

/**
 * @brief Class that represents the Halt instruction. The instruction stops the
 * execution of the program.
 */
class Halt : public Instruction {
 public:
  Halt() {}
  Halt(const string &line) {
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
    if (operands_.size() != 0) {
      throw invalid_argument("halt instruction must have no operands");
      return;
    }
    halted = true;
  }

  string getName() const override { return "halt"; }

 private:
  vector<Operand> operands_;
};

#endif  // HALT_H