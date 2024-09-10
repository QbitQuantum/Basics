VNGError VngoClear3D::init()
{
    strcpy(hwName,"Clear3D");

    if (clrInitLib(CLR_INIT_NORMAL | DEBUG_OFF))
    {
        term();
        return VNGO_INTERNAL_ERROR;
    }

    err = DirectDrawCreate(NULL, &dd, NULL);

    if (err != DD_OK)
    {
        term();
        return VNGO_INTERNAL_ERROR;
    }

    pContext = clrCreateContext();

    VertPool = (IvoryArena*)ivory_alloc(CLEAR3D_MAX_BATCH * 8 * sizeof (LL_Vert));
    if (VertPool == NULL)
    {
        term();
        return VNGO_MEMALLOC_ERROR;
    }

    ivory_arena_initialize(VertPool,CLEAR3D_MAX_BATCH * 8 * sizeof (LL_Vert));

    VgSystem.CL3DTx = new VngoTextureManager;
    if (VgSystem.CL3DTx == NULL)
    {
        term();
        return VNGO_MEMALLOC_ERROR;
    }
    VgSystem.CL3DTx->screen = this;

    type_info = SCREENTYPE_CLEAR3D;
    return VNGO_NO_ERROR;
}