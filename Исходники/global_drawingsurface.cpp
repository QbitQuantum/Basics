void RawDrawImageResized(int xx, int yy, int gotSlot, int width, int height) {
    if ((gotSlot < 0) || (gotSlot >= MAX_SPRITES) || (spriteset[gotSlot] == NULL))
        quit("!RawDrawImageResized: invalid sprite slot number specified");
    // very small, don't draw it
    if ((width < 1) || (height < 1))
        return;

    multiply_up_coordinates(&xx, &yy);
    multiply_up_coordinates(&width, &height);

    // resize the sprite to the requested size
    Bitmap *newPic = BitmapHelper::CreateBitmap(width, height, spriteset[gotSlot]->GetColorDepth());

    newPic->StretchBlt(spriteset[gotSlot],
        RectWH(0, 0, spritewidth[gotSlot], spriteheight[gotSlot]),
        RectWH(0, 0, width, height));

    RAW_START();
    if (newPic->GetColorDepth() != abuf->GetColorDepth())
        quit("!RawDrawImageResized: image colour depth mismatch: the background image must have the same colour depth as the sprite being drawn");

    put_sprite_256(xx, yy, newPic);
    delete newPic;
    invalidate_screen();
    mark_current_background_dirty();
    update_polled_stuff_if_runtime();  // this operation can be slow so stop music skipping
    RAW_END();
}