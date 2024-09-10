void TextureManager::bindFromImage(const QImage& image, QGLWidget* cxt)
{
    Create();
    Q_ASSERT( "Must be called only with valid GL context" && cxt );

    if ( image.width() != image.height() || ( image.width() & ( image.width() - 1 ) ) ) {
        // Compute texture size
        int longest  = qMax( image.width(), image.height() );
        int tex_size = 2;
        while ( tex_size < longest ) {
            tex_size *= 2;
        }
        // FIXME: Check if Qt does this for us already. [Note that it does scale to the nearest power of two]
        bindImage( 
            image.scaled( tex_size, tex_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ),
            cxt );
    } else {
        bindImage( image, cxt );
    }
}