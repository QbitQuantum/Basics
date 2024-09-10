// This member is called for each Instruction in a function..
void FunctionGen::printInstruction(const Instruction &I) {
  //if (AnnotationWriter) AnnotationWriter->emitInstructionAnnot(&I, Out);
	if (isa<AllocaInst>(I)) return;
	Out << "  ";
	std::string name;
	std::string name2;
	if (I.hasName()){
		name=I.getName().str();
		for (int k=0;k<name.size();k++)
			if (name[k]=='.') name[k]='_';
	}else if(!I.getType()->isVoidTy()){
		int SlotNum=Machine.getLocalSlot(&I);
		if (SlotNum==-1){
			name="<badref>";
		}else{
			char tmp[100];
			memset(tmp,0,sizeof(tmp));
			sprintf(tmp,"v%d",SlotNum);
			name=tmp;
		}
	}

	if (isa<PHINode>(I)) {
		Out << "if\n";

		for (unsigned op = 0, Eop = I.getNumOperands(); op < Eop; op += 2) {
			Out << "    ::";
			Out <<"(currentLabel == ";
			Out<<gos.find(I.getOperand(op+1)->getName())->second<<")->";
			Out<<name<<" = ";
			writeOperand(I.getOperand(op),false);
			Out<<"\n";
		}
		Out<<"  fi;\n";
		return ;
	}
	if (!flag){
		Out<<"currentLabel = "<<gos.find(I.getParent()->getName())->second<<";\n  ";
		flag=true;
	}

  // Print out indentation for an instruction.
  
	if (const CallInst *CI = dyn_cast<CallInst>(&I)) {
		if (CI->getCalledValue()->getName()!="printf")
			Out <<"run ";
		goto flag1;
	}
	if (I.hasName() || !I.getType()->isVoidTy())
	Out <<name<<" = ";
flag1:
  // Print out name if it exists...
/*
  if (I.hasName()) {
	  Helper::PrintLLVMName(Out, &I);
    Out << " = ";
  } else if (!I.getType()->isVoidTy()) {
    // Print out the def slot taken.
    int SlotNum = Machine.getLocalSlot(&I);
    if (SlotNum == -1)
      Out << "<badref> = ";
    else
      Out << '%' << SlotNum << " = ";
  }
  */
/*
  // If this is a volatile load or store, print out the volatile marker.
  if ((isa<LoadInst>(I)  && cast<LoadInst>(I).isVolatile()) ||
      (isa<StoreInst>(I) && cast<StoreInst>(I).isVolatile())) {
      Out << "volatile ";
  } else if (isa<CallInst>(I) && cast<CallInst>(I).isTailCall()) {
    // If this is a call, check if it's a tail call.
    Out << "tail ";
  }
*/
  // Print out the opcode...
//  Out << I.getOpcodeName();
  std::string opcodeName = I.getOpcodeName();

  // Print out optimization information.
  //WriteOptimizationInfo(Out, &I);

  // Print out the compare instruction predicates
  // Print out the type of the operands...
  const Value *Operand = I.getNumOperands() ? I.getOperand(0) : 0;

  // Special case conditional branches to swizzle the condition out to the front
  if (isa<BranchInst>(I)) {
	  if (cast<BranchInst>(I).isConditional()){
		BranchInst &BI(cast<BranchInst>(I));
		Out << "if\n    ::(";
		writeOperand(BI.getCondition(), false);
		Out << "!= 0) -> goto Label";
		Out << gos.find(BI.getSuccessor(0)->getName())->second;
		//writeOperand(BI.getSuccessor(0), false);
		Out << "\n    ::(";
		writeOperand(BI.getCondition(), false);
		Out << "==0) -> goto Label";
		Out << gos.find(BI.getSuccessor(1)->getName())->second;
		//writeOperand(BI.getSuccessor(1), false);
		Out << "\n  fi";
	  }else{
		  BranchInst &BI(cast<BranchInst>(I));
		  Out <<"goto Label"<<gos.find(BI.getSuccessor(0)->getName())->second;
	  }
  } else if (isa<SwitchInst>(I)) {
    // Special case switch instruction to get formatting nice and correct.
    Out << ' ';
    writeOperand(Operand        , true);
    Out << ", ";
    writeOperand(I.getOperand(1), true);
    Out << " [";

    for (unsigned op = 2, Eop = I.getNumOperands(); op < Eop; op += 2) {
      Out << "\n    ";
      writeOperand(I.getOperand(op  ), true);
      Out << ", ";
      writeOperand(I.getOperand(op+1), true);
    }
    Out << "\n  ]";
  } else if (isa<IndirectBrInst>(I)) {
    // Special case indirectbr instruction to get formatting nice and correct.
    Out << ' ';
    writeOperand(Operand, true);
    Out << ", [";
    
    for (unsigned i = 1, e = I.getNumOperands(); i != e; ++i) {
      if (i != 1)
        Out << ", ";
      writeOperand(I.getOperand(i), true);
    }
    Out << ']';
  } else if (isa<PHINode>(I)) {
    Out << ' ';
    TypeGener.print(I.getType(), Out);
    Out << ' ';

    for (unsigned op = 0, Eop = I.getNumOperands(); op < Eop; op += 2) {
      if (op) Out << ", ";
      Out << "[ ";
      writeOperand(I.getOperand(op  ), false); Out << ", ";
      writeOperand(I.getOperand(op+1), false); Out << " ]";
    }
  } else if (const ExtractValueInst *EVI = dyn_cast<ExtractValueInst>(&I)) {
    Out << ' ';
    writeOperand(I.getOperand(0), true);
    for (const unsigned *i = EVI->idx_begin(), *e = EVI->idx_end(); i != e; ++i)
      Out << ", " << *i;
  } else if (const InsertValueInst *IVI = dyn_cast<InsertValueInst>(&I)) {
    Out << ' ';
    writeOperand(I.getOperand(0), true); Out << ", ";
    writeOperand(I.getOperand(1), true);
    for (const unsigned *i = IVI->idx_begin(), *e = IVI->idx_end(); i != e; ++i)
      Out << ", " << *i;
  } else if (isa<ReturnInst>(I) && !Operand) {
    return;
  } else if (const CallInst *CI = dyn_cast<CallInst>(&I)) {
    // Print the calling convention being used.
    switch (CI->getCallingConv()) {
    case CallingConv::C: break;   // default
    case CallingConv::Fast:  Out << " fastcc"; break;
    case CallingConv::Cold:  Out << " coldcc"; break;
    case CallingConv::X86_StdCall:  Out << " x86_stdcallcc"; break;
    case CallingConv::X86_FastCall: Out << " x86_fastcallcc"; break;
    case CallingConv::X86_ThisCall: Out << " x86_thiscallcc"; break;
    case CallingConv::ARM_APCS:     Out << " arm_apcscc "; break;
    case CallingConv::ARM_AAPCS:    Out << " arm_aapcscc "; break;
    case CallingConv::ARM_AAPCS_VFP:Out << " arm_aapcs_vfpcc "; break;
    case CallingConv::MSP430_INTR:  Out << " msp430_intrcc "; break;
    case CallingConv::PTX_Kernel:   Out << " ptx_kernel"; break;
    case CallingConv::PTX_Device:   Out << " ptx_device"; break;
    default: Out << " cc" << CI->getCallingConv(); break;
    }

    Operand = CI->getCalledValue();
    const PointerType    *PTy = cast<PointerType>(Operand->getType());
    const FunctionType   *FTy = cast<FunctionType>(PTy->getElementType());
    const Type         *RetTy = FTy->getReturnType();
    const AttrListPtr &PAL = CI->getAttributes();

//    if (PAL.getRetAttributes() != Attribute::None)
//      Out << ' ' << Attribute::getAsString(PAL.getRetAttributes());

    // If possible, print out the short form of the call instruction.  We can
    // only do this if the first argument is a pointer to a nonvararg function,
    // and if the return type is not a pointer to a function.
    //
	name2=Operand->getName();

	if (name2=="pthread_create"){
		writeParamOperand(CI->getArgOperand(2),NULL);
		Out<<'(';
		writeParamOperand(CI->getArgOperand(3),NULL);
		Out<<", "<<"_return"<<retCount<<");\n";
		retCount++;
		return ;
	}

	if (name2=="printf"){
		Out<<' '<<name2;
	}else{
		Out << ' ';
		if (!FTy->isVarArg() &&
			(!RetTy->isPointerTy() ||
			!cast<PointerType>(RetTy)->getElementType()->isFunctionTy())) {
			//TypeGener.print(RetTy, Out);
			// Out << ' ';
			writeOperand(Operand, false);
		} else {
			writeOperand(Operand, false);
		}
	}
    Out << '(';
    for (unsigned op = 0, Eop = CI->getNumArgOperands(); op < Eop; ++op) {
      if (op > 0)
        Out << ", ";
		writeParamOperand(CI->getArgOperand(op), PAL.getParamAttributes(op + 1));
    }
	if (name2!="printf"){
		Out<<", ";
		if (RetTy->isVoidTy())
			Out<<"_syn";
		else Out <<"_return"<<retCount;
	}
    Out << ')';
	if (name2!="printf") {
		if (RetTy->isVoidTy()){
			Out << ";\n  _syn?0";
		}else{
			Out << ";\n  _return"<<retCount<<"?"<<name;
			retCount++;
		}
	}
//   if (PAL.getFnAttributes() != Attribute::None)
//     Out << ' ' << Attribute::getAsString(PAL.getFnAttributes());
  } else if (const InvokeInst *II = dyn_cast<InvokeInst>(&I)) {
    Operand = II->getCalledValue();
    const PointerType    *PTy = cast<PointerType>(Operand->getType());
    const FunctionType   *FTy = cast<FunctionType>(PTy->getElementType());
    const Type         *RetTy = FTy->getReturnType();
    const AttrListPtr &PAL = II->getAttributes();

    // Print the calling convention being used.
    switch (II->getCallingConv()) {
    case CallingConv::C: break;   // default
    case CallingConv::Fast:  Out << " fastcc"; break;
    case CallingConv::Cold:  Out << " coldcc"; break;
    case CallingConv::X86_StdCall:  Out << " x86_stdcallcc"; break;
    case CallingConv::X86_FastCall: Out << " x86_fastcallcc"; break;
    case CallingConv::X86_ThisCall: Out << " x86_thiscallcc"; break;
    case CallingConv::ARM_APCS:     Out << " arm_apcscc "; break;
    case CallingConv::ARM_AAPCS:    Out << " arm_aapcscc "; break;
    case CallingConv::ARM_AAPCS_VFP:Out << " arm_aapcs_vfpcc "; break;
    case CallingConv::MSP430_INTR:  Out << " msp430_intrcc "; break;
    case CallingConv::PTX_Kernel:   Out << " ptx_kernel"; break;
    case CallingConv::PTX_Device:   Out << " ptx_device"; break;
    default: Out << " cc" << II->getCallingConv(); break;
    }

    if (PAL.getRetAttributes() != Attribute::None)
      Out << ' ' << Attribute::getAsString(PAL.getRetAttributes());

    // If possible, print out the short form of the invoke instruction. We can
    // only do this if the first argument is a pointer to a nonvararg function,
    // and if the return type is not a pointer to a function.
    //
    Out << ' ';
    if (!FTy->isVarArg() &&
        (!RetTy->isPointerTy() ||
         !cast<PointerType>(RetTy)->getElementType()->isFunctionTy())) {
      TypeGener.print(RetTy, Out);
      Out << ' ';
      writeOperand(Operand, false);
    } else {
      writeOperand(Operand, true);
    }
    Out << '(';
    for (unsigned op = 0, Eop = II->getNumArgOperands(); op < Eop; ++op) {
      if (op)
        Out << ", ";
	  writeParamOperand(II->getArgOperand(op), PAL.getParamAttributes(op + 1));
    }

    Out << ')';
    if (PAL.getFnAttributes() != Attribute::None)
      Out << ' ' << Attribute::getAsString(PAL.getFnAttributes());

    Out << "\n          to ";
    writeOperand(II->getNormalDest(), true);
    Out << " unwind ";
    writeOperand(II->getUnwindDest(), true);

  } else if (isa<CastInst>(I)) {
		if (Operand){
			Out << ' ';
			writeOperand(Operand,false);
		}
	/*  
    if (Operand) {
      Out << ' ';
      writeOperand(Operand, true);   // Work with broken code
    }
    Out << " to ";
    TypeGener.print(I.getType(), Out);
	*/
  } else if (isa<VAArgInst>(I)) {
    if (Operand) {
      Out << ' ';
      writeOperand(Operand, true);   // Work with broken code
    }
    Out << ", ";
    TypeGener.print(I.getType(), Out);
  } else if (Operand) {   // Print the normal way.

    // PrintAllTypes - Instructions who have operands of all the same type
    // omit the type from all but the first operand.  If the instruction has
    // different type operands (for example br), then they are all printed.
/*
	bool PrintAllTypes = false;
    const Type *TheType = Operand->getType();

    // Select, Store and ShuffleVector always print all types.
    if (isa<SelectInst>(I) || isa<StoreInst>(I) || isa<ShuffleVectorInst>(I)
        || isa<ReturnInst>(I)) {
      PrintAllTypes = true;
    } else {
      for (unsigned i = 1, E = I.getNumOperands(); i != E; ++i) {
        Operand = I.getOperand(i);
        // note that Operand shouldn't be null, but the test helps make dump()
        // more tolerant of malformed IR
        if (Operand && Operand->getType() != TheType) {
          PrintAllTypes = true;    // We have differing types!  Print them all!
          break;
        }
      }
    }

    if (!PrintAllTypes) {
      Out << ' ';
      TypeGener.print(TheType, Out);
    }
*/
	
	if (isa<SelectInst>(I)){
		Out << '(';
		writeOperand(I.getOperand(0),false);
		Out << "!=0 -> ";
		writeOperand(I.getOperand(1),false);
		Out << " : ";
		writeOperand(I.getOperand(2),false);
		Out << ")";
	}else if (isa<StoreInst>(I)){
		writeOperand(I.getOperand(1),false);
		Out << " = ";
		writeOperand(I.getOperand(0),false);
	}else  if (const CmpInst *CI = dyn_cast<CmpInst>(&I)){
		Out << '(';
		writeOperand(I.getOperand(0),false);
		Out << ' ' << Helper::getPredicateText(CI->getPredicate())<<' ';
		writeOperand(I.getOperand(1),false);
		Out << ')';
	}else if (const BinaryOperator *BI=dyn_cast<BinaryOperator>(&I)){
		writeOperand(I.getOperand(0),false);
		switch (BI->getOpcode()){
			case Add:
			case FAdd:Out<<" + ";break;
			case Sub:
			case FSub:Out << " - ";break;
			case Mul:
			case FMul:Out << " * "; break;
			case UDiv:
			case SDiv:
			case FDiv:Out << " / ";break;
			case URem:
			case SRem:
			case FRem:Out << " % ";break;
			case Shl:Out << " << ";break;
			case LShr:
			case AShr:Out << " >> ";break;
			case And:Out << " & ";break;
			case Or:Out << " | ";break;
			case Xor:Out<< " ^ ";break;
		}
		writeOperand(I.getOperand(1),false);
	}else if (isa<ReturnInst>(I)){
		Out <<"__return!";
		writeOperand(I.getOperand(0),false);
		Out << ";\n  goto LabelSkip";
	}else{
		for (unsigned i = 0, E = I.getNumOperands(); i != E; ++i) {
			if (i) Out << ",[other] ";
			writeOperand(I.getOperand(i), false);
		}	
	}
  }
	Out << ";\n";
  // Print post operand alignment for load/store.
/*
  if (isa<LoadInst>(I) && cast<LoadInst>(I).getAlignment()) {
    Out << ", align " << cast<LoadInst>(I).getAlignment();
  } else if (isa<StoreInst>(I) && cast<StoreInst>(I).getAlignment()) {
    Out << ", align " << cast<StoreInst>(I).getAlignment();
  }

  // Print Metadata info.
  SmallVector<std::pair<unsigned, MDNode*>, 4> InstMD;
  I.getAllMetadata(InstMD);
  if (!InstMD.empty()) {
    SmallVector<StringRef, 8> MDNames;
    I.getType()->getContext().getMDKindNames(MDNames);
    for (unsigned i = 0, e = InstMD.size(); i != e; ++i) {
      unsigned Kind = InstMD[i].first;
       if (Kind < MDNames.size()) {
         Out << ", !" << MDNames[Kind];
      } else {
        Out << ", !<unknown kind #" << Kind << ">";
      }
      Out << ' ';
	  Helper::WriteAsOperandInternal(Out, InstMD[i].second, &TypeGener, &Machine,
                             TheModule);
    }
  }
*/
  //printInfoComment(I);
}