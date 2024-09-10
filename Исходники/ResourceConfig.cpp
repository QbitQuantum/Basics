int ResourceConfig::SafeReadColor(StringParser &theVal)
{
	theVal.SkipWhitespace();
	if(theVal.GetChar()=='(')
	{
		// special color (std or dec)
		std::string aType;
		theVal.IncrementPos();
		theVal.ReadString(aType);
		int aColor = 0;
		if(stricmp(aType.c_str(),"STD")==0) // standard color
		{
			EnsureComma(theVal);
			std::string aName;
			theVal.ReadString(aName); 
			const char *aPtr = aName.c_str();

			if(stricmp(aPtr,"3DDarkShadow")==0) aColor = ColorScheme::GetColorRef(StandardColor_3DDarkShadow); 
			else if(stricmp(aPtr,"3DFace")==0) aColor = ColorScheme::GetColorRef(StandardColor_3DFace); 
			else if(stricmp(aPtr,"3DHilight")==0) aColor = ColorScheme::GetColorRef(StandardColor_3DHilight); 
			else if(stricmp(aPtr,"3DShadow")==0) aColor = ColorScheme::GetColorRef(StandardColor_3DShadow); 
			else if(stricmp(aPtr,"Scrollbar")==0) aColor = ColorScheme::GetColorRef(StandardColor_Scrollbar); 
			else if(stricmp(aPtr,"ButtonText")==0) aColor = ColorScheme::GetColorRef(StandardColor_ButtonText); 
			else if(stricmp(aPtr,"GrayText")==0) aColor = ColorScheme::GetColorRef(StandardColor_GrayText); 
			else if(stricmp(aPtr,"Hilight")==0) aColor = ColorScheme::GetColorRef(StandardColor_Hilight); 
			else if(stricmp(aPtr,"HilightText")==0) aColor = ColorScheme::GetColorRef(StandardColor_HilightText); 
			else if(stricmp(aPtr,"ToolTipBack")==0) aColor = ColorScheme::GetColorRef(StandardColor_ToolTipBack); 
			else if(stricmp(aPtr,"ToolTipText")==0) aColor = ColorScheme::GetColorRef(StandardColor_ToolTipText); 
			else if(stricmp(aPtr,"MenuBack")==0) aColor = ColorScheme::GetColorRef(StandardColor_MenuBack); 
			else if(stricmp(aPtr,"MenuText")==0) aColor = ColorScheme::GetColorRef(StandardColor_MenuText); 
			else if(stricmp(aPtr,"Back")==0) aColor = ColorScheme::GetColorRef(StandardColor_Back); 
			else if(stricmp(aPtr,"Text")==0) aColor = ColorScheme::GetColorRef(StandardColor_Text); 
			else if(stricmp(aPtr,"Link")==0) aColor = ColorScheme::GetColorRef(StandardColor_Link); 
			else if(stricmp(aPtr,"LinkDown")==0) aColor = ColorScheme::GetColorRef(StandardColor_LinkDown); 
			else
				throw ConfigObjectException("Invalid standard color: " + aType);
		}
		else if(stricmp(aType.c_str(),"DEC")==0)
		{
			EnsureComma(theVal); 
			int r,g,b;
			theVal.ReadValue(r); EnsureComma(theVal);
			theVal.ReadValue(g); EnsureComma(theVal);
			theVal.ReadValue(b); 
			aColor = ((r&0xff)<<16) | ((g&0xff)<<8) | (b&0xff);
		}

		EnsureCloseParen(theVal);
		return aColor;
	}

	int aColor = 0;
	for(int i=0; i<6; i++)
	{
		aColor<<=4;
		int aDigit = ResourceConfig_GetHexDigit(theVal.GetChar());
		if(aDigit<0)
			throw ConfigObjectException("Invalid color specification.");

		aColor |= aDigit;
		theVal.IncrementPos();
	}
	
	return aColor;
}