/**
 * @brief Set the number of registers
 *
 * @param numRegisters Number of registers
 */
void RAM::setNumRegisters(unsigned numRegisters) {
  numRegisters_ = numRegisters;
  registers_.resize(numRegisters_);
  for (size_t i = 0; i < registers_.size(); ++i) {
    registers_[i] = 0;
  }
}

/**
 * @brief Set the number of memory cells
 *
 * @param numMemory Number of memory cells
 */
void RAM::setNumMemory(unsigned numMemory) {
  numMemory_ = numMemory;
  memory_.resize(numMemory_, 0);
  for (size_t i = 0; i < memory_.size(); ++i) {
    memory_[i] = 0;
  }
}

/**
 * @brief Set the number of string memory cells
 *
 * @param numStringMemory Number of string memory cells
 */
void RAM::setNumStringMemory(unsigned numStringMemory) {
  numStringMemory_ = numStringMemory;
  stringMemory_.resize(numStringMemory_, "");
  for (size_t i = 0; i < stringMemory_.size(); ++i) {
    stringMemory_[i] = "";
  }
}