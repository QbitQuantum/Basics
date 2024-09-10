int common_substr_len(string str1, string str2)
{
	string::size_type minLen;
	if (str1.length() < str2.length()) 
	{
		minLen = str1.length();
	}
	else
	{
		minLen = str2.length();
		str1.swap(str2); //make str1 the shorter string
	}

	string::size_type maxSubstrLen = 0;
	string::size_type posBeg;
	string::size_type substrLen;
	string sub;
	for (posBeg = 0; posBeg < minLen; posBeg++) 
	{
		for (substrLen = minLen-posBeg; substrLen > 0; substrLen--) 
		{
			sub = str1.substr(posBeg, substrLen);
			if (str2.find(sub) != string::npos) 
			{
				if (maxSubstrLen < substrLen) 
				{
					maxSubstrLen = substrLen;
				}
				
				if (maxSubstrLen >= minLen-posBeg-1) 
				{
					return maxSubstrLen;
				}				
			}
		}		
	}
	return 0;
}