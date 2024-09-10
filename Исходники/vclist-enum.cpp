void EnumVCM(bool bEnc)
{
	ICINFO info;
	char buf[256];

	for (int i = 0; ICInfo(ICTYPE_VIDEO, i, &info); i++)
	{
		HIC hic = ICOpen(ICTYPE_VIDEO, info.fccHandler, bEnc ? ICMODE_COMPRESS : ICMODE_DECOMPRESS);
		if (hic == NULL)
			continue;
		ICGetInfo(hic, &info, sizeof(info));
		ICClose(hic);
		wsprintf(buf, "VCM\t%d\t%S\t%c%c%c%c\n", bEnc, info.szDescription, FCC4PRINTF(info.fccHandler));
		printf("%s", buf);
	}
}