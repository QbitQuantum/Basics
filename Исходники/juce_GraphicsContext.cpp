void Graphics::drawEllipse (float x, float y, float width, float height, float lineThickness) const
{
    Path p;
    p.addEllipse (x, y, width, height);
    strokePath (p, PathStrokeType (lineThickness));
}