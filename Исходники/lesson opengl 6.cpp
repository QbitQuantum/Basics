GLvoid KillGLWindow( GLvoid )              // Корректное разрушение окна

{

    if( fullscreen ) {            // Мы в полноэкранном режиме?

        ChangeDisplaySettings( NULL, 0 );        // Если да, то переключаемся обратно в оконный режим

        ShowCursor( TRUE );            // Показать курсор мышки

    }


    if( hRC )                // Существует ли Контекст Рендеринга?

    {
        if( !wglMakeCurrent( NULL, NULL ) )        // Возможно ли освободить RC и DC?

        {
            MessageBox( NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );

        }

        if( !wglDeleteContext( hRC ) )        // Возможно ли удалить RC?

        {

            MessageBox( NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );

        }

        hRC = NULL;              // Установить RC в NULL

    }


    if( hDC && !ReleaseDC( hWnd, hDC ) )          // Возможно ли уничтожить DC?

    {

        MessageBox( NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );

        hDC = NULL;              // Установить DC в NULL

    }

    if(hWnd && !DestroyWindow(hWnd))            // Возможно ли уничтожить окно?

    {

        MessageBox( NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );

        hWnd = NULL;                // Установить hWnd в NULL

    }

    if( !UnregisterClass( "OpenGL", hInstance ) )        // Возможно ли разрегистрировать класс

    {

        MessageBox( NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);

        hInstance = NULL;                // Установить hInstance в NULL

    }

}