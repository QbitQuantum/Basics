void MinusMinusCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable = *vm.getVariable(parameters[1]);

	if (variable.getType() == VariableType::nulltype)
	{
		variable = *vm.getVariable(parameters[2]);
		parameters[1] = parameters[2];
	}

	if (variable.getType() != VariableType::nulltype && variable.getTokenType() == IToken::TYPE_NUMBER)
	{
		double number1 = atof(variable.getValue().c_str()) - 1;

		for (string & item : vm.getFunctionParametersByKey(parameters.at(1))) 
		{
			vm.setVariable(item, to_string(number1), supergeheimeToken, variable.getTokenType());
		}
		vm.setReturnValue(to_string(number1));
		vm.setReturnToken(variable.getTokenType());
	}
	else 
	{
		throwCustomError("cannot decrease an undefined variable.", vm, supergeheimeToken);
	}
}