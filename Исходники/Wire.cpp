void Wire::cutWire(osg::Vec3 normal, float dist)
{

    normal.normalize();

    DrawArrayLengths *newPrimitives = new DrawArrayLengths(PrimitiveSet::POLYGON);
    UShortArray *newIndices = new UShortArray();

    int startIndex = 0;

    int index = vert->getNumElements();
    for (unsigned int i = 0; i < primitives->getNumPrimitives(); i++)
    {
        float oldd = -1;
        int numInd = 0;
        for (int v = 0; v < (*primitives)[i]; v++)
        {
            osg::Vec3 p = (*vert)[indices->index(startIndex + v)];
            float d = (p - normal * dist) * normal;
            /* Grundidee:
			* wir laufen allen Punkte von jedem Polygon einmal
			* durch; liegt der Punkte im "Verbleib" Bereich, wird
			* wird er einfach kopiert, liegt er ausserhalb, dann
			* wird er weggelassen
			* !! Immer wenn ein Wechsel zwischen "verbleibt" und\
			* und "weglassen" erfolgt, dann muss mindestens ein
			* zusaetzlicher Punkt eingefuegt werden.
			*/
            if (v == 0 && d >= 0)
            {
                newIndices->push_back((*indices)[startIndex + v]);
                numInd++;
            }
            else
            {
                if (d < 0)
                {
                    if (oldd > 0)
                    {
                        osg::Vec3 b = (*vert)[(*indices)[startIndex + v - 1]];
                        osg::Vec3 r = p - b;
                        float t = (dist - normal * p) / (normal * r);
                        osg::Vec3 newP = p + r * t;
                        osg::Vec3 n1 = (*normals)[(*indices)[startIndex + v]];
                        osg::Vec3 n2 = (*normals)[(*indices)[startIndex + v - 1]];
                        osg::Vec3 newN = n1 + (n1 - n2) * t;
                        vert->push_back(newP);
                        normals->push_back(newN);
                        newIndices->push_back(index);
                        index++;
                        numInd++;
                    }
                    else
                    {
                    }
                }
                else
                {
                    if (oldd < 0)
                    {
                        osg::Vec3 b = (*vert)[(*indices)[startIndex + v - 1]];
                        osg::Vec3 r = p - b;
                        float t = (dist - normal * p) / (normal * r);
                        osg::Vec3 newP = p + r * t;
                        osg::Vec3 n1 = (*normals)[(*indices)[startIndex + v]];
                        osg::Vec3 n2 = (*normals)[(*indices)[startIndex + v - 1]];
                        osg::Vec3 newN = n1 + (n1 - n2) * t;
                        vert->push_back(newP);
                        normals->push_back(newN);
                        newIndices->push_back(index);
                        index++;
                        numInd++;
                    }

                    newIndices->push_back((*indices)[startIndex + v]);
                    numInd++;
                }
            }
            oldd = d;
        }

        osg::Vec3 p = (*vert)[indices->index(startIndex)];
        float d = (p - normal * dist) * normal;

        if (d < 0)
        {
            if (oldd > 0)
            {
                osg::Vec3 b = (*vert)[(*indices)[startIndex + (*primitives)[i] - 1]];
                osg::Vec3 r = p - b;
                float t = (dist - normal * p) / (normal * r);
                osg::Vec3 newP = p + r * t;
                osg::Vec3 n1 = (*normals)[(*indices)[startIndex]];
                osg::Vec3 n2 = (*normals)[(*indices)[startIndex + (*primitives)[i] - 1]];
                osg::Vec3 newN = n1 + (n1 - n2) * t;
                vert->push_back(newP);
                normals->push_back(newN);
                newIndices->push_back(index);
                index++;
                numInd++;
            }
        }
        else
        {
            if (oldd < 0)
            {
                osg::Vec3 b = (*vert)[(*indices)[startIndex + (*primitives)[i] - 1]];
                osg::Vec3 r = p - b;
                float t = (dist - normal * p) / (normal * r);
                osg::Vec3 newP = p + r * t;
                osg::Vec3 n1 = (*normals)[(*indices)[startIndex]];
                osg::Vec3 n2 = (*normals)[(*indices)[startIndex + (*primitives)[i] - 1]];
                osg::Vec3 newN = n1 + (n1 - n2) * t;
                vert->push_back(newP);
                normals->push_back(newN);
                newIndices->push_back(index);
                index++;
                numInd++;
            }
        }
        newPrimitives->push_back(numInd);
        startIndex += (*primitives)[i];
    }

    geom->setVertexIndices(newIndices);
    geom->setNormalIndices(newIndices);

    geom->removePrimitiveSet(0, geom->getNumPrimitiveSets());
    geom->addPrimitiveSet(newPrimitives);
    primitives = newPrimitives;
    indices = newIndices;

    // calcColors();
    geom->dirtyBound();
    geom->dirtyDisplayList();
}