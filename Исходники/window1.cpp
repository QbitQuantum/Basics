void Window1_Render(Win32Window* window, float alpha, float elapsedtime)
{
    static float time = 0;
    float world[16];

    time += elapsedtime;

    DrawingItem* drawingitem = window->GetDrawingItem();
    DrawingLayer& bottomlayer = drawingitem->GetBottomLayer();
    {
        NativeContext	context		= bottomlayer.GetContext();
        float			bigradius	= 150;
        float			smallradius	= 80;
        float			m2pi		= 6.293185f;
        int				segments	= 16;

        GLMatrixRotationAxis(world, fmodf(time * 20.0f, 360.0f) * (3.14152f / 180.0f), 0, 0, 1);

        context.Clear(OpenGLColor(0.0f, 0.125f, 0.3f, 1.0f));
        context.SetWorldTransform(world);
        context.MoveTo(0, bigradius);

        for( int i = 1; i <= segments; ++i )
        {
            if( i % 2 == 1 )
            {
                context.LineTo(
                    sinf((m2pi / segments) * i) * smallradius,
                    cosf((m2pi / segments) * i) * smallradius);
            }
            else
            {
                context.LineTo(
                    sinf((m2pi / segments) * i) * bigradius,
                    cosf((m2pi / segments) * i) * bigradius);
            }
        }
    }

    DrawingLayer& feedbacklayer = drawingitem->GetFeedbackLayer();
    {
        NativeContext context = feedbacklayer.GetContext();

        GLMatrixRotationAxis(world, -fmodf(time * 20.0f, 360.0f) * (3.14152f / 180.0f), 0, 0, 1);

        context.Clear(OpenGLColor(0, 0, 0, 0));
        context.SetWorldTransform(world);
        context.SetColor(OpenGLColor(0, 1, 0, 1));

        context.MoveTo(-120, 120);
        context.LineTo(120, 120);
        context.LineTo(120, -120);
        context.LineTo(-120, -120);
        context.LineTo(-120, 120);
    }

    drawingitem->RecomposeLayers();
}