BOOL ResonanceStudioDraw::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    // Added code for factory here--odd place to put it.
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
    if ( FAILED(hr)) return FALSE;

    ptheDrawTimeFrequencyGrid = new DrawTimeFrequencyGrid();

    if ( !ptheDrawTimeFrequencyGrid->Initialize( 10.0 ) )
        return FALSE;

    return TRUE;
}