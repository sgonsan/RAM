/**
 * @brief Get the halted flag
 *
 * @return `true` If the machine is halted
 */
bool RAM::getHalted() const { return halted_; }

/**
 * @brief Get the executable flag
 *
 * @return `true` If the program is executable
 */
bool RAM::getExecutable() const { return executable_; }

/**
 * @brief Get the number of registers
 *
 * @return unsigned Number of registers
 */
unsigned RAM::getNumRegisters() const { return numRegisters_; }

/**
 * @brief Get the number of memory cells
 *
 * @return unsigned Number of memory cells
 */
unsigned RAM::getNumMemory() const { return numMemory_; }

/**
 * @brief Get the number of string memory cells
 *
 * @return unsigned Number of string memory cells
 */
unsigned RAM::getNumStringMemory() const { return numStringMemory_; }