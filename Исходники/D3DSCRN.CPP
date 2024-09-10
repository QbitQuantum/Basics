VNGError VngoDirect3D::init(char *targetName)
{
    target = targetName;

    if (target != NULL)
    {
        if (DirectDrawEnumerate(FindDeviceCallback,(LPVOID)this)==DD_OK)
        {
            if (dd==NULL)
                err = DirectDrawCreate(&targetID, &dd, NULL);
            if (err != DD_OK)
            {
                if (dd != NULL)
                {
                    dd->Release();
                    dd = NULL;
                }
                err = DirectDrawCreate(NULL, &dd, NULL);
            }
        }
        else
        {
            if (dd==NULL)
                err = DirectDrawCreate(NULL, &dd, NULL);
        }
    }
    else
    {
        if (dd==NULL)
            err = DirectDrawCreate(NULL, &dd, NULL);
    }


    if (err != DD_OK)
        return VNGO_INTERNAL_ERROR;

    err = dd->QueryInterface(IID_IDirect3D2, (void**)&d3d);

    if (err != DD_OK)
        return VNGO_INTERNAL_ERROR;


    VgSystem->D3DTx = new VngoTextureManager;
    if (VgSystem->D3DTx)
    {
        VgSystem->D3DTx->screen = this;
    }
    else
    {
        term();
        return VNGO_INTERNAL_ERROR;
    }

    type_info = SCREENTYPE_D3D;
    return VNGO_NO_ERROR;
}