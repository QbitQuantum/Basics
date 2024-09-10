_EXPORT void SubjectToThread (BString &string)
{
// a regex that matches a non-ASCII UTF8 character:
#define U8C \
	"[\302-\337][\200-\277]" \
	"|\340[\302-\337][\200-\277]" \
	"|[\341-\357][\200-\277][\200-\277]" \
	"|\360[\220-\277][\200-\277][\200-\277]" \
	"|[\361-\367][\200-\277][\200-\277][\200-\277]" \
	"|\370[\210-\277][\200-\277][\200-\277][\200-\277]" \
	"|[\371-\373][\200-\277][\200-\277][\200-\277][\200-\277]" \
	"|\374[\204-\277][\200-\277][\200-\277][\200-\277][\200-\277]" \
	"|\375[\200-\277][\200-\277][\200-\277][\200-\277][\200-\277]"

#define PATTERN \
	"^ +" \
	"|^(\\[[^]]*\\])(\\<|  +| *(\\<(\\w|" U8C "){2,3} *(\\[[^\\]]*\\])? *:)+ *)" \
	"|^(  +| *(\\<(\\w|" U8C "){2,3} *(\\[[^\\]]*\\])? *:)+ *)" \
	"| *\\(fwd\\) *$"

	if (gRebuf == NULL && atomic_add(&gLocker,1) == 0)
	{
		// the idea is to compile the regexp once to speed up testing

		for (int i=0; i<256; ++i) gTranslation[i]=i;
		for (int i='a'; i<='z'; ++i) gTranslation[i]=toupper(i);

		gRe.translate = gTranslation;
		gRe.regs_allocated = REGS_FIXED;
		re_syntax_options = RE_SYNTAX_POSIX_EXTENDED;

		const char *pattern = PATTERN;
		// count subexpressions in PATTERN
		for (unsigned int i=0; pattern[i] != 0; ++i)
		{
			if (pattern[i] == '\\')
				++i;
			else if (pattern[i] == '(')
				++gNsub;
		}

		const char *err = re_compile_pattern(pattern,strlen(pattern),&gRe);
		if (err == NULL)
			gRebuf = &gRe;
		else
			fprintf(stderr, "Failed to compile the regex: %s\n", err);
	}
	else
	{
		int32 tries = 200;
		while (gRebuf == NULL && tries-- > 0)
			snooze(10000);
	}

	if (gRebuf)
	{
		struct re_registers regs;
		// can't be static if this function is to be thread-safe

		regs.num_regs = gNsub;
		regs.start = (regoff_t*)malloc(gNsub*sizeof(regoff_t));
		regs.end = (regoff_t*)malloc(gNsub*sizeof(regoff_t));

		for (int start=0;
		    (start=re_search(gRebuf, string.String(), string.Length(),
							0, string.Length(), &regs)) >= 0;
			)
		{
			//
			// we found something
			//

			// don't delete [bemaildaemon]...
			if (start == regs.start[1])
				start = regs.start[2];

			string.Remove(start,regs.end[0]-start);
			if (start) string.Insert(' ',1,start);
		}

		free(regs.start);
		free(regs.end);
	}

	// Finally remove leading and trailing space.  Some software, like
	// tm-edit 1.8, appends a space to the subject, which would break
	// threading if we left it in.
	trim_white_space(string);
}