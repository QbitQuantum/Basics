void
clip_to_rect(PathIterator& path,
             double x0, double y0, double x1, double y1,
             bool inside, std::vector<Polygon>& results)
{
    double xmin, ymin, xmax, ymax;
    if (x0 < x1)
    {
        xmin = x0;
        xmax = x1;
    }
    else
    {
        xmin = x1;
        xmax = x0;
    }

    if (y0 < y1)
    {
        ymin = y0;
        ymax = y1;
    }
    else
    {
        ymin = y1;
        ymax = y0;
    }

    if (!inside)
    {
        std::swap(xmin, xmax);
        std::swap(ymin, ymax);
    }

    Polygon polygon1, polygon2;
    double x = 0, y = 0;
    unsigned code = 0;
    path.rewind(0);

    do
    {
        // Grab the next subpath and store it in polygon1
        polygon1.clear();
        do
        {
            if (code == agg::path_cmd_move_to)
            {
                polygon1.push_back(XY(x, y));
            }

            code = path.vertex(&x, &y);

            if (code == agg::path_cmd_stop)
            {
                break;
            }

            if (code != agg::path_cmd_move_to)
            {
                polygon1.push_back(XY(x, y));
            }
        }
        while ((code & agg::path_cmd_end_poly) != agg::path_cmd_end_poly);

        // The result of each step is fed into the next (note the
        // swapping of polygon1 and polygon2 at each step).
        clip_to_rect_one_step(polygon1, polygon2, clip_to_rect_filters::xlt(xmax));
        clip_to_rect_one_step(polygon2, polygon1, clip_to_rect_filters::xgt(xmin));
        clip_to_rect_one_step(polygon1, polygon2, clip_to_rect_filters::ylt(ymax));
        clip_to_rect_one_step(polygon2, polygon1, clip_to_rect_filters::ygt(ymin));

        // Empty polygons aren't very useful, so skip them
        if (polygon1.size())
        {
            results.push_back(polygon1);
        }
    }
    while (code != agg::path_cmd_stop);
}