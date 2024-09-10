void LocationDialog::displayCross(HWND hDlg, double latitude, double longitude)
{
    short xImage, yImage;
    HWND hMap = GetDlgItem(hDlg, IDC_MAP_PICTURE);

    HDC hDC = GetDC(hMap);
    if (hDC == NULL)
        return;
    int oRop = SetROP2(hDC, R2_XORPEN);
    HPEN pen = CreatePen(PS_SOLID, 3, CROSS_COLOR);
    HPEN oPen = (HPEN)SelectObject(hDC, pen);

    HRGN hrgn = CreateRectRgn(1, 1, mapWidth, mapHeight - 1);
    if (hrgn != NULL) {
        SelectClipRgn(hDC, hrgn);
        DeleteObject(hrgn);
    }
                                 
    // calculation of x-coordinate differs in sign from original map,
    //   which uses different convention for longitude.
    xImage = (int)((-longitude-minLongitude)*mapWidth/mapLongWidth);
    yImage = (int)((latitude-minLatitude)*mapHeight/mapLatHeight);
    if (crossVisible) {
        short xOld, yOld;
        
        xOld = (int) ((-crossLongitude-minLongitude)*mapWidth/mapLongWidth);
        yOld = (int) ((crossLatitude-minLatitude)*mapHeight/mapLatHeight);

        // erase.
        MoveToEx(hDC, xOld-CROSS_SIZE, mapHeight-yOld, NULL);
        LineTo(hDC, xOld+CROSS_SIZE, mapHeight-yOld);
        MoveToEx(hDC, xOld, mapHeight-yOld-CROSS_SIZE, NULL);
        LineTo(hDC, xOld,mapHeight-yOld+CROSS_SIZE);
    }
    MoveToEx(hDC, xImage-CROSS_SIZE, mapHeight-yImage, NULL);
    LineTo(hDC, xImage+CROSS_SIZE, mapHeight-yImage);
    MoveToEx(hDC, xImage, mapHeight-yImage-CROSS_SIZE, NULL);
    LineTo(hDC, xImage, mapHeight-yImage+CROSS_SIZE);
    crossVisible = TRUE;
    
    crossLatitude = latitude;
    crossLongitude = longitude;
    
    SetROP2(hDC, oRop);
    SelectObject(hDC, oPen);
    DeleteObject(pen);
    
    ReleaseDC(hMap, hDC);    
}