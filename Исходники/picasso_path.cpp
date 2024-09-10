void PICAPI ps_path_arc_to(ps_path* path, float rx, float ry, float a, ps_bool large, ps_bool cw, const ps_point* ep)
{
    if (!picasso::is_valid_system_device()) {
        global_status = STATUS_DEVICE_ERROR;
        return;
    }

    if (!path || !ep || rx <= 0.0 || ry <= 0.0) {
        global_status = STATUS_INVALID_ARGUMENT;
        return;
    }

    scalar x1 = path->path.last_x();
    scalar y1 = path->path.last_y();

    picasso::bezier_arc_svg arc(x1, y1, FLT_TO_SCALAR(rx), FLT_TO_SCALAR(ry), FLT_TO_SCALAR(a),
                            (large ? true : false), (cw ? true : false), FLT_TO_SCALAR(ep->x), FLT_TO_SCALAR(ep->y));
    picasso::conv_curve cr(arc);
    if (picasso::_is_closed_path(path->path))
        path->path.concat_path(cr, 0);
    else
        path->path.join_path(cr, 0);
    global_status = STATUS_SUCCEED;
}