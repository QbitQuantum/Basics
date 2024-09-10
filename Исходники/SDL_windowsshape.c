int
Win32_SetWindowShape(SDL_WindowShaper *shaper,SDL_Surface *shape,SDL_WindowShapeMode *shape_mode) {
    SDL_ShapeData *data;
    HRGN mask_region = NULL;

    if( (shaper == NULL) ||
        (shape == NULL) ||
        ((shape->format->Amask == 0) && (shape_mode->mode != ShapeModeColorKey)) ||
        (shape->w != shaper->window->w) ||
        (shape->h != shaper->window->h) ) {
        return SDL_INVALID_SHAPE_ARGUMENT;
    }

    data = (SDL_ShapeData*)shaper->driverdata;
    if(data->mask_tree != NULL)
        SDL_FreeShapeTree(&data->mask_tree);
    data->mask_tree = SDL_CalculateShapeTree(*shape_mode,shape);

    SDL_TraverseShapeTree(data->mask_tree,&CombineRectRegions,&mask_region);
    SDL_assert(mask_region != NULL);

    SetWindowRgn(((SDL_WindowData *)(shaper->window->driverdata))->hwnd, mask_region, TRUE);

    return 0;
}