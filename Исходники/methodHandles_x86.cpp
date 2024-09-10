// Code generation
address MethodHandles::generate_method_handle_interpreter_entry(MacroAssembler* _masm,
                                                                vmIntrinsics::ID iid) {
  const bool not_for_compiler_entry = false;  // this is the interpreter entry
  assert(is_signature_polymorphic(iid), "expected invoke iid");
  if (iid == vmIntrinsics::_invokeGeneric ||
      iid == vmIntrinsics::_compiledLambdaForm) {
    // Perhaps surprisingly, the symbolic references visible to Java are not directly used.
    // They are linked to Java-generated adapters via MethodHandleNatives.linkMethod.
    // They all allow an appendix argument.
    __ hlt();           // empty stubs make SG sick
    return NULL;
  }

  // rsi/r13: sender SP (must preserve; see prepare_to_jump_from_interpreted)
  // rbx: Method*
  // rdx: argument locator (parameter slot count, added to rsp)
  // rcx: used as temp to hold mh or receiver
  // rax, rdi: garbage temps, blown away
  Register rdx_argp   = rdx;   // argument list ptr, live on error paths
  Register rax_temp   = rax;
  Register rcx_mh     = rcx;   // MH receiver; dies quickly and is recycled
  Register rbx_method = rbx;   // eventual target of this invocation

  // here's where control starts out:
  __ align(CodeEntryAlignment);
  address entry_point = __ pc();

  if (VerifyMethodHandles) {
    Label L;
    BLOCK_COMMENT("verify_intrinsic_id {");
    __ cmpb(Address(rbx_method, Method::intrinsic_id_offset_in_bytes()), (int) iid);
    __ jcc(Assembler::equal, L);
    if (iid == vmIntrinsics::_linkToVirtual ||
        iid == vmIntrinsics::_linkToSpecial) {
      // could do this for all kinds, but would explode assembly code size
      trace_method_handle(_masm, "bad Method*::intrinsic_id");
    }
    __ STOP("bad Method*::intrinsic_id");
    __ bind(L);
    BLOCK_COMMENT("} verify_intrinsic_id");
  }

  // First task:  Find out how big the argument list is.
  Address rdx_first_arg_addr;
  int ref_kind = signature_polymorphic_intrinsic_ref_kind(iid);
  assert(ref_kind != 0 || iid == vmIntrinsics::_invokeBasic, "must be _invokeBasic or a linkTo intrinsic");
  if (ref_kind == 0 || MethodHandles::ref_kind_has_receiver(ref_kind)) {
    __ movptr(rdx_argp, Address(rbx_method, Method::const_offset()));
    __ load_sized_value(rdx_argp,
                        Address(rdx_argp, ConstMethod::size_of_parameters_offset()),
                        sizeof(u2), /*is_signed*/ false);
    // assert(sizeof(u2) == sizeof(Method::_size_of_parameters), "");
    rdx_first_arg_addr = __ argument_address(rdx_argp, -1);
  } else {
    DEBUG_ONLY(rdx_argp = noreg);
  }

  if (!is_signature_polymorphic_static(iid)) {
    __ movptr(rcx_mh, rdx_first_arg_addr);
    DEBUG_ONLY(rdx_argp = noreg);
  }

  // rdx_first_arg_addr is live!

  trace_method_handle_interpreter_entry(_masm, iid);

  if (iid == vmIntrinsics::_invokeBasic) {
    generate_method_handle_dispatch(_masm, iid, rcx_mh, noreg, not_for_compiler_entry);

  } else {
    // Adjust argument list by popping the trailing MemberName argument.
    Register rcx_recv = noreg;
    if (MethodHandles::ref_kind_has_receiver(ref_kind)) {
      // Load the receiver (not the MH; the actual MemberName's receiver) up from the interpreter stack.
      __ movptr(rcx_recv = rcx, rdx_first_arg_addr);
    }
    DEBUG_ONLY(rdx_argp = noreg);
    Register rbx_member = rbx_method;  // MemberName ptr; incoming method ptr is dead now
    __ pop(rax_temp);           // return address
    __ pop(rbx_member);         // extract last argument
    __ push(rax_temp);          // re-push return address
    generate_method_handle_dispatch(_masm, iid, rcx_recv, rbx_member, not_for_compiler_entry);
  }

  return entry_point;
}