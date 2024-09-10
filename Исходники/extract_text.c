//This function Extracts Text from a line that's found between two specified
//chunks of text 'ItemStart' and 'ItemEnd'
char *GenericExtractFromLine(char *Line, char *ItemName, char *ItemStart, char *ItemEnd, ListNode *Vars, int Flags)
{
char *ptr, *ptr2, *Token=NULL, *Item=NULL;
int GTF=0;

		if (Flags & EXTRACT_WITHIN_QUOTES) GTF=GETTOKEN_QUOTES;

		if (StrLen(ItemStart)) ptr=Gettoken(Line,ItemStart,&Token,0);
		else ptr=Line;

		ptr=Gettoken(ptr,ItemEnd,&Token,GTF);
		
		//check if the start string occurs more than once in the Token that we've grabbed
		if (StrLen(ItemStart)) ptr2=strstr(Token,ItemStart);
		else ptr2=NULL;

		while (ptr2)
		{
		ptr2+=StrLen(ItemStart);
		memmove(Token,ptr2,Token+StrLen(Token)-ptr2+1);
		//because of memmove we can strstr in Token again	
		ptr2=strstr(Token,ItemStart);
		}

		if (Flags & EXTRACT_INCLUDE_START) 
		{
			Item=MCopyStr(Item,ItemStart,Token,NULL);
			Token=CopyStr(Token,Item);
		}


    if (Flags & EXTRACT_DEQUOTE) Item=HTTPUnQuote(Item,Token);
    else if (Flags & EXTRACT_DEHTMLQUOTE) Item=HtmlDeQuote(Item,Token);
    else if (Flags & EXTRACT_DESLASHQUOTE) Item=DeQuoteStr(Item,Token);
    else Item=CopyStr(Item,Token);
		StripLeadingWhitespace(Item);
		StripTrailingWhitespace(Item);
		StripQuotes(Item);

		if (Flags & EXTRACT_NOSPACES)
		{
			ptr2=strchr(Item,' ');
			while (ptr2)
			{
				*ptr2='+';
				ptr2=strchr(ptr2,' ');
			}
		}

		//Do this without disturbing ptr, as we must return ptr
		ptr2=ItemName;
		if (Flags & EXTRACT_GUESSTYPE) 
		{
			Token=ItemCodeFromFileExtension(Token, ItemName, Item);
		}

		SetVar(Vars,ptr2,Item);

DestroyString(Token);
DestroyString(Item);

return(ptr);
}