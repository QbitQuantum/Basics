void C_Fill::Refresh()
{
	if(GetFlags() & C_BIT_INVISIBLE || Parent_ == NULL)
		return;

	F4CSECTIONHANDLE* Leave=UI_Enter(Parent_); 
	Parent_->SetUpdateRect(GetX(),GetY(),GetX()+GetW(),GetY()+GetH(),GetFlags(),GetClient());
	UI_Leave(Leave);
}