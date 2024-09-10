/*!
  \internal
  Removes from internal read buffer \a nbytes.
  Returns true if successfull or false if there were not enought bytes in buffer to fullfill
  the request.
*/
bool cAsyncNetIOPrivate::consumeWriteBuf( Q_ULONG nbytes )
{
	if ( nbytes > wsize )
	{
		wsize = 0;
		return false;
	}

	if ( nbytes <= 0 || nbytes > wsize )
		return false;
	wsize -= nbytes;
	for ( ; ; )
	{
		QByteArray* a = ewba.first();
		if ( windex + nbytes >= a->size() )
		{
			nbytes -= a->size() - windex;
			ewba.remove();
			windex = 0;
			if ( nbytes == 0 )
				break;
		}
		else
		{
			windex += nbytes;
			break;
		}
	}
	return false;
}