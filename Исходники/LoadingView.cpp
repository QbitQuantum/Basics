void
LoadingView::doDraw(Surface &viewArea, Surface &clientArea)
{
    if (dirty)
        render();

    screen->fill(Color::black);
    backgroundSurface.blt(clientArea, 0, 0);
    clientArea.FillRoundRect(iRect(165, 40, 635, 225), 10, Color::black);
    clientArea.RoundRect(iRect(165, 40, 635, 225), 10, Color::yellow);
    surface.blt(clientArea, 172, 45);

    View::doDraw(viewArea, clientArea);
}