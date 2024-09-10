static char
CharToVms(int c)
{
    if (c == PERIOD) {
	if (leaf_dot++)
	    c = '$';
    } else if (!isAlnum(c) && !strchr("_-", c)) {
	c = '$';
    }
    return (c);
}