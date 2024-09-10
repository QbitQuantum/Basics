   bool initGL () {
 
     bool success = false;
 
     // obtain a device context for the window 
     dcHandle = GetDC(windowHandle);
 
     if (dcHandle) {
 
       // describe requirements
  
       PIXELFORMATDESCRIPTOR pfd = { 
         sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd 
         1,                                // version number 
         0
         | PFD_DRAW_TO_WINDOW              // support window 
         | PFD_SUPPORT_OPENGL              // support OpenGL 
         | PFD_GENERIC_FORMAT              // generic format
         | PFD_DOUBLEBUFFER                // double buffered 
         ,
         PFD_TYPE_RGBA,                    // RGBA type 
         16,                               // 16-bit color depth 
         0, 0, 0, 0, 0, 0,                 // color bits ignored 
         1,                                // alpha buffer 
         0,                                // shift bit ignored 
         0,                                // no accumulation buffer 
         0, 0, 0, 0,                       // accum bits ignored 
         16,                               // 16-bit z-buffer     
         0,                                // no stencil buffer 
         0,                                // no auxiliary buffer 
         PFD_MAIN_PLANE,                   // main layer 
         0,                                // reserved 
         0, 0, 0                           // layer masks ignored 
       };
 
       int  iPixelFormat; 
 
       // get the device context's best, available pixel format match 
       iPixelFormat = ChoosePixelFormat(dcHandle, &pfd); 
 
       if (iPixelFormat != 0) {
 
         // make that match the device context's current pixel format 
         SetPixelFormat(dcHandle, iPixelFormat, &pfd); 
 
         // create GL context
 
         if ( ( glrcHandle = wglCreateContext( dcHandle ) ) )
             success = true;
         else
           printMessage("wglCreateContext failed");
 
       }
       else
         printMessage("iPixelFormat == 0!");
 
       ReleaseDC(windowHandle,dcHandle);
     }
 
     return success;
   }