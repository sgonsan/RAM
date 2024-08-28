#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <map>

#include "operand.h"

using namespace std;

/**
 * @brief Abstract class to represent an instruction. It contains a pure virtual
 * method to execute the instruction.
 */
class Instruction {
 public:
  virtual ~Instruction() = default;
  virtual void execute(vector<double> &memory, vector<string> &stringMemory,
                       vector<double> &registers, unsigned &pc, bool &halted,
                       const map<string, pair<unsigned, bool>> &labels_,
                       ostream &out) const = 0;
  virtual string getName() const = 0;
  friend ostream &operator<<(ostream &os, const Instruction &instruction) {
    os << instruction.getName();
    return os;
  }
};

#endif  // INSTRUCTION_H