bool string2Region(const wchar_t* _str , xuiRegion& region)
{
    static std::wstring str;
    str=L"";
    static std::wstring typeStr;
    typeStr = L"";
    int i = 0;
    for(i = 0 ; i < (int)wcslen(_str) ; i ++)
    {
        if(_str[i] == '[')
        {
            break;
        }
        if( _str[i] != ' ' && _str[i] != '\t')
        {
            typeStr.push_back(_str[i]);              
        }
    }

    for(; i < (int)wcslen(_str) ; i ++) 
    {
        if(_str[i] != ' ' && _str[i] != '\t') 
        {
            str.push_back(_str[i]);
        }
    }

    if(typeStr == L"rect" || typeStr == L"RECT" || typeStr == L"Rect")
    {
        stringToRect(str.c_str() , region.Rect2D() );
        region._type = xuiRegion::eRT_Rect;
    }
    else if(typeStr == L"DELTA" || typeStr == L"delta" || typeStr == L"Delta")
    {
        float x , y , w , h;
        swscanf(str.c_str(),L"[%f,%f,%f,%f]",&x,&y,&w,&h);
        region.Rect2D().x += x;
        region.Rect2D().y += y;
        region.Rect2D().w += (w - x) ;
        region.Rect2D().h += (h - y) ;
    }
    return true;
}