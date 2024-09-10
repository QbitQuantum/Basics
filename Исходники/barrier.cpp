void constructBarrierPoints(const Vector<Point> &vec, F32 width, Vector<Point> &barrierEnds )
{
    bool loop = vec[0] == vec[vec.size() - 1];

    Vector<Point> edgeVector;
    for(S32 i = 0; i < vec.size() - 1; i++)
    {
        Point e = vec[i+1] - vec[i];
        e.normalize();
        edgeVector.push_back(e);
    }

    Point lastEdge = edgeVector[edgeVector.size() - 1];
    Vector<F32> extend;
    for(S32 i = 0; i < edgeVector.size(); i++)
    {
        Point curEdge = edgeVector[i];
        double cosTheta = curEdge.dot(lastEdge);

        if(cosTheta >= -0.01)
        {
            F32 extendAmt = width * 0.5 * tan( acos(cosTheta) / 2 );
            if(extendAmt > 0.01)
                extendAmt -= 0.01;
            extend.push_back(extendAmt);
        }
        else
            extend.push_back(0);
        lastEdge = curEdge;
    }
    F32 first = extend[0];
    extend.push_back(first);

    for(S32 i = 0; i < edgeVector.size(); i++)
    {
        F32 extendBack = extend[i];
        F32 extendForward = extend[i+1];
        if(i == 0 && !loop)
            extendBack = 0;
        if(i == edgeVector.size() - 1 && !loop)
            extendForward = 0;

        Point start = vec[i] - edgeVector[i] * extendBack;
        Point end = vec[i+1] + edgeVector[i] * extendForward;
        barrierEnds.push_back(start);
        barrierEnds.push_back(end);
    }
}