void doFlyEffect(LICE_IBitmap *fb, HWND hwnd)
{
    static int initted;
    if (!initted)
    {
        initted=1;
        cam = new pl_Cam;
        cam->Fov=90.0;
        cam->WantZBuffer=true;
        if (cam->WantZBuffer) cam->Sort = -1;
        cam->Y = 800; // move the camera up from the ground
        cam->Pitch = 180.0;

        setup_materials(mat); // intialize materials and palette

        land = setup_landscape(mat[0],mat[1],mat[2]); // create landscape
        sky = land->Children.Get(0); // unhierarchicalize the sky from the land
        land->Children.Delete(0);
        sky2 = land->Children.Get(0);
        land->Children.Delete(0);

        int x;
        for(x=0; x<sizeof(lights)/sizeof(lights[0]); x++)
        {
            lights[x].Set(PL_LIGHT_POINT,(x%4 - 1.5) * LAND_SIZE /4.0,
                          500+(rand()%1000),
                          (x/4-1.5)*LAND_SIZE/4.0,(rand()%1000)/700.0,(rand()%1000)/700.0,(rand()%1000)/700.0,LAND_SIZE*1.0);
        }

    }

    LICE_Clear(fb,0);
    cam->Begin(fb);

    int x;
    for(x=0; x<sizeof(lights)/sizeof(lights[0]); x++)
        cam->RenderLight(&lights[x]);

    // lots of rendering special casing
    if (draw_sky) { // if we're drawing the sky
        if (cam->Y > 2000) { // if above the sky, only render the skies, with
            // no far clip plane

            cam->RenderObject(sky);
            cam->RenderObject(sky2);
        } else {           // otherwise, render the sky (but not the second sky),
            // and the land, with a far clip plane


            cam->RenderObject(sky);
            cam->RenderObject(land);
        }
    } else { // not drawing sky, just render the land

        cam->RenderObject(land);
    }
    cam->End(); // finish rendering

    static POINT lpos;
    POINT p;
    GetCursorPos(&p);
    int mouse_x  = 0;
    int mouse_y  = 0;
    int mouse_b=0;

    if (hwnd)
    {
        mouse_x = p.x-lpos.x;
        mouse_y = p.y-lpos.y;
        if (GetAsyncKeyState(VK_LBUTTON)&0x8000) mouse_b|=2;

        RECT r;
        GetWindowRect(hwnd,&r);
        p.x=(r.right+r.left)/2;
        p.y=(r.bottom+r.top)/2;
        SetCursorPos(p.x,p.y);
    }
    lpos=p;
    // We calculate the amount of time in thousanths of seconds this frame took
    double prevtime = 10; //((uclock() / (float) UCLOCKS_PER_SEC) - prevtime)*1000.0;

    if (mouse_b & 2) { // if right button hit, we go forward quickly
        cam->X -=
            prevtime*4*sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
        cam->Z +=
            prevtime*4*cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
        cam->Y +=
            prevtime*4*sin(cam->Pitch*PL_PI/180.0);
    } else if (mouse_b & 1) { // if left button hit, we go forward slowly
        cam->X -=
            prevtime*2*sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
        cam->Z +=
            prevtime*2*cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
        cam->Y +=
            prevtime*2*sin(cam->Pitch*PL_PI/180.0);
    }
    cam->Pitch += (mouse_y*mouse_sens); // update pitch and pan of ship
    cam->Pan += (mouse_x*mouse_sens)*(-cos(cam->Pitch*PL_PI/180.0));

    if (cam->X > LAND_SIZE/2) cam->X = LAND_SIZE/2; // make sure we don't go
    if (cam->X < -LAND_SIZE/2) cam->X = -LAND_SIZE/2; // too far away
    if (cam->Z > LAND_SIZE/2) cam->Z = LAND_SIZE/2;
    if (cam->Z < -LAND_SIZE/2) cam->Z = -LAND_SIZE/2;
    if (cam->Y < 0) cam->Y = 0;
    if (cam->Y > 8999) cam->Y = 8999;
#if 0

    while (kbhit()) switch(getch()) { // handle keystrokes
        case 27:
            done++;
            break;    // ESC == quit
        // + is for zooming in.
        case '=':
        case '+':
            cam->Fov -= 1.0;
            if (cam->Fov < 1.0) cam->Fov = 1.0;
            sprintf(lastmessage,"FOV: %2.f",cam->Fov);
            break;
        // - is for zooming out
        case '-':
            cam->Fov += 1.0;
            if (cam->Fov > 179.0) cam->Fov = 179.0;
            sprintf(lastmessage,"FOV: %2.f",cam->Fov);
            break;
        // [ decreases mouse sensitivity
        case '[':
            mouse_sens /= 1.1;
            sprintf(lastmessage,"MouseSens: %.3f",mouse_sens);
            break;
        // ] increases mouse sensitivity
        case ']':
            mouse_sens *= 1.1;
            sprintf(lastmessage,"MouseSens: %.3f",mouse_sens);
            break;
        // v toggles vsync
        case 'v':
            wait_vsync ^= 1;
            sprintf(lastmessage,"VSync %s",wait_vsync ? "on" : "off");
            break;
        // s toggles sky
        case 's':
            draw_sky ^= 1;
            sprintf(lastmessage,"Sky %s",draw_sky ? "on" : "off");
            break;
        }
#endif

    //LICE_ScaledBlit(fb,mat[2]->Texture,0,0,fb->getWidth(),fb->getHeight(),0,0,mat[2]->Texture->getWidth(),mat[2]->Texture->getHeight(),1.0f,0);
}