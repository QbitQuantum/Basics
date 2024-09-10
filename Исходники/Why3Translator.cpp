void Why3Translator::visitIndentedUnlessBlock(Statement const& _statement)
{
	bool isBlock = !!dynamic_cast<Block const*>(&_statement);
	if (isBlock)
		newLine();
	else
		indent();
	_statement.accept(*this);
	if (isBlock)
		newLine();
	else
		unindent();
}