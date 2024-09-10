//////////////////////////////////////////////////////////////////////////////
//
// CGargle::Clone
//
HRESULT CGargle::Clone(IMediaObjectInPlace **ppCloned) 
{
    if (!ppCloned)
        return E_POINTER;

    HRESULT hr = S_OK;
    CGargle * pNewGargle = new CComObject<CGargle>;
    if( !pNewGargle )
        hr = E_OUTOFMEMORY;

    hr = pNewGargle->Init();

    IMediaObject * pCloned = NULL;
    if( SUCCEEDED( hr ) )
    {
        IUnknown *pUnk;
        hr = pNewGargle->QueryInterface( IID_IUnknown, (void **) &pUnk );
        if( SUCCEEDED( hr ) )
        {
            hr = pUnk->QueryInterface( IID_IMediaObject, (void **) &pCloned );
            pUnk->Release();
        }
    }
    else
    {
        return hr;
    }

    //
    // Copy parameter control information
    //
    if (SUCCEEDED(hr))
        hr = pNewGargle->CopyParamsFromSource((CParamsManager *) this);

    // Copy current parameter values
    GargleFX params;
    if (SUCCEEDED(hr))
        hr = GetAllParameters(&params);

    if (SUCCEEDED(hr))
        hr = pNewGargle->SetAllParameters(&params);

    if (SUCCEEDED(hr))
    {
        // Copy the input and output types
        DMO_MEDIA_TYPE mt;
        DWORD cInputStreams = 0;
        DWORD cOutputStreams = 0;
        GetStreamCount(&cInputStreams, &cOutputStreams);

        for (DWORD i = 0; i < cInputStreams && SUCCEEDED(hr); ++i)
        {
            hr = GetInputCurrentType(i, &mt);
            if (hr == DMO_E_TYPE_NOT_SET)
            {
                hr = S_OK; // great, don't need to set the cloned DMO
            }
            else if (SUCCEEDED(hr))
            {
                hr = pCloned->SetInputType(i, &mt, 0);
                MoFreeMediaType( &mt );
            }
        }

        for (i = 0; i < cOutputStreams && SUCCEEDED(hr); ++i)
        {
            hr = GetOutputCurrentType(i, &mt);
            if (hr == DMO_E_TYPE_NOT_SET)
            {
                hr = S_OK; // great, don't need to set the cloned DMO
            }
            else if (SUCCEEDED(hr))
            {
                hr = pCloned->SetOutputType(i, &mt, 0);
                MoFreeMediaType( &mt );
            }
        }

        if (SUCCEEDED(hr))
            hr = pCloned->QueryInterface(IID_IMediaObjectInPlace, (void**)ppCloned);

        // Release the object's original ref.  If clone succeeded (made it through QI) then returned pointer
        // has one ref.  If we failed, refs drop to zero, freeing the object.
        pCloned->Release();
    }
    return hr;
}