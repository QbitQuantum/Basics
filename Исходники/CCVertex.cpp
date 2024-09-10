NS_CC_BEGIN

void ccVertexLineToPolygon(Vec2 *points, float stroke, Vec2 *vertices, unsigned int offset, unsigned int nuPoints)
{
    nuPoints += offset;
    if(nuPoints<=1) return;

    stroke *= 0.5f;

    unsigned int idx;
    unsigned int nuPointsMinus = nuPoints-1;

    for(unsigned int i = offset; i<nuPoints; i++)
    {
        idx = i*2;
        Vec2 p1 = points[i];
        Vec2 perpVector;

        if(i == 0)
            perpVector = (p1 - points[i+1]).getNormalized().getPerp();
        else if(i == nuPointsMinus)
            perpVector = (points[i-1] - p1).getNormalized().getPerp();
        else
        {
            Vec2 p2 = points[i+1];
            Vec2 p0 = points[i-1];

            Vec2 p2p1 = (p2 - p1).getNormalized();
            Vec2 p0p1 = (p0 - p1).getNormalized();

            // Calculate angle between vectors
            float angle = acosf(p2p1.dot(p0p1));

            if(angle < CC_DEGREES_TO_RADIANS(70))
                perpVector = p2p1.getMidpoint(p0p1).getNormalized().getPerp();
            else if(angle < CC_DEGREES_TO_RADIANS(170))
                perpVector = p2p1.getMidpoint(p0p1).getNormalized();
            else
                perpVector = (p2 - p0).getNormalized().getPerp();
        }
        perpVector = perpVector * stroke;

        vertices[idx].set(p1.x + perpVector.x, p1.y + perpVector.y);
        vertices[idx + 1].set(p1.x - perpVector.x, p1.y - perpVector.y);

    }

    // Validate vertexes
    offset = (offset==0) ? 0 : offset-1;
    for(unsigned int i = offset; i<nuPointsMinus; i++)
    {
        idx = i*2;
        const unsigned int idx1 = idx+2;

        Vec2 p1 = vertices[idx];
        Vec2 p2 = vertices[idx+1];
        Vec2 p3 = vertices[idx1];
        Vec2 p4 = vertices[idx1+1];

        float s;
        //BOOL fixVertex = !ccpLineIntersect(Vec2(p1.x, p1.y), Vec2(p4.x, p4.y), Vec2(p2.x, p2.y), Vec2(p3.x, p3.y), &s, &t);
        bool fixVertex = !ccVertexLineIntersect(p1.x, p1.y, p4.x, p4.y, p2.x, p2.y, p3.x, p3.y, &s);
        if(!fixVertex)
            if (s<0.0f || s>1.0f)
                fixVertex = true;

        if(fixVertex)
        {
            vertices[idx1] = p4;
            vertices[idx1+1] = p3;
        }
    }
}