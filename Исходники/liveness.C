ReadWriteInfo LivenessAnalyzer::calcRWSets(Instruction::Ptr curInsn, Block* blk, Address a)
{

  liveness_cerr << "calcRWSets for " << curInsn->format() << " @ " << hex << a << dec << endl;
  ReadWriteInfo ret;
  ret.read = abi->getBitArray();
  ret.written = abi->getBitArray();
  ret.insnSize = curInsn->size();
  std::set<RegisterAST::Ptr> cur_read, cur_written;
  curInsn->getReadSet(cur_read);
  curInsn->getWriteSet(cur_written);
    liveness_printf("Read registers: \n");
  
  for (std::set<RegisterAST::Ptr>::const_iterator i = cur_read.begin(); 
       i != cur_read.end(); i++) 
  {
    MachRegister cur = (*i)->getID();
    if (cur.getArchitecture() == Arch_ppc64)
	cur = MachRegister((cur.val() & ~Arch_ppc64) | Arch_ppc32);
    liveness_printf("\t%s \n", cur.name().c_str());
    MachRegister base = cur.getBaseRegister();
    if (cur == x86::flags || cur == x86_64::flags){
      if (width == 4){
        ret.read[getIndex(x86::of)] = true;
        ret.read[getIndex(x86::cf)] = true;
        ret.read[getIndex(x86::pf)] = true;
        ret.read[getIndex(x86::af)] = true;
        ret.read[getIndex(x86::zf)] = true;
        ret.read[getIndex(x86::sf)] = true;
        ret.read[getIndex(x86::df)] = true;
        ret.read[getIndex(x86::tf)] = true;
        ret.read[getIndex(x86::nt_)] = true;
      }
      else {
        ret.read[getIndex(x86_64::of)] = true;
        ret.read[getIndex(x86_64::cf)] = true;
        ret.read[getIndex(x86_64::pf)] = true;
        ret.read[getIndex(x86_64::af)] = true;
        ret.read[getIndex(x86_64::zf)] = true;
        ret.read[getIndex(x86_64::sf)] = true;
        ret.read[getIndex(x86_64::df)] = true;
        ret.read[getIndex(x86_64::tf)] = true;
        ret.read[getIndex(x86_64::nt_)] = true;
      }
    }
    else{
      base = changeIfMMX(base);
      ret.read[getIndex(base)] = true;
    }
  }
  liveness_printf("Write Registers: \n"); 
  for (std::set<RegisterAST::Ptr>::const_iterator i = cur_written.begin(); 
       i != cur_written.end(); i++) {  
    MachRegister cur = (*i)->getID();
    if (cur.getArchitecture() == Arch_ppc64)
	cur = MachRegister((cur.val() & ~Arch_ppc64) | Arch_ppc32);
    liveness_printf("\t%s \n", cur.name().c_str());
    MachRegister base = cur.getBaseRegister();
    if (cur == x86::flags || cur == x86_64::flags){
      if (width == 4){
        ret.written[getIndex(x86::of)] = true;
        ret.written[getIndex(x86::cf)] = true;
        ret.written[getIndex(x86::pf)] = true;
        ret.written[getIndex(x86::af)] = true;
        ret.written[getIndex(x86::zf)] = true;
        ret.written[getIndex(x86::sf)] = true;
        ret.written[getIndex(x86::df)] = true;
        ret.written[getIndex(x86::tf)] = true;
        ret.written[getIndex(x86::nt_)] = true;
      }
      else {
        ret.written[getIndex(x86_64::of)] = true;
        ret.written[getIndex(x86_64::cf)] = true;
        ret.written[getIndex(x86_64::pf)] = true;
        ret.written[getIndex(x86_64::af)] = true;
        ret.written[getIndex(x86_64::zf)] = true;
        ret.written[getIndex(x86_64::sf)] = true;
        ret.written[getIndex(x86_64::df)] = true;
        ret.written[getIndex(x86_64::tf)] = true;
        ret.written[getIndex(x86_64::nt_)] = true;
      }
    }
    else{
      base = changeIfMMX(base);
      ret.written[getIndex(base)] = true;
      if ((cur != base && cur.size() < 4) || isMMX(base)) ret.read[getIndex(base)] = true;
    }
  }
  InsnCategory category = curInsn->getCategory();
  switch(category)
  {
  case c_CallInsn:
      // Call instructions not at the end of a block are thunks, which are not ABI-compliant.
      // So make conservative assumptions about what they may read (ABI) but don't assume they write anything.
      ret.read |= (abi->getCallReadRegisters());
      if(blk->lastInsnAddr() == a)
      {
          ret.written |= (abi->getCallWrittenRegisters());
      }
    break;
  case c_ReturnInsn:
    ret.read |= (abi->getReturnReadRegisters());
    // Nothing written implicitly by a return
    break;
  case c_BranchInsn:
    if(!curInsn->allowsFallThrough() && isExitBlock(blk))
    {
      //Tail call, union of call and return
      ret.read |= ((abi->getCallReadRegisters()) |
		   (abi->getReturnReadRegisters()));
      ret.written |= (abi->getCallWrittenRegisters());
    }
    break;
  default:
    {
      bool isInterrupt = false;
      bool isSyscall = false;


      if ((curInsn->getOperation().getID() == e_int) ||
	  (curInsn->getOperation().getID() == e_int3)) {
	isInterrupt = true;
      }
      static RegisterAST::Ptr gs(new RegisterAST(x86::gs));
      if (((curInsn->getOperation().getID() == e_call) &&
	   /*(curInsn()->getOperation().isRead(gs))) ||*/
	   (curInsn->getOperand(0).format(curInsn->getArch()) == "16")) ||
	  (curInsn->getOperation().getID() == e_syscall) || 
	  (curInsn->getOperation().getID() == e_int) || 
	  (curInsn->getOperation().getID() == power_op_sc)) {
	isSyscall = true;
      }

      if (curInsn->getOperation().getID() == power_op_svcs) {
	isSyscall = true;
      }
      if (isInterrupt || isSyscall) {
	ret.read |= (abi->getSyscallReadRegisters());
	ret.written |= (abi->getSyscallWrittenRegisters());
      }
    }
    break;
  }	  
  return ret;
}