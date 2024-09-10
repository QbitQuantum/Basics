int prString_FindRegexp(struct VMGlobals *g, int numArgsPushed)
{
	int err;

	PyrSlot *a = g->sp - 2; // source string
	PyrSlot *b = g->sp - 1; // pattern
	PyrSlot *c = g->sp;     // offset

	if (!isKindOfSlot(b, class_string) || (NotInt(c))) return errWrongType;
//	post("prString_FindRegexp\n");
	int maxfind = MAXREGEXFIND;
	int offset = slotRawInt(c);
	int stringsize = slotRawObject(a)->size + 1;
	int patternsize =  slotRawObject(b)->size + 1;
	char *string = (char*)malloc(slotRawObject(a)->size + 1);
	err = slotStrVal(a, string, slotRawObject(a)->size + 1);
	if (err){
		free(string);
		return err;
	}
	char *pattern = (char*)malloc(slotRawObject(b)->size + 1);
	err = slotStrVal(b, pattern, slotRawObject(b)->size + 1);
	if (err) return err;
	UParseError uerr;
	UErrorCode status = (UErrorCode)0;
	UChar *regexStr;
	UChar *ustring;

	regexStr =  (UChar*)malloc((patternsize)*sizeof(UChar));
	u_charsToUChars (pattern, regexStr, patternsize);

	ustring =  (UChar*)malloc((stringsize)*sizeof(UChar));
	u_charsToUChars (string+offset, ustring, stringsize-offset);


	unsigned flags = UREGEX_MULTILINE;
	int groupNumber = 0;
	SCRegExRegion * what;
	int indx = 0;
	int size = 0;

	URegularExpression *expression = uregex_open(regexStr, -1, flags, &uerr, &status);
	if(U_FAILURE(status)) goto nilout;

	 if(!U_FAILURE(status)) {
		uregex_setText(expression, ustring, -1, &status);
		what =  (SCRegExRegion*)malloc((maxfind)*sizeof(SCRegExRegion));
		for(int i=0; i< maxfind; i++)
		{
			SCRegExRegion range;
			range.matched = false;
			what[i] = range;
		}

		int32_t groups = uregex_groupCount(expression, &status) + 1;
		if(U_FAILURE(status)) goto nilout;
//		post("groups: %i\n", groups);
		while (uregex_findNext(expression, &status) && size<maxfind)
		{
			if(U_FAILURE(status)) return errNone;

			for(int i=0; i< groups; ++i){
				what[size].group = i;
				what[size].start = sc_clip(uregex_start(expression, i, &status), 0, stringsize) ;
				if(U_FAILURE(status)) goto nilout;
				what[size].end = sc_clip(uregex_end(expression, i, &status), 0, stringsize);
				what[size].matched = true;
//				post("index:%i, size:%i, start %i, end %i\n", i, size, what[i].start, what[i].end);
				size = indx++ + 1;
				if(U_FAILURE(status)) goto nilout;
			}
		}

		PyrObject *result_array = newPyrArray(g->gc, size, 0, true);
		result_array->size = 0;

		if (size>0) //(matched)
		{
			for (int i = 0; i < size; i++)
			{
				if (what[0].matched == false)
				{
					result_array->size++;
					SetNil(result_array->slots+i);
				}
				else
				{
					result_array->size++;

					int match_start =  what[i].start;
					int match_length = what[i].end -  what[i].start;
//					post("for i:%i, start %i, end %i\n",  i, what[i].start,  what[i].end);
//					char *match = (char*)malloc(match_length);
					char match[match_length];

					strncpy(match, string + offset + match_start, match_length);
					match[match_length] = 0;
					PyrObject *array = newPyrArray(g->gc, 2, 0, true);
					array->size = 2;
					SetInt(array->slots, match_start + offset);

					PyrObject *matched_string = (PyrObject*)newPyrString(g->gc, match, 0, true);
					SetObject(array->slots+1, matched_string);
					g->gc->GCWrite(matched_string, array->slots + 1);

					SetObject(result_array->slots + i, array);
					g->gc->GCWrite(array, result_array->slots + i);
				}
			}
		}
		else
		{
			SetNil(a);
		}
		 free(what);
		 free(pattern);
		 free(regexStr);
		 free(ustring);
		 free(string);
		SetObject(a, result_array);
		g->gc->GCWrite(result_array,a);
		//uregex_close(expression);
		return errNone;
	}

		nilout:
			free(string);
			free(what);
			free(pattern);
			free(regexStr);
			free(ustring);
			SetNil(a);
			return errNone;
}