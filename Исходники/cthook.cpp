void C_TimerHook::Refresh()
{
	if(!Ready() || (GetFlags() & C_BIT_INVISIBLE))
		return;

	Parent_->SetUpdateRect(GetX(),GetY(),GetX()+GetW(),GetY()+GetH(),GetFlags(),GetClient());
	if(RefreshCallback_)
		(*RefreshCallback_)(GetID(),C_TYPE_TIMER,this);
}