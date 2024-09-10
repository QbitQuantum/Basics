void IdentifierToReturnValueCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	vm.setReturnValue(parameters.at(1));
	vm.setReturnToken(node.getToken()->getSubType());
	vm.addIdentifer(parameters.at(1));

	vm.addArrayTypeToArrayTypes(node.getToken()->getText(), node.getToken()->getSubType());
}