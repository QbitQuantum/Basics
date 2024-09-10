//用空格或者'-'分割字符串,取后部分。
AnsiString GetStrName(AnsiString AStr)
{
    AnsiString IName;
    int IPos;
    IPos = AStr.Pos("-");
    if(IPos == 0)
    {
    	IPos = AStr.Pos(" ");
    	if(IPos == 0)
    	{
    		IName = "";
    	}
    	else
    	{
    		IName = AStr.SubString(IPos + 1, AStr.Length());
    	}	
    }
    else
    {
    	IName = AStr.SubString(IPos + 1,AStr.Length());
    }
    return IName;
}