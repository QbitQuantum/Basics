extern "C" int __cdecl _mbbtype_l(
        unsigned char c,
        int ctype,
        _locale_t plocinfo
        )
{
        _LocaleUpdate _loc_update(plocinfo);

        switch(ctype) {

            case(_MBC_LEAD):
                if ( _ismbbtrail_l(c, _loc_update.GetLocaleT()) )
                    return(_MBC_TRAIL);
                else
                    return(_MBC_ILLEGAL);

            case(_MBC_TRAIL):
            case(_MBC_SINGLE):
            case(_MBC_ILLEGAL):
            default:
                if ( _ismbblead_l(c, _loc_update.GetLocaleT()) )
                    return(_MBC_LEAD);
                else if (_ismbbprint_l( c, _loc_update.GetLocaleT()))
                    return(_MBC_SINGLE);
                else
                    return(_MBC_ILLEGAL);

        }

}