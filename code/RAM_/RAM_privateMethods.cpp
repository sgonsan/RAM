/**
 * @brief Reset the machine
 *
 */
void RAM::reset_(void) {
  cout << "Resetting machine..." << endl;
  pc_ = 0;
  reset_(registers_);
  memory_.clear();
  stringMemory_.clear();
  labels_.clear();
  try {
    for (Instruction *instruction : program_) {
      delete instruction;
    }
  } catch (const exception &e) {
    cout << "Error deleting instructions: " << e.what() << endl;
  }
  program_.resize(1000);
  halted_ = false;
  executable_ = false;
  isReset_ = true;
  cout << "Machine reset" << endl;
}

/**
 * @brief Create an instruction from a string
 *
 * @param line String with the instruction
 */
void RAM::createInstruction_(const string &line) {
  if (line.empty()) {
    return;
  }
  if (line.find("halt") != string::npos) {
    program_.push_back(new Halt(line));
  } else if (line.find("add") != string::npos && line.find("add") == 0) {
    program_.push_back(new Add(line));
  } else if (line.find("sub") != string::npos && line.find("sub") == 0) {
    program_.push_back(new Sub(line));
  } else if (line.find("mul") != string::npos && line.find("mul") == 0) {
    program_.push_back(new Mul(line));
  } else if (line.find("div") != string::npos && line.find("div") == 0) {
    program_.push_back(new Div(line));
  } else if (line.find("load") != string::npos && line.find("load") == 0) {
    program_.push_back(new Load(line));
  } else if (line.find("store") != string::npos && line.find("store") == 0) {
    program_.push_back(new Store(line));
  } else if (line.find("read") != string::npos && line.find("read") == 0) {
    program_.push_back(new Read(line));
  } else if (line.find("write") != string::npos && line.find("write") == 0) {
    program_.push_back(new Write(line));
  } else if (line.find("jump") != string::npos && line.find("jump") == 0) {
    program_.push_back(new Jump(line));
  } else if (line.find("jzero") != string::npos && line.find("jzero") == 0) {
    program_.push_back(new Jzero(line));
  } else if (line.find("jgtz") != string::npos && line.find("jgtz") == 0) {
    program_.push_back(new Jgtz(line));
  } else if (line.find("jltz") != string::npos && line.find("jltz") == 0) {
    program_.push_back(new Jltz(line));
  } else {
    throw invalid_argument("Unknown instruction: " + line);
  }
}

/**
 * @brief Create a data from a string
 *
 * @param line String with the data
 */
void RAM::createData_(const string &line, unsigned &memory_ptr,
                      unsigned &stringMemory_ptr) {
  if (line.empty()) {
    return;
  }

  if (line.find(".string") != string::npos) {  // tag: .string "string"
    if (stringMemory_ptr >= numStringMemory_) {
      throw invalid_argument("String memory limit exceeded");
    }
    stringMemory_.push_back(
        line.substr(line.find('"') + 1, line.rfind('"') - line.find('"') - 1));
    labels_[line.substr(0, line.find(':'))] =
        pair<unsigned, bool>(stringMemory_ptr, true);
    stringMemory_ptr++;
  } else if (line.find(".int") != string::npos) {  // tag: .int 123
    if (memory_ptr >= numMemory_) {
      throw invalid_argument("Memory limit exceeded");
    }
    memory_.push_back(stoi(line.substr(line.find('.') + 5)));
    labels_[line.substr(0, line.find(':'))] =
        pair<unsigned, bool>(memory_ptr, false);
    memory_ptr++;
  } else if (line.find(".float") != string::npos) {  // tag: .float 123.45
    if (memory_ptr >= numMemory_) {
      throw invalid_argument("Memory limit exceeded");
    }
    memory_.push_back(stof(line.substr(line.find('.') + 7)));
    labels_[line.substr(0, line.find(':'))] =
        pair<unsigned, bool>(memory_ptr, false);
    memory_ptr++;
  } else if (line.find(".double") != string::npos) {  // tag: .double 123.45
    if (memory_ptr >= numMemory_) {
      throw invalid_argument("Memory limit exceeded");
    }
    memory_.push_back(stod(line.substr(line.find('.') + 8)));
    labels_[line.substr(0, line.find(':'))] =
        pair<unsigned, bool>(memory_ptr, false);
    memory_ptr++;
  } else {
    throw invalid_argument("Unknown data type: " + line);
  }
}

/**
 * @brief Check if the memory is all zeros
 *
 * @return `true` If all memory cells are zero
 * @return `false` If at least one memory cell is not zero
 */
bool RAM::allZero_(const vector<double> &vec) const {
  for (double i : vec) {
    if (i < -1e-6 || i > 1e-6) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Check if the memory is all zeros
 *
 * @return `true` If all memory cells are zero
 * @return `false` If at least one memory cell is not zero
 */
bool RAM::allZero_(const vector<string> &vec) const {
  for (string i : vec) {
    if (!i.empty()) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Clear a vector of doubles
 *
 * @param vec Vector to clear
 */
void RAM::reset_(vector<double> &vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    vec[i] = 0;
  }
}

/**
 * @brief Clear a vector of strings
 *
 * @param vec Vector to clear
 */
void RAM::reset_(vector<string> &vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    vec[i] = "";
  }
}

/**
 * @brief Add a command to the command history
 *
 * @param command Command to add
 */
void RAM::addCommandToHistory_(const std::string &command) {
  commandHistory_.push_back(command);
}