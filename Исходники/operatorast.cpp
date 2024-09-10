std::shared_ptr<Type> BinaryOpExpressionAST::expressionType(const TypeChecker& checker) const {
	auto& boolTypes = checker.operators().binaryOpReturnTypes();

	if (boolTypes.count(mOp) > 0) {
		return boolTypes.at(mOp);
	} else {
		if (mOp == Operator('=')) {
			return checker.findType("Void");
		} else {
			return mLeftHandSide->expressionType(checker);
		}
	}
}