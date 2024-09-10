static void
square_samples(GwyContainer *data, GwyRunType run)
{
    GwyDataField *dfield, *dfields[3];
    gdouble xreal, yreal, qx, qy;
    gint oldid, newid, xres, yres;
    GQuark quark;

    g_return_if_fail(run & BASICOPS_RUN_MODES);
    gwy_app_data_browser_get_current(GWY_APP_DATA_FIELD, dfields + 0,
                                     GWY_APP_MASK_FIELD, dfields + 1,
                                     GWY_APP_SHOW_FIELD, dfields + 2,
                                     GWY_APP_DATA_FIELD_ID, &oldid,
                                     0);
    dfield = dfields[0];
    xres = gwy_data_field_get_xres(dfield);
    yres = gwy_data_field_get_yres(dfield);
    xreal = gwy_data_field_get_xreal(dfield);
    yreal = gwy_data_field_get_yreal(dfield);
    qx = xres/xreal;
    qy = yres/yreal;
    if (fabs(log(qx/qy)) > 1.0/hypot(xres, yres)) {
        /* Resample */
        if (qx < qy)
            xres = MAX(GWY_ROUND(xreal*qy), 1);
        else
            yres = MAX(GWY_ROUND(yreal*qx), 1);

        dfields[0] = gwy_data_field_new_resampled(dfields[0], xres, yres,
                                                  GWY_INTERPOLATION_BSPLINE);
        if (dfields[1]) {
            dfields[1]
                = gwy_data_field_new_resampled(dfields[1], xres, yres,
                                               GWY_INTERPOLATION_ROUND);
        }
        if (dfields[2]) {
            dfields[2]
                = gwy_data_field_new_resampled(dfields[2], xres, yres,
                                               GWY_INTERPOLATION_BSPLINE);
        }
    }
    else {
        /* Ratios are equal, just duplicate */
        dfields[0] = gwy_data_field_duplicate(dfields[0]);
        if (dfields[1])
            dfields[1] = gwy_data_field_duplicate(dfields[1]);
        if (dfields[2])
            dfields[2] = gwy_data_field_duplicate(dfields[2]);
    }


    newid = gwy_app_data_browser_add_data_field(dfields[0], data, TRUE);
    g_object_unref(dfields[0]);
    gwy_app_sync_data_items(data, data, oldid, newid, FALSE,
                            GWY_DATA_ITEM_GRADIENT,
                            GWY_DATA_ITEM_RANGE,
                            GWY_DATA_ITEM_MASK_COLOR,
                            0);

    if (dfields[1]) {
        quark = gwy_app_get_mask_key_for_id(newid);
        gwy_container_set_object(data, quark, dfields[1]);
        g_object_unref(dfields[1]);
    }
    if (dfields[2]) {
        quark = gwy_app_get_show_key_for_id(newid);
        gwy_container_set_object(data, quark, dfields[2]);
        g_object_unref(dfields[2]);
    }

    gwy_app_channel_log_add_proc(data, oldid, newid);
}