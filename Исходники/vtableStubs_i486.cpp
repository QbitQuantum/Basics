// used by compiler only; may use only caller saved registers eax, ebx, ecx.
// edx holds first int arg, esi, edi, ebp are callee-save & must be preserved.
// Leave reciever in ecx; required behavior when +OptoArgsInRegisters
// is modifed to put first oop in ecx.
//
// NOTE: If this code is used by the C1, the receiver_location is always 0.
VtableStub* VtableStubs::create_vtable_stub(int vtable_index, int receiver_location) {
  const int i486_code_length = VtableStub::pd_code_size_limit(true);
  VtableStub* s = new(i486_code_length) VtableStub(true, vtable_index, receiver_location);
  ResourceMark rm;
  MacroAssembler* masm = new MacroAssembler(new CodeBuffer(s->entry_point(), i486_code_length));

#ifndef PRODUCT
#ifdef COMPILER2
  if (CountCompiledCalls) __ incl(Address((int)OptoRuntime::nof_megamorphic_calls_addr(), relocInfo::none));
#endif
#endif

  // get receiver (need to skip return address on top of stack)
#ifdef COMPILER1
  assert(receiver_location == 0, "receiver is always in ecx - no location info needed");
#else
  if( receiver_location < SharedInfo::stack0 ) {
    assert(receiver_location == ECX_num, "receiver expected in ecx");
  } else {
    __ movl(ecx, Address(esp, SharedInfo::reg2stack(OptoReg::Name(receiver_location)) * wordSize+wordSize/*skip return address*/));
  }
#endif
  // get receiver klass
  address npe_addr = __ pc();
  __ movl(eax, Address(ecx, oopDesc::klass_offset_in_bytes()));
  // compute entry offset (in words)
  int entry_offset = instanceKlass::vtable_start_offset() + vtable_index*vtableEntry::size();
#ifndef PRODUCT
  if (DebugVtables) { 
    Label L;
    // check offset vs vtable length
    __ cmpl(Address(eax, instanceKlass::vtable_length_offset()*wordSize), vtable_index*vtableEntry::size());
    __ jcc(Assembler::greater, L);
    __ movl(ebx, vtable_index);
    __ call_VM(noreg, CAST_FROM_FN_PTR(address, bad_compiled_vtable_index), ecx, ebx);
    __ bind(L);
  }
#endif // PRODUCT
  // load methodOop and target address
#ifdef COMPILER1
  __ movl(ebx, Address(eax, entry_offset*wordSize + vtableEntry::method_offset_in_bytes()));
  address ame_addr = __ pc();
  __ movl(edx, Address(ebx, methodOopDesc::from_compiled_code_entry_point_offset()));
  if (DebugVtables) {
    Label L;
    __ testl(edx, edx);
    __ jcc(Assembler::notZero, L);
    __ stop("Vtable entry is NULL");
    __ bind(L);
  }
  // eax: receiver klass
  // ebx: methodOop
  // ecx: receiver
  // edx: entry point
  __ jmp(edx);
#else
  __ movl(eax, Address(eax, entry_offset*wordSize + vtableEntry::method_offset_in_bytes()));
  address ame_addr = __ pc();
  __ movl(ebx, Address(eax, methodOopDesc::from_compiled_code_entry_point_offset()));  

  if (DebugVtables) {
    Label L;
    __ testl(ebx, ebx);
    __ jcc(Assembler::notZero, L);
    __ stop("Vtable entry is NULL");
    __ bind(L);
  } 


  // jump to target (either compiled code or c2iadapter)
  // eax: methodOop (in case we call c2iadapter)
  __ jmp(ebx);
#endif // COMPILER1

  masm->flush();
  s->set_exception_points(npe_addr, ame_addr);
  return s;
}