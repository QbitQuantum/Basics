/*
** We call this routine to emmit the PostScript code
** for the character we have loaded with load_char().
*/
void GlyphToType3::PSConvert(TTStreamWriter& stream)
{
    int j, k;

    /* Step thru the contours.
     * j = index to xcoor, ycoor, tt_flags (point data)
     * k = index to epts_ctr (which points belong to the same contour) */
    for(j = k = 0; k < num_ctr; k++)
    {
        // A TrueType contour consists of on-path and off-path points.
        // Two consecutive on-path points are to be joined with a
        // line; off-path points between on-path points indicate a
        // quadratic spline, where the off-path point is the control
        // point. Two consecutive off-path points have an implicit
        // on-path point midway between them.
        std::list<FlaggedPoint> points;

        // Represent flags and x/y coordinates as a C++ list
        for (; j <= epts_ctr[k]; j++)
        {
            if (!(tt_flags[j] & 1)) {
                points.push_back(FlaggedPoint(OFF_PATH, xcoor[j], ycoor[j]));
            } else {
                points.push_back(FlaggedPoint(ON_PATH, xcoor[j], ycoor[j]));
            }
        }

        if (points.size() == 0) {
            // Don't try to access the last element of an empty list
            continue;
        }

        // For any two consecutive off-path points, insert the implied
        // on-path point.
        FlaggedPoint prev = points.back();
        for (std::list<FlaggedPoint>::iterator it = points.begin();
             it != points.end();
             it++)
        {
            if (prev.flag == OFF_PATH && it->flag == OFF_PATH)
            {
                points.insert(it,
                              FlaggedPoint(ON_PATH,
                                           (prev.x + it->x) / 2,
                                           (prev.y + it->y) / 2));
            }
            prev = *it;
        }
        // Handle the wrap-around: insert a point either at the beginning
        // or at the end that has the same coordinates as the opposite point.
        // This also ensures that the initial point is ON_PATH.
        if (points.front().flag == OFF_PATH)
        {
            assert(points.back().flag == ON_PATH);
            points.insert(points.begin(), points.back());
        }
        else
        {
            assert(points.front().flag == ON_PATH);
            points.push_back(points.front());
        }

        // The first point
        stack(stream, 3);
        PSMoveto(stream, points.front().x, points.front().y);

        // Step through the remaining points
        std::list<FlaggedPoint>::const_iterator it = points.begin();
        for (it++; it != points.end(); /* incremented inside */)
        {
            const FlaggedPoint& point = *it;
            if (point.flag == ON_PATH)
            {
                stack(stream, 3);
                PSLineto(stream, point.x, point.y);
                it++;
            } else {
                std::list<FlaggedPoint>::const_iterator prev = it, next = it;
                prev--;
                next++;
                assert(prev->flag == ON_PATH);
                assert(next->flag == ON_PATH);
                stack(stream, 7);
                PSCurveto(stream,
                          prev->x, prev->y,
                          point.x, point.y,
                          next->x, next->y);
                it++;
                it++;
            }
        }
    }

    /* Now, we can fill the whole thing. */
    stack(stream, 1);
    stream.puts( pdf_mode ? "f" : "_cl" );
} /* end of PSConvert() */