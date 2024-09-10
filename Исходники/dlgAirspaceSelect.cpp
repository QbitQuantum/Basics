static void OnPaintListItem(WindowControl * Sender, LKSurface& Surface) {
    if (!Sender) {
        return;
    }

    unsigned int n = UpLimit - LowLimit;
    TCHAR sTmp[50];

    Surface.SetTextColor(RGB_BLACK);

    const int LineHeight = Sender->GetHeight();
    const int TextHeight = Surface.GetTextHeight(_T("dp"));

    const int TextPos = (LineHeight - TextHeight) / 2; // offset for text vertical center

    if (DrawListIndex < n) {

        const size_t i = (FullFlag) ? StrIndex[LowLimit + DrawListIndex] : (LowLimit + DrawListIndex);

        // Poco::Thread::sleep(100);

        const int width = Sender->GetWidth(); // total width

        const int w0 = LineHeight; // Picto Width
        const int w2 = Surface.GetTextWidth(TEXT(" 000km")); // distance Width
        _stprintf(sTmp, _T(" 000%s "), MsgToken(2179));
        const int w3 = Surface.GetTextWidth(sTmp); // bearing width

        const int w1 = width - w0 - 2*w2 - w3; // Max Name width

        // Draw Picto
        const RECT PictoRect = {0, 0, w0, LineHeight};

        AirspaceSelectInfo[i].airspace->DrawPicto(Surface, PictoRect);


        // Draw Name
        Surface.DrawTextClip(w0, TextPos, AirspaceSelectInfo[i].airspace->Name() , w1);

        LK_tcsncpy(sTmp,  CAirspaceManager::GetAirspaceTypeShortText(AirspaceSelectInfo[i].Type) , 4);
        const int w4 = Surface.GetTextWidth(sTmp);

        Surface.DrawTextClip(w1+w2, TextPos, sTmp,w4);

        // Draw Distance : right justified after waypoint Name
        _stprintf(sTmp, TEXT("%.0f%s"), AirspaceSelectInfo[i].Distance  , Units::GetDistanceName());
        const int x2 = width - w3 - Surface.GetTextWidth(sTmp);
        Surface.DrawText(x2, TextPos, sTmp);

        // Draw Bearing right justified after distance
        _stprintf(sTmp, TEXT("%d%s"), iround(AirspaceSelectInfo[i].Direction), MsgToken(2179));
        const int x3 = width - Surface.GetTextWidth(sTmp);
        Surface.DrawText(x3, TextPos, sTmp);
    } else {
        if (DrawListIndex == 0) {
            // LKTOKEN  _@M466_ = "No Match!"
            Surface.DrawText(IBLSCALE(2), TextPos, MsgToken(466));
        }
    }
}