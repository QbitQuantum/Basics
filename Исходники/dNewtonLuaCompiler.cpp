dNewtonLuaCompiler::dUserVariable dNewtonLuaCompiler::EmitLoadConstant(const dUserVariable& constName)
{
	dString localVariableAliasName(m_currentClosure->NewTemp());
	dCILInstr::dIntrisicType constType = dCILInstr::m_luaType;
	dCILInstr::dIntrisicType variableType = dCILInstr::m_luaType;
	int token = constName.GetToken();
	switch (token)
	{
		case _INTEGER:
			variableType = dCILInstr::m_int;
			constType = dCILInstr::m_constInt;
			break;
		default:
			dAssert(0);
	}

	dCILInstrMove* const move = new dCILInstrMove(*m_currentClosure, localVariableAliasName, dCILInstr::dArgType(variableType), constName.GetString(), dCILInstr::dArgType (constType));
	TRACE_INSTRUCTION(move);
	return dUserVariable(move);
}