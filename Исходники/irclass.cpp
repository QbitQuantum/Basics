llvm::GlobalVariable * IrAggr::getInterfaceVtbl(BaseClass * b, bool new_instance, size_t interfaces_index)
{
    ClassGlobalMap::iterator it = interfaceVtblMap.find(b->base);
    if (it != interfaceVtblMap.end())
        return it->second;

    IF_LOG Logger::println("Building vtbl for implementation of interface %s in class %s",
        b->base->toPrettyChars(), aggrdecl->toPrettyChars());
    LOG_SCOPE;

    ClassDeclaration* cd = aggrdecl->isClassDeclaration();
    assert(cd && "not a class aggregate");

    FuncDeclarations vtbl_array;
    b->fillVtbl(cd, &vtbl_array, new_instance);

    std::vector<llvm::Constant*> constants;
    constants.reserve(vtbl_array.dim);

    if (!b->base->isCPPinterface()) { // skip interface info for CPP interfaces
        // start with the interface info
        VarDeclarationIter interfaces_idx(ClassDeclaration::classinfo->fields, 3);

        // index into the interfaces array
        llvm::Constant* idxs[2] = {
            DtoConstSize_t(0),
            DtoConstSize_t(interfaces_index)
        };

        llvm::Constant* c = llvm::ConstantExpr::getGetElementPtr(
            getInterfaceArraySymbol(), idxs, true);

        constants.push_back(c);
    }

    // add virtual function pointers
    size_t n = vtbl_array.dim;
    for (size_t i = b->base->vtblOffset(); i < n; i++)
    {
        Dsymbol* dsym = static_cast<Dsymbol*>(vtbl_array.data[i]);
        if (dsym == NULL)
        {
            // FIXME
            // why is this null?
            // happens for mini/s.d
            constants.push_back(getNullValue(getVoidPtrType()));
            continue;
        }

        FuncDeclaration* fd = dsym->isFuncDeclaration();
        assert(fd && "vtbl entry not a function");

        assert((!fd->isAbstract() || fd->fbody) &&
            "null symbol in interface implementation vtable");

        fd->codegen(Type::sir);
        assert(fd->ir.irFunc && "invalid vtbl function");

        LLFunction *fn = fd->ir.irFunc->func;

        // If the base is a cpp interface, 'this' parameter is a pointer to
        // the interface not the underlying object as expected. Instead of
        // the function, we place into the vtable a small wrapper, called thunk,
        // that casts 'this' to the object and then pass it to the real function.
        if (b->base->isCPPinterface()) {
            TypeFunction *f = (TypeFunction*)fd->type->toBasetype();
            assert(f->fty.arg_this);

            // create the thunk function
            OutBuffer name;
            name.writestring("Th");
            name.printf("%i", b->offset);
            name.writestring(fd->mangle());
            LLFunction *thunk = LLFunction::Create(isaFunction(fn->getType()->getContainedType(0)),
                                                 DtoLinkage(fd), name.toChars(), gIR->module);

            // create entry and end blocks
            llvm::BasicBlock* beginbb = llvm::BasicBlock::Create(gIR->context(), "entry", thunk);
            llvm::BasicBlock* endbb = llvm::BasicBlock::Create(gIR->context(), "endentry", thunk);
            gIR->scopes.push_back(IRScope(beginbb, endbb));

            // copy the function parameters, so later we can pass them to the real function
            std::vector<LLValue*> args;
            llvm::Function::arg_iterator iarg = thunk->arg_begin();
            for (; iarg != thunk->arg_end(); ++iarg)
                args.push_back(iarg);

            // cast 'this' to Object
            LLValue* &thisArg = args[(f->fty.arg_sret == 0) ? 0 : 1];
            LLType* thisType = thisArg->getType();
            thisArg = DtoBitCast(thisArg, getVoidPtrType());
            thisArg = DtoGEP1(thisArg, DtoConstInt(-b->offset));
            thisArg = DtoBitCast(thisArg, thisType);

            // call the real vtbl function.
            LLValue *retVal = gIR->ir->CreateCall(fn, args);

            // return from the thunk
            if (thunk->getReturnType() == LLType::getVoidTy(gIR->context()))
                llvm::ReturnInst::Create(gIR->context(), beginbb);
            else
                llvm::ReturnInst::Create(gIR->context(), retVal, beginbb);

            // clean up
            gIR->scopes.pop_back();
            thunk->getBasicBlockList().pop_back();

            fn = thunk;
        }

        constants.push_back(fn);
    }

    // build the vtbl constant
    llvm::Constant* vtbl_constant = LLConstantStruct::getAnon(gIR->context(), constants, false);

    // create the global variable to hold it
    llvm::GlobalValue::LinkageTypes _linkage = DtoExternalLinkage(aggrdecl);

    std::string mangle("_D");
    mangle.append(cd->mangle());
    mangle.append("11__interface");
    mangle.append(b->base->mangle());
    mangle.append("6__vtblZ");

    llvm::GlobalVariable* GV = getOrCreateGlobal(cd->loc,
        *gIR->module,
        vtbl_constant->getType(),
        true,
        _linkage,
        vtbl_constant,
        mangle
    );

    // insert into the vtbl map
    interfaceVtblMap.insert(std::make_pair(b->base, GV));

    return GV;
}