void C_Tile::Refresh()
{
	if(GetFlags() & C_BIT_INVISIBLE || !Ready() || !Parent_)
		return;

	Parent_->SetUpdateRect(GetX(),GetY(),GetX()+GetW(),GetY()+GetH(),GetFlags(),GetClient());
}