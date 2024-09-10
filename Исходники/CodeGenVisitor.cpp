void CodeGenVisitor::visit(FunctionCallExpression* e) {
	llvm::Function* cf = module_->getFunction(e->getId());
	if (!cf) {
		throw "function to call not found";
		return;
	}

	auto values = e->getValues()->getValues();
	if (cf->arg_size() != values.size()) {
		throw "argument size mismatch";
		return;
	}

	std::vector<llvm::Value*> args;
	auto iter = values.begin();
	auto end = values.end();
	for (; iter != end; ++iter) {
		Expression *expr = (*iter);
		expr->accept(this);
		if (!value_) {
			throw "error evaluating expression";
		}
		args.push_back(value_);
	}

	if (cf->getFunctionType()->getReturnType() == typeToLLVMType(Type::VOID)) {
		builder_->CreateCall(cf, args);
		// just handle void functions as if they returned 0
		value_ = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(0, 32, 10));
	} else {
		value_ = builder_->CreateCall(cf, args, "calltmp");
	}
}