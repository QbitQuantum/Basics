void modify_roi_in(struct dt_iop_module_t *self, struct dt_dev_pixelpipe_iop_t *piece, const dt_iop_roi_t *roi_out, dt_iop_roi_t *roi_in)
{
    *roi_in = *roi_out;

    int roir = roi_in->width+roi_in->x;
    int roib = roi_in->height+roi_in->y;
    int roix = roi_in->x;
    int roiy = roi_in->y;

    //dt_iop_spots_params_t *d = (dt_iop_spots_params_t *)piece->data;
    dt_develop_blend_params_t *bp = self->blend_params;

    // We iterate through all spots or polygons
    dt_masks_form_t *grp = dt_masks_get_from_id(darktable.develop,bp->mask_id);
    if (grp && (grp->type & DT_MASKS_GROUP))
    {
        GList *forms = g_list_first(grp->points);
        while(forms)
        {
            dt_masks_point_group_t *grpt = (dt_masks_point_group_t *)forms->data;
            //we get the spot
            dt_masks_form_t *form = dt_masks_get_from_id(self->dev,grpt->formid);
            if (form)
            {
                //we get the area for the form
                int fl,ft,fw,fh;
                if (!dt_masks_get_area(self,piece,form,&fw,&fh,&fl,&ft))
                {
                    forms = g_list_next(forms);
                    continue;
                }

                //if the form is outside the roi, we just skip it
                fw *= roi_in->scale, fh *= roi_in->scale, fl *= roi_in->scale, ft *= roi_in->scale;
                if (ft>=roi_out->y+roi_out->height || ft+fh<=roi_out->y || fl>=roi_out->x+roi_out->width || fl+fw<=roi_out->x)
                {
                    forms = g_list_next(forms);
                    continue;
                }

                //we get the area for the source
                if (!dt_masks_get_source_area(self,piece,form,&fw,&fh,&fl,&ft))
                {
                    forms = g_list_next(forms);
                    continue;
                }
                fw *= roi_in->scale, fh *= roi_in->scale, fl *= roi_in->scale, ft *= roi_in->scale;

                //we enlarge the roi if needed
                roiy = fminf(ft,roiy);
                roix = fminf(fl,roix);
                roir = fmaxf(fl+fw,roir);
                roib = fmaxf(ft+fh,roib);
            }
            forms = g_list_next(forms);
        }
    }

    //now we set the values
    roi_in->x = CLAMP(roix, 0, piece->pipe->iwidth*roi_in->scale-1);
    roi_in->y = CLAMP(roiy, 0, piece->pipe->iheight*roi_in->scale-1);
    roi_in->width = CLAMP(roir-roi_in->x, 1, piece->pipe->iwidth*roi_in->scale-roi_in->x);
    roi_in->height = CLAMP(roib-roi_in->y, 1, piece->pipe->iheight*roi_in->scale-roi_in->y);
}