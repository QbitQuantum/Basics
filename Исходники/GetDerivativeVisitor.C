	Expression * GetDerivativeVisitor::visit(Variable * expression) {
		Expression * resultExpr = (Expression *)0;
		std::string varName = expression->getName();

		if (varName == derivativeVariableName) {
			resultExpr = new Number(1.0);
		} else {
			Expression * varExpr = (Expression *)0;
			Scope * scope = getCurrentScope();

			while (varExpr == 0 && scope != 0) {
				varExpr = scope->getExpressionByIdentifier(varName);
				scope = scope->getParentScope();
			}

			if (varExpr == 0) {
				throw UnknownIdentifierException(varName);
			}

			resultExpr = varExpr->accept(this);
		}

		return resultExpr;
	}