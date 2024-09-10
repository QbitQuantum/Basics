void DynamicSprite_Resize(ScriptDynamicSprite *sds, int width, int height) {
    if ((width < 1) || (height < 1))
        quit("!DynamicSprite.Resize: width and height must be greater than zero");
    if (sds->slot == 0)
        quit("!DynamicSprite.Resize: sprite has been deleted");

    multiply_up_coordinates(&width, &height);

    if (width * height >= 25000000)
        quitprintf("!DynamicSprite.Resize: new size is too large: %d x %d", width, height);

    // resize the sprite to the requested size
    Bitmap *newPic = BitmapHelper::CreateBitmap(width, height, spriteset[sds->slot]->GetColorDepth());
    newPic->StretchBlt(spriteset[sds->slot],
        RectWH(0, 0, spritewidth[sds->slot], spriteheight[sds->slot]),
        RectWH(0, 0, width, height));

    delete spriteset[sds->slot];

    // replace the bitmap in the sprite set
    add_dynamic_sprite(sds->slot, newPic, (game.spriteflags[sds->slot] & SPF_ALPHACHANNEL) != 0);
}