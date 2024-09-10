bool CDirectDraw::InitDirectDraw ()
{
	if(DDinitialized)
		return true;

    dErr = DirectDrawCreate (NULL, &lpDD, NULL);
    if(FAILED(dErr))
        return false;

    dErr = lpDD -> CreateClipper (0, &lpDDClipper, NULL);
    if(FAILED(dErr))
        return false;

    dErr = lpDDClipper->SetHWnd (0, GUI.hWnd);
    if(FAILED(dErr))
        return false;

	DDinitialized = true;

    return (true);
}