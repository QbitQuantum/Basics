void
WSNamesScreen::drawText (const GLMatrix &matrix)
{
    GLfloat  alpha;
    float    x, y, border = 10.0f;
    CompRect oe = screen->getCurrentOutputExtents ();

    x = oe.centerX () - textData.getWidth () / 2;

    /* assign y (for the lower corner!) according to the setting */
    switch (optionGetTextPlacement ())
    {
    case WorkspacenamesOptions::TextPlacementCenteredOnScreen:
        y = oe.centerY () + textData.getHeight () / 2;
        break;
    case WorkspacenamesOptions::TextPlacementTopOfScreen:
    case WorkspacenamesOptions::TextPlacementBottomOfScreen:
    {
        CompRect workArea = screen->currentOutputDev ().workArea ();

        if (optionGetTextPlacement () ==
                WorkspacenamesOptions::TextPlacementTopOfScreen)
            y = oe.y1 () + workArea.y () +
                (2 * border) + textData.getHeight ();
        else
            y = oe.y1 () + workArea.y () +
                workArea.height () - (2 * border);
    }
    break;
    default:
        return;
        break;
    }

    if (timer)
        alpha = timer / (optionGetFadeTime () * 1000.0f);
    else
        alpha = 1.0f;

    textData.draw (matrix, floor (x), floor (y), alpha);
}