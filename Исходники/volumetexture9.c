static HRESULT
NineVolumeTexture9_ctor( struct NineVolumeTexture9 *This,
                         struct NineUnknownParams *pParams,
                         UINT Width, UINT Height, UINT Depth, UINT Levels,
                         DWORD Usage,
                         D3DFORMAT Format,
                         D3DPOOL Pool,
                         HANDLE *pSharedHandle )
{
    struct pipe_resource *info = &This->base.base.info;
    struct pipe_screen *screen = pParams->device->screen;
    enum pipe_format pf;
    unsigned l;
    D3DVOLUME_DESC voldesc;
    HRESULT hr;

    DBG("This=%p pParams=%p Width=%u Height=%u Depth=%u Levels=%u "
        "Usage=%d Format=%d Pool=%d pSharedHandle=%p\n",
        This, pParams, Width, Height, Depth, Levels,
        Usage, Format, Pool, pSharedHandle);

    user_assert(Width && Height && Depth, D3DERR_INVALIDCALL);

    /* user_assert(!pSharedHandle || Pool == D3DPOOL_DEFAULT, D3DERR_INVALIDCALL); */
    user_assert(!pSharedHandle, D3DERR_INVALIDCALL); /* TODO */

    /* An IDirect3DVolume9 cannot be bound as a render target can it ? */
    user_assert(!(Usage & (D3DUSAGE_RENDERTARGET | D3DUSAGE_DEPTHSTENCIL)),
                D3DERR_INVALIDCALL);
    user_assert(!(Usage & D3DUSAGE_AUTOGENMIPMAP), D3DERR_INVALIDCALL);

    pf = d3d9_to_pipe_format_checked(screen, Format, PIPE_TEXTURE_3D, 0,
                                     PIPE_BIND_SAMPLER_VIEW, FALSE,
                                     Pool == D3DPOOL_SCRATCH);

    if (pf == PIPE_FORMAT_NONE)
        return D3DERR_INVALIDCALL;

    /* We support ATI1 and ATI2 hacks only for 2D and Cube textures */
    if (Format == D3DFMT_ATI1 || Format == D3DFMT_ATI2)
        return D3DERR_INVALIDCALL;

    if (compressed_format(Format)) {
        const unsigned w = util_format_get_blockwidth(pf);
        const unsigned h = util_format_get_blockheight(pf);
        /* Compressed formats are not compressed on depth component */
        user_assert(!(Width % w) && !(Height % h), D3DERR_INVALIDCALL);
    }

    info->screen = pParams->device->screen;
    info->target = PIPE_TEXTURE_3D;
    info->format = pf;
    info->width0 = Width;
    info->height0 = Height;
    info->depth0 = Depth;
    if (Levels)
        info->last_level = Levels - 1;
    else
        info->last_level = util_logbase2(MAX2(MAX2(Width, Height), Depth));
    info->array_size = 1;
    info->nr_samples = 0;
    info->nr_storage_samples = 0;
    info->bind = PIPE_BIND_SAMPLER_VIEW;
    info->usage = PIPE_USAGE_DEFAULT;
    info->flags = 0;

    if (Usage & D3DUSAGE_DYNAMIC) {
        info->usage = PIPE_USAGE_DYNAMIC;
    }
    if (Usage & D3DUSAGE_SOFTWAREPROCESSING)
        DBG("Application asked for Software Vertex Processing, "
            "but this is unimplemented\n");

    This->volumes = CALLOC(info->last_level + 1, sizeof(*This->volumes));
    if (!This->volumes)
        return E_OUTOFMEMORY;
    This->base.pstype = 3;

    hr = NineBaseTexture9_ctor(&This->base, pParams, NULL,
                               D3DRTYPE_VOLUMETEXTURE, Format, Pool, Usage);
    if (FAILED(hr))
        return hr;

    voldesc.Format = Format;
    voldesc.Type = D3DRTYPE_VOLUME;
    voldesc.Usage = Usage;
    voldesc.Pool = Pool;
    for (l = 0; l <= info->last_level; ++l) {
        voldesc.Width = u_minify(Width, l);
        voldesc.Height = u_minify(Height, l);
        voldesc.Depth = u_minify(Depth, l);

        hr = NineVolume9_new(This->base.base.base.device, NineUnknown(This),
                             This->base.base.resource, l,
                             &voldesc, &This->volumes[l]);
        if (FAILED(hr))
            return hr;
    }

    /* Textures start initially dirty */
    NineVolumeTexture9_AddDirtyBox(This, NULL);

    return D3D_OK;
}