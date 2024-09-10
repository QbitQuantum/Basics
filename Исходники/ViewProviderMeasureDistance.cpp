void ViewProviderMeasureDistance::updateData(const App::Property* prop)
{
    if (prop->getTypeId() == App::PropertyVector::getClassTypeId() ||
        prop == &Mirror || prop == &DistFactor) {
        if (strcmp(prop->getName(),"P1") == 0) {
            Base::Vector3d v = static_cast<const App::PropertyVector*>(prop)->getValue();
            pCoords->point.set1Value(0, SbVec3f(v.x,v.y,v.z));
        }
        else if (strcmp(prop->getName(),"P2") == 0) {
            Base::Vector3d v = static_cast<const App::PropertyVector*>(prop)->getValue();
            pCoords->point.set1Value(1, SbVec3f(v.x,v.y,v.z));
        }

        SbVec3f pt1 = pCoords->point[0];
        SbVec3f pt2 = pCoords->point[1];
        SbVec3f dif = pt1-pt2;

        float length = fabs(dif.length())*DistFactor.getValue();
        if (Mirror.getValue())
            length = -length;


        if (dif.sqrLength() < 10.0e-6f) {
            pCoords->point.set1Value(2, pt1+SbVec3f(0.0f,0.0f,length));
            pCoords->point.set1Value(3, pt2+SbVec3f(0.0f,0.0f,length));
        }
        else {
            SbVec3f dir = dif.cross(SbVec3f(1.0f,0.0f,0.0f));
            if (dir.sqrLength() < 10.0e-6f)
                dir = dif.cross(SbVec3f(0.0f,1.0f,0.0f));
            if (dir.sqrLength() < 10.0e-6f)
                dir = dif.cross(SbVec3f(0.0f,0.0f,1.0f));
            dir.normalize();
            if (dir.dot(SbVec3f(0.0f,0.0f,1.0f)) < 0.0f)
                length = -length;
            pCoords->point.set1Value(2, pt1 + length*dir);
            pCoords->point.set1Value(3, pt2 + length*dir);
        }

        SbVec3f pos = (pCoords->point[2]+pCoords->point[3])/2.0f;
        pTranslation->translation.setValue(pos);

        std::stringstream s;
        s.precision(3);
        s.setf(std::ios::fixed | std::ios::showpoint);
        s << dif.length();
        pLabel->string.setValue(s.str().c_str());
    }

    ViewProviderDocumentObject::updateData(prop);
}