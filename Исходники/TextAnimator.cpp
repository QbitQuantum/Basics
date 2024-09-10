void TextAnimator::updateObject(TextAnimObj& obj)
{
	core::rect<s32> r = obj.pTextObj->getRect();
	video::SColor textCol;

	// offset the object as expected
	switch ( obj.dir )
	{
	case	TAD_VERTICAL:
		offsetRect(r, 0, obj.offsetPerTick);
		break;

	case	TAD_HORIZONTAL:
		offsetRect(r, obj.offsetPerTick, 0);
		break;
	}
	obj.pTextObj->setRect(r);

	// perform whatever effect we need to
	switch ( obj.effect )
	{
	case	TAE_NONE:
		break;

	case	TAE_FADEOUT:
		{
			if ( obj.ticksBeforeEffect <= obj.numTicksAnimated )
			{
				textCol = obj.pTextObj->getTextColor();
				textCol.setAlpha( textCol.getAlpha() + obj.effectDelta);
				obj.pTextObj->setTextColor(textCol);
			}
		}
		break;

	case	TAE_FADEIN:
		{
			if ( obj.ticksBeforeEffect >= obj.numTicksAnimated )
			{
				textCol = obj.pTextObj->getTextColor();
				textCol.setAlpha( textCol.getAlpha() + obj.effectDelta);
				obj.pTextObj->setTextColor(textCol);
			}
		}
		break;

	default:
		break;
	}

	obj.numTicksAnimated++;

}