void LLSTDebuggingPass::insertLoadInstCheck(Function& F)
{
    Value* BrokenPointerMessage = m_builder->CreateGlobalStringPtr("\npointer is broken\n");

    InstructionVector Loads;
    for (Function::iterator BB = F.begin(); BB != F.end(); ++BB)
    {
        for(BasicBlock::iterator II = BB->begin(); II != BB->end(); ++II)
        {
            if (LoadInst* Load = dyn_cast<LoadInst>(II)) {
                Loads.push_back(Load);
            }
        }
    }

    for(std::size_t i = 0; i < Loads.size(); i++)
    {
        LoadInst* Load = dyn_cast<LoadInst>(Loads[i]);
        if (belongsToSmalltalkType( Load->getType() )) {

            //split BB right after load inst. The new BB contains code that will be executed if pointer is OK
            BasicBlock* PointerIsOkBB = Load->getParent()->splitBasicBlock(++( static_cast<BasicBlock::iterator>(Load) ));
            BasicBlock* PointerIsBrokenBB = BasicBlock::Create(m_module->getContext(), "", &F, PointerIsOkBB);
            BasicBlock* PointerIsNotSmallIntBB = BasicBlock::Create(m_module->getContext(), "", &F, PointerIsBrokenBB);

            Instruction* branchToPointerIsOkBB = ++( static_cast<BasicBlock::iterator>(Load) );
            //branchToPointerIsOkBB is created by splitBasicBlock() just after load inst
            //We force builder to insert instructions before branchToPointerIsOkBB
            m_builder->SetInsertPoint(branchToPointerIsOkBB);

            //If pointer to class is null, jump to PointerIsBroken, otherwise to PointerIsOkBB
            Value* objectPtr = m_builder->CreateBitCast( Load, m_baseTypes.object->getPointerTo());

            Value* isSmallInt = m_builder->CreateCall(isSmallInteger, objectPtr);
            m_builder->CreateCondBr(isSmallInt, PointerIsOkBB, PointerIsNotSmallIntBB);

            m_builder->SetInsertPoint(PointerIsNotSmallIntBB);
            Value* klassPtr = m_builder->CreateCall(getObjectClass, objectPtr);
            Value* pointerIsNull = m_builder->CreateICmpEQ(klassPtr, ConstantPointerNull::get(m_baseTypes.klass->getPointerTo()) );
            m_builder->CreateCondBr(pointerIsNull, PointerIsBrokenBB, PointerIsOkBB);

            branchToPointerIsOkBB->eraseFromParent(); //We don't need it anymore

            m_builder->SetInsertPoint(PointerIsBrokenBB);
            m_builder->CreateCall(_printf, BrokenPointerMessage);
            m_builder->CreateBr(PointerIsOkBB);
        }
    }
}