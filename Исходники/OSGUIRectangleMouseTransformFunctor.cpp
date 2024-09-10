bool UIRectangleMouseTransformFunctor::viewportToRenderingSurface(const Pnt2f& ViewportPoint,
                                                                  const Viewport* TheViewport,
                                                                  Pnt2f& Result) const
{
    //Get Viewport to View Space line
    Line l;
    if( !TheViewport->getCamera()->calcViewRay( l, ViewportPoint.x(), ViewportPoint.y(), *TheViewport ) )
    {
        return false;
    }

    //Transform Line to UIRectangle Space
    Matrix m ;
    getParent()->accumulateMatrix(m);

    m.invert();

    Pnt3f pos;
    Vec3f dir;

    m.multFull(l.getPosition (), pos);
    m.mult    (l.getDirection(), dir);

    l.setValue(pos, dir);
    //ia->scale(dir.length());

    //Intersect the Line with the UIRectangle quad
    Real32 t;
    if(!intersectLineRect(l,getParent()->getPoint(),
                          getParent()->getPoint() + Vec3f(getParent()->getWidth(),0,0),
                          getParent()->getPoint() + Vec3f(getParent()->getWidth(),getParent()->getHeight(),0),
                          getParent()->getPoint() + Vec3f(0,getParent()->getHeight(),0)
                          ,t))
    {
        return false;
    }

    //Return the point on the quad of the intersection if there was one
    Result.setValues(l.getPosition().x() + t*l.getDirection().x() - getParent()->getPoint().x(), 
                     getParent()->getHeight() - l.getPosition().y() - t*l.getDirection().y() + getParent()->getPoint().y());
    return true;
}