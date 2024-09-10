/**
* 恢复当前状态
*/
IRoleState *RoleStateMangager::popState()
{
	if (!_states.empty())
	{
		IRoleState *state = _states.back();
		if (state) state->Exit();
		_states.pop_back();
		if (_states.empty())
		{
			return NULL;
		}
		state = _states.back();
		if (state) state->Enter();
		return state;
	}
	else
	{
		return NULL;
	}
}