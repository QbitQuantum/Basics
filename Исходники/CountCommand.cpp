void CountCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();
	shared_ptr<Variable> var = vm.getVariable(parameters[1]);

	if (var->getTokenType() != IToken::TYPE_FACT_ARRAY && var->getTokenType() != IToken::TYPE_NUMBER_ARRAY && var->getTokenType() != IToken::TYPE_TEXT_ARRAY) 
	{
		throwCustomError("cannot count array " + var->getValue(), vm, supergeheimeToken);

		return;
	}
	shared_ptr<Array> array =  vm.getVariableArray(parameters[1]);

	if (array != nullptr) 
	{
		if (parameters.size() > 2) 
		{
			auto var = vm.getVariable(parameters[2]);

			if (var->getTokenType() == IToken::TYPE_NUMBER && var->getType() == VariableType::number) 
			{
				int index = atof(var->getValue().c_str());

				if (index < 0) 
				{
					throwCustomError("index is below zero.", vm, supergeheimeToken);
				}
				else if (index > (int)array->arraySizes.size() - 1) 
				{
					throwCustomError("index out of bounds range.", vm, supergeheimeToken);
				}
				else 
				{
					vm.setReturnValue(to_string(array->arraySizes.at(index)));
					vm.setReturnToken(IToken::TYPE_NUMBER);
				}
			}
			else 
			{
				throwCustomError("input is not a number.", vm, supergeheimeToken);
			}
		}
		else
		{
			vm.setReturnValue(to_string(array->variableArrayDictionary.size()));
			vm.setReturnToken(IToken::TYPE_NUMBER);
		}
	}
	else 
	{
		throwCustomError("array is not found.", vm, supergeheimeToken);
	}
}