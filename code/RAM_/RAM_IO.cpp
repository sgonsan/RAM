/**
 * @brief Add a command to the command history
 *
 * @param command Command to add
 */
void RAM::addCommandToHistory(const std::string &command) {
  addCommandToHistory_(command);
}

/**
 * @brief Write the registers to an output stream
 *
 * @param os Output stream
 * @return ostream Output stream
 */
ostream &RAM::writeRegisters(ostream &os) const {
  if (allZero_(registers_)) {
    os << "Registers are all zeros" << endl;
    return os;
  }
  for (size_t i = 0; i < registers_.size(); ++i) {
    if (registers_[i] < -1e-6 || registers_[i] > 1e-6) {
      os << "Registers[" << i << "]\t = " << registers_[i] << endl;
    }
  }
  return os;
}

/**
 * @brief Print the registers using the writeRegisters method
 *
 */
void RAM::printRegisters() {
  writeRegisters();
  commandHistory_.push_back("Show registers state");
}

/**
 * @brief Write the memory to an output stream
 *
 * @param os Output stream
 * @return ostream Output stream
 */
ostream &RAM::writeMemory(ostream &os) const {
  if (allZero_(memory_)) {
    os << "Memory is all zeros" << endl;
    return os;
  }
  for (size_t i = 0; i < memory_.size(); ++i) {
    if (memory_[i] < -1e-6 || memory_[i] > 1e-6) {
      os << "Memory[" << i << "]\t = " << memory_[i] << endl;
    }
  }
  return os;
}

/**
 * @brief Print the memory using the writeMemory method
 *
 */
void RAM::printMemory() {
  writeMemory();
  commandHistory_.push_back("Show memory state");
}

/**
 * @brief Write the string memory to an output stream
 *
 * @param os Output stream
 * @return ostream Output stream
 */
ostream &RAM::writeStringMemory(ostream &os) const {
  if (allZero_(stringMemory_)) {
    os << "String memory is empty" << endl;
    return os;
  }
  for (size_t i = 0; i < stringMemory_.size(); ++i) {
    if (!stringMemory_[i].empty()) {
      os << "StringMemory[" << i << "]\t = \"" << stringMemory_[i] << "\""
         << endl;
    }
  }
  return os;
}

/**
 * @brief Print the string memory using the writeStringMemory method
 *
 */
void RAM::printStringMemory() {
  writeStringMemory();
  commandHistory_.push_back("Show string memory state");
}

/**
 * @brief Write the machine to an output stream
 *
 * @param os Output stream
 * @return ostream Output stream
 */
ostream &RAM::writeMachine(ostream &os) const {
  os << "Number of registers: " << numRegisters_ << endl;
  os << "Registers: " << endl;
  writeRegisters(os);
  os << "Number of memory cells: " << numMemory_ << endl;
  os << "Memory: " << endl;
  writeMemory(os);
  os << "Number of string memory cells: " << endl;
  os << "String Memory: " << numStringMemory_ << endl;
  writeStringMemory(os);
  return os;
}

/**
 * @brief Print the machine using the writeMachine method
 *
 */
void RAM::printMachine() {
  writeMachine();
  commandHistory_.push_back("Show machine state");
}

/**
 * @brief Write the command history to an output stream
 *
 * @param os Output stream
 * @return ostream Output stream
 */
ostream &RAM::writeCommandHistory(ostream &os) const {
  if (commandHistory_.empty()) {
    os << "No commands have been executed yet." << std::endl;
    return os;
  }
  for (size_t i = 0; i < commandHistory_.size(); ++i) {
    os << "[" << i << "] " << commandHistory_[i] << endl;
  }
  return os;
}

/**
 * @brief Print the command history using the writeCommandHistory method
 *
 */
void RAM::printCommandHistory() const { writeCommandHistory(); }