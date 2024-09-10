long C_DrawList::CheckHotSpots(long relX,long relY)
{
	MAPICONLIST *item;
	C_HASHNODE *me;
	long curidx;
	long x,y,w,h;

	if(Flags_ & C_BIT_INVISIBLE || Parent_ == NULL)
		return(0);

	Last_=NULL;

	item=(MAPICONLIST*)Root_->GetFirst(&me,&curidx);
	while(item)
	{
		if(!(item->Flags & C_BIT_INVISIBLE) && item->Flags & C_BIT_ENABLED)
		{
			x=item->x+item->Icon->GetX();
			y=item->y+item->Icon->GetY();
			w=item->Icon->GetW();
			h=item->Icon->GetH();

			if(relX >= x && relY >= y && relX < (x+w) && relY < (y+h))
			{
				Last_=item;
				SetMenu(Last_->Owner->GetMenu());
			}
		}
		item=(MAPICONLIST*)Root_->GetNext(&me,&curidx);
	}
	if(Last_)
		return(GetID());
	return(0);
}