// doDraw
//---------------------------------------------------------------------------
void MenuTemplateView::doDraw(const Surface &viewArea, const Surface &clientArea)
{
    //setWorldRect();

    if (Desktop::getVisible("GameView")) {
        clientArea.bltLookup(getClientRect(), Palette::darkGray256.getColorArray());
        clientArea.drawWindowsBorder(Color::white, Color::white, Color::white);

    } else {
        // Set the following to get does exist.
        if (backgroundSurface.getFrameCount() > 0) {
            backgroundSurface.blt(viewArea, 0, 0);
        } else {
            throw Exception("Where is the background surface?");
        }

        //titlePackedSurface.blt(clientArea, bodyTextRect.min.x, 390);
        titlePackedSurface.bltBlend(clientArea, bodyTextRect.min.x, 390, Palette::colorTable6040);
    }

    // Set the following to get does exist.
    //if (titleSurface.getFrameCount() > 0)
    //{
    //	curTitleFlashTime += TimerInterface::getTimeSlice();
    //
    //	if (curTitleFlashTime > titleFlashTimeHalf * 2.0f)
    //	{
    //		// Since we are done, draw the solid image.
    //		titleSurface.blt(viewArea, bodyTextRect.min.x, 394);
    //	}
    //	else if (curTitleFlashTime > titleFlashTimeHalf)
    //	{
    //		float titleFlashPercent = 1.0f - (float(curTitleFlashTime) / float(titleFlashTimeHalf));
    //
    //		titleSurface.bltBrightness(viewArea, iXY(bodyTextRect.min.x, 394), titleFlashPercent);
    //	}
    //	else
    //	{
    //		float titleFlashPercent = float(curTitleFlashTime) / float(titleFlashTimeHalf);
    //
    //		titleSurface.bltBrightness(viewArea, iXY(bodyTextRect.min.x, 394), titleFlashPercent);
    //	}
    //} else
    //{
    //	throw Exception("Where is the title surface?");
    //}

    //iRect r(100, 100, 200, 110);
    //clientArea.fillRect(r, Color::chartreuse);
    //r.translate(iXY(0, 15));
    //clientArea.fillRect(r, Color::cobaltGreen);
    //r.translate(iXY(0, 15));
    //clientArea.fillRect(r, Color::emeraldGreen);
    //r.translate(iXY(0, 15));
    //clientArea.fillRect(r, Color::forestGreen);
    //r.translate(iXY(0, 15));
    //clientArea.fillRect(r, Color::darkOliveGreen);
    //r.translate(iXY(0, 15));
    //clientArea.fillRect(r, Color::terreVerte);
    //r.translate(iXY(0, 15));

    // Set the following to get does exist.
    //if (globeSurface.getFrameCount() > 0)
    //{
    //	globeSurface.nextFrame();
    //	globeSurface.blt(viewArea, 0, 0);
    //	globeSurface.bltBlend(viewArea, 0, 0, Palette::colorTable8020);
    //} else
    //{
    //	throw Exception("Where is the f*****g globe surface?");
    //}

    View::doDraw(viewArea, clientArea);

    //iXY pos;
    //pos.x = 0;
    //pos.y = SCREEN_YPIX - netPanzerLogo.getPixY();

    //netPanzerLogo.nextFrame();
    //netPanzerLogo.blt(viewArea, pos);

} // end doDraw