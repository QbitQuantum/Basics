	//--------------------------------------------------------------------------------
    void TemplateSimplePro::setLv()
    {
        IText* pTextlv = getLayout()->getText("Text_Lv");
        assert(pTextlv);
        std::wstring Lv = pTextlv->getWidget()->getCaption();
        int curLv = _wtoi( Lv.c_str() );
        if ( curLv >= 100 )
            curLv = 10;
        else
            curLv += 1;
        wchar_t temp[10] = L"";
        Lv.clear();
        Lv = _itow(curLv, temp, 10);
        pTextlv->getWidget()->setCaption(Lv);
    }