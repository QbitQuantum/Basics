Handle< ::v8::Value> GlobalVariable::New(const Arguments& args)
{
    HandleScope scope;
    if (args.Length()) {
        REQ_LLVM_MODULE_ARG(0, module);
        REQ_LLVM_TYPE_ARG(1, type);
        REQ_UTF8_ARG(2, name);
        REQ_LLVM_CONST_ARG(3, init);

        GlobalVariable* val = new GlobalVariable(new ::llvm::GlobalVariable(*module, type, false, llvm::GlobalValue::InternalLinkage, init, *name));

        val->Wrap(args.This());
    }
    return args.This();
}