/* At process attach */
BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpv)
{
    TRACE("WineD3D DLLMain Reason=%d\n", fdwReason);
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
       HMODULE mod;
       char buffer[MAX_PATH+10];
       DWORD size = sizeof(buffer);
       HKEY hkey = 0;
       HKEY appkey = 0;
       DWORD len;
       WNDCLASSA wc;

       atifs_shader_backend.shader_dll_load_init();
       glsl_shader_backend.shader_dll_load_init();
       arb_program_shader_backend.shader_dll_load_init();
       none_shader_backend.shader_dll_load_init();

       /* We need our own window class for a fake window which we use to retrieve GL capabilities */
       /* We might need CS_OWNDC in the future if we notice strange things on Windows.
        * Various articles/posts about OpenGL problems on Windows recommend this. */
       wc.style                = CS_HREDRAW | CS_VREDRAW;
       wc.lpfnWndProc          = DefWindowProcA;
       wc.cbClsExtra           = 0;
       wc.cbWndExtra           = 0;
       wc.hInstance            = hInstDLL;
       wc.hIcon                = LoadIconA(NULL, (LPCSTR)IDI_WINLOGO);
       wc.hCursor              = LoadCursorA(NULL, (LPCSTR)IDC_ARROW);
       wc.hbrBackground        = NULL;
       wc.lpszMenuName         = NULL;
       wc.lpszClassName        = "WineD3D_OpenGL";

       if (!RegisterClassA(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
       {
           ERR("Failed to register window class 'WineD3D_OpenGL'!\n");
           return FALSE;
       }

       DisableThreadLibraryCalls(hInstDLL);

       mod = GetModuleHandleA( "winex11.drv" );
       if (mod)
       {
           wine_tsx11_lock_ptr   = (void *)GetProcAddress( mod, "wine_tsx11_lock" );
           wine_tsx11_unlock_ptr = (void *)GetProcAddress( mod, "wine_tsx11_unlock" );
       }
       else /* We are most likely on Windows */
       {
           wine_tsx11_lock_ptr   = wined3d_do_nothing;
           wine_tsx11_unlock_ptr = wined3d_do_nothing;
       }
       /* @@ Wine registry key: HKCU\Software\Wine\Direct3D */
       if ( RegOpenKeyA( HKEY_CURRENT_USER, "Software\\Wine\\Direct3D", &hkey ) ) hkey = 0;

       len = GetModuleFileNameA( 0, buffer, MAX_PATH );
       if (len && len < MAX_PATH)
       {
            HKEY tmpkey;
            /* @@ Wine registry key: HKCU\Software\Wine\AppDefaults\app.exe\Direct3D */
            if (!RegOpenKeyA( HKEY_CURRENT_USER, "Software\\Wine\\AppDefaults", &tmpkey ))
            {
                char *p, *appname = buffer;
                if ((p = strrchr( appname, '/' ))) appname = p + 1;
                if ((p = strrchr( appname, '\\' ))) appname = p + 1;
                strcat( appname, "\\Direct3D" );
                TRACE("appname = [%s]\n", appname);
                if (RegOpenKeyA( tmpkey, appname, &appkey )) appkey = 0;
                RegCloseKey( tmpkey );
            }
       }

       if ( 0 != hkey || 0 != appkey )
       {
            if ( !get_config_key( hkey, appkey, "VertexShaderMode", buffer, size) )
            {
                if (!strcmp(buffer,"none"))
                {
                    TRACE("Disable vertex shaders\n");
                    wined3d_settings.vs_mode = VS_NONE;
                }
            }
            if ( !get_config_key( hkey, appkey, "PixelShaderMode", buffer, size) )
            {
                if (!strcmp(buffer,"enabled"))
                {
                    TRACE("Allow pixel shaders\n");
                    wined3d_settings.ps_mode = PS_HW;
                }
                if (!strcmp(buffer,"disabled"))
                {
                    TRACE("Disable pixel shaders\n");
                    wined3d_settings.ps_mode = PS_NONE;
                }
            }
            if ( !get_config_key( hkey, appkey, "VertexBufferMode", buffer, size) )
            {
                if (!strcmp(buffer,"none"))
                {
                    TRACE("Disable Vertex Buffer Hardware support\n");
                    wined3d_settings.vbo_mode = VBO_NONE;
                }
                else if (!strcmp(buffer,"hardware"))
                {
                    TRACE("Allow Vertex Buffer Hardware support\n");
                    wined3d_settings.vbo_mode = VBO_HW;
                }
            }
            if ( !get_config_key( hkey, appkey, "UseGLSL", buffer, size) )
            {
                if (!strcmp(buffer,"disabled"))
                {
                    TRACE("Use of GL Shading Language disabled\n");
                    wined3d_settings.glslRequested = FALSE;
                }
            }
            if ( !get_config_key( hkey, appkey, "OffscreenRenderingMode", buffer, size) )
            {
                if (!strcmp(buffer,"backbuffer"))
                {
                    TRACE("Using the backbuffer for offscreen rendering\n");
                    wined3d_settings.offscreen_rendering_mode = ORM_BACKBUFFER;
                }
                else if (!strcmp(buffer,"pbuffer"))
                {
                    TRACE("Using PBuffers for offscreen rendering\n");
                    wined3d_settings.offscreen_rendering_mode = ORM_PBUFFER;
                }
                else if (!strcmp(buffer,"fbo"))
                {
                    TRACE("Using FBOs for offscreen rendering\n");
                    wined3d_settings.offscreen_rendering_mode = ORM_FBO;
                }
            }
            if ( !get_config_key( hkey, appkey, "RenderTargetLockMode", buffer, size) )
            {
                if (!strcmp(buffer,"disabled"))
                {
                    TRACE("Disabling render target locking\n");
                    wined3d_settings.rendertargetlock_mode = RTL_DISABLE;
                }
                else if (!strcmp(buffer,"readdraw"))
                {
                    TRACE("Using glReadPixels for render target reading and glDrawPixels for writing\n");
                    wined3d_settings.rendertargetlock_mode = RTL_READDRAW;
                }
                else if (!strcmp(buffer,"readtex"))
                {
                    TRACE("Using glReadPixels for render target reading and textures for writing\n");
                    wined3d_settings.rendertargetlock_mode = RTL_READTEX;
                }
                else if (!strcmp(buffer,"texdraw"))
                {
                    TRACE("Using textures for render target reading and glDrawPixels for writing\n");
                    wined3d_settings.rendertargetlock_mode = RTL_TEXDRAW;
                }
                else if (!strcmp(buffer,"textex"))
                {
                    TRACE("Reading render targets via textures and writing via textures\n");
                    wined3d_settings.rendertargetlock_mode = RTL_TEXTEX;
                }
            }
            if ( !get_config_key( hkey, appkey, "VideoMemorySize", buffer, size) )
            {
                int TmpVideoMemorySize = atoi(buffer);
                if(TmpVideoMemorySize > 0)
                {
                    wined3d_settings.emulated_textureram = TmpVideoMemorySize *1024*1024;
                    TRACE("Use %iMB = %d byte for emulated_textureram\n",
                            TmpVideoMemorySize,
                            wined3d_settings.emulated_textureram);
                }
                else
                    ERR("VideoMemorySize is %i but must be >0\n", TmpVideoMemorySize);
            }
            if ( !get_config_key( hkey, appkey, "WineLogo", buffer, size) )
            {
                wined3d_settings.logo = HeapAlloc(GetProcessHeap(), 0, strlen(buffer) + 1);
                if(wined3d_settings.logo) strcpy(wined3d_settings.logo, buffer);
            }
            if ( !get_config_key( hkey, appkey, "Multisampling", buffer, size) )
            {
                if (!strcmp(buffer,"enabled"))
                {
                    TRACE("Allow multisampling\n");
                    wined3d_settings.allow_multisampling = TRUE;
                }
            }
       }
       if (wined3d_settings.vs_mode == VS_HW)
           TRACE("Allow HW vertex shaders\n");
       if (wined3d_settings.ps_mode == PS_NONE)
           TRACE("Disable pixel shaders\n");
       if (wined3d_settings.vbo_mode == VBO_NONE)
           TRACE("Disable Vertex Buffer Hardware support\n");
       if (wined3d_settings.glslRequested)
           TRACE("If supported by your system, GL Shading Language will be used\n");

       if (appkey) RegCloseKey( appkey );
       if (hkey) RegCloseKey( hkey );
    }
    return TRUE;
}