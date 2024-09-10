bool SdfRenderer::while_condition(QString str, int i)
{
	return (str[i] != 'L') && (str[i] != 'C') && (str[i] != 'M')
		&& (str[i] != 'Z') && (i != str.length());
}