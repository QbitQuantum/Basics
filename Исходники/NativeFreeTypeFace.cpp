/**
 * FreeType 用 ストリーム読み込み関数
 * @param stream	FT_Streamへのポインタ
 * @param offset	ストリーム先頭からのオフセット
 * @param buffer	格納先バッファ
 * @param count		読み出すバイト数
 * @return	何バイト読み込まれたか
 */
unsigned long tNativeFreeTypeFace::IoFunc(
    FT_Stream stream,
    unsigned long   offset,
    unsigned char*  buffer,
    unsigned long   count )
{
    if(count != 0)
    {
        tNativeFreeTypeFace * _this =
            static_cast<tNativeFreeTypeFace*>(stream->descriptor.pointer);
        DWORD result = GetFontData(_this->DC,
                                   _this->IsTTC ? TVP_TT_TABLE_ttcf : 0,
                                   offset, buffer, count);
        if(result == GDI_ERROR)
        {
            // エラー
            return 0;
        }
        return result;
    }
    return 0;
}