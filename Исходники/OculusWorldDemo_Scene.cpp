void OculusWorldDemoApp::RenderGrid(ovrEyeType eye)
{
    Recti renderViewport = EyeTexture[eye].Header.RenderViewport;    

    // Draw actual pixel grid on the RT.
    // 1:1 mapping to screen pixels, origin in top-left.
    Matrix4f ortho;
    ortho.SetIdentity();
    ortho.M[0][0] = 2.0f / (renderViewport.w);       // X scale
    ortho.M[0][3] = -1.0f;                           // X offset
    ortho.M[1][1] = -2.0f / (renderViewport.h);      // Y scale (for Y=down)
    ortho.M[1][3] = 1.0f;                            // Y offset (Y=down)
    ortho.M[2][2] = 0;
    pRender->SetProjection(ortho);

    pRender->SetDepthMode(false, false);
    Color cNormal ( 255, 0, 0 );
    Color cSpacer ( 255, 255, 0 );
    Color cMid ( 0, 128, 255 );

    int lineStep = 1;
    int midX = 0;
    int midY = 0;
    int limitX = 0;
    int limitY = 0;

    switch ( GridMode )
    {
    case Grid_Rendertarget4:
        lineStep = 4;
        midX    = renderViewport.w / 2;
        midY    = renderViewport.h / 2;
        limitX  = renderViewport.w / 2;
        limitY  = renderViewport.h / 2;
        break;
    case Grid_Rendertarget16:
        lineStep = 16;
        midX    = renderViewport.w / 2;
        midY    = renderViewport.h / 2;
        limitX  = renderViewport.w / 2;
        limitY  = renderViewport.h / 2;
        break;
    case Grid_Lens:
        {                           
            lineStep = 48;
            Vector2f rendertargetNDC = FovPort(EyeRenderDesc[eye].Fov).TanAngleToRendertargetNDC(Vector2f(0.0f));
            midX    = (int)( ( rendertargetNDC.x * 0.5f + 0.5f ) * (float)renderViewport.w + 0.5f );
            midY    = (int)( ( rendertargetNDC.y * 0.5f + 0.5f ) * (float)renderViewport.h + 0.5f );
            limitX  = Alg::Max ( renderViewport.w - midX, midX );
            limitY  = Alg::Max ( renderViewport.h - midY, midY );
        }
        break;
    default: OVR_ASSERT ( false ); break;
    }

    int spacerMask = (lineStep<<2)-1;


    for ( int xp = 0; xp < limitX; xp += lineStep )
    {
        float x[4];
        float y[4];
        x[0] = (float)( midX + xp );
        y[0] = (float)0;
        x[1] = (float)( midX + xp );
        y[1] = (float)renderViewport.h;
        x[2] = (float)( midX - xp );
        y[2] = (float)0;
        x[3] = (float)( midX - xp );
        y[3] = (float)renderViewport.h;
        if ( xp == 0 )
        {
            pRender->RenderLines ( 1, cMid, x, y );
        }
        else if ( ( xp & spacerMask ) == 0 )
        {
            pRender->RenderLines ( 2, cSpacer, x, y );
        }
        else
        {
            pRender->RenderLines ( 2, cNormal, x, y );
        }
    }
    for ( int yp = 0; yp < limitY; yp += lineStep )
    {
        float x[4];
        float y[4];
        x[0] = (float)0;
        y[0] = (float)( midY + yp );
        x[1] = (float)renderViewport.w;
        y[1] = (float)( midY + yp );
        x[2] = (float)0;
        y[2] = (float)( midY - yp );
        x[3] = (float)renderViewport.w;
        y[3] = (float)( midY - yp );
        if ( yp == 0 )
        {
            pRender->RenderLines ( 1, cMid, x, y );
        }
        else if ( ( yp & spacerMask ) == 0 )
        {
            pRender->RenderLines ( 2, cSpacer, x, y );
        }
        else
        {
            pRender->RenderLines ( 2, cNormal, x, y );
        }
    }
}