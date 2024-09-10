HRESULT VBoxDispD3DOpen(VBOXDISPD3D *pD3D)
{
#ifdef VBOX_WDDM_WOW64
    pD3D->hD3DLib = LoadLibraryW(L"VBoxD3D9wddm-x86.dll");
#else
    pD3D->hD3DLib = LoadLibraryW(L"VBoxD3D9wddm.dll");
#endif
    if (!pD3D->hD3DLib)
    {
        DWORD winErr = GetLastError();
        WARN((__FUNCTION__": LoadLibraryW failed, winErr = (%d)", winErr));
        return E_FAIL;
    }

    do
    {
        pD3D->pfnDirect3DCreate9Ex = (PFNVBOXDISPD3DCREATE9EX)GetProcAddress(pD3D->hD3DLib, "Direct3DCreate9Ex");
        if (!pD3D->pfnDirect3DCreate9Ex)
        {
            WARN(("no Direct3DCreate9Ex"));
            break;
        }

        pD3D->pfnVBoxWineExD3DDev9CreateTexture = (PFNVBOXWINEEXD3DDEV9_CREATETEXTURE)GetProcAddress(pD3D->hD3DLib, "VBoxWineExD3DDev9CreateTexture");
        if (!pD3D->pfnVBoxWineExD3DDev9CreateTexture)
        {
            WARN(("no VBoxWineExD3DDev9CreateTexture"));
            break;
        }

        pD3D->pfnVBoxWineExD3DDev9CreateCubeTexture = (PFNVBOXWINEEXD3DDEV9_CREATECUBETEXTURE)GetProcAddress(pD3D->hD3DLib, "VBoxWineExD3DDev9CreateCubeTexture");
        if (!pD3D->pfnVBoxWineExD3DDev9CreateCubeTexture)
        {
            WARN(("no VBoxWineExD3DDev9CreateCubeTexture"));
            break;
        }

        pD3D->pfnVBoxWineExD3DDev9CreateVolumeTexture = (PFNVBOXWINEEXD3DDEV9_CREATEVOLUMETEXTURE)GetProcAddress(pD3D->hD3DLib, "VBoxWineExD3DDev9CreateVolumeTexture");
        if (!pD3D->pfnVBoxWineExD3DDev9CreateVolumeTexture)
        {
            WARN(("no VBoxWineExD3DDev9CreateVolumeTexture"));
            break;
        }

        pD3D->pfnVBoxWineExD3DDev9Flush = (PFNVBOXWINEEXD3DDEV9_FLUSH)GetProcAddress(pD3D->hD3DLib, "VBoxWineExD3DDev9Flush");
        if (!pD3D->pfnVBoxWineExD3DDev9Flush)
        {
            WARN(("no VBoxWineExD3DDev9Flush"));
            break;
        }

        pD3D->pfnVBoxWineExD3DDev9FlushToHost = (PFNVBOXWINEEXD3DDEV9_FLUSHTOHOST)GetProcAddress(pD3D->hD3DLib, "VBoxWineExD3DDev9FlushToHost");
        if (!pD3D->pfnVBoxWineExD3DDev9FlushToHost)
        {
            WARN(("no VBoxWineExD3DDev9FlushToHost"));
            break;
        }

        pD3D->pfnVBoxWineExD3DDev9Finish = (PFNVBOXWINEEXD3DDEV9_FINISH)GetProcAddress(pD3D->hD3DLib, "VBoxWineExD3DDev9Finish");
        if (!pD3D->pfnVBoxWineExD3DDev9Finish)
        {
            WARN(("no VBoxWineExD3DDev9Finish"));
            break;
        }

        pD3D->pfnVBoxWineExD3DDev9VolBlt = (PFNVBOXWINEEXD3DDEV9_VOLBLT)GetProcAddress(pD3D->hD3DLib, "VBoxWineExD3DDev9VolBlt");
        if (!pD3D->pfnVBoxWineExD3DDev9VolBlt)
        {
            WARN(("no VBoxWineExD3DDev9VolBlt"));
            break;
        }

        pD3D->pfnVBoxWineExD3DDev9VolTexBlt = (PFNVBOXWINEEXD3DDEV9_VOLTEXBLT)GetProcAddress(pD3D->hD3DLib, "VBoxWineExD3DDev9VolTexBlt");
        if (!pD3D->pfnVBoxWineExD3DDev9VolTexBlt)
        {
            WARN(("no VBoxWineExD3DDev9VolTexBlt"));
            break;
        }

        pD3D->pfnVBoxWineExD3DDev9Update = (PFNVBOXWINEEXD3DDEV9_UPDATE)GetProcAddress(pD3D->hD3DLib, "VBoxWineExD3DDev9Update");
        if (!pD3D->pfnVBoxWineExD3DDev9Update)
        {
            WARN(("no VBoxWineExD3DDev9Update"));
            break;
        }

        pD3D->pfnVBoxWineExD3DDev9Term = (PFNVBOXWINEEXD3DDEV9_TERM)GetProcAddress(pD3D->hD3DLib, "VBoxWineExD3DDev9Term");
        if (!pD3D->pfnVBoxWineExD3DDev9Term)
        {
            WARN(("no VBoxWineExD3DDev9Term"));
            break;
        }

        pD3D->pfnVBoxWineExD3DRc9SetShRcState = (PFNVBOXWINEEXD3DRC9_SETSHRCSTATE)GetProcAddress(pD3D->hD3DLib, "VBoxWineExD3DRc9SetShRcState");
        if (!pD3D->pfnVBoxWineExD3DRc9SetShRcState)
        {
            WARN(("no VBoxWineExD3DRc9SetShRcState"));
            break;
        }

        pD3D->pfnVBoxWineExD3DSwapchain9Present = (PFNVBOXWINEEXD3DSWAPCHAIN9_PRESENT)GetProcAddress(pD3D->hD3DLib, "VBoxWineExD3DSwapchain9Present");
        if (!pD3D->pfnVBoxWineExD3DSwapchain9Present)
        {
            WARN(("no VBoxWineExD3DSwapchain9Present"));
            break;
        }

        return S_OK;

    } while (0);

    VBoxDispD3DClose(pD3D);

    return E_FAIL;
}