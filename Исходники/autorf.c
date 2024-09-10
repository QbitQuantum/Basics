ISRF isPPostive2(SACHEAD *hdr, float *trace, float interval)
{
	int pre, suf;
	int index ;
	index = rintf( (hdr->o - hdr->b) / (hdr->delta) );
	pre = rintf( (hdr->o - hdr->b - interval ) / (hdr->delta) );
	suf = rintf( (hdr->o - hdr->b + interval ) / (hdr->delta) );
	if( integf(trace, pre, suf, hdr->delta) > 0.0f &&  trace[index] < 1.0f )
		return GOOD;
	else
		return BAD;
}