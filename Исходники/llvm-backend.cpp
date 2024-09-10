void llvm_initialize_backend(void) {
  // Initialize LLVM options.
  std::vector<const char*> Args;
  Args.push_back(progname); // program name

  // Allow targets to specify PIC options and other stuff to the corresponding
  // LLVM backends.
#ifdef LLVM_SET_TARGET_OPTIONS
  LLVM_SET_TARGET_OPTIONS(Args);
#endif
  
  if (time_report)
    Args.push_back("--time-passes");
  if (fast_math_flags_set_p())
    Args.push_back("--enable-unsafe-fp-math");
  if (!flag_omit_frame_pointer)
    Args.push_back("--disable-fp-elim");
  if (!flag_zero_initialized_in_bss)
    Args.push_back("--nozero-initialized-in-bss");
  if (flag_debug_asm)
    Args.push_back("--asm-verbose");
  if (flag_debug_pass_structure)
    Args.push_back("--debug-pass=Structure");
  if (flag_debug_pass_arguments)
    Args.push_back("--debug-pass=Arguments");
  if (flag_exceptions)
    Args.push_back("--enable-eh");

  // If there are options that should be passed through to the LLVM backend
  // directly from the command line, do so now.  This is mainly for debugging
  // purposes, and shouldn't really be for general use.
  std::vector<std::string> ArgStrings;
  if (llvm_optns) {
    std::string Opts = llvm_optns;
    for (std::string Opt = getToken(Opts); !Opt.empty(); Opt = getToken(Opts))
      ArgStrings.push_back(Opt);
  }
  for (unsigned i = 0, e = ArgStrings.size(); i != e; ++i)
    Args.push_back(ArgStrings[i].c_str());
  Args.push_back(0);  // Null terminator.
  
  int pseudo_argc = Args.size()-1;
  cl::ParseCommandLineOptions(pseudo_argc, (char**)&Args[0]);

  TheModule = new Module("");

  // If the target wants to override the architecture, e.g. turning
  // powerpc-darwin-... into powerpc64-darwin-... when -m64 is enabled, do so
  // now.
  std::string TargetTriple = TARGET_NAME;
#ifdef LLVM_OVERRIDE_TARGET_ARCH
  std::string Arch = LLVM_OVERRIDE_TARGET_ARCH();
  if (!Arch.empty()) {
    std::string::size_type DashPos = TargetTriple.find('-');
    if (DashPos != std::string::npos)// If we have a sane t-t, replace the arch.
      TargetTriple = Arch + TargetTriple.substr(DashPos);
  }
#endif
  TheModule->setTargetTriple(TargetTriple);
  
  TheTypeConverter = new TypeConverter();
  
  // Create the TargetMachine we will be generating code with.
  // FIXME: Figure out how to select the target and pass down subtarget info.
  std::string Err;
  const TargetMachineRegistry::Entry *TME = 
    TargetMachineRegistry::getClosestStaticTargetForModule(*TheModule, Err);
  if (!TME) {
    cerr << "Did not get a target machine!\n";
    exit(1);
  }

  // Figure out the subtarget feature string we pass to the target.
  std::string FeatureStr;
  // The target can set LLVM_SET_SUBTARGET_FEATURES to configure the LLVM
  // backend.
#ifdef LLVM_SET_SUBTARGET_FEATURES
  SubtargetFeatures Features;
  LLVM_SET_SUBTARGET_FEATURES(Features);
  FeatureStr = Features.getString();
#endif
  TheTarget = TME->CtorFn(*TheModule, FeatureStr);

  // Install information about target datalayout stuff into the module for
  // optimizer use.
  TheModule->setDataLayout(TheTarget->getTargetData()->
                           getStringRepresentation());
  
  if (optimize) {
    RegisterScheduler::setDefault(createDefaultScheduler);
  } else {
    RegisterScheduler::setDefault(createBFS_DAGScheduler);
  }
  
  RegisterRegAlloc::setDefault(createLinearScanRegisterAllocator);
 
  if (!optimize && debug_info_level > DINFO_LEVEL_NONE)
    TheDebugInfo = new DebugInfo(TheModule);
}