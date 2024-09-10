static int renderer_overlay_wallpaper( GdkPixbuf *background,
                                       const char *wallpaper,
                                       MMB_Screen *screen,
                                       int clip )
{
    GError *error = NULL;
    GdkPixbuf *image = gdk_pixbuf_new_from_file( wallpaper, &error );

    if ( error != NULL ) {
        fprintf( stderr, "Failed to parse image: %s\n" , error->message );
        return 0;
    }

    double wp_width  = gdk_pixbuf_get_width( image );
    double wp_height = gdk_pixbuf_get_height( image );

    for ( int monitor = 0; monitor < screen->num_monitors; monitor++ ) {

        MMB_Rectangle rectangle = screen->monitors[monitor];
        double w_scale = wp_width/( double )( rectangle.w );
        double h_scale = wp_height/( double )( rectangle.h );

        // Picture is small then screen, center it.
        if ( w_scale < 1 && h_scale < 1 ) {
            gdk_pixbuf_copy_area( image, 0,0,
                                  wp_width, wp_height,
                                  background,
                                  rectangle.x + ( rectangle.w-wp_width )/2,
                                  rectangle.y + ( rectangle.h-wp_height )/2
                                );
        }
        // Picture is smaller on one of the sides and we want to clip.
        else if ( clip && ( w_scale < 1 || h_scale < 1 ) ) {
            double x_off = ( ( float )rectangle.w-wp_width )/2.0;
            double y_off = ( ( float )rectangle.h-wp_height )/2.0;
            gdk_pixbuf_copy_area( image,
                                  -( x_off < 0 )*x_off,-( y_off < 0 )*y_off,
                                  wp_width+( x_off < 0 )*2*x_off,
                                  wp_height+( y_off < 0 )*2*y_off,
                                  background,
                                  rectangle.x + ( ( x_off> 0 )?x_off:0 ),
                                  rectangle.y + ( ( y_off> 0 )?y_off:0 ) );

        }
        // Picture is bigger/equal then screen.
        // Scale to fit.
        else {
            int new_w= 0;
            int new_h = 0;
            double x_off = 0;
            double y_off = 0;

            if ( clip ) {
                if ( w_scale < h_scale ) {
                    new_w = wp_width/w_scale;
                    new_h = wp_height/w_scale;
                } else {
                    new_w = wp_width/h_scale;
                    new_h = wp_height/h_scale;
                }

                x_off = ( ( new_w-rectangle.w )/2.0 );
                y_off = ( ( new_h-rectangle.h )/2.0 );
            } else {
                if ( w_scale > h_scale ) {
                    new_w = wp_width/w_scale;
                    new_h = wp_height/w_scale;
                } else {
                    new_w = wp_width/h_scale;
                    new_h = wp_height/h_scale;
                }
            }

            GdkPixbuf *scaled_wp = gdk_pixbuf_scale_simple( image, new_w, new_h, GDK_INTERP_HYPER );
            gdk_pixbuf_copy_area(
                scaled_wp,
                ( int )ceil( x_off ),( int )ceil( y_off ),
                new_w-ceil(x_off)*2,
                new_h-ceil(y_off)*2,
                background,
                rectangle.x + ( ( double )rectangle.w-new_w+x_off*2 )/2,
                rectangle.y + ( ( double )rectangle.h-new_h+y_off*2 )/2 );

            g_object_unref( scaled_wp );
        }
    }

    g_object_unref( image );
    return 1;
}