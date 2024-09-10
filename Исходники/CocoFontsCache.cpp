void CocoFontsCache::init()
{
    if(FT_Init_FreeType(&ftLibrary)) { trace("Could not initialize FreeType library!\n"); }
    else { trace("FreeType OK!\n"); }
}