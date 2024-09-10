BGBBTJ_API LRESULT WINAPI DriverProc(
	DWORD_PTR dwDriverId, 
	HDRVR hDriver, 
	UINT uMsg, 
	LPARAM lParam1, 
	LPARAM lParam2) 
{
	ICOPEN * icopen;
	ICINFO *icinfo;
	BGBBTJ_VidCodecCTX *ctx;
	
	ctx=(BGBBTJ_VidCodecCTX *)dwDriverId;

//	BTJPG_DriverInit();
//	btjpg_printf("DriverProc: %d %p %p\n",
//		uMsg, (void *)lParam1, (void *)lParam2);

	switch(uMsg)
	{
	case DRV_LOAD:
	case DRV_FREE:
		return(DRVCNF_OK);

	case DRV_OPEN:
		btjpg_printf("DriverProc: DRV_OPEN: %d %p %p\n",
			uMsg, (void *)lParam1, (void *)lParam2);

		icopen=(ICOPEN *)lParam2;
		if(icopen && (icopen->fccType!=ICTYPE_VIDEO))
			{ return(DRVCNF_CANCEL); }

		if(icopen)
		{
			btjpg_printf("\tdwSize=%d\n", icopen->dwSize);
			btjpg_printf("\tfccType=0x%08X (%.4s)\n",
				icopen->fccType, &(icopen->fccType));
			btjpg_printf("\tfccHandler=0x%08X (%.4s)\n",
				icopen->fccHandler, &(icopen->fccHandler));
			btjpg_printf("\tdwVersion=0x%08X\n", icopen->dwVersion);
			btjpg_printf("\tdwFlags=0x%08X\n", icopen->dwFlags);
			btjpg_printf("\tdwError=0x%08X\n", icopen->dwError);
			btjpg_printf("\tpV1Reserved=%p\n", icopen->pV1Reserved);
			btjpg_printf("\tpV2Reserved=%p\n", icopen->pV2Reserved);
			btjpg_printf("\tdnDevNode=0x%08X\n", icopen->dnDevNode);
		}

		BTJPG_DriverInit();

//		ctx = malloc(sizeof(CODEC));
		ctx=BGBBTJ_VidCodecCTX_New();
		ctx->viFlags=0;

		if(!ctx)
		{
			if(icopen)
				{ icopen->dwError = ICERR_MEMORY; }
			return(0);
		}

//		ctx->viQuality=75*100;
		ctx->viQuality=100*100;

		if(icopen)
		{
			if((icopen->dwFlags&ICMODE_FASTCOMPRESS)==ICMODE_FASTCOMPRESS)
				{ ctx->viFlags|=BGBBTJ_VIFL_FASTENCODE; }
			if((icopen->dwFlags&ICMODE_FASTDECOMPRESS)==ICMODE_FASTDECOMPRESS)
				{ ctx->viFlags|=BGBBTJ_VIFL_FASTDECODE; }
			icopen->dwError=ICERR_OK;
		}
		return((LRESULT)ctx);

	case DRV_CLOSE :
//		compress_end(ctx);
//		decompress_end(ctx);
//		clean_dll_bindings(ctx);
//		status_destroy_always(&ctx->status);
//		free(ctx);
		BGBBTJ_VidCodecCTX_Destroy(ctx);
		BTJPG_DriverDeinit();
		return(DRVCNF_OK);

	case DRV_DISABLE:
	case DRV_ENABLE:
		return(DRVCNF_OK);

	case DRV_INSTALL:
	case DRV_REMOVE:
		return(DRVCNF_OK);

	case DRV_QUERYCONFIGURE:
	case DRV_CONFIGURE:
		return(DRVCNF_CANCEL);

	case ICM_GETINFO:
		btjpg_printf("ICM_GETINFO: %p %p\n",
			(void *)lParam1, (void *)lParam2);

		if (lParam1 && (lParam2>=sizeof(ICINFO)))
		{
			icinfo = (ICINFO *)lParam1;

			icinfo->fccType = ICTYPE_VIDEO;
			icinfo->fccHandler = RIFF_TAG_BTIC;
			icinfo->dwFlags =
				VIDCF_FASTTEMPORALC |
				VIDCF_FASTTEMPORALD |
				VIDCF_QUALITY |
				VIDCF_TEMPORAL |
				VIDCF_COMPRESSFRAMES;

			icinfo->dwVersion = 0;
#if !defined(ICVERSION)
#define ICVERSION       0x0104
#endif
			icinfo->dwVersionICM = ICVERSION;
			
//			wcscpy(icinfo->szName, XVID_NAME_L); 
//			wcscpy(icinfo->szDescription, XVID_DESC_L);

			wcscpy(icinfo->szName, L"BTIC"); 
			wcscpy(icinfo->szDescription, L"BGBTech Image Codec");
						
			return(lParam2);
		}

		return(0);
		
	case ICM_ABOUT :
		btjpg_printf("ICM_ABOUT: %p %p\n",
			(void *)lParam1, (void *)lParam2);
		return(ICERR_UNSUPPORTED);
//		DialogBoxParam(g_hInst,
//			MAKEINTRESOURCE(IDD_ABOUT),
//			(HWND)lParam1, about_proc, 0);
//		return(ICERR_OK);

	case ICM_CONFIGURE:
	case ICM_GETSTATE:
	case ICM_SETSTATE:
		btjpg_printf("ICM_CONFIGURE: %p %p\n",
			(void *)lParam1, (void *)lParam2);
		return(ICERR_UNSUPPORTED);

	case ICM_GET:
		btjpg_printf("ICM_GET: %p %p\n",
			(void *)lParam1, (void *)lParam2);
		return(ICERR_UNSUPPORTED);
	case ICM_SET:
		btjpg_printf("ICM_SET: %p %p\n",
			(void *)lParam1, (void *)lParam2);
		return(ICERR_UNSUPPORTED);

	case ICM_GETDEFAULTQUALITY:
		btjpg_printf("ICM_GETDEFAULTQUALITY: %p %p\n",
			(void *)lParam1, (void *)lParam2);
		*(DWORD *)lParam1=90*100;
		return(ICERR_OK);
	case ICM_GETQUALITY:
		btjpg_printf("ICM_GETQUALITY: %p %p\n",
			(void *)lParam1, (void *)lParam2);
		*(DWORD *)lParam1=ctx->viQuality;
		return(ICERR_OK);
	case ICM_SETQUALITY:
		btjpg_printf("ICM_SETQUALITY: %p %p\n",
			(void *)lParam1, (void *)lParam2);
		ctx->viQuality=*(DWORD *)lParam1;
		btjpg_printf("ICM_SETQUALITY: Q=%d%%\n",
			ctx->viQuality/100);
		return(ICERR_OK);

	case ICM_GETBUFFERSWANTED:
		btjpg_printf("ICM_GETBUFFERSWANTED: %p %p\n",
			(void *)lParam1, (void *)lParam2);
		ctx->viQuality=*(DWORD *)lParam1;
		return(ICERR_UNSUPPORTED);

	case ICM_GETDEFAULTKEYFRAMERATE:
		btjpg_printf("ICM_GETDEFAULTKEYFRAMERATE: %p %p\n",
			(void *)lParam1, (void *)lParam2);
		ctx->viQuality=*(DWORD *)lParam1;
		return(ICERR_UNSUPPORTED);

	case ICM_COMPRESS_QUERY:
		return(btjvfw_compress_query(ctx,
			(BITMAPINFO *)lParam1, (BITMAPINFO *)lParam2));
	case ICM_COMPRESS_GET_FORMAT:
		return(btjvfw_compress_get_format(ctx,
			(BITMAPINFO *)lParam1, (BITMAPINFO *)lParam2));
	case ICM_COMPRESS_GET_SIZE:
		return(btjvfw_compress_get_size(ctx,
			(BITMAPINFO *)lParam1, (BITMAPINFO *)lParam2));
	case ICM_COMPRESS_FRAMES_INFO:
		return(btjvfw_compress_frames_info(ctx,
			(ICCOMPRESSFRAMES *)lParam1));
	case ICM_COMPRESS_BEGIN:
		return(btjvfw_compress_begin(ctx,
			(BITMAPINFO *)lParam1, (BITMAPINFO *)lParam2));
	case ICM_COMPRESS_END:
		return(btjvfw_compress_end(ctx));
	case ICM_COMPRESS:
		return(btjvfw_compress(ctx, (ICCOMPRESS *)lParam1));

	case ICM_DECOMPRESS_QUERY:
		return(btjvfw_decompress_query(ctx,
			(BITMAPINFO *)lParam1, (BITMAPINFO *)lParam2));
	case ICM_DECOMPRESS_GET_FORMAT:
		return(btjvfw_decompress_get_format(ctx,
			(BITMAPINFO *)lParam1, (BITMAPINFO *)lParam2));
	case ICM_DECOMPRESS_BEGIN:
		return(btjvfw_decompress_begin(ctx,
			(BITMAPINFO *)lParam1, (BITMAPINFO *)lParam2));
	case ICM_DECOMPRESS_END:
		return(btjvfw_decompress_end(ctx));
	case ICM_DECOMPRESS:
		return(btjvfw_decompress(ctx, (ICDECOMPRESS *)lParam1));

	case ICM_DECOMPRESS_GET_PALETTE:
		btjpg_printf("ICM_DECOMPRESS_GET_PALETTE: %p %p\n",
			(void *)lParam1, (void *)lParam2);
		return(ICERR_UNSUPPORTED);
	case ICM_DECOMPRESS_SET_PALETTE:
		btjpg_printf("ICM_DECOMPRESS_SET_PALETTE: %p %p\n",
			(void *)lParam1, (void *)lParam2);
		return(ICERR_UNSUPPORTED);

	case ICM_DECOMPRESSEX_QUERY:
	case ICM_DECOMPRESSEX_BEGIN:
	case ICM_DECOMPRESSEX_END:
	case ICM_DECOMPRESSEX:
		btjpg_printf("ICM_DECOMPRESSEX: %p %p\n",
			(void *)lParam1, (void *)lParam2);
		return(ICERR_UNSUPPORTED);

    /* VFWEXT entry point */
    case ICM_USER+0x0fff :
		btjpg_printf("ICM_USER: %p %p\n",
			(void *)lParam1, (void *)lParam2);
        return(ICERR_UNSUPPORTED);

	default:
		btjpg_printf("Default: %d %p %p\n", uMsg,
			(void *)lParam1, (void *)lParam2);
		if(uMsg<DRV_USER)
		{
			return(DefDriverProc(dwDriverId,
				hDriver, uMsg, lParam1, lParam2));
		}
		else 
			{ return(ICERR_UNSUPPORTED); }
	}
}