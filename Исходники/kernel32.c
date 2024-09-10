void Win_FindNextFileA(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	ReturnValue->Val->Integer = FindNextFileA(Param[0]->Val->Pointer, Param[1]->Val->Pointer);
}