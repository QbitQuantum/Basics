//----------------------------------------------------------------------------
void ConvexHull2D::OnDisplay ()
{
    ClearScreen();

    ColorRGB black(0,0,0), gray(128,128,128), blue(0,0,255);

    int dimension = mHull->GetDimension();
    int numSimplices = mHull->GetNumSimplices();
    const int* indices = mHull->GetIndices();

    int i0, i1, x0, y0, x1, y1;
    Vector2f v0, v1;

    if (dimension == 0)
    {
        // draw point
        v0 = mVertices[0];
        x0 = UnitToScreen(v0.X());
        y0 = UnitToScreen(v0.Y());
        SetPixel(x0, y0, gray);
    }
    else if (dimension == 1)
    {
        // draw line segment
        v0 = mVertices[indices[0]];
        x0 = UnitToScreen(v0.X());
        y0 = UnitToScreen(v0.Y());

        v1 = mVertices[indices[1]];
        x1 = UnitToScreen(v1.X());
        y1 = UnitToScreen(v1.Y());

        DrawLine(x0, y0, x1, y1, gray);
    }
    else
    {
        // draw convex polygon
        for (i0 = numSimplices - 1, i1 = 0; i1 < numSimplices; i0 = i1++)
        {
            v0 = mVertices[indices[i0]];
            x0 = UnitToScreen(v0.X());
            y0 = UnitToScreen(v0.Y());

            v1 = mVertices[indices[i1]];
            x1 = UnitToScreen(v1.X());
            y1 = UnitToScreen(v1.Y());

            DrawLine(x0, y0, x1, y1, gray);
        }
    }

    // draw input points
    for (i0 = 0; i0 < mNumVertices; ++i0)
    {
        v0 = mVertices[i0];
        x0 = UnitToScreen(v0.X());
        y0 = UnitToScreen(v0.Y());
        SetThickPixel(x0, y0, 1, blue);
    }

    // draw hull vertices
    if (indices)
    {
        for (i0 = 0; i0 < numSimplices; ++i0)
        {
            v0 = mVertices[indices[i0]];
            x0 = UnitToScreen(v0.X());
            y0 = UnitToScreen(v0.Y());
            SetThickPixel(x0, y0, 1, black);
        }
    }
    else
    {
        v0 = mVertices[0];
        x0 = UnitToScreen(v0.X());
        y0 = UnitToScreen(v0.Y());
        SetThickPixel(x0, y0, 1, black);
    }

    WindowApplication2::OnDisplay();
}