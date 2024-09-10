	virtual bool operator()(int pos, const RichPara& para)// A++ bug here....
	{
		if(!IsNull(para.format.label)) {
			AddLinkRef(link, para.format.label);
			ref.FindAdd(para.format.label);
		}
		for(int i = 0; i < para.part.GetCount(); i++)
			if(para.part[i].IsText()) {
				const wchar *s = para.part[i].text;
				for(;;) {
					while(!IsLetter(*s) && !IsDigit(*s) && *s)
						s++;
					if(*s == '\0')
						break;
					StringBuffer sb;
					while(IsLetter(*s) || IsDigit(*s))
						sb.Cat(ToAscii(ToLower(*s++)));
					words.FindAdd(TopicWordIndex(sb));
				}
			}
		return false;
	}