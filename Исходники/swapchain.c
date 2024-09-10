HRESULT swapchain_init(IWineD3DSwapChainImpl *swapchain, WINED3DSURFTYPE surface_type,
        IWineD3DDeviceImpl *device, WINED3DPRESENT_PARAMETERS *present_parameters, IUnknown *parent)
{
    const struct wined3d_adapter *adapter = device->adapter;
    const struct wined3d_format_desc *format_desc;
    BOOL displaymode_set = FALSE;
    WINED3DDISPLAYMODE mode;
    RECT client_rect;
    HWND window = NULL;
#ifdef VBOX_WITH_WDDM
    IWineD3DSwapChainImpl *overridenSwapchain = NULL;
    HDC hDC = NULL;
#endif
    HRESULT hr;
    UINT i;

    if (present_parameters->BackBufferCount > WINED3DPRESENT_BACK_BUFFER_MAX)
    {
        ERR("The application requested %u back buffers, this is not supported.\n",
                present_parameters->BackBufferCount);
        return WINED3DERR_INVALIDCALL;
    }

    if (present_parameters->BackBufferCount > 1)
    {
        FIXME("The application requested more than one back buffer, this is not properly supported.\n"
                "Please configure the application to use double buffering (1 back buffer) if possible.\n");
    }

    switch (surface_type)
    {
        case SURFACE_GDI:
            swapchain->lpVtbl = &IWineGDISwapChain_Vtbl;
            break;

        case SURFACE_OPENGL:
            swapchain->lpVtbl = &IWineD3DSwapChain_Vtbl;
            break;

        case SURFACE_UNKNOWN:
            FIXME("Caller tried to create a SURFACE_UNKNOWN swapchain.\n");
            return WINED3DERR_INVALIDCALL;
    }

#ifdef VBOX_WITH_WDDM
    if (present_parameters->hDeviceWindow)
    {
        overridenSwapchain = swapchain_find(device, present_parameters->hDeviceWindow);
        if (!overridenSwapchain)
        {
            ERR("invalid window handle supplied");
            return E_FAIL;
        }

        window = overridenSwapchain->win_handle;
        hDC = overridenSwapchain->hDC;
    }
    else
    {
        hr = VBoxExtWndCreate(present_parameters->BackBufferWidth, present_parameters->BackBufferHeight, &window, &hDC);
        if (FAILED(hr))
        {
            ERR("VBoxExtWndCreate failed, hr 0x%x", hr);
            return hr;
        }
    }
    Assert(window);
    Assert(hDC);
    present_parameters->hDeviceWindow = window;
#else
    window = present_parameters->hDeviceWindow ? present_parameters->hDeviceWindow : device->createParms.hFocusWindow;
#endif

    swapchain->device = device;
    swapchain->parent = parent;
    swapchain->ref = 1;
    swapchain->win_handle = window;
#ifndef VBOX_WITH_WDDM
    swapchain->device_window = window;
#else
    Assert(window);
    swapchain->hDC = hDC;
    swapchain->presentRt = NULL;
#endif

    if (!present_parameters->Windowed && window)
    {
        swapchain_setup_fullscreen_window(swapchain, present_parameters->BackBufferWidth,
                present_parameters->BackBufferHeight);
    }

    IWineD3D_GetAdapterDisplayMode(device->wined3d, adapter->ordinal, &mode);
    swapchain->orig_width = mode.Width;
    swapchain->orig_height = mode.Height;
    swapchain->orig_fmt = mode.Format;
    format_desc = getFormatDescEntry(mode.Format, &adapter->gl_info);

#ifndef VBOX_WITH_WDDM
    GetClientRect(window, &client_rect);
#else
    client_rect.left = 0;
    client_rect.top = 0;
    client_rect.right = present_parameters->BackBufferWidth;
    client_rect.bottom = present_parameters->BackBufferHeight;
#endif
    if (present_parameters->Windowed
            && (!present_parameters->BackBufferWidth || !present_parameters->BackBufferHeight
            || present_parameters->BackBufferFormat == WINED3DFMT_UNKNOWN))
    {

        if (!present_parameters->BackBufferWidth)
        {
            present_parameters->BackBufferWidth = client_rect.right;
            TRACE("Updating width to %u.\n", present_parameters->BackBufferWidth);
        }

        if (!present_parameters->BackBufferHeight)
        {
            present_parameters->BackBufferHeight = client_rect.bottom;
            TRACE("Updating height to %u.\n", present_parameters->BackBufferHeight);
        }

        if (present_parameters->BackBufferFormat == WINED3DFMT_UNKNOWN)
        {
            present_parameters->BackBufferFormat = swapchain->orig_fmt;
            TRACE("Updating format to %s.\n", debug_d3dformat(swapchain->orig_fmt));
        }
    }
    swapchain->presentParms = *present_parameters;

    if (wined3d_settings.offscreen_rendering_mode == ORM_FBO
            && present_parameters->BackBufferCount
            && (present_parameters->BackBufferWidth != client_rect.right
            || present_parameters->BackBufferHeight != client_rect.bottom))
    {
        TRACE("Rendering to FBO. Backbuffer %ux%u, window %ux%u.\n",
                present_parameters->BackBufferWidth,
                present_parameters->BackBufferHeight,
                client_rect.right, client_rect.bottom);
        swapchain->render_to_fbo = TRUE;
    }

    TRACE("Creating front buffer.\n");
    hr = IWineD3DDeviceParent_CreateRenderTarget(device->device_parent, parent,
            swapchain->presentParms.BackBufferWidth, swapchain->presentParms.BackBufferHeight,
            swapchain->presentParms.BackBufferFormat, swapchain->presentParms.MultiSampleType,
            swapchain->presentParms.MultiSampleQuality, TRUE /* Lockable */, &swapchain->frontBuffer);
    if (FAILED(hr))
    {
        WARN("Failed to create front buffer, hr %#x.\n", hr);
        goto err;
    }

    IWineD3DSurface_SetContainer(swapchain->frontBuffer, (IWineD3DBase *)swapchain);
    ((IWineD3DSurfaceImpl *)swapchain->frontBuffer)->Flags |= SFLAG_SWAPCHAIN;
    if (surface_type == SURFACE_OPENGL)
    {
        IWineD3DSurface_ModifyLocation(swapchain->frontBuffer, SFLAG_INDRAWABLE, TRUE);
    }

    /* MSDN says we're only allowed a single fullscreen swapchain per device,
     * so we should really check to see if there is a fullscreen swapchain
     * already. Does a single head count as full screen? */

    if (!present_parameters->Windowed)
    {
        WINED3DDISPLAYMODE mode;

        /* Change the display settings */
        mode.Width = present_parameters->BackBufferWidth;
        mode.Height = present_parameters->BackBufferHeight;
        mode.Format = present_parameters->BackBufferFormat;
        mode.RefreshRate = present_parameters->FullScreen_RefreshRateInHz;

        hr = IWineD3DDevice_SetDisplayMode((IWineD3DDevice *)device, 0, &mode);
        if (FAILED(hr))
        {
            WARN("Failed to set display mode, hr %#x.\n", hr);
            goto err;
        }
        displaymode_set = TRUE;
    }

#ifndef VBOX_WITH_WDDM
    swapchain->context = HeapAlloc(GetProcessHeap(), 0, sizeof(swapchain->context));
    if (!swapchain->context)
    {
        ERR("Failed to create the context array.\n");
        hr = E_OUTOFMEMORY;
        goto err;
    }
    swapchain->num_contexts = 1;
#endif

    if (surface_type == SURFACE_OPENGL)
    {
#ifdef VBOX_WITH_WDDM
        struct wined3d_context * swapchainContext;
#endif
        const struct wined3d_gl_info *gl_info = &device->adapter->gl_info;

        /* In WGL both color, depth and stencil are features of a pixel format. In case of D3D they are separate.
         * You are able to add a depth + stencil surface at a later stage when you need it.
         * In order to support this properly in WineD3D we need the ability to recreate the opengl context and
         * drawable when this is required. This is very tricky as we need to reapply ALL opengl states for the new
         * context, need torecreate shaders, textures and other resources.
         *
         * The context manager already takes care of the state problem and for the other tasks code from Reset
         * can be used. These changes are way to risky during the 1.0 code freeze which is taking place right now.
         * Likely a lot of other new bugs will be exposed. For that reason request a depth stencil surface all the
         * time. It can cause a slight performance hit but fixes a lot of regressions. A fixme reminds of that this
         * issue needs to be fixed. */
        if (!present_parameters->EnableAutoDepthStencil
                || swapchain->presentParms.AutoDepthStencilFormat != WINED3DFMT_D24_UNORM_S8_UINT)
        {
            FIXME("Add OpenGL context recreation support to context_validate_onscreen_formats\n");
        }
        swapchain->ds_format = getFormatDescEntry(WINED3DFMT_D24_UNORM_S8_UINT, gl_info);

#ifdef VBOX_WITH_WDDM
        swapchainContext = context_find_create(device, swapchain, (IWineD3DSurfaceImpl *)swapchain->frontBuffer,
                swapchain->ds_format);
        if (!swapchainContext)
#else
        swapchain->context[0] = context_create(swapchain, (IWineD3DSurfaceImpl *)swapchain->frontBuffer,
                swapchain->ds_format);
        if (!swapchain->context[0])
#endif
        {
            WARN("Failed to create context.\n");
            hr = WINED3DERR_NOTAVAILABLE;
            goto err;
        }
#ifdef VBOX_WITH_WDDM
        context_release(swapchainContext);
#else
        context_release(swapchain->context[0]);
#endif
    }
    else
    {
#ifndef VBOX_WITH_WDDM
        swapchain->context[0] = NULL;
#endif
    }

    if (swapchain->presentParms.BackBufferCount > 0)
    {
        swapchain->backBuffer = HeapAlloc(GetProcessHeap(), 0,
                sizeof(*swapchain->backBuffer) * swapchain->presentParms.BackBufferCount);
        if (!swapchain->backBuffer)
        {
            ERR("Failed to allocate backbuffer array memory.\n");
            hr = E_OUTOFMEMORY;
            goto err;
        }

        for (i = 0; i < swapchain->presentParms.BackBufferCount; ++i)
        {
            TRACE("Creating back buffer %u.\n", i);
            hr = IWineD3DDeviceParent_CreateRenderTarget(device->device_parent, parent,
                    swapchain->presentParms.BackBufferWidth, swapchain->presentParms.BackBufferHeight,
                    swapchain->presentParms.BackBufferFormat, swapchain->presentParms.MultiSampleType,
                    swapchain->presentParms.MultiSampleQuality, TRUE /* Lockable */, &swapchain->backBuffer[i]);
            if (FAILED(hr))
            {
                WARN("Failed to create back buffer %u, hr %#x.\n", i, hr);
                goto err;
            }

            IWineD3DSurface_SetContainer(swapchain->backBuffer[i], (IWineD3DBase *)swapchain);
            ((IWineD3DSurfaceImpl *)swapchain->backBuffer[i])->Flags |= SFLAG_SWAPCHAIN;
        }
    }

    /* Swapchains share the depth/stencil buffer, so only create a single depthstencil surface. */
    if (present_parameters->EnableAutoDepthStencil && surface_type == SURFACE_OPENGL)
    {
        TRACE("Creating depth/stencil buffer.\n");
        if (!device->auto_depth_stencil_buffer)
        {
            hr = IWineD3DDeviceParent_CreateDepthStencilSurface(device->device_parent, parent,
                    swapchain->presentParms.BackBufferWidth, swapchain->presentParms.BackBufferHeight,
                    swapchain->presentParms.AutoDepthStencilFormat, swapchain->presentParms.MultiSampleType,
                    swapchain->presentParms.MultiSampleQuality, FALSE /* FIXME: Discard */,
                    &device->auto_depth_stencil_buffer);
            if (FAILED(hr))
            {
                WARN("Failed to create the auto depth stencil, hr %#x.\n", hr);
                goto err;
            }

            IWineD3DSurface_SetContainer(device->auto_depth_stencil_buffer, NULL);
        }
    }

    IWineD3DSwapChain_GetGammaRamp((IWineD3DSwapChain *)swapchain, &swapchain->orig_gamma);

#ifdef VBOX_WITH_WDDM
    if (overridenSwapchain)
    {
        swapchain_invalidate(overridenSwapchain);
    }
#endif

    return WINED3D_OK;

err:
    if (displaymode_set)
    {
        DEVMODEW devmode;

        ClipCursor(NULL);

        /* Change the display settings */
        memset(&devmode, 0, sizeof(devmode));
        devmode.dmSize = sizeof(devmode);
        devmode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
        devmode.dmBitsPerPel = format_desc->byte_count * 8;
        devmode.dmPelsWidth = swapchain->orig_width;
        devmode.dmPelsHeight = swapchain->orig_height;
        ChangeDisplaySettingsExW(adapter->DeviceName, &devmode, NULL, CDS_FULLSCREEN, NULL);
    }

    if (swapchain->backBuffer)
    {
        for (i = 0; i < swapchain->presentParms.BackBufferCount; ++i)
        {
            if (swapchain->backBuffer[i]) IWineD3DSurface_Release(swapchain->backBuffer[i]);
        }
        HeapFree(GetProcessHeap(), 0, swapchain->backBuffer);
    }

#ifdef VBOX_WITH_WDDM
    if (!device->NumberOfSwapChains)
    {
        while (device->numContexts)
        {
            context_destroy(device, device->contexts[0]);
        }
    }
#else
    if (swapchain->context)
    {
        if (swapchain->context[0])
        {
            context_release(swapchain->context[0]);
            context_destroy(device, swapchain->context[0]);
            swapchain->num_contexts = 0;
        }
        HeapFree(GetProcessHeap(), 0, swapchain->context);
    }
#endif

    if (swapchain->frontBuffer) IWineD3DSurface_Release(swapchain->frontBuffer);

#ifdef VBOX_WITH_WDDM
    if (!overridenSwapchain && swapchain->win_handle)
    {
        VBoxExtWndDestroy(swapchain->win_handle, swapchain->hDC);
    }

    swapchain_invalidate(swapchain);
#endif

    return hr;
}