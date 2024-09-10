UINT RenderCache::Paint(HDC hdc, RectI bounds, DisplayModel* dm, int pageNo, PageInfo* pageInfo,
                        bool* renderOutOfDateCue) {
    AssertCrash(pageInfo->shown && 0.0 != pageInfo->visibleRatio);

    if (!dm->ShouldCacheRendering(pageNo)) {
        int rotation = dm->GetRotation();
        float zoom = dm->GetZoomReal(pageNo);
        bounds = pageInfo->pageOnScreen.Intersect(bounds);

        RectD area = bounds.Convert<double>();
        area.Offset(-pageInfo->pageOnScreen.x, -pageInfo->pageOnScreen.y);
        area = dm->GetEngine()->Transform(area, pageNo, zoom, rotation, true);

        RenderedBitmap* bmp = dm->GetEngine()->RenderBitmap(pageNo, zoom, rotation, &area);
        bool success = bmp && bmp->GetBitmap() && bmp->StretchDIBits(hdc, bounds);
        delete bmp;

        return success ? 0 : RENDER_DELAY_FAILED;
    }

    int rotation = dm->GetRotation();
    float zoom = dm->GetZoomReal();
    USHORT targetRes = GetTileRes(dm, pageNo);
    USHORT maxRes = GetMaxTileRes(dm, pageNo, rotation);
    if (maxRes < targetRes)
        maxRes = targetRes;

    Vec<TilePosition> queue;
    queue.Append(TilePosition(0, 0, 0));
    UINT renderDelayMin = RENDER_DELAY_UNDEFINED;
    bool neededScaling = false;

    while (queue.size() > 0) {
        TilePosition tile = queue.PopAt(0);
        RectI tileOnScreen = GetTileOnScreen(dm->GetEngine(), pageNo, rotation, zoom, tile, pageInfo->pageOnScreen);
        if (tileOnScreen.IsEmpty()) {
            // display an error message when only empty tiles should be drawn (i.e. on page loading errors)
            renderDelayMin = std::min(RENDER_DELAY_FAILED, renderDelayMin);
            continue;
        }
        tileOnScreen = pageInfo->pageOnScreen.Intersect(tileOnScreen);
        RectI isect = bounds.Intersect(tileOnScreen);
        if (isect.IsEmpty())
            continue;

        bool isTargetRes = tile.res == targetRes;
        UINT renderDelay = PaintTile(hdc, isect, dm, pageNo, tile, tileOnScreen, isTargetRes, renderOutOfDateCue,
                                     isTargetRes ? &neededScaling : nullptr);
        if (!(isTargetRes && 0 == renderDelay) && tile.res < maxRes) {
            queue.Append(TilePosition(tile.res + 1, tile.row * 2, tile.col * 2));
            queue.Append(TilePosition(tile.res + 1, tile.row * 2, tile.col * 2 + 1));
            queue.Append(TilePosition(tile.res + 1, tile.row * 2 + 1, tile.col * 2));
            queue.Append(TilePosition(tile.res + 1, tile.row * 2 + 1, tile.col * 2 + 1));
        }
        if (isTargetRes && renderDelay > 0)
            neededScaling = true;
        renderDelayMin = std::min(renderDelay, renderDelayMin);
        // paint tiles from left to right from top to bottom
        if (tile.res > 0 && queue.size() > 0 && tile.res < queue.at(0).res)
            queue.Sort(cmpTilePosition);
    }

#ifdef CONSERVE_MEMORY
    if (!neededScaling) {
        if (renderOutOfDateCue)
            *renderOutOfDateCue = false;
        // free tiles with different resolution
        TilePosition tile(targetRes, (USHORT)-1, 0);
        FreePage(dm, pageNo, &tile);
    }
    FreeNotVisible();
#endif

    return renderDelayMin;
}