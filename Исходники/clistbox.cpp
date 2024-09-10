BOOL C_ListBox::Process(long ID,short HitType)
{
	gSoundMgr->PlaySound(GetSound(HitType));
	switch(HitType)
	{
		case C_TYPE_LMOUSEUP:
			if(Callback_)
				(*Callback_)(ID,HitType,this);
			if(GetFlags() & C_BIT_ABSOLUTE)
				OpenWindow((short)(Parent_->GetX() + GetX()),
						   (short)(Parent_->GetY() + GetY() + GetH() + 1),
						   (short)GetW(), (short)GetListHeight());//! 
			else
				OpenWindow((short)(Parent_->GetX() + Parent_->VX_[GetClient()] + GetX()),
						   (short)(Parent_->GetY() + Parent_->VY_[GetClient()] + GetY() + GetH() + 1),
						   (short)GetW(),(short)GetListHeight());//! 
			return(TRUE);
			break;
	}
	return(FALSE);
}