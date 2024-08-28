#include "operand.h"

/**
 * @brief Construct a new Operand object
 *
 */
Operand::Operand() {
  value_ = 0;
  addressing_mode_ = 0;
  tag_ = "";
}

/**
 * @brief Construct a new Operand object
 *
 * @param operand String with the operand
 */
Operand::Operand(const std::string &operand, const bool &is_tag) {
  value_ = 0;
  addressing_mode_ = 0;
  if (is_tag) {  // Tag
    tag_ = operand;
  } else {
    if (operand[0] == '=') {  // Immediate addressing mode
      value_ = std::stoi(operand.substr(1));
      addressing_mode_ = 0;
    } else if (operand[0] == '*') {  // Indirect addressing mode
      value_ = std::stoi(operand.substr(1));
      addressing_mode_ = 1;
    } else if (isdigit(operand[0])) {  // Direct addressing mode
      value_ = std::stoi(operand);
      addressing_mode_ = 2;
    } else {  // Invalid operand
      throw std::invalid_argument("Invalid operand");
    }
  }
}

/**
 * @brief Construct a new Operand object
 *
 * @param value Integer with the value of the operand
 * @param addressing_mode Integer with the addressing mode of the operand
 */
Operand::Operand(const int &value, const int &addressing_mode) {
  value_ = value;
  addressing_mode_ = addressing_mode;
}

/**
 * @brief Get the value of the operand
 *
 * @return int Value of the operand
 */
double Operand::getValue() const { return value_; }

/**
 * @brief Get the addressing mode of the operand
 *
 * @return int Addressing mode of the operand
 */
int Operand::getAddressingMode() const { return addressing_mode_; }

/**
 * @brief Get the tag of the operand
 *
 * @return string Tag of the operand
 */
std::string Operand::getTag() const { return tag_; }

/**
 * @brief Set the value of the operand
 *
 * @param value Integer with the value of the operand
 */
void Operand::setValue(const int &value) { value_ = value; }

/**
 * @brief Set the addressing mode of the operand
 *
 * @param addressing_mode Integer with the addressing mode of the operand
 */
void Operand::setAddressingMode(const int &addressing_mode) {
  addressing_mode_ = addressing_mode;
}

/**
 * @brief Set the tag of the operand
 *
 * @param tag String with the tag of the operand
 */
void Operand::setTag(const std::string &tag) { tag_ = tag; }

/**
 * @brief Overload the << operator to print the operand
 *
 * @param os Output stream
 * @param operand Operand to print
 * @return std::ostream& Output stream
 */
std::ostream &operator<<(std::ostream &os, const Operand &operand) {
  switch (operand.getAddressingMode()) {
    case 0:
      os << "=" << operand.getValue();
      break;
    case 1:
      os << "*" << operand.getValue();
      break;
    case 2:
      os << operand.getValue();
      break;
    default:
      os << "Invalid addressing mode";
      break;
  }
  return os;
}