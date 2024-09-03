#include "regex"

/**
 * @brief Construct a new RAM::RAM object
 *
 */
RAM::RAM() {
  // Initialize program counter to 0s
  pc_ = 0;
  // Initialize halted to false
  halted_ = false;
  // Initialize number of registers to 32
  numRegisters_ = 32;
  // Initialize number of memory cells to 1024
  numMemory_ = 1024;
  // Initialize number of string memory cells to 64
  numStringMemory_ = 64;
  // Initialize registers with 32 cells with 0s
  setNumRegisters(numRegisters_);
  // Initialize memory with 1024 cells with 0s
  setNumMemory(numMemory_);
  // Initialize string memory with 64 cells with ""
  setNumStringMemory(numStringMemory_);
  // Initialize program with 1000 cells all set to nullptr
  program_.resize(1000);
  // Initialize halted to false
  halted_ = false;
  // Initialize executable to false
  executable_ = false;
}

/**
 * @brief Public method to reset the machine
 *
 */
void RAM::reset(void) {
  if (!isReset_) reset_();
  commandHistory_.push_back("Reset machine");
}

/**
 * @brief Load a program from a file
 *
 * @param filename String with the name of the file
 */
void RAM::loadProgram(const string &filename) {
  if (!isReset_) reset_();
  ifstream file(filename);
  try {
    executable_ = true;
    if (file.is_open()) {
      program_.clear();
      string line;
      bool data = false, comment = false;
      unsigned memory_ptr = 0, stringMemory_ptr = 0;

      while (getline(file, line)) {
        if (line.empty()) {
          continue;
        }

        // Remove leading and trailing whitespaces
        line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");

        if (line.find("/*") != string::npos) {
          comment = true;
        } else if (line.find("*/") != string::npos) {
          comment = false;
        }

        if (!comment) {
          if (line[0] != '/' && line[1] != '/') {
            if (line.find("/*") != string::npos) {
              comment = true;
              continue;
            } else if (line.find("*/") != string::npos) {
              comment = false;
              continue;
            }
            if (line.find(".data") != string::npos) {
              data = true;
              continue;
            } else if (line.find(".code") != string::npos) {
              data = false;
              continue;
            }

            if (line.find(':') != string::npos) {
              if (!data)
                labels_[line.substr(0, line.find(':'))] =
                    pair<unsigned, bool>(program_.size(), false);
              else
                try {
                  createData_(line, memory_ptr, stringMemory_ptr);
                } catch (const exception &e) {
                  executable_ = false;
                  throw invalid_argument("Error creating data: " +
                                         string(e.what()));
                }
            } else {
              try {
                if (!data) createInstruction_(line);
              } catch (const exception &e) {
                executable_ = false;
                throw invalid_argument("Error creating instruction: " +
                                       string(e.what()));
              }
            }
          }
        }
      }

      if (comment) {
        executable_ = false;
        throw invalid_argument("The program has an unclosed comment");
      }
      if (program_.empty()) {
        executable_ = false;
        throw invalid_argument("No instructions found in file: " + filename);
      }

      file.close();
      cout << "Program \"" << filename << "\" loaded successfully" << endl;
      commandHistory_.push_back("Load program: " + filename + " (success)");
    } else {
      executable_ = false;
      throw invalid_argument("Error opening file: " + filename);
    }
  } catch (const exception &e) {
    cout << "Error loading program: " << e.what() << endl;
    file.close();
    commandHistory_.push_back("Load program: " + filename + " (error)");
  }
  isReset_ = false;
}

/**
 * @brief Execute the program loaded if it is executable. If not, print an error
 * message to the console.
 *
 */
void RAM::executeProgram() {
  if (!executable_) {
    cout << "Program is not executable or not loaded" << endl;
    commandHistory_.push_back("Execute program (error)");
    return;
  }
  try {
    pc_ = 0;
    cout << "--- Program execution start here ---" << endl;
    while (!halted_ && pc_ < program_.size()) {
      program_[pc_]->execute(memory_, stringMemory_, registers_, pc_, halted_,
                             labels_, cout);
      ++pc_;
    }
    if (halted_) cout << "--- HALTED ---" << endl;
    commandHistory_.push_back("Execute program (success)");

  } catch (const exception &e) {
    cout << "Error executing program: " << e.what() << endl;
    commandHistory_.push_back("Execute program (error)");
  }
  cout << "--- Program execution finish here ---" << endl << endl;
}
