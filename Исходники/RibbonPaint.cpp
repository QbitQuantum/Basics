void RibbonPaint::keyDown( ci::app::KeyEvent event )
{
    if(_state != kStateNormal) return;

    char keyPressed = event.getChar();
    int colorMode;
    switch (keyPressed)
    {
    case 's':
        saveOutBrushImageAndParameters();
        break;
    case 'o':
        _drawParams = !_drawParams;
        _params.show( !_params.isVisible() );
        break;
    case 'r':
        randomizeBrush();
        break;
    case 'm':
        createBrush();
        break;
    case 'g':
        _glitchSegment = !_glitchSegment;
        break;
    case 'l':
        _useBezier = !_useBezier;
    case 'p':
        _drawPins = !_drawPins;
        break;
    case '1': // COLORMODE_HSV
    case '2': // COLORMODE_RGB
    case '3': // COLORMODE_RGBINVERSE
    case '4': // COLORMODE_RGB_B
    case '5': // COLORMODE_RGB_C
    case '6': // COLORMODE_GRAYSCALE
    case '7': // COLORMODE_ALPHABLEND_1
    case '8': // COLORMODE_ALPHABLEND_2
        colorMode = boost::lexical_cast<int>( keyPressed );
        toggleAdditiveBlending( colorMode < COLORMODE_GRAYSCALE);
        _colorMode = colorMode;
        break;
    default:
        console() << keyPressed << std::endl;
        break;
    }

    // slowdown or speed up how fast our object chases the mouse - clamp addition of speed (determined by ternary operator)
    if(event.getCode() == ci::app::KeyEvent::KEY_LEFT || event.getCode() == ci::app::KeyEvent::KEY_RIGHT) {
        if(event.getCode() == ci::app::KeyEvent::KEY_LEFT)
            _mouseChaseDamping -= 0.02;
        else if(event.getCode() == ci::app::KeyEvent::KEY_RIGHT)
            _mouseChaseDamping += 0.02;

        _mouseChaseDamping = ci::math<float>::clamp(_mouseChaseDamping, 0.02, 1.0);
        updateParams();
    }

    if(event.getCode() == ci::app::KeyEvent::KEY_UP || event.getCode() == ci::app::KeyEvent::KEY_DOWN)
    {
        _alphaWhenDrawing = ci::math<double>::clamp(_alphaWhenDrawing + ((event.getCode() == ci::app::KeyEvent::KEY_UP) ? 0.005 : -0.005), 0.0, 1.0);
        updateParams();
    }

    // exit fullscreen with escape, and toggle with F
    if ( event.getChar() == 'f' || (isFullScreen() && event.getCode() == ci::app::KeyEvent::KEY_ESCAPE) )
    {
        ci::gl::clear(_clearColor);
        setFullScreen( !isFullScreen() );
    }
}