int main(int argc, char *argv[])
{
    ESContext esContext;
    UserData  userData;



    //==========================================================
    // Init GLES Context
    //==========================================================
    esInitContext ( &esContext );
    esContext.userData = &userData;

    esCreateWindow ( &esContext, "Model 3D Render", 640, 480, ES_WINDOW_ALPHA | ES_WINDOW_DEPTH);

    if ( !Init ( &esContext ) )
        return 0;

    esRegisterDrawFunc ( &esContext, Draw );
    esRegisterUpdateFunc ( &esContext, Update );


    esMainLoop ( &esContext );

    ShutDown ( &esContext );
    return 1;
}