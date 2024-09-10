//
// 
// 
//
// CIwGameCommandIfVar Implementation
// 
// 
// 
//
bool CIwGameCommandIfVar::Execute(float dt)
{
	if (!IIwGameCommandExecutor::Execute(dt))
		return false;

	CIwGame* game = NULL;
	CIwGameScene* scene = NULL;
	CIwGameActor* actor = NULL;
	unsigned int class_hash = Program->getManager()->getParent()->getClassTypeHash();
	if (class_hash == CIwGameXomlNames::Game_Hash)
		game = (CIwGame*)Program->getManager()->getParent();
	else
	if (class_hash == CIwGameXomlNames::Scene_Hash)
		scene = (CIwGameScene*)Program->getManager()->getParent();

	if (game != NULL)
		scene = game->findScene(Params[3].getHash());

	IIwGameXomlResource* cont = (actor != NULL) ? (IIwGameXomlResource*)actor : (IIwGameXomlResource*)scene;
	CIwGameXomlVariable* var = CIwGameXomlVariable::GetVariable(Params[0], scene);
	if (var != NULL)
	{
		CIwGameString op = getParameter2(cont);
		op.ToLower();
		if (op == "==")
			ReturnValue = (int)var->checkCondition(CO_Equal, getParameter3(cont));
		else
		if (op == "!=")
			ReturnValue = (int)var->checkCondition(CO_NotEqual, getParameter3(cont));
		else
		if (op == "gt")
			ReturnValue = (int)var->checkCondition(CO_Greater, getParameter3(cont));
		else
		if (op == "lt")
			ReturnValue = (int)var->checkCondition(CO_Less, getParameter3(cont));
		else
		if (op == "gte")
			ReturnValue = (int)var->checkCondition(CO_GreaterEqual, getParameter3(cont));
		else
		if (op == "lte")
			ReturnValue = (int)var->checkCondition(CO_LessEqual, getParameter3(cont));
		else
		if (op == "and")
			ReturnValue = (int)var->checkCondition(CO_And, getParameter3(cont));
		else
			CIwGameError::LogError("Warning: IfVar command - operator invalid - ", op.c_str());
	}
	else
		CIwGameError::LogError("Warning: IfVar command - variable not found - ", Params[0].c_str());

	return false;
}