int LoadSaveSlotScreenshot(int slnum, int width, int height) {
    int gotSlot;
    multiply_up_coordinates(&width, &height);

    if (read_savedgame_screenshot(get_save_game_path(slnum), gotSlot) != 0)
        return 0;

    if (gotSlot == 0)
        return 0;

    if ((spritewidth[gotSlot] == width) && (spriteheight[gotSlot] == height))
        return gotSlot;

    // resize the sprite to the requested size
    Bitmap *newPic = BitmapHelper::CreateBitmap(width, height, spriteset[gotSlot]->GetColorDepth());
    newPic->StretchBlt(spriteset[gotSlot],
        RectWH(0, 0, spritewidth[gotSlot], spriteheight[gotSlot]),
        RectWH(0, 0, width, height));

    update_polled_stuff_if_runtime();

    // replace the bitmap in the sprite set
    free_dynamic_sprite(gotSlot);
    add_dynamic_sprite(gotSlot, newPic);

    return gotSlot;
}