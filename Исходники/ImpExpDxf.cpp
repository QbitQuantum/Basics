void ImpExpDxfWrite::exportEllipseArc(BRepAdaptor_Curve& c)
{
    gp_Elips ellp = c.Ellipse();
    gp_Pnt p = ellp.Location();
    double center[3] = {0,0,0};
    gPntToTuple(center, p);

    double major = ellp.MajorRadius();
    double minor = ellp.MinorRadius();

    gp_Dir xaxis = ellp.XAxis().Direction();       //direction of major axis
    //rotation appears to be the clockwise angle between major & +Y??
    double rotation = xaxis.AngleWithRef(gp_Dir(0, 1, 0), gp_Dir(0, 0, 1));

    double f = c.FirstParameter();
    double l = c.LastParameter();
    gp_Pnt s = c.Value(f);
    gp_Pnt m = c.Value((l+f)/2.0);
    gp_Pnt e = c.Value(l);

    gp_Vec v1(m,s);
    gp_Vec v2(m,e);
    gp_Vec v3(0,0,1);
    double a = v3.DotCross(v1,v2);     // a = v3 dot (v1 cross v2)
                                       // relates to "handedness" of 3 vectors
                                       // a > 0 ==> v2 is CCW from v1 (righthanded)?
                                       // a < 0 ==> v2 is CW from v1 (lefthanded)?

    double startAngle = fmod(f,2.0*M_PI);  //revolutions
    double endAngle = fmod(l,2.0*M_PI);
    bool endIsCW = (a < 0) ? true: false;      //if !endIsCW swap(start,end)
    //not sure if this is a hack or not. seems to make valid arcs.
    if (!endIsCW) {
        startAngle = -startAngle;
        endAngle   = -endAngle;
    }

    writeEllipse(center, major, minor, rotation, startAngle, endAngle, endIsCW);
}