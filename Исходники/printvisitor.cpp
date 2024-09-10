bool PrintVisitor::needParentheses(Expression* expression, OperatorChar op) {
	if (auto binaryOperatorExpression = dynamic_cast<BinaryOperatorExpression*>(expression)) {
		Operator inputOperator;
		Operator nodeOperator;
		if (mCalcEngine.getBinaryOperator(op, inputOperator)
			&& mCalcEngine.getBinaryOperator(binaryOperatorExpression->op(), nodeOperator)) {
			return inputOperator.precedence() > nodeOperator.precedence();
		}
	}

	return false;
}