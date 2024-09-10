static NOINLINE int UpdateParam(equalizer* p)
{
	if (p->Codec.In.Format.Type == PACKET_AUDIO)
	{
		int n;
		const eqfilter *src;
		eqfilter *dst;

		src = Band44100;
		dst = p->Filter;
		for (n=0;n<MAXFILTER;++n,++src,++dst)
		{
			dst->alpha0 = fix_mul(src->alpha,Pow(p->Eq[n])-FIXC(1.));
			dst->beta = ACCFAST_BSHIFT(src->beta);
			dst->gamma = ACCFAST_BSHIFT(src->gamma);
		}

		p->ScalePreamp = Pow(p->Amplify);
		UpdateScale(p);
	}
	return ERR_NONE;
}