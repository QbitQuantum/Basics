extern "C" unsigned int __cdecl _mbctoupper_l(
        unsigned int c,
        _locale_t plocinfo
        )
{
        unsigned char val[2];
        unsigned char ret[4];
        _LocaleUpdate _loc_update(plocinfo);

        if (c > 0x00FF)
        {

            val[0] = (c >> 8) & 0xFF;
            val[1] = c & 0xFF;

            if ( !_ismbblead_l(val[0], _loc_update.GetLocaleT()) )
                return c;


            if ( __acrt_LCMapStringA(
                        _loc_update.GetLocaleT(),
                        _loc_update.GetLocaleT()->mbcinfo->mblocalename,
                        LCMAP_UPPERCASE,
                        (const char *)val,
                        2,
                        (char *)ret,
                        2,
                        _loc_update.GetLocaleT()->mbcinfo->mbcodepage,
                        TRUE ) == 0 )
                return c;

            c = ret[1];
            c += ret[0] << 8;

            return c;


        }