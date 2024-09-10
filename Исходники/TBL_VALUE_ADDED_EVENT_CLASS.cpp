void	TBL_VALUE_ADDED_EVENT_CLASS::Set_BILLING_NBR(char	* sParam)
{
		if ( strlen(sParam)>32 ) 
			 throw TException( " Set_BILLING_NBR  string over 32!");
		strcpy(item.BILLING_NBR,sParam);
}