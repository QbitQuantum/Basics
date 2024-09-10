CocoaWindowed::CocoaWindowed(
        const cgl::PixelFormat& pixel_format, const cgl::Context& context, Size screen_size,
        bool fullscreen, bool retina):
        _window(antares_window_create(
                    pixel_format.c_obj(), context.c_obj(),
                    screen_size.width, screen_size.height, fullscreen, retina)) { }