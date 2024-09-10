UT_uint32 PD_DocIterator::find(UT_TextIterator & text, UT_uint32 iLen, bool bForward)
{
	if(text.getStatus() != UTIter_OK)
	{
		m_status = UTIter_OutOfBounds;
		return 0;
	}
	
	UT_sint32 iInc = bForward ? 1 : -1;
	UT_uint32 iOrigPos = text.getPosition();
	
	while(getStatus() == UTIter_OK)
	{
		UT_UCS4Char What = text.getChar();
		
		// find the first character ...
		while(getStatus() == UTIter_OK && getChar() != What)
			(*this) += iInc;

		if(getStatus() != UTIter_OK) // we are past the end
			return 0; 

		UT_uint32 i = 1;
	
		while(i < iLen)
		{
			// cmp next pair
			text += iInc;
			if(text.getStatus() != UTIter_OK)
			{
				// there are fewer chars then we were led to believe
				m_status = UTIter_OutOfBounds;
				return 0;
			}
			
			What = text.getChar();
			

			(*this) += iInc;
			if(getStatus() != UTIter_OK) // we are past the end
				return 0;
			
			if(getChar() != What) //hard luck, try again
				break;

			// good, lets try the next pair
			i++;
		}

		if(i == iLen) // that was the last char, return ...
			return getPosition() - iLen + 1;

		// too bad, start over again
		UT_return_val_if_fail ( i < iLen,0 );
		(*this) += iInc;
		text.setPosition(iOrigPos);
	}

	UT_return_val_if_fail (getStatus() != UTIter_OK , 0);
	return 0;
}