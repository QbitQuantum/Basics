/** \fn VideoOutWindow::ApplyDBScaleAndMove(void)
 *  \brief Apply scales and moves for "Overscan" and "Underscan" DB settings.
 *
 *  It doesn't make any sense to me to offset an image such that it is clipped.
 *  Therefore, we only apply offsets if there is an underscan or overscan which
 *  creates "room" to move the image around. That is, if we overscan, we can
 *  move the "viewport". If we underscan, we change where we place the image
 *  into the display window. If no over/underscanning is performed, you just
 *  get the full original image scaled into the full display area.
 */
void VideoOutWindow::ApplyDBScaleAndMove(void)
{
    if (db_scale_vert > 0)
    {
        // Veritcal overscan. Move the Y start point in original image.
        float tmp = 1.0f - 2.0f * db_scale_vert;
        video_rect.moveTop((int) round(video_rect.height() * db_scale_vert));
        video_rect.setHeight((int) round(video_rect.height() * tmp));

        // If there is an offset, apply it now that we have a room.
        int yoff = db_move.y();
        if (yoff > 0)
        {
            // To move the image down, move the start point up.
            // Don't offset the image more than we have overscanned.
            yoff = min(video_rect.top(), yoff);
            video_rect.moveTop(video_rect.top() - yoff);
        }
        else if (yoff < 0)
        {
            // To move the image up, move the start point down.
            // Don't offset the image more than we have overscanned.
            if (abs(yoff) > video_rect.top())
                yoff = 0 - video_rect.top();
            video_rect.moveTop(video_rect.top() - yoff);
        }
    }
    else if (db_scale_vert < 0)
    {
        // Vertical underscan. Move the starting Y point in the display window.
        // Use the abolute value of scan factor.
        float vscanf = fabs(db_scale_vert);
        float tmp = 1.0f - 2.0f * vscanf;

        display_video_rect.moveTop(
            (int) round(display_visible_rect.height() * vscanf) +
            display_visible_rect.top());

        display_video_rect.setHeight(
            (int) round(display_visible_rect.height() * tmp));

        // Now offset the image within the extra blank space created by
        // underscanning. To move the image down, increase the Y offset
        // inside the display window.
        int yoff = db_move.y();
        if (yoff > 0)
        {
            // Don't offset more than we have underscanned.
            yoff = min(display_video_rect.top(), yoff);
            display_video_rect.moveTop(display_video_rect.top() + yoff);
        }
        else if (yoff < 0)
        {
            // Don't offset more than we have underscanned.
            if (abs(yoff) > display_video_rect.top())
                yoff = 0 - display_video_rect.top();
            display_video_rect.moveTop(display_video_rect.top() + yoff);
        }
    }

    // Horizontal.. comments, same as vertical...
    if (db_scale_horiz > 0)
    {
        float tmp = 1.0f - 2.0f * db_scale_horiz;
        video_rect.moveLeft(
            (int) round(video_disp_dim.width() * db_scale_horiz));
        video_rect.setWidth((int) round(video_disp_dim.width() * tmp));

        int xoff = db_move.x();
        if (xoff > 0)
        {
            xoff = min(video_rect.left(), xoff);
            video_rect.moveLeft(video_rect.left() - xoff);
        }
        else if (xoff < 0)
        {
            if (abs(xoff) > video_rect.left())
                xoff = 0 - video_rect.left();
            video_rect.moveLeft(video_rect.left() - xoff);
        }
    }
    else if (db_scale_horiz < 0)
    {
        float hscanf = fabs(db_scale_horiz);
        float tmp = 1.0f - 2.0f * hscanf;

        display_video_rect.moveLeft(
            (int) round(display_visible_rect.width() * hscanf) +
            display_visible_rect.left());

        display_video_rect.setWidth(
            (int) round(display_visible_rect.width() * tmp));

        int xoff = db_move.x();
        if (xoff > 0)
        {
            xoff = min(display_video_rect.left(), xoff);
            display_video_rect.moveLeft(display_video_rect.left() + xoff);
        }
        else if (xoff < 0)
        {
            if (abs(xoff) > display_video_rect.left())
                xoff = 0 - display_video_rect.left();
            display_video_rect.moveLeft(display_video_rect.left() + xoff);
        }
    }

}