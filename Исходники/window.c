HWND WINAPI
User32CreateWindowEx(DWORD dwExStyle,
                     LPCSTR lpClassName,
                     LPCSTR lpWindowName,
                     DWORD dwStyle,
                     int x,
                     int y,
                     int nWidth,
                     int nHeight,
                     HWND hWndParent,
                     HMENU hMenu,
                     HINSTANCE hInstance,
                     LPVOID lpParam,
                     DWORD dwFlags)
{
    LARGE_STRING WindowName;
    LARGE_STRING lstrClassName, *plstrClassName;
    UNICODE_STRING ClassName;
    WNDCLASSEXA wceA;
    WNDCLASSEXW wceW;
    HMODULE hLibModule = NULL;
    DWORD save_error;
    BOOL Unicode, ClassFound = FALSE;
    HWND Handle = NULL;

#if 0
    DbgPrint("[window] User32CreateWindowEx style %d, exstyle %d, parent %d\n", dwStyle, dwExStyle, hWndParent);
#endif

    if (!RegisterDefaultClasses)
    {
       TRACE("RegisterSystemControls\n");
       RegisterSystemControls();
    }

    Unicode = !(dwFlags & NUCWE_ANSI);

    if (IS_ATOM(lpClassName))
    {
        plstrClassName = (PVOID)lpClassName;
    }
    else
    {
        if(Unicode)
            RtlInitUnicodeString(&ClassName, (PCWSTR)lpClassName);
        else
        {
            if (!RtlCreateUnicodeStringFromAsciiz(&ClassName, (PCSZ)lpClassName))
            {
                SetLastError(ERROR_OUTOFMEMORY);
                return (HWND)0;
            }
        }

        /* Copy it to a LARGE_STRING */
        lstrClassName.Buffer = ClassName.Buffer;
        lstrClassName.Length = ClassName.Length;
        lstrClassName.MaximumLength = ClassName.MaximumLength;
        plstrClassName = &lstrClassName;
    }

    /* Initialize a LARGE_STRING */
    RtlInitLargeString(&WindowName, lpWindowName, Unicode);

    // HACK: The current implementation expects the Window name to be UNICODE
    if (!Unicode)
    {
        NTSTATUS Status;
        PSTR AnsiBuffer = WindowName.Buffer;
        ULONG AnsiLength = WindowName.Length;

        WindowName.Length = 0;
        WindowName.MaximumLength = AnsiLength * sizeof(WCHAR);
        WindowName.Buffer = RtlAllocateHeap(RtlGetProcessHeap(),
                                            0,
                                            WindowName.MaximumLength);
        if (!WindowName.Buffer)
        {
            SetLastError(ERROR_OUTOFMEMORY);
            goto cleanup;
        }

        Status = RtlMultiByteToUnicodeN(WindowName.Buffer,
                                        WindowName.MaximumLength,
                                        &WindowName.Length,
                                        AnsiBuffer,
                                        AnsiLength);
        if (!NT_SUCCESS(Status))
        {
            goto cleanup;
        }
    }

    if(!hMenu && (dwStyle & (WS_OVERLAPPEDWINDOW | WS_POPUP)))
    {
        if(Unicode)
        {
            wceW.cbSize = sizeof(WNDCLASSEXW);
            if(GetClassInfoExW(hInstance, (LPCWSTR)lpClassName, &wceW) && wceW.lpszMenuName)
            {
                hMenu = LoadMenuW(hInstance, wceW.lpszMenuName);
            }
        }
        else
        {
            wceA.cbSize = sizeof(WNDCLASSEXA);
            if(GetClassInfoExA(hInstance, lpClassName, &wceA) && wceA.lpszMenuName)
            {
                hMenu = LoadMenuA(hInstance, wceA.lpszMenuName);
            }
        }
    }

    if (!Unicode) dwExStyle |= WS_EX_SETANSICREATOR;

    for(;;)
    {
       Handle = NtUserCreateWindowEx(dwExStyle,
                                     plstrClassName,
                                     NULL,
                                     &WindowName,
                                     dwStyle,
                                     x,
                                     y,
                                     nWidth,
                                     nHeight,
                                     hWndParent,
                                     hMenu,
                                     hInstance,
                                     lpParam,
                                     dwFlags,
                                     NULL);
       if (Handle) break;
       if (!ClassFound)
       {
          save_error = GetLastError();
          if ( save_error == ERROR_CANNOT_FIND_WND_CLASS )
          {
              ClassFound = VersionRegisterClass(ClassName.Buffer, NULL, NULL, &hLibModule);
              if (ClassFound) continue;
          }
       }
       if (hLibModule)
       {
          save_error = GetLastError();
          FreeLibrary(hLibModule);
          SetLastError(save_error);
          hLibModule = 0;
       }
       break;
    }

#if 0
    DbgPrint("[window] NtUserCreateWindowEx() == %d\n", Handle);
#endif
cleanup:
    if(!Unicode)
    {
        if (!IS_ATOM(lpClassName))
        {
            RtlFreeUnicodeString(&ClassName);
        }

        RtlFreeLargeString(&WindowName);
    }

    return Handle;
}