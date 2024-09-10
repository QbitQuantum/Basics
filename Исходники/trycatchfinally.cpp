void TryCatchScope::emitCatchBodies(IRState &irs, llvm::Value *ehPtrSlot) {
  assert(catchBlocks.empty());

  auto &PGO = irs.funcGen().pgo;
  const auto entryCount = PGO.setCurrentStmt(stmt);

  struct CBPrototype {
    Type *t;
    llvm::BasicBlock *catchBB;
    uint64_t catchCount;
    uint64_t uncaughtCount;
  };
  llvm::SmallVector<CBPrototype, 8> cbPrototypes;
  cbPrototypes.reserve(stmt->catches->dim);

  for (auto c : *stmt->catches) {
    auto catchBB =
        irs.insertBBBefore(endbb, llvm::Twine("catch.") + c->type->toChars());
    irs.scope() = IRScope(catchBB);
    irs.DBuilder.EmitBlockStart(c->loc);
    PGO.emitCounterIncrement(c);

    bool isCPPclass = false;

    if (auto lp = c->langPlugin()) // CALYPSO
      lp->codegen()->toBeginCatch(irs, c);
    else
    {

    const auto cd = c->type->toBasetype()->isClassHandle();
    isCPPclass = cd->isCPPclass();

    const auto enterCatchFn = getRuntimeFunction(
        Loc(), irs.module,
        isCPPclass ? "__cxa_begin_catch" : "_d_eh_enter_catch");
    const auto ptr = DtoLoad(ehPtrSlot);
    const auto throwableObj = irs.ir->CreateCall(enterCatchFn, ptr);

    // For catches that use the Throwable object, create storage for it.
    // We will set it in the code that branches from the landing pads
    // (there might be more than one) to catchBB.
    if (c->var) {
      // This will alloca if we haven't already and take care of nested refs
      // if there are any.
      DtoDeclarationExp(c->var);

      // Copy the exception reference over from the _d_eh_enter_catch return
      // value.
      DtoStore(DtoBitCast(throwableObj, DtoType(c->var->type)),
               getIrLocal(c->var)->value);
    }
    }

    // Emit handler, if there is one. The handler is zero, for instance,
    // when building 'catch { debug foo(); }' in non-debug mode.
    if (isCPPclass) {
      // from DMD:

      /* C++ catches need to end with call to __cxa_end_catch().
       * Create:
       *   try { handler } finally { __cxa_end_catch(); }
       * Note that this is worst case code because it always sets up an
       * exception handler. At some point should try to do better.
       */
      FuncDeclaration *fdend =
          FuncDeclaration::genCfunc(nullptr, Type::tvoid, "__cxa_end_catch");
      Expression *efunc = VarExp::create(Loc(), fdend);
      Expression *ecall = CallExp::create(Loc(), efunc);
      ecall->type = Type::tvoid;
      Statement *call = ExpStatement::create(Loc(), ecall);
      Statement *stmt =
          c->handler ? TryFinallyStatement::create(Loc(), c->handler, call)
                     : call;
      Statement_toIR(stmt, &irs);
    } else {
      if (c->handler)
        Statement_toIR(c->handler, &irs);
    }

    if (!irs.scopereturned())
    {
      // CALYPSO FIXME: _cxa_end_catch won't be called if it has already returned
      if (auto lp = c->langPlugin())
        lp->codegen()->toEndCatch(irs, c);
      irs.ir->CreateBr(endbb);
    }

    irs.DBuilder.EmitBlockEnd();

    // PGO information, currently unused
    auto catchCount = PGO.getRegionCount(c);
    // uncaughtCount is handled in a separate pass below

    cbPrototypes.push_back({c->type->toBasetype(), catchBB, catchCount, 0}); // CALYPSO
  }

  // Total number of uncaught exceptions is equal to the execution count at
  // the start of the try block minus the one after the continuation.
  // uncaughtCount keeps track of the exception type mismatch count while
  // iterating through the catch block prototypes in reversed order.
  auto uncaughtCount = entryCount - PGO.getRegionCount(stmt);
  for (auto it = cbPrototypes.rbegin(), end = cbPrototypes.rend(); it != end;
       ++it) {
    it->uncaughtCount = uncaughtCount;
    // Add this catch block's match count to the uncaughtCount, because these
    // failed to match the remaining (lexically preceding) catch blocks.
    uncaughtCount += it->catchCount;
  }

  catchBlocks.reserve(stmt->catches->dim);

  auto c_it = stmt->catches->begin(); // CALYPSO
  for (const auto &p : cbPrototypes) {
    auto branchWeights =
        PGO.createProfileWeights(p.catchCount, p.uncaughtCount);
    LLGlobalVariable *ci;
    if (auto lp = (*c_it)->langPlugin()) // CALYPSO
      ci = lp->codegen()->toCatchScopeType(irs, p.t);
    else {
      ClassDeclaration *cd = p.t->isClassHandle();
      DtoResolveClass(cd);
      if (cd->isCPPclass()) {
        const char *name = Target::cppTypeInfoMangle(cd);
        auto cpp_ti = getOrCreateGlobal(
            cd->loc, irs.module, getVoidPtrType(), /*isConstant=*/true,
            LLGlobalValue::ExternalLinkage, /*init=*/nullptr, name);

        // Wrap std::type_info pointers inside a __cpp_type_info_ptr class instance so that
        // the personality routine may differentiate C++ catch clauses from D ones.
        OutBuffer mangleBuf;
        mangleBuf.writestring("_D");
        mangleToBuffer(cd, &mangleBuf);
        mangleBuf.printf("%d%s", 18, "_cpp_type_info_ptr");
        const auto wrapperMangle = getIRMangledVarName(mangleBuf.peekString(), LINKd);

        RTTIBuilder b(ClassDeclaration::cpp_type_info_ptr);
        b.push(cpp_ti);

        auto wrapperType = llvm::cast<llvm::StructType>(
            static_cast<IrTypeClass*>(ClassDeclaration::cpp_type_info_ptr->type->ctype)->getMemoryLLType());
        auto wrapperInit = b.get_constant(wrapperType);

        ci = getOrCreateGlobal(
            cd->loc, irs.module, wrapperType, /*isConstant=*/true,
            LLGlobalValue::LinkOnceODRLinkage, wrapperInit, wrapperMangle);
      } else {
        ci = getIrAggr(cd)->getClassInfoSymbol();
      }
    }
    catchBlocks.push_back({ci, p.catchBB, branchWeights});
    c_it++;
  }
}