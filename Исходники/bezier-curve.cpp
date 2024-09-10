void BezierCurve::feed(PathSink &sink, bool moveto_initial) const
{
    if (size() > 4) {
        Curve::feed(sink, moveto_initial);
        return;
    }

    Point ip = controlPoint(0);
    if (moveto_initial) {
        sink.moveTo(ip);
    }
    switch (size()) {
    case 2:
        sink.lineTo(controlPoint(1));
        break;
    case 3:
        sink.quadTo(controlPoint(1), controlPoint(2));
        break;
    case 4:
        sink.curveTo(controlPoint(1), controlPoint(2), controlPoint(3));
        break;
    default:
        // TODO: add a path sink method that accepts a vector of control points
        //       and converts to cubic spline by default
        assert(false);
        break;
    }
}