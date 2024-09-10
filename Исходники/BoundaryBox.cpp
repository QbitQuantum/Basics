BYTE SquareBox::BoxIsCollide(BoundaryBox* other, const bool& back)
{
   if (other == NULL) return 10;

   if (other->type() == BBOX_SQUARE)
   {
      Rect oBox = dynamic_cast<SquareBox*>(other)->getBox();
      /*return !(rcBox.left > oBox.right ||
               rcBox.right < oBox.left ||
               rcBox.top > oBox.bottom ||
               rcBox.bottom < oBox.top);*/
	  Rect tmp;
	  if(IntersectRect(&tmp, &rcBox, &oBox))
	  {
		  if(rcBox.left < oBox.right && rcBox.right > oBox.right && back)
		  {
			  return 1;
		  }
		  else if(rcBox.right > oBox.left && rcBox.left < oBox.left && !back)
		  {
			  return 2;
		  } 
		  else if(rcBox.bottom > oBox.top && rcBox.top < oBox.top)
		  {
			  return 0;
		  }
		  else if(rcBox.top < oBox.bottom)
		  {
			  return 3;
		  }
	  }
	  else
		  return 4;
   }
   else if (other->type() == BBOX_CIRCLE)
   {
      /*return other->IsCollide(this);*/
	   return 0;
   }

   return 4;
}