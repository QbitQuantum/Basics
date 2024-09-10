bool Line::intersect(const CylinderVolume &cyl, 
                           Real           &enter,  
                           Real           &exit ) const
{
    Real  radius = cyl.getRadius();

    Vec3r adir;
    Vec3r o_adir;
    Pnt3r apos;

    cyl.getAxis(apos, adir);

    o_adir = adir;
    adir.normalize();

    bool isect;

    Real  ln;
    Real  dl;
    Vec3r RC;
    Vec3r n;
    Vec3r D;

    RC = _pos - apos;

    n  = _dir.cross (adir);
    ln =  n  .length(    );

    if(ln == 0.f)    // IntersectionLine is parallel to CylinderAxis
    {
        D  = RC - (RC.dot(adir)) * adir;
        dl = D.length();

        if(dl <= radius)   // line lies in cylinder
        {
            enter = 0.f;
            exit  = Inf;
        }
        else
        {
            return false;
        }
    }
    else
    {
        n.normalize();

        dl    = osgAbs(RC.dot(n));        //shortest distance
        isect = (dl <= radius);

        if(isect)
        {                 // if ray hits cylinder
            Real  t;
            Real  s;
            Vec3r O;

            O = RC.cross(adir);
            t = - (O.dot(n)) / ln;
            O = n.cross(adir);

            O.normalize();

            s = osgAbs (
                (osgSqrt ((radius * radius) - (dl * dl))) / (_dir.dot(O)));

            exit = t + s;

            if(exit < 0.f)
                return false;

            enter = t - s;

            if(enter < 0.f)
                enter = 0.f;
        }
        else
        {
            return false;
        }
    }

    Real t;

    Plane bottom(-adir, apos);

    if(bottom.intersect(*this, t))
    {
        if(bottom.isInHalfSpace(_pos))
        {
            if(t > enter) 
                enter = t;
        }
        else
        {
            if(t < exit) 
                exit = t;
        }
    }
    else
    {
        if(bottom.isInHalfSpace(_pos))
            return false;
    }
    
    Plane top(adir, apos + o_adir);

    if(top.intersect(*this, t))
    {
        if(top.isInHalfSpace(_pos))
        {
            if(t > enter)
                enter = t;
        }
        else
        {
            if(t < exit)
                exit = t;
        }
    }
    else
    {
        if(top.isInHalfSpace(_pos))
            return false;
    }

    return (enter < exit);
}