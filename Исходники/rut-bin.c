static void
allocate_cb (RutObject *graphable,
             void *user_data)
{
    RutBin *bin = RUT_BIN (graphable);

    if (bin->child)
    {
        float child_width, child_height;
        float child_x = bin->left_padding;
        float child_y = bin->top_padding;
        float available_width =
            bin->width - bin->left_padding - bin->right_padding;
        float available_height =
            bin->height - bin->top_padding - bin->bottom_padding;

        rut_sizable_get_preferred_width (bin->child,
                                         -1, /* for_height */
                                         NULL, /* min_width_p */
                                         &child_width);

        if (child_width > available_width)
            child_width = available_width;

        switch (bin->x_position)
        {
        case RUT_BIN_POSITION_BEGIN:
            break;

        case RUT_BIN_POSITION_CENTER:
            if (child_width < available_width)
                child_x = nearbyintf (bin->width / 2.0f - child_width / 2.0f);
            break;

        case RUT_BIN_POSITION_END:
            if (child_width < available_width)
                child_x = bin->width - bin->right_padding - child_width;
            break;

        case RUT_BIN_POSITION_EXPAND:
            child_width = available_width;
            break;
        }

        rut_sizable_get_preferred_height (bin->child,
                                          child_width, /* for_width */
                                          NULL, /* min_height_p */
                                          &child_height);

        if (child_height > available_height)
            child_height = available_height;

        switch (bin->y_position)
        {
        case RUT_BIN_POSITION_BEGIN:
            break;

        case RUT_BIN_POSITION_CENTER:
            if (child_height < available_height)
                child_y = nearbyintf (bin->height / 2.0f - child_height / 2.0f);
            break;

        case RUT_BIN_POSITION_END:
            if (child_height < available_height)
                child_y = bin->height - bin->bottom_padding - child_height;
            break;

        case RUT_BIN_POSITION_EXPAND:
            child_height = available_height;
            break;
        }

        rut_transform_init_identity (bin->child_transform);
        rut_transform_translate (bin->child_transform, child_x, child_y, 0.0f);
        rut_sizable_set_size (bin->child, child_width, child_height);
    }
}