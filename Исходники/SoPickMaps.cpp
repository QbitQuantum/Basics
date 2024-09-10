void
_SoNurbsPickV4CurveMap::intersectLine()

//
////////////////////////////////////////////////////////////////////////
{
    SbVec3f             point;
    SoPickedPoint       *pp;

    if (!pickAction->intersect(CP[0], CP[1], point))
        return;

    pp = pickAction->addIntersection(point);
    if (pp != NULL) {

        SbVec3f         norm;
        SbVec4f         texCoord;
        float           ratioFromV1;

        // Compute normal as vector pointing back along the pick ray.
	norm = -pickAction->getLine().getDirection();
        norm.normalize();
        pp->setObjectNormal(norm);
        pp->setMaterialIndex(0);

        // Compute interpolated texture coordinate 
        ratioFromV1 = ((point - CP[0]).length() /
                       (CP[1] - CP[0]).length());
        texCoord[0] = (TP[0][0] * (1.0 - ratioFromV1) +
                    TP[1][0] * ratioFromV1);
        texCoord[1] = (TP[0][1] * (1.0 - ratioFromV1) +
                    TP[1][1] * ratioFromV1);
        texCoord[2] = 0.0;
        texCoord[3] = 1.0;
        pp->setObjectTextureCoords(texCoord);
    }
}