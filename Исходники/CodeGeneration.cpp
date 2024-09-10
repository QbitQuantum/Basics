  /// @brief Generate LLVM-IR for the SCoP @p S.
  bool runOnScop(Scop &S) override {
    AI = &getAnalysis<IslAstInfo>();

    // Check if we created an isl_ast root node, otherwise exit.
    isl_ast_node *AstRoot = AI->getAst();
    if (!AstRoot)
      return false;

    LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
    DT = &getAnalysis<DominatorTreeWrapperPass>().getDomTree();
    SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();
    DL = &S.getRegion().getEntry()->getParent()->getParent()->getDataLayout();
    RI = &getAnalysis<RegionInfoPass>().getRegionInfo();
    Region *R = &S.getRegion();
    assert(!R->isTopLevelRegion() && "Top level regions are not supported");

    ScopAnnotator Annotator;
    Annotator.buildAliasScopes(S);

    simplifyRegion(R, DT, LI, RI);
    assert(R->isSimple());
    BasicBlock *EnteringBB = S.getRegion().getEnteringBlock();
    assert(EnteringBB);
    PollyIRBuilder Builder = createPollyIRBuilder(EnteringBB, Annotator);

    IslNodeBuilder NodeBuilder(Builder, Annotator, this, *DL, *LI, *SE, *DT, S);

    // Only build the run-time condition and parameters _after_ having
    // introduced the conditional branch. This is important as the conditional
    // branch will guard the original scop from new induction variables that
    // the SCEVExpander may introduce while code generating the parameters and
    // which may introduce scalar dependences that prevent us from correctly
    // code generating this scop.
    BasicBlock *StartBlock =
        executeScopConditionally(S, this, Builder.getTrue());
    auto SplitBlock = StartBlock->getSinglePredecessor();

    // First generate code for the hoisted invariant loads and transitively the
    // parameters they reference. Afterwards, for the remaining parameters that
    // might reference the hoisted loads. Finally, build the runtime check
    // that might reference both hoisted loads as well as parameters.
    // If the hoisting fails we have to bail and execute the original code.
    Builder.SetInsertPoint(SplitBlock->getTerminator());
    if (!NodeBuilder.preloadInvariantLoads()) {

      auto *FalseI1 = Builder.getFalse();
      auto *SplitBBTerm = Builder.GetInsertBlock()->getTerminator();
      SplitBBTerm->setOperand(0, FalseI1);
      auto *StartBBTerm = StartBlock->getTerminator();
      Builder.SetInsertPoint(StartBBTerm);
      Builder.CreateUnreachable();
      StartBBTerm->eraseFromParent();
      isl_ast_node_free(AstRoot);

    } else {

      NodeBuilder.addParameters(S.getContext());

      Value *RTC = buildRTC(Builder, NodeBuilder.getExprBuilder());
      Builder.GetInsertBlock()->getTerminator()->setOperand(0, RTC);
      Builder.SetInsertPoint(&StartBlock->front());

      NodeBuilder.create(AstRoot);

      NodeBuilder.finalizeSCoP(S);
      fixRegionInfo(EnteringBB->getParent(), R->getParent());
    }

    verifyGeneratedFunction(S, *EnteringBB->getParent());

    // Mark the function such that we run additional cleanup passes on this
    // function (e.g. mem2reg to rediscover phi nodes).
    Function *F = EnteringBB->getParent();
    F->addFnAttr("polly-optimized");

    return true;
  }