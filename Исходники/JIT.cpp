void Jit::GetStateAndFlushAll(RegCacheState &state)
{
	gpr.GetState(state.gpr);
	fpr.GetState(state.fpr);
	FlushAll();
}