int main(int argc, char **argv) {
  PrettyStackTraceProgram X(argc, argv);
  cl::ParseCommandLineOptions(argc, argv, "llvm codegen stress-tester\n");

  if (!ForcedChoiceStr.empty()) {
    std::stringstream ss(ForcedChoiceStr);
    copy(std::istream_iterator<int>(ss), std::istream_iterator<int>(),
         std::back_inserter(ForcedChoices));
  }

  if (Seed == INT_MIN) {
    Seed = ::time(0) + ::getpid();
  } else {
    if (!Fuzz)
      report_fatal_error("can't supply a seed in exhaustive mode");
  }
  ::srand(Seed);

  Shmem =
      (struct shared *)::mmap(0, sizeof(struct shared), PROT_READ | PROT_WRITE,
                              MAP_SHARED | MAP_ANON, -1, 0);
  ensure(Shmem != MAP_FAILED);
  ensure(0 == atexit(exit_handler));
  Shmem->NextId = 1;

  if (RT) {
    ensure(0 == sem_init(&Shmem->sem, 1, 4));
    setpri();
  }

  Module *M = new Module("", getGlobalContext());
  C = &M->getContext();
  std::vector<Type *> ArgsTy;
  for (int i = 0; i < N + 1; ++i) {
    ArgsTy.push_back(IntegerType::getIntNTy(*C, W));
    ArgsTy.push_back(IntegerType::getIntNTy(*C, 1));
    ArgsTy.push_back(IntegerType::getIntNTy(*C, W / 2));
    ArgsTy.push_back(IntegerType::getIntNTy(*C, W * 2));
  }
  unsigned RetWidth = W;
  auto FuncTy = FunctionType::get(Type::getIntNTy(*C, RetWidth), ArgsTy, 0);
  F = Function::Create(FuncTy, GlobalValue::ExternalLinkage, "func", M);
  BBs.push_back(BasicBlock::Create(*C, "", F));
  Builder = new IRBuilder<true, NoFolder>(BBs[0]);
  int Budget = N;
  Builder->SetInsertPoint(BBs[0]);

  // action happens here
  Value *V = genVal(Budget, RetWidth, false, false);
  // terminate the sole non-terminated BB
  Builder->CreateRet(V);

  // fixup branch targets
  for (auto &bi : Branches) {
    BasicBlock *BB1 = chooseTarget();
    bi->setSuccessor(0, BB1);
    if (bi->isConditional())
      bi->setSuccessor(1, chooseTarget(BB1));
  }

// finally, fixup the Phis -- first by splitting any BBs where a non-Phi
// precedes a Phi
redo:
  for (auto &bb : *F) {
    bool notphi = false;
    for (auto &i : bb) {
      if (!isa<PHINode>(i))
        notphi = true;
      if (notphi && isa<PHINode>(i)) {
        i.getParent()->splitBasicBlock(i, "phisp");
        goto redo;
      }
    }
  }

  // and second by giving them incoming edges
  for (auto p = inst_begin(F), pe = inst_end(F); p != pe; ++p) {
    PHINode *P = dyn_cast<PHINode>(&*p);
    if (!P)
      continue;
    BasicBlock *BB = P->getParent();
    for (pred_iterator PI = pred_begin(BB), E = pred_end(BB); PI != E; ++PI) {
      BasicBlock *Pred = *PI;
      ensure(Budget == 0);
      Value *V =
        genVal(Budget, P->getType()->getPrimitiveSizeInBits(), true, false);
      P->addIncoming(V, Pred);
    }
  }

  // drop any program where we have a non-entry BB that lacks predecessors;
  // would be better to avoid creating these in the first place
  bool first = true;
  for (auto &bb : *F) {
    if (first) {
      first = false;
    } else {
      int p = 0;
      for (pred_iterator PI = pred_begin(&bb), E = pred_end(&bb); PI != E; ++PI)
        p++;
      if (p == 0)
        exit(0);
    }
  }

  std::string SStr;
  raw_string_ostream SS(SStr);
  legacy::PassManager Passes;
  if (Verify)
    Passes.add(createVerifierPass());
  Passes.add(createPrintModulePass(SS));
  Passes.run(*M);

  if (!Fuzz) {
    std::stringstream ss;
    ss << "func" << std::to_string(Id);
    ::srand(::time(0) + ::getpid());
    std::string FN = std::to_string(rand() % NumFiles) + ".ll";
    std::string func = SS.str();
    func.replace(func.find("func"), 4, ss.str());
    int fd = open(FN.c_str(), O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
    ensure(fd > 2);
    /*
     * bad hack -- instead of locking the file we're going to count on an atomic
     * write and bail if it doesn't work -- this works fine on Linux
     */
    unsigned res = write(fd, func.c_str(), func.length());
    ensure(res == func.length());
    res = close(fd);
    ensure(res == 0);
  } else {
    outs() << SS.str();
  }

  if (Id == 0) {
    // fixme wait for all children
  }
  return 0;
}