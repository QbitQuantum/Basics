TBool CInputDialog::KeyEventL(TInt aKeyCode)
{
	TBool keyResult = ETrue;
	switch(aKeyCode)
	{
	case KLeftSoftKey:
	case KOKKey:
		{
			TBuf<20> tBuf;
			this->iEdwin->GetText(tBuf);
			if(iIsNull)
			{
				MInputObserver& observer = iObserver;
				TInt commandType = iCommandType;
				CleanupSelf();
				observer.InputResponseEvent(commandType,tBuf);
			}
			else
			{
				if(tBuf.Length()==0)
				{
					this->SetInfo(iMainEngine.GetDesById(ETurkeyTextRes_InputNull));
				}
				else
				{
					MInputObserver& observer = iObserver;
					TInt commandType = iCommandType;
					CleanupSelf();
					observer.InputResponseEvent(commandType,tBuf);
				}
			}
		}
		break;

	case KRightSoftKey:
		{
			MInputObserver& observer = iObserver;
			CleanupSelf();
			observer.InputResponseEvent(-1,KNullDesC);
		}
		break;

	default:
		keyResult = EFalse;
		break;
	}
	return ETrue;
}