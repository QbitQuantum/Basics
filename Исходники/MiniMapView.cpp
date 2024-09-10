// doDraw
//---------------------------------------------------------------------------
void MiniMapView::doDraw(const Surface &viewArea, const Surface &clientArea)
{
    assert(this != 0);
    assert(viewArea.getDoesExist());
    assert(clientArea.getDoesExist());

    if (decreaseSize != 0) {
        doDecreaseSize(decreaseSize);
        decreaseSize = 0;
    }
    if (increaseSize != 0) {
        doIncreaseSize(increaseSize);
        increaseSize = 0;
    }

    float dt = TimerInterface::getTimeSlice();

    Surface *miniMap;
    miniMap = MiniMapInterface::getMiniMap();

    if (needScale) {
        scaleGroupWait += dt;

        if (scaleGroupWait > 1.0f) {
            miniMapSurface.create(getViewRect().getSize(), getViewRect().getSize().x , 1);

            //miniMapSurface.scale(getViewRect().getSize());
            iRect r(iXY(0, 0), getViewRect().getSize());

            miniMapSurface.bltScale(*miniMap, r);

            needScale      = false;
            scaleGroupWait = 0.0f;
        }
    }

    iRect r(getViewRect().min, getViewRect().max);

    if (needScale) {
        // Draw the slow on the fly scaled map.
        if (mapDrawType == MAP_SOLID) {
            clientArea.bltScale(*miniMap, r);
        } else if (mapDrawType == MAP_2080) {
            clientArea.bltBlendScale(*miniMap, r, Palette::colorTable2080);
        } else if (mapDrawType == MAP_4060) {
            clientArea.bltBlendScale(*miniMap, r, Palette::colorTable4060);
        }
        //else if (mapDrawType == MAP_BLEND_GREEN)
        //{
        //clientArea.bltLookup(iRect(iXY(0, 0), getSize()), Palette::green256.getColorArray());
        //}
        else if (mapDrawType == MAP_BLEND_GRAY) {
            clientArea.bltLookup(iRect(iXY(0, 0), getSize()), Palette::gray256.getColorArray());
        } else if (mapDrawType == MAP_BLEND_DARK_GRAY) {
            clientArea.bltLookup(iRect(iXY(0, 0), getSize()), Palette::darkGray256.getColorArray());
        } else if (mapDrawType == MAP_BLACK) {
            clientArea.fill(Color::black);
        } else if (mapDrawType == MAP_TRANSPARENT) {}
    }
    else {
        // Draw the fast not on the fly scaled map.
        if (mapDrawType == MAP_SOLID) {
            miniMapSurface.blt(clientArea, 0, 0);
        } else if (mapDrawType == MAP_2080) {
            clientArea.blendIn(miniMapSurface, iXY(0, 0), Palette::colorTable2080);
        } else if (mapDrawType == MAP_4060) {
            clientArea.blendIn(miniMapSurface, iXY(0, 0), Palette::colorTable4060);
        }
        //else if (mapDrawType == MAP_BLEND_GREEN)
        //{
        //clientArea.bltLookup(iRect(iXY(0, 0), getSize()), Palette::green256.getColorArray());
        //}
        else if (mapDrawType == MAP_BLEND_GRAY) {
            clientArea.bltLookup(iRect(iXY(0, 0), getSize()), Palette::gray256.getColorArray());
        } else if (mapDrawType == MAP_BLEND_DARK_GRAY) {
            clientArea.bltLookup(iRect(iXY(0, 0), getSize()), Palette::darkGray256.getColorArray());
        } else if (mapDrawType == MAP_BLACK) {
            clientArea.fill(Color::black);
        } else if (mapDrawType == MAP_TRANSPARENT) {}
    }

    // Draw a hairline border.
    //viewArea.drawRect(Color::white);
    viewArea.drawLookupBorder(Palette::darkGray256.getColorArray());

    // Draw the world view box.
    clientArea.bltLookup(MiniMapInterface::getWorldWindow(), Palette::darkGray256.getColorArray());

    // Draw the units and such on the minimap.
    MiniMapInterface::annotateMiniMap((Surface &) clientArea);

    // Draw the world view box corners.
    clientArea.drawBoxCorners(MiniMapInterface::getWorldWindow(), 5, Color::white);

    // Draw an inner black rect inside the outer white rect, for visibility reasons.
    //iRect innerRect(MiniMapInterface::getWorldWindow());
    //
    //innerRect.min += 1;
    //innerRect.max -= 1;
    //
    //clientArea.drawBoxCorners(innerRect, 4, Color::black);

    // If the mouse is over the client area, then change the cursor.
    if (getClientRect().contains(getScreenToClientPos(mouse.getScreenPos()))) {
        if (selectionAnchor) {
            // Since we are selecting units, draw the selection box.
            clientArea.drawRect(selectionAnchorDownPos, selectionAnchorCurPos, Color::white);
        } else {
            // Draw a box which show where the area which you click will be located.
            drawMouseBox(clientArea);
        }
    }

    GameTemplateView::doDraw(viewArea, clientArea);

} // end doDraw