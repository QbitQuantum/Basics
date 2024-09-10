static void
update_requires_expression(BPackageResolvableExpression& expression,
	const ProvidesList& providesList)
{
	// find the best-matching provides
	BPackageResolvable* bestProvides = NULL;
	for (ProvidesList::const_iterator it = providesList.begin();
		it != providesList.end(); ++it) {
		BPackageResolvable* provides = *it;
		if (!expression.Matches(*provides))
			continue;

		if (bestProvides == NULL || bestProvides->Version().InitCheck() != B_OK
			|| (provides->Version().InitCheck() == B_OK
				&& provides->Version().Compare(bestProvides->Version()) > 0)) {
			bestProvides = provides;
		}
	}

	if (bestProvides == NULL || bestProvides->Version().InitCheck() != B_OK)
		return;

	// Update the expression. Enforce the minimum found version, if the requires
	// has no version requirement or also a minimum. Otherwise enforce the exact
	// version found.
	BPackageResolvableOperator newOperator = B_PACKAGE_RESOLVABLE_OP_EQUAL;
	switch (expression.Operator()) {
		case B_PACKAGE_RESOLVABLE_OP_LESS:
		case B_PACKAGE_RESOLVABLE_OP_LESS_EQUAL:
		case B_PACKAGE_RESOLVABLE_OP_EQUAL:
		case B_PACKAGE_RESOLVABLE_OP_NOT_EQUAL:
			break;
		case B_PACKAGE_RESOLVABLE_OP_GREATER_EQUAL:
		case B_PACKAGE_RESOLVABLE_OP_GREATER:
		case B_PACKAGE_RESOLVABLE_OP_ENUM_COUNT:
			newOperator = B_PACKAGE_RESOLVABLE_OP_GREATER_EQUAL;
			break;
	}

	expression.SetTo(expression.Name(), newOperator, bestProvides->Version());
}