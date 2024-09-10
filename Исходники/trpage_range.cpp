bool trpgRangeTable::Read(trpgReadBuffer &buf)
{
	int32 numRange;
	trpgToken tok;
	int32 len;
	valid = false;

	try {
		buf.Get(numRange);
		if (numRange < 0) throw 1;
		for (int i=0;i<numRange;i++) {
			// Read in the individual range
			buf.GetToken(tok,len);
			if (tok != TRPG_RANGE) throw 1;
			buf.PushLimit(len);
			trpgRange range;
			bool status = range.Read(buf);
			buf.PopLimit();
			if (!status) throw 1;
			AddRange(range);
		}

		valid = true;
	}

	catch (...) {
		return false;
	}

	return isValid();
}