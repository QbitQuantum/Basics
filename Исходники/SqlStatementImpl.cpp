/**
Copies the content of a text column, identified by aColumnIndex, to the place refered by aDest parameter.

If the destination buffer is not big enough, the function will copy as much data as possible and will
return KErrOverflow.

@param aColumnIndex Column index
@param aDest Refers to the place where the column data will be copied.

@return KErrNone, if the function completes successfully,
                  otherwise one of the other system-wide error codes.

@panic SqlDb 5 Column index out of bounds.
@panic SqlDb 11 Statement cursor not positioned on a row
*/	
TInt CSqlStatementImpl::ColumnText(TInt aColumnIndex, TDes& aDest)
	{
	__ASSERT_ALWAYS((TUint)aColumnIndex < (TUint)iColumnCnt, __SQLPANIC(ESqlPanicBadColumnIndex));
	__ASSERT_ALWAYS(iState == CSqlStatementImpl::EAtRow, __SQLPANIC(ESqlPanicInvalidRow));
	iColumnValBufIt.MoveTo(aColumnIndex);		
	TInt err = KErrNone;
	//The text column value has not been transferred to the client side if its length is >= KSqlMaxDesLen characters.
	//In this case an additional call to the server is made to get the column value.
	if(!iColumnValBufIt.IsPresent())
		{
		if(iColumnValBufIt.Type() != ESqlText)
			{
			aDest.Zero();
			return err;
			}
		TPtr8 ptr(reinterpret_cast <TUint8*> (const_cast <TUint16*> (aDest.Ptr())), aDest.MaxLength() * sizeof(TUint16));
		err = iSqlStmtSession.ReadColumnValue(aColumnIndex, ptr);
		switch(err)
		    {
	        case KErrNone:
	        case KErrOverflow:
	            aDest.SetLength(ptr.Length() / sizeof(TUint16));
	            break;
	        default:
	            break;
		    }
		}
	else
		{
		TPtrC src = iColumnValBufIt.Text();
		TInt len = src.Length();
		if(len > aDest.MaxLength())
			{
			len = aDest.MaxLength();
			err = KErrOverflow;
			}
		aDest.Copy(src.Ptr(), len);
		}
	return err;
	}