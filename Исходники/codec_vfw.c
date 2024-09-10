static LBXGL_VidCodecCTX *vfw_begin_decompress(int fcc,
	PDGL_BMPInfoHeader *in, PDGL_BMPInfoHeader *out)
{
	LBXGL_VidCodecCTX *ctx;
	vfw_ctxinfo *info;
	int err;

	ctx=LBXGL_VidCodecCTX_New();
	info=gcalloc(sizeof(vfw_ctxinfo));
	ctx->data=info;

	info->ihead=malloc(sizeof(BITMAPINFOHEADER));
	memset(info->ihead, 0, sizeof(BITMAPINFOHEADER));
	info->ihead->biSize		= sizeof(BITMAPINFOHEADER);
	info->ihead->biWidth		= in->biWidth;
	info->ihead->biHeight		= in->biHeight;
	info->ihead->biPlanes		= in->biPlanes;
	info->ihead->biBitCount		= in->biBitCount;
	info->ihead->biCompression	= in->biCompression;
	info->ihead->biSizeImage	=
		in->biWidth*in->biHeight*in->biBitCount/8;

	info->ohead=malloc(sizeof(BITMAPINFOHEADER));
	memset(info->ohead, 0, sizeof(BITMAPINFOHEADER));
	info->ohead->biSize		= sizeof(BITMAPINFOHEADER);
	info->ohead->biWidth		= out->biWidth;
//	info->ohead->biHeight		= -out->biHeight;
	info->ohead->biHeight		= out->biHeight;
	info->ohead->biPlanes		= out->biPlanes;
	info->ohead->biBitCount		= out->biBitCount;
	info->ohead->biCompression	= out->biCompression;
	info->ihead->biSizeImage	=
		out->biWidth*out->biHeight*out->biBitCount/8;

	info->buffer=malloc(out->biWidth*out->biHeight*out->biBitCount/8);

//	info->hicd = ICOpen(ICTYPE_VIDEO, fcc, ICMODE_FASTDECOMPRESS);
	info->hicd = ICLocate(ICTYPE_VIDEO, fcc,
		info->ihead, info->ohead, ICMODE_FASTDECOMPRESS);
	if(!info->hicd)
	{
		printf("VFW: decompress %0.4s %0.4s: fail\n",
			&fcc, &in->biCompression);
		return(NULL);
	}
	printf("VFW: decompress %0.4s %0.4s: ok\n", &fcc, &in->biCompression);


	err=ICDecompressBegin(info->hicd, info->ihead, info->ohead);
	if(err)
	{
		printf("VFW: err %d, %0.4s %0.4s: fail\n", err,
			&fcc, &in->biCompression);
		return(NULL);
	}

	vfw_hicd[vfw_n_hicd++]=info->hicd;

	ctx->decompress_frame=&vfw_decompress_frame;

	return(ctx);
}