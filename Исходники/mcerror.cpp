void MCError::add(uint2 id, MCScriptPoint &sp)
{
	add(id, sp.getline(), sp.getpos(), sp.gettoken());
}