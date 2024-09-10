// FinishTransaction
Command*
TransformBox::FinishTransaction()
{
	Command* command = fCurrentCommand;
	if (fCurrentCommand) {
		fCurrentCommand->SetNewTransformation(Pivot(), Translation(),
			LocalRotation(), LocalXScale(), LocalYScale());
		fCurrentCommand = NULL;
	}
	return command;
}