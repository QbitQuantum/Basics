osg::Image* gradientImage()
{
    unsigned char* buffer = new unsigned char[640 * 480 * 3];
    agg::rendering_buffer renderingBuf( buffer, 640, 480, 640*3 );
    agg::pixfmt_rgb24 pixelFormat( renderingBuf );
    agg::renderer_base<agg::pixfmt_rgb24> renderer( pixelFormat );
    renderer.clear( agg::rgba8(150, 150, 150) );
    
    agg::rgba8 span[640];
    for ( unsigned int i=0; i<640; ++i )
    {
        agg::rgba c(380.0 + 400.0 * (float)i / 640.0, 0.8);
        span[i] = agg::rgba8(c);
    }
    for ( unsigned int i=0; i<480; ++i )
    {
        renderer.blend_color_hspan( 0, i, 640, span, NULL );
    }
    
    osg::ref_ptr<osg::Image> image = new osg::Image;
    image->setImage( 640, 480, 1, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, buffer, osg::Image::USE_NEW_DELETE );
    return image.release();
}