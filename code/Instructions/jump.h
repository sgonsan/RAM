#ifndef JUMP_H
#define JUMP_H

#include "../instruction.h"

/**
 * @brief Class that represents the Jump instruction. The instruction jumps to a
 * tag.
 */
class Jump : public Instruction {
 public:
  Jump() {}
  Jump(const string &line) {
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
      operands_.push_back(Operand(operand, true));
    }
  }

  void execute(vector<double> &memory, vector<string> &stringMemory,
               vector<double> &registers, unsigned &pc, bool &halted,
               const map<std::string, pair<unsigned, bool>> &labels_,
               ostream &out) const override {
    pc = labels_.at(operands_[0].getTag()).first;
  }

  string getName() const override { return "jump"; }

 private:
  vector<Operand> operands_;
};

#endif  // JUMP_H