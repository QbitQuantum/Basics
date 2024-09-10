// Quality comes in 0-100, while the zlib param needs to be 0-9 
CPLErr CompressZLIB(buf_mgr &dst, buf_mgr &src, const ILImage &img)
{
    if (Z_OK==compress2((Bytef *)dst.buffer,(uLongf *)&dst.size,
        (Bytef *)src.buffer,src.size,img.quality/10)) return CE_None;
    CPLError(CE_Failure,CPLE_AppDefined,"MRF: Error during zlib compression");
    return CE_Failure;
}