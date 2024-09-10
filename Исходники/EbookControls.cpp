static void CreateEbookStyles()
{
    const int pageBorderX = 16;
    const int pageBorderY = 32;

    // only create styles once
    if (styleMainWnd)
        return;

    styleMainWnd = new Style();
    // TODO: support changing this color to gRenderCache.colorRange[1]
    //       or GetSysColor(COLOR_WINDOW) if gGlobalPrefs.useSysColors
    styleMainWnd->Set(Prop::AllocColorSolid(PropBgColor, COLOR_SEPIA));

    stylePage = new Style();
    stylePage->Set(Prop::AllocPadding(pageBorderY, pageBorderX, pageBorderY, pageBorderX));
    stylePage->Set(Prop::AllocColorSolid(PropBgColor, "transparent"));

    styleBtnNextPrevDefault = new Style(gStyleButtonDefault);
    styleBtnNextPrevDefault->SetBorderWidth(0.f);
    //styleBtnNextPrevDefault->Set(Prop::AllocPadding(1, 1, 1, 4));
    styleBtnNextPrevDefault->Set(Prop::AllocPadding(0, 8, 0, 8));
    styleBtnNextPrevDefault->Set(Prop::AllocWidth(PropStrokeWidth, 0.f));
    styleBtnNextPrevDefault->Set(Prop::AllocColorSolid(PropFill, "gray"));
    styleBtnNextPrevDefault->Set(Prop::AllocColorSolid(PropBgColor, "transparent"));
    styleBtnNextPrevDefault->Set(Prop::AllocAlign(PropVertAlign, ElAlignCenter));

    styleBtnNextPrevMouseOver = new Style(styleBtnNextPrevDefault);
    styleBtnNextPrevMouseOver->Set(Prop::AllocColorSolid(PropFill, "black"));

    styleStatus = new Style(gStyleButtonDefault);
    styleStatus->Set(Prop::AllocColorSolid(PropBgColor, COLOR_LIGHT_GRAY));
    styleStatus->Set(Prop::AllocColorSolid(PropColor, "black"));
    styleStatus->Set(Prop::AllocFontSize(8));
    styleStatus->Set(Prop::AllocFontWeight(FontStyleRegular));
    styleStatus->Set(Prop::AllocPadding(3, 0, 3, 0));
    styleStatus->SetBorderWidth(0);
    styleStatus->Set(Prop::AllocTextAlign(Align_Center));

    styleProgress = new Style();
    styleProgress->Set(Prop::AllocColorSolid(PropBgColor, COLOR_LIGHT_GRAY));
    styleProgress->Set(Prop::AllocColorSolid(PropColor, COLOR_LIGHT_BLUE));

    _onexit(DeleteEbookStyles);
}