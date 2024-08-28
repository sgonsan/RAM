#ifndef OPERAND_H
#define OPERAND_H

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @brief Class to represent an operand. It can be a tag, or value with an
 * addressing mode. The addressing mode can be: 0 for immediate, 1 for direct
 * and 2 for indirect.
 */
class Operand {
 public:
  Operand();
  Operand(const std::string &operand, const bool &is_tag = false);
  Operand(const int &value, const int &addressing_mode);

  double getValue() const;
  int getAddressingMode() const;
  std::string getTag() const;

  void setValue(const int &value);
  void setAddressingMode(const int &addressing_mode);
  void setTag(const std::string &tag);

  friend std::ostream &operator<<(std::ostream &os, const Operand &operand);

 private:
  std::string tag_;
  double value_;
  int addressing_mode_;
};

#include "operand.cpp"

#endif  // OPERAND_H