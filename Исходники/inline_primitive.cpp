  static void float_op(MathOperation op, Class* klass,
      JITOperations& ops, Inliner& i)
  {
    i.use_send_for_failure();

    Value* self = i.recv();
    ops.check_class(self, klass, i.failure());

    Value* arg = i.arg(0);

    BasicBlock* not_float = ops.new_block();

    ops.check_class(arg, klass, not_float);

    // Float#*(Float)
    Value* farg  = ops.b().CreateBitCast(arg, ops.state()->ptr_type("Float"),
        "arg_float");

    Value* unboxed_rhs = ops.b().CreateLoad(
        ops.b().CreateConstGEP2_32(farg,  0, 1, "arg.value_pos"), "farg");

    BasicBlock* perform = ops.new_block();

    BasicBlock* unbox_block = ops.current_block();

    ops.b().CreateBr(perform);

    // Float#*(Fixnum)
    ops.set_block(not_float);

    ops.verify_guard(ops.check_if_fixnum(arg), i.failure());

    Value* fix_rhs = ops.b().CreateSIToFP(
        ops.fixnum_to_native(arg), unboxed_rhs->getType());

    BasicBlock* convert_block = ops.current_block();

    ops.b().CreateBr(perform);

    // perform operation

    perform->moveAfter(convert_block);
    ops.set_block(perform);

    PHINode* rhs = ops.b().CreatePHI(fix_rhs->getType(), "rhs");
    rhs->addIncoming(unboxed_rhs, unbox_block);
    rhs->addIncoming(fix_rhs, convert_block);

    Value* fself = ops.b().CreateBitCast(self, ops.state()->ptr_type("Float"),
        "self_float");

    Value* lhs = ops.b().CreateLoad(
        ops.b().CreateConstGEP2_32(fself, 0, 1, "self.value_pos"), "fself");

    Value* performed = 0;

    switch(op) {
    case cAdd:
      performed = ops.b().CreateFAdd(lhs, rhs, "float.add");
      break;
    case cSub:
      performed = ops.b().CreateFSub(lhs, rhs, "float.sub");
      break;
    case cMultiply:
      performed = ops.b().CreateFMul(lhs, rhs, "float.mul");
      break;
    case cDivide:
      performed = ops.b().CreateFDiv(lhs, rhs, "float.div");
      break;
    case cMod:
      performed = ops.b().CreateFRem(lhs, rhs, "float.mod");
      break;
    default:
      abort();
    }

    Signature sig(ops.state(), ops.state()->ptr_type("Float"));
    sig << "VM";

    Function* func = sig.function("rbx_float_allocate");
    func->setDoesNotAlias(0, true); // return value

    Value* call_args[] = { ops.vm() };
    CallInst* res = sig.call("rbx_float_allocate", call_args, 1, "result", ops.b());

    ops.b().CreateStore(
        performed,
        ops.b().CreateConstGEP2_32(res, 0, 1));

    i.exception_safe();
    i.set_result(ops.b().CreateBitCast(res, ops.ObjType));
  }