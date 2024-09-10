bool operator==(const CubicBezierTimingFunction& lhs, const TimingFunction& rhs)
{
    if (rhs.type() != TimingFunction::CubicBezierFunction)
        return false;

    const CubicBezierTimingFunction& ctf = toCubicBezierTimingFunction(rhs);
    if ((lhs.subType() == CubicBezierTimingFunction::Custom) && (ctf.subType() == CubicBezierTimingFunction::Custom))
        return (lhs.x1() == ctf.x1()) && (lhs.y1() == ctf.y1()) && (lhs.x2() == ctf.x2()) && (lhs.y2() == ctf.y2());

    return lhs.subType() == ctf.subType();
}