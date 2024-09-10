void GetFromValueCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();
	string rValue = vm.getReturnValue();
	IToken rToken = vm.getReturnToken();

	if (&rValue != nullptr)
	{
		vm.setReturnValue("");
		vm.setReturnToken(IToken::ANY);

		if (vm.isAnIdentifier(rValue))
		{
			if (!vm.hasValueInFunctionParameters(parameters[1]))
			{
				vector<string> value = vm.getFunctionParametersByValue(rValue);

				if (value.size() > 0)
				{
					vm.setVariable(parameters[1], vm.getVariable(value.back())->getValue(), supergeheimeToken, rToken);
				}
				else
				{
					// Exception var undefined
					vm.setVariable(parameters[1], "", supergeheimeToken, rToken);
				}
				vm.setFunctionParameter(parameters[1], rValue);
			}
		}
		else
		{
			vm.setVariable(parameters[1], rValue, supergeheimeToken, rToken);
		}
	}
}