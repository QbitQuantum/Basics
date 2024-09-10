void CodeGen_SPIR_Dev::add_kernel(Stmt stmt, std::string name, const std::vector<Argument> &args) {

    // Now deduce the types of the arguments to our function
    vector<llvm::Type *> arg_types(args.size()+1);
    for (size_t i = 0; i < args.size(); i++) {
        if (args[i].is_buffer) {
            arg_types[i] = llvm_type_of(UInt(8))->getPointerTo(1); // __global = addrspace(1)
        } else {
            arg_types[i] = llvm_type_of(args[i].type);
        }
    }
    // Add local (shared) memory buffer parameter.
    arg_types[args.size()] = llvm_type_of(UInt(8))->getPointerTo(3); // __local = addrspace(3)

    // Make our function
    function_name = name;
    FunctionType *func_t = FunctionType::get(void_t, arg_types, false);
    function = llvm::Function::Create(func_t, llvm::Function::ExternalLinkage, name, module);
    function->setCallingConv(llvm::CallingConv::SPIR_KERNEL);

    // Mark the buffer args as no alias
    for (size_t i = 0; i < args.size(); i++) {
        if (args[i].is_buffer) {
            function->setDoesNotAlias(i+1);
        }
    }
    // Mark the local memory as no alias (probably not necessary?)
    function->setDoesNotAlias(args.size());


    // Make the initial basic block
    entry_block = BasicBlock::Create(*context, "entry", function);
    builder->SetInsertPoint(entry_block);
    
    vector<Value *> kernel_arg_address_space = init_kernel_metadata(*context, "kernel_arg_addr_space");
    vector<Value *> kernel_arg_access_qual = init_kernel_metadata(*context, "kernel_arg_access_qual");
    vector<Value *> kernel_arg_type = init_kernel_metadata(*context, "kernel_arg_type");
    vector<Value *> kernel_arg_base_type = init_kernel_metadata(*context, "kernel_arg_base_type");
    vector<Value *> kernel_arg_type_qual = init_kernel_metadata(*context, "kernel_arg_type_qual");
    vector<Value *> kernel_arg_name = init_kernel_metadata(*context, "kernel_arg_name");
    
    // Put the arguments in the symbol table
    {
        llvm::Function::arg_iterator arg = function->arg_begin();
        for (std::vector<Argument>::const_iterator iter = args.begin();
            iter != args.end();
            ++iter, ++arg) {
            if (iter->is_buffer) {
                // HACK: codegen expects a load from foo to use base
                // address 'foo.host', so we store the device pointer
                // as foo.host in this scope.
                sym_push(iter->name + ".host", arg);
                
                kernel_arg_address_space.push_back(ConstantInt::get(i32, 1));
            } else {
                sym_push(iter->name, arg);

                kernel_arg_address_space.push_back(ConstantInt::get(i32, 0));
            }
            arg->setName(iter->name);

            kernel_arg_name.push_back(MDString::get(*context, iter->name));
            kernel_arg_access_qual.push_back(MDString::get(*context, "none"));
            kernel_arg_type_qual.push_back(MDString::get(*context, ""));
            // TODO: 'Type' isn't correct, but we don't have C to get the type name from...
            // This really shouldn't matter anyways. Everything SPIR needs is in the function
            // type, this metadata seems redundant.
            kernel_arg_type.push_back(MDString::get(*context, "type"));
            kernel_arg_base_type.push_back(MDString::get(*context, "type"));
        }
        arg->setName("shared");

        kernel_arg_address_space.push_back(ConstantInt::get(i32, 3)); // __local = addrspace(3)
        kernel_arg_name.push_back(MDString::get(*context, "shared"));
        kernel_arg_access_qual.push_back(MDString::get(*context, "none"));
        kernel_arg_type.push_back(MDString::get(*context, "char*"));
        kernel_arg_base_type.push_back(MDString::get(*context, "char*"));
        kernel_arg_type_qual.push_back(MDString::get(*context, ""));
    }

    // We won't end the entry block yet, because we'll want to add
    // some allocas to it later if there are local allocations. Start
    // a new block to put all the code.
    BasicBlock *body_block = BasicBlock::Create(*context, "body", function);
    builder->SetInsertPoint(body_block);

    debug(1) << "Generating llvm bitcode...\n";
    // Ok, we have a module, function, context, and a builder
    // pointing at a brand new basic block. We're good to go.
    stmt.accept(this);

    // Now we need to end the function
    builder->CreateRetVoid();

    // Make the entry block point to the body block
    builder->SetInsertPoint(entry_block);
    builder->CreateBr(body_block);

    // Add the nvvm annotation that it is a kernel function.
    Value *kernel_metadata[] =
    {
        function, 
        MDNode::get(*context, kernel_arg_address_space), 
        MDNode::get(*context, kernel_arg_access_qual), 
        MDNode::get(*context, kernel_arg_type), 
        MDNode::get(*context, kernel_arg_type_qual), 
        MDNode::get(*context, kernel_arg_name)
    };
    MDNode *mdNode = MDNode::get(*context, kernel_metadata);
    module->getOrInsertNamedMetadata("opencl.kernels")->addOperand(mdNode);


    // Now verify the function is ok
    verifyFunction(*function);

    // Finally, verify the module is ok
    verifyModule(*module);
    debug(2) << "Done generating llvm bitcode\n";
}