void C_Slider::Draw(SCREEN *surface,UI95_RECT *cliprect)
{
	UI95_RECT rect,s;

	if(!Ready()) return;

	if(GetFlags() & C_BIT_INVISIBLE)
		return;

	rect.left=GetX();
	rect.right=rect.left+GetW();
	rect.top=GetY();
	rect.bottom=rect.top+GetH();

//	if(BgImage_)
//	{
//		BgImage_->Blit(0,0,BgImage_->Header->w,BgImage_->Header->h,rect.left,rect.top,800,dest);
//		//Parent_->Blit(BgImage_->Image,&BgImage_->rect,&rect,GetFlags(),GetClient());
//	}
	if(Slider_)
	{
		s.left=0;
		s.top=0;
		s.right=Slider_->Header->w;
		s.bottom=Slider_->Header->h;

		rect.left=GetX()+SX_;
		rect.top=GetY()+SY_;
		rect.right=rect.left+Slider_->Header->w;
		rect.bottom=rect.top+Slider_->Header->h;

		if(GetFlags() & C_BIT_ABSOLUTE)
		{
			if(!Parent_->ClipToArea(&s,&rect,&Parent_->Area_))
				return;
		}
		else
		{
			rect.left+=Parent_->VX_[GetClient()];
			rect.top+=Parent_->VY_[GetClient()];
			rect.right+=Parent_->VX_[GetClient()];
			rect.bottom+=Parent_->VY_[GetClient()];
			if(!Parent_->ClipToArea(&s,&rect,&Parent_->ClientArea_[GetClient()]))
				return;
		}

		if(!Parent_->ClipToArea(&s,&rect,cliprect))
			return;

		rect.left+=Parent_->GetX();
		rect.top+=Parent_->GetY();
		rect.right+=Parent_->GetX();
		rect.bottom+=Parent_->GetY();

		Slider_->Blit(surface,s.left,s.top,s.right-s.left,s.bottom-s.top,rect.left,rect.top);
		if(MouseOver_ || (GetFlags() & C_BIT_FORCEMOUSEOVER))
			HighLite(surface,cliprect);
	}
}