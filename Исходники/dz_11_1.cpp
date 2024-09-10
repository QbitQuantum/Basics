bool plmin(const char *&ch)
{
    if (!mulDiv(ch))
        return false;
	while ((*ch == '+') || (*ch == '-'))
    {
        ch++;
		if ((*ch == '+') || (*ch == '-'))
			return false;
        if (!mulDiv(ch))
            return false;
    }
	return true;
}