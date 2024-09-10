QMap<QString, QSharedPointer<types::TypeExpression>> LuaSemanticAnalyzer::variableTypes() const
{
	QMap<QString, QSharedPointer<qrtext::core::types::TypeExpression>> result = SemanticAnalyzer::variableTypes();
	for (const QString &identifier : mIntrinsicFunctions.keys()) {
		result.remove(identifier);
	}

	return result;
}