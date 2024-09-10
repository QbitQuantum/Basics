 static void close(void)
 {
     wglMakeCurrent(NULL, NULL);
     wglDeleteContext(hRC);
 }