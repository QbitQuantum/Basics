int 
main(int argc, char** argv)
{
    HDC hDC;				/* device context */
    HGLRC hRC;				/* opengl context */
    HWND  hWnd;				/* window */
    MSG   msg;				/* message */
    int   i;
    char* s;
    char  t[80];
    char* p;
    int verbose = 0;

    while (--argc) {
	if (strcmp("-h", argv[argc]) == 0) {
	    printf("Usage: wglinfo [-v] [-t] [-m] [-h] [-dispay <dname>] [-nfbc] [-fpcinfo]\n");
	    printf("        -v: Print visuals info in verbose form.\n");
	    printf("        -t: Print verbose table (not implemented on Win32)\n");
	    printf("        -m: Don't print mid table headers (in long tables). (not on Win32)\n");
	    printf("        -display <dname>: Print GLX visuals on specified server. (not on Win32)\n");
	    printf("        -nfbc: Don't use fbconfig extension (not available on Win32)\n");
	    printf("        -fbcinfo: print out additional fbconfig information (not on Win32)\n");
	    printf("        -h: This screen.\n");
	    exit(0);
	} else if (strcmp("-v", argv[argc]) == 0) {
	    verbose = 1;
	}
    }

    hWnd = CreateOpenGLWindow("wglinfo", 0, 0, 100, 100, PFD_TYPE_RGBA, 0);
    if (hWnd == NULL)
	exit(1);

    hDC = GetDC(hWnd);
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

    ShowWindow(hWnd, SW_HIDE);

    /* output header information */
    printf("display: N/A\n");
    printf("server wgl vendor string: N/A\n");
    printf("server wgl version string: N/A\n");
    printf("server wgl extensions (WGL_): N/A\n");
    printf("client wgl version: N/A\n");
    printf("client wgl extensions (WGL_): none\n");
    printf("OpenGL vendor string: %s\n", glGetString(GL_VENDOR));
    printf("OpenGL renderer string: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version string: %s\n", glGetString(GL_VERSION));
    printf("OpenGL extensions (GL_): \n");

    /* do the magic to separate all extensions with comma's, except
       for the last one that _may_ terminate in a space. */
    i = 0;
    s = (char*)glGetString(GL_EXTENSIONS);
    t[79] = '\0';
    p = &t[0];
    while(*s) {
	t[i++] = *s;
	if(*s == ' ') {
	    if (*(s+1) != '\0') {
		t[i-1] = ',';
		t[i] = ' ';
		p = &t[i++];
	    } else {	       /* zoinks! last one terminated in a space! */
		t[i-1] = '\0';
	    }
	}
	if(i > 80 - 5) {
	    *p = t[i] = '\0';
	    printf("    %s\n", t);
	    p++;
	    i = strlen(p);
	    strcpy(t, p);
	}
	s++;
    }
    t[i] = '\0';
    printf("    %s.\n\n", t);

    /* enumerate all the formats */
    VisualInfo(hDC, verbose);

    PostQuitMessage(0);
    while(GetMessage(&msg, hWnd, 0, 0)) {
	TranslateMessage(&msg);
	DispatchMessage(&msg);
    }

    wglMakeCurrent(NULL, NULL);
    ReleaseDC(hWnd, hDC);
    wglDeleteContext(hRC);
    DestroyWindow(hWnd);

    return msg.wParam;
}