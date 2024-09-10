  void ShellCompiler::init(const Dict& opts) {
    // Base class
    CompilerInternal::init(opts);

    // Default options
    string compiler = "gcc";
    string compiler_setup = "-fPIC -shared";
    vector<string> flags;

    // Read options
    for (auto&& op : opts) {
      if (op.first=="compiler") {
        compiler = op.second.to_string();
      } else if (op.first=="compiler_setup") {
        compiler_setup = op.second.to_string();
      } else if (op.first=="flags") {
        flags = op.second;
      }
    }

    // Construct the compiler command
    stringstream cmd;
    cmd << compiler << " " << compiler_setup;
    for (vector<string>::const_iterator i=flags.begin(); i!=flags.end(); ++i) {
      cmd << " " << *i;
    }

    // C/C++ source file
    cmd << " " << name_;

    // Name of temporary file
#ifdef HAVE_MKSTEMPS
    // Preferred solution
    char bin_name[] = "tmp_casadi_compiler_shell_XXXXXX.so";
    if (mkstemps(bin_name, 3) == -1) {
      casadi_error("Failed to create a temporary file name");
    }
    bin_name_ = bin_name;
#else
    // Fallback, may result in deprecation warnings
    char* bin_name = tempnam(0, "ca.so");
    bin_name_ = bin_name;
    free(bin_name);
#endif

    // Have relative paths start with ./
    if (bin_name_.at(0)!='/') {
      bin_name_ = "./" + bin_name_;
    }

    // Temporary file
    cmd << " -o " << bin_name_;

    // Compile into a shared library
    if (system(cmd.str().c_str())) {
      casadi_error("Compilation failed. Tried \"" + cmd.str() + "\"");
    }

    // Load shared library
    handle_ = dlopen(bin_name_.c_str(), RTLD_LAZY);
    casadi_assert_message(handle_!=0, "CommonExternal: Cannot open function: "
                          << bin_name_ << ". error code: "<< dlerror());
    // reset error
    dlerror();
  }