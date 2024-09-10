int   XComDoc_Compress(_xcd_int8* dest_buf,_xcd_int8* src_buf, int src_len,int compressRate)
{
	if(compressRate == XCOMDOC_COMPRESS_ENCRYPT)
		return XComDoc_Encrypot(dest_buf,src_buf,src_len);

    if(compressRate <= 10)
    {
#ifndef _WIN32_WCE
        uLong dest_len =  compressBound(src_len);
#else
        uLong dest_len =  2 * src_len + 12;
#endif
        compress2((Byte *)dest_buf,&dest_len,(Byte *)src_buf,src_len,compressRate - 1);
        return dest_len;
    }    
    else//大于10。用LZMA压缩
    {
        size_t dest_len = 2 * src_len + 12;
#ifdef _USE_LZMA_        
        struct _outProp
        {
            char _v;
            int  _disSize;
        }outProps;
        CompressLzma(dest_buf , &dest_len , src_buf ,src_len , (unsigned char*)&outProps , compressRate - 6 );
#else
        XEVOL_LOG(eXL_ERROR_FALT , "lzma not compiled, uncompressed failed\n");
        assert(0);
#endif
        return (int)dest_len;
    }
	
}