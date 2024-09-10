//----------------------------------------------------------------------------
void MapTextureToQuad::SelectVertex (const Vector2f& position)
{
    // Identify vertex within 5 pixels of mouse click.
    const float pixelRange = 5.0f;
    mSelected = -1;
    for (int i = 0; i < 4; ++i)
    {
        Vector2f diff = position - mVertex[i];
        if (diff.Length() <= pixelRange)
        {
            mSelected = i;
            break;
        }
    }
}