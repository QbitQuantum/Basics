void CommonFunction::VectorTruncate(CCPoint &v,float maxLen)
{
	if (v.getLengthSq()>maxLen*maxLen)
	{
		v=v.normalize()*maxLen;
	}
}