vector<int> CglResouce::Build3DText(unsigned char *str)
{
    vector<int> result;
    result.clear();

    HDC hDC=wglGetCurrentDC();
    //设置当前字体 
    SelectObject(wglGetCurrentDC(),hFont); 

    DWORD dwChar;
    GLYPHMETRICSFLOAT pgmf[1];
    for(size_t i=0;i<strlen((char *)str);i++)
    {
        if(IsDBCSLeadByte(str[i]))
        {
            dwChar=(DWORD)((str[i]<<8)|str[i+1]);
            i++;
        }
        else 
            dwChar=str[i];

        result.push_back( glGenLists(1) );

        wglUseFontOutlines(hDC,dwChar,1,result.back(),0.0,0.1f,WGL_FONT_POLYGONS,pgmf);

    }
    return result;
}