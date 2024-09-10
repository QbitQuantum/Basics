void AddItemToArrayAtCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();
	string arrayIdentifier = vm.getFunctionParameterValueByKey(parameters[1]);
	shared_ptr<Variable> valueParam = vm.getVariable(parameters.at(parameters.size() - 1));
	vector<shared_ptr<Variable>> arrayIndexesVariables;
	vector<string> arrayIndexes;
	shared_ptr<Variable> param2;

	for (size_t i = 2; i < parameters.size()-1; i++)
	{
		arrayIndexesVariables.push_back(vm.getVariable(parameters[i]));
		arrayIndexes.push_back(vm.getVariable(parameters[i])->getValue());
	}
	list<string> functionParams = vm.getFunctionParametersByKey(parameters[1]);
	string value = valueParam->getValue();
	string arrayKey = functionParams.back();

	for (auto it : arrayIndexesVariables) 
	{
		if (it->getType() != VariableType::number) 
		{
			shared_ptr<Error> error = make_shared<Error>("you want to set an item from an array, but the index isn't a number", ".md", supergeheimeToken->getLineNumber(), supergeheimeToken->getPosition(), ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			vm.triggerRunFailure();
		}

		if (it->getValue() == "") 
		{
			shared_ptr<Error> error = make_shared<Error>("you want to add an item to an array, but the key is empty", ".md", supergeheimeToken->getLineNumber(), supergeheimeToken->getPosition(), ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			vm.triggerRunFailure();
		}
	}

	if (value != "" && arrayKey != "")
	{
		VariableType arrayType = valueParam->getType();
		pair<string, string> arrayTypes = vm.getVariableTypeSameAsArrayType(arrayIdentifier, valueParam->getTokenType());

		if (arrayTypes.first != arrayTypes.second)
		{
            Variable var1 = Variable(arrayTypes.second);
            Variable var2 = Variable(arrayTypes.first);
			throwCustomError("cannot add " + var2.getValue() + " to array", vm, supergeheimeToken);
		}
		else
		{
			for (string& item : functionParams)
			{
				vm.addItemToVariableArrayAt(item, arrayIndexes, valueParam);
			}
		}
	}
	else
	{
		if (value == "") 
		{
			shared_ptr<Error> error = make_shared<Error>("you want to add an item to an array, but the value is empty", ".md", supergeheimeToken->getLineNumber(), supergeheimeToken->getPosition(), ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			vm.triggerRunFailure(); 
		}
		else if (arrayKey == "") 
		{
			shared_ptr<Error> error = make_shared<Error>("you want to add an item to an array, but the array is undefined", ".md", supergeheimeToken->getLineNumber(), supergeheimeToken->getPosition(), ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			vm.triggerRunFailure();
		}
	}
}