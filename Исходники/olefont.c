static void test_font_events_disp(void)
{
    static const WCHAR nameW[] = {'N','a','m','e',0};
    static const WCHAR sizeW[] = {'S','i','z','e',0};
    static const WCHAR boldW[] = {'B','o','l','d',0};
    static const WCHAR italicW[] = {'I','t','a','l','i','c',0};
    static const WCHAR underlineW[] = {'U','n','d','e','r','l','i','n','e',0};
    static const WCHAR strikeW[] = {'S','t','r','i','k','e','t','h','r','o','u','g','h',0};
    static const WCHAR weightW[] = {'W','e','i','g','h','t',0};
    static const WCHAR charsetW[] = {'C','h','a','r','s','e','t',0};

    static const struct font_dispid font_dispids[] =
    {
        { DISPID_FONT_NAME, nameW },
        { DISPID_FONT_SIZE, sizeW },
        { DISPID_FONT_BOLD, boldW },
        { DISPID_FONT_ITALIC, italicW },
        { DISPID_FONT_UNDER, underlineW },
        { DISPID_FONT_STRIKE, strikeW },
        { DISPID_FONT_WEIGHT, weightW },
        { DISPID_FONT_CHARSET, charsetW }
    };

    IFont *pFont;
    IFont *pFont2;
    IConnectionPointContainer *pCPC;
    IConnectionPoint *pCP;
    FONTDESC fontdesc;
    HRESULT hr;
    DWORD dwCookie;
    IFontDisp *pFontDisp;
    DISPPARAMS dispparams;
    VARIANTARG vararg;
    INT i;

    fontdesc.cbSizeofstruct = sizeof(fontdesc);
    fontdesc.lpstrName = MSSansSerif_font;
    fontdesc.cySize.int64 = 12 * 10000; /* 12 pt */
    fontdesc.sWeight = FW_NORMAL;
    fontdesc.sCharset = 0;
    fontdesc.fItalic = FALSE;
    fontdesc.fUnderline = FALSE;
    fontdesc.fStrikethrough = FALSE;

    hr = pOleCreateFontIndirect(&fontdesc, &IID_IFont, (void **)&pFont);
    EXPECT_HR(hr, S_OK);

    hr = IFont_QueryInterface(pFont, &IID_IConnectionPointContainer, (void **)&pCPC);
    EXPECT_HR(hr, S_OK);

    hr = IConnectionPointContainer_FindConnectionPoint(pCPC, &IID_IFontEventsDisp, &pCP);
    EXPECT_HR(hr, S_OK);
    IConnectionPointContainer_Release(pCPC);

    hr = IConnectionPoint_Advise(pCP, (IUnknown *)&FontEventsDisp, &dwCookie);
    EXPECT_HR(hr, S_OK);
    IConnectionPoint_Release(pCP);

    fonteventsdisp_invoke_called = 0;
    fonteventsdisp_invoke_arg0 = NULL;
    hr = IFont_put_Bold(pFont, TRUE);
    EXPECT_HR(hr, S_OK);

    ok(fonteventsdisp_invoke_called == 1, "IFontEventDisp::Invoke wasn't called once\n");
    SysFreeString(fonteventsdisp_invoke_arg0);

    hr = IFont_QueryInterface(pFont, &IID_IFontDisp, (void **)&pFontDisp);
    EXPECT_HR(hr, S_OK);

    for (i = 0; i < ARRAY_SIZE(font_dispids); i++)
    {
        switch (font_dispids[i].dispid)
        {
        case DISPID_FONT_NAME:
        {
            static const WCHAR arialW[] = {'A','r','i','a','l',0};
            V_VT(&vararg) = VT_BSTR;
            V_BSTR(&vararg) = SysAllocString(arialW);
            break;
        }
        case DISPID_FONT_SIZE:
            V_VT(&vararg) = VT_CY;
            S(V_CY(&vararg)).Lo = 25;
            S(V_CY(&vararg)).Hi = 0;
            break;
        case DISPID_FONT_BOLD:
            V_VT(&vararg) = VT_BOOL;
            V_BOOL(&vararg) = VARIANT_FALSE;
            break;
        case DISPID_FONT_ITALIC:
        case DISPID_FONT_UNDER:
        case DISPID_FONT_STRIKE:
            V_VT(&vararg) = VT_BOOL;
            V_BOOL(&vararg) = VARIANT_TRUE;
            break;
        case DISPID_FONT_WEIGHT:
            V_VT(&vararg) = VT_I2;
            V_I2(&vararg) = FW_BLACK;
            break;
        case DISPID_FONT_CHARSET:
            V_VT(&vararg) = VT_I2;
            V_I2(&vararg) = 1;
            break;
        default:
            ;
        }

        dispparams.cNamedArgs = 0;
        dispparams.rgdispidNamedArgs = NULL;
        dispparams.cArgs = 1;
        dispparams.rgvarg = &vararg;
        fonteventsdisp_invoke_called = 0;
        hr = IFontDisp_Invoke(pFontDisp, font_dispids[i].dispid, &IID_NULL, 0, DISPATCH_PROPERTYPUT, &dispparams, NULL, NULL, NULL);
        ok(hr == S_OK, "dispid=%d, got 0x%08x\n", font_dispids[i].dispid, hr);
        ok(fonteventsdisp_invoke_called == 1, "dispid=%d, DISPID_FONT_CHANGED not called, got %d\n", font_dispids[i].dispid,
            fonteventsdisp_invoke_called);
        if (hr == S_OK)
        {
            ok(!lstrcmpW(font_dispids[i].name, fonteventsdisp_invoke_arg0), "dispid=%d, got %s, expected %s\n",
                font_dispids[i].dispid, wine_dbgstr_w(fonteventsdisp_invoke_arg0), wine_dbgstr_w(font_dispids[i].name));
            SysFreeString(fonteventsdisp_invoke_arg0);
        }
        VariantClear(&vararg);
    }

    IFontDisp_Release(pFontDisp);

    hr = IFont_Clone(pFont, &pFont2);
    EXPECT_HR(hr, S_OK);
    IFont_Release(pFont);

    /* this test shows that the notification routine isn't called again */
    fonteventsdisp_invoke_called = 0;
    hr = IFont_put_Bold(pFont2, FALSE);
    EXPECT_HR(hr, S_OK);
    ok(fonteventsdisp_invoke_called == 0, "got %d\n", fonteventsdisp_invoke_called);

    IFont_Release(pFont2);
}