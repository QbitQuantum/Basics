void renderer_init()
{
    SYS_VERIFY( shader_create( &s_renderer.paperShader, &s_shader_paper, 1u, 1u, 0u ) );
    SYS_VERIFY( shader_create( &s_renderer.penShader, &s_shader_pen, 0u, 2u, 0u ) );
    SYS_VERIFY( shader_create( &s_renderer.pageShader, &s_shader_page, 0u, 0u, 3u ) );
    SYS_VERIFY( shader_create( &s_renderer.pageFlipShader, &s_shader_pageflip, 1u, 0u, 2u ) );
    SYS_VERIFY( shader_create( &s_renderer.burnHoleShader, &s_shader_burnhole, 0u, 2u, 1u ) );
    SYS_VERIFY( shader_create( &s_renderer.noiseShader, &s_shader_noise, 0u, 0u, 0u ) );
#ifndef SYS_BUILD_MASTER
    SYS_VERIFY( shader_create( &s_renderer.debugPenShader, &s_shader_debugpen, 1u, 0u, 0u ) );
#endif

    SYS_VERIFY( rendertarget_create( &s_renderer.noiseTarget, 512u, 512u, PixelFormat_R8G8B8A8 ) );
    
    graphics_setBlendMode( BlendMode_Disabled );

    // fill noise map:
    graphics_setRenderTarget( &s_renderer.noiseTarget );
    graphics_setShader( &s_renderer.noiseShader );
    graphics_drawFullscreenQuad();
    
    const int width = sys_getScreenWidth();
    const int height = sys_getScreenHeight();

    // create page:
    for( uint i = 0u; i < SYS_COUNTOF( s_renderer.pages ); ++i )
    {
        page_create( &s_renderer.pages[ i ], width, height );
    }

    s_renderer.currentPage = 0u;
    s_renderer.lastPage = 1u;
    
    s_renderer.currentCommand = 0u;

    s_renderer.pageNumber = 0u;

    s_renderer.pageState = PageState_Done;
    s_renderer.stateTime = 0.0f;

    clearStrokeBuffer( &s_renderer.strokeBuffer );

    float3 color;
    color.x = 0.2f;
    color.y = 0.2f;
    color.z = 0.2f;
    createPen( &s_renderer.pens[ Pen_Default ], 2.0f, 1.0f, &color );
    createPen( &s_renderer.pens[ Pen_Font ], 2.0f, 1.0f, &color );
    createPen( &s_renderer.pens[ Pen_Fat ], 3.0f, 1.0f, &color );
    createPen( &s_renderer.pens[ Pen_DebugRed ], 2.0f, 1.0f, float3_set( &color, 1.0f, 0.0f, 0.0f ) );
    createPen( &s_renderer.pens[ Pen_DebugGreen ], 2.0f, 1.0f, float3_set( &color, 0.0f, 1.0f, 0.0f ) );
    createPen( &s_renderer.pens[ Pen_PageNumber ], 2.0f, 1.0f, float3_set( &color, 0.0f, 0.0f, 0.0f ) );

    // create page flip mesh:
    createPageFlipMesh( &s_renderer.pageFlipMesh, 64u, 36u );

    s_renderer.flipTime = -1.0f;

    for( uint i = 0u; i < SYS_COUNTOF(s_renderer.burnHoles); ++i )
    {
        s_renderer.burnHoles[i].size = -1.0f;
    }

    renderer_setDrawSpeed( 0.5f );
    renderer_setPen( Pen_Default );
    renderer_setTransform( 0 );
}