bool HostProgramTuning::VisitCallExpr(CallExpr *E) {

	if (E != NULL){
		QualType q = E->getType();
		const Type *t = q.getTypePtrOrNull();

		if(t != NULL)
		{
			FunctionDecl *func = E->getDirectCallee();
			
			if (!func) return false;
			ProcessFuncCall(func->getNameInfo().getName().getAsString(), E);
		}
	}


	return true;
}