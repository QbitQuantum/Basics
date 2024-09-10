//Función que se encarga de la inicialización de OpenGL.
//Recibe la ventana sobre la que OpenGL hará el render.
bool cGraphicManager::Init( cWindow * lpWindow )
{
   //Se crear el contexto de renderizado:
   bool lbRet = CreateContext( lpWindow );
   if ( lbRet )
   {
      //Se establece el estado de OpenGL:
      InitializeGLState();	
   }
   return lbRet;
}