//----------------------------------------------------------------------------//
void BasicImage::render(GeometryBuffer& buffer, const Rectf& dest_area,
                        const Rectf* clip_area, const ColourRect& colours) const
{
    const QuadSplitMode quad_split_mode(TopLeftToBottomRight);

    Rectf dest(dest_area);
    // apply rendering offset to the destination Rect
    dest.offset(d_scaledOffset);

    // get the rect area that we will actually draw to (i.e. perform clipping)
    Rectf final_rect(clip_area ? dest.getIntersection(*clip_area) : dest );

    // check if rect was totally clipped
    if ((final_rect.getWidth() == 0) || (final_rect.getHeight() == 0))
        return;

    // Obtain correct scale values from the texture
    const Vector2f& scale = d_texture->getTexelScaling();
    const Vector2f tex_per_pix(d_area.getWidth() / dest.getWidth(), d_area.getHeight() / dest.getHeight());

    // calculate final, clipped, texture co-ordinates
    const Rectf tex_rect((d_area.d_min + ((final_rect.d_min - dest.d_min) * tex_per_pix)) * scale,
                          (d_area.d_max + ((final_rect.d_max - dest.d_max) * tex_per_pix)) * scale);

    // URGENT FIXME: Shouldn't this be in the hands of the user?
    final_rect.d_min.d_x = CoordConverter::alignToPixels(final_rect.d_min.d_x);
    final_rect.d_min.d_y = CoordConverter::alignToPixels(final_rect.d_min.d_y);
    final_rect.d_max.d_x = CoordConverter::alignToPixels(final_rect.d_max.d_x);
    final_rect.d_max.d_y = CoordConverter::alignToPixels(final_rect.d_max.d_y);

    Vertex vbuffer[6];

    // vertex 0
    vbuffer[0].position   = Vector3f(final_rect.left(), final_rect.top(), 0.0f);
    vbuffer[0].colour_val = colours.d_top_left;
    vbuffer[0].tex_coords = Vector2f(tex_rect.left(), tex_rect.top());

    // vertex 1
    vbuffer[1].position   = Vector3f(final_rect.left(), final_rect.bottom(), 0.0f);
    vbuffer[1].colour_val = colours.d_bottom_left;
    vbuffer[1].tex_coords = Vector2f(tex_rect.left(), tex_rect.bottom());

    // vertex 2
    vbuffer[2].position.d_x   = final_rect.right();
    vbuffer[2].position.d_z   = 0.0f;
    vbuffer[2].colour_val     = colours.d_bottom_right;
    vbuffer[2].tex_coords.d_x = tex_rect.right();

    // top-left to bottom-right diagonal
    if (quad_split_mode == TopLeftToBottomRight)
    {
        vbuffer[2].position.d_y   = final_rect.bottom();
        vbuffer[2].tex_coords.d_y = tex_rect.bottom();
    }
    // bottom-left to top-right diagonal
    else
    {
        vbuffer[2].position.d_y   = final_rect.top();
        vbuffer[2].tex_coords.d_y = tex_rect.top();
    }

    // vertex 3
    vbuffer[3].position   = Vector3f(final_rect.right(), final_rect.top(), 0.0f);
    vbuffer[3].colour_val = colours.d_top_right;
    vbuffer[3].tex_coords = Vector2f(tex_rect.right(), tex_rect.top());

    // vertex 4
    vbuffer[4].position.d_x   = final_rect.left();
    vbuffer[4].position.d_z   = 0.0f;
    vbuffer[4].colour_val     = colours.d_top_left;
    vbuffer[4].tex_coords.d_x = tex_rect.left();

    // top-left to bottom-right diagonal
    if (quad_split_mode == TopLeftToBottomRight)
    {
        vbuffer[4].position.d_y   = final_rect.top();
        vbuffer[4].tex_coords.d_y = tex_rect.top();
    }
    // bottom-left to top-right diagonal
    else
    {
        vbuffer[4].position.d_y   = final_rect.bottom();
        vbuffer[4].tex_coords.d_y = tex_rect.bottom();
    }

    // vertex 5
    vbuffer[5].position = Vector3f(final_rect.right(), final_rect.bottom(), 0.0f);
    vbuffer[5].colour_val= colours.d_bottom_right;
    vbuffer[5].tex_coords = Vector2f(tex_rect.right(), tex_rect.bottom());

    buffer.setActiveTexture(d_texture);
    buffer.appendGeometry(vbuffer, 6);
}