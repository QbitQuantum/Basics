Lines
_clipper_ln(ClipperLib::ClipType clipType, const Lines &subject, const Polygons &clip,
    bool safety_offset_)
{
    // convert Lines to Polylines
    Polylines polylines;
    polylines.reserve(subject.size());
    for (const Line &line : subject)
        polylines.emplace_back(Polyline(line.a, line.b));
    
    // perform operation
    polylines = _clipper_pl(clipType, polylines, clip, safety_offset_);
    
    // convert Polylines to Lines
    Lines retval;
    for (Polylines::const_iterator polyline = polylines.begin(); polyline != polylines.end(); ++polyline)
        retval.emplace_back(polyline->operator Line());
    return retval;
}