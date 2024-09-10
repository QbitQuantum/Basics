WINGDIAPI BOOL APIENTRY
wglSwapBuffers(
   HDC hdc )
{
   return DrvSwapBuffers( hdc );
}