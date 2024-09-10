address TemplateInterpreterGenerator::generate_math_entry(AbstractInterpreter::MethodKind kind) {

  // rbx,: Method*
  // rcx: scratrch
  // r13: sender sp

  if (!InlineIntrinsics) return NULL; // Generate a vanilla entry

  address entry_point = __ pc();

  // These don't need a safepoint check because they aren't virtually
  // callable. We won't enter these intrinsics from compiled code.
  // If in the future we added an intrinsic which was virtually callable
  // we'd have to worry about how to safepoint so that this code is used.

  // mathematical functions inlined by compiler
  // (interpreter must provide identical implementation
  // in order to avoid monotonicity bugs when switching
  // from interpreter to compiler in the middle of some
  // computation)
  //
  // stack: [ ret adr ] <-- rsp
  //        [ lo(arg) ]
  //        [ hi(arg) ]
  //

  if (kind == Interpreter::java_lang_math_fmaD) {
    __ movdbl(xmm0, Address(rsp, wordSize));
    __ movdbl(xmm1, Address(rsp, 3 * wordSize));
    __ movdbl(xmm2, Address(rsp, 5 * wordSize));
    __ fmad(xmm0, xmm1, xmm2, xmm0);
  } else if (kind == Interpreter::java_lang_math_fmaF) {
    __ movflt(xmm0, Address(rsp, wordSize));
    __ movflt(xmm1, Address(rsp, 2 * wordSize));
    __ movflt(xmm2, Address(rsp, 3 * wordSize));
    __ fmaf(xmm0, xmm1, xmm2, xmm0);
  } else if (kind == Interpreter::java_lang_math_sqrt) {
    __ sqrtsd(xmm0, Address(rsp, wordSize));
  } else if (kind == Interpreter::java_lang_math_exp) {
    __ movdbl(xmm0, Address(rsp, wordSize));
    if (StubRoutines::dexp() != NULL) {
      __ call(RuntimeAddress(CAST_FROM_FN_PTR(address, StubRoutines::dexp())));
    } else {
      __ call_VM_leaf0(CAST_FROM_FN_PTR(address, SharedRuntime::dexp));
    }
  } else if (kind == Interpreter::java_lang_math_log) {
    __ movdbl(xmm0, Address(rsp, wordSize));
    if (StubRoutines::dlog() != NULL) {
      __ call(RuntimeAddress(CAST_FROM_FN_PTR(address, StubRoutines::dlog())));
    } else {
      __ call_VM_leaf0(CAST_FROM_FN_PTR(address, SharedRuntime::dlog));
    }
  } else if (kind == Interpreter::java_lang_math_log10) {
    __ movdbl(xmm0, Address(rsp, wordSize));
    if (StubRoutines::dlog10() != NULL) {
      __ call(RuntimeAddress(CAST_FROM_FN_PTR(address, StubRoutines::dlog10())));
    } else {
      __ call_VM_leaf0(CAST_FROM_FN_PTR(address, SharedRuntime::dlog10));
    }
  } else if (kind == Interpreter::java_lang_math_sin) {
    __ movdbl(xmm0, Address(rsp, wordSize));
    if (StubRoutines::dsin() != NULL) {
      __ call(RuntimeAddress(CAST_FROM_FN_PTR(address, StubRoutines::dsin())));
    } else {
      __ call_VM_leaf0(CAST_FROM_FN_PTR(address, SharedRuntime::dsin));
    }
  } else if (kind == Interpreter::java_lang_math_cos) {
    __ movdbl(xmm0, Address(rsp, wordSize));
    if (StubRoutines::dcos() != NULL) {
      __ call(RuntimeAddress(CAST_FROM_FN_PTR(address, StubRoutines::dcos())));
    } else {
      __ call_VM_leaf0(CAST_FROM_FN_PTR(address, SharedRuntime::dcos));
    }
  } else if (kind == Interpreter::java_lang_math_pow) {
    __ movdbl(xmm1, Address(rsp, wordSize));
    __ movdbl(xmm0, Address(rsp, 3 * wordSize));
    if (StubRoutines::dpow() != NULL) {
      __ call(RuntimeAddress(CAST_FROM_FN_PTR(address, StubRoutines::dpow())));
    } else {
      __ call_VM_leaf0(CAST_FROM_FN_PTR(address, SharedRuntime::dpow));
    }
  } else if (kind == Interpreter::java_lang_math_tan) {
    __ movdbl(xmm0, Address(rsp, wordSize));
    if (StubRoutines::dtan() != NULL) {
      __ call(RuntimeAddress(CAST_FROM_FN_PTR(address, StubRoutines::dtan())));
    } else {
      __ call_VM_leaf0(CAST_FROM_FN_PTR(address, SharedRuntime::dtan));
    }
  } else {
    __ fld_d(Address(rsp, wordSize));
    switch (kind) {
    case Interpreter::java_lang_math_abs:
      __ fabs();
      break;
    default:
      ShouldNotReachHere();
    }

    // return double result in xmm0 for interpreter and compilers.
    __ subptr(rsp, 2*wordSize);
    // Round to 64bit precision
    __ fstp_d(Address(rsp, 0));
    __ movdbl(xmm0, Address(rsp, 0));
    __ addptr(rsp, 2*wordSize);
  }


  __ pop(rax);
  __ mov(rsp, r13);
  __ jmp(rax);

  return entry_point;
}