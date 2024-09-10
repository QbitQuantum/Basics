void ViewProviderFemConstraintGear::updateData(const App::Property* prop)
{
    Fem::ConstraintGear* pcConstraint = static_cast<Fem::ConstraintGear*>(this->getObject());

    // Gets called whenever a property of the attached object changes
    if (strcmp(prop->getName(),"BasePoint") == 0) {
        if (pcConstraint->Height.getValue() > Precision::Confusion()) {
            // Remove and recreate the symbol
            pShapeSep->removeAllChildren();

            Base::Vector3f base = pcConstraint->BasePoint.getValue();
            Base::Vector3f axis = pcConstraint->Axis.getValue();
            Base::Vector3f direction = pcConstraint->DirectionVector.getValue();
            if (direction.Length() < Precision::Confusion())
                direction = Base::Vector3f(0,1,0);
            float radius = pcConstraint->Radius.getValue();
            float dia = pcConstraint->Diameter.getValue();
            if (dia < 2 * radius)
                dia = 2 * radius;
            float angle = pcConstraint->ForceAngle.getValue() / 180 * M_PI;

            SbVec3f b(base.x, base.y, base.z);
            SbVec3f ax(axis.x, axis.y, axis.z);
            SbVec3f dir(direction.x, direction.y, direction.z);
            //Base::Console().Error("DirectionVector: %f, %f, %f\n", direction.x, direction.y, direction.z);

            createPlacement(pShapeSep, b, SbRotation(SbVec3f(0,1,0), ax));
            pShapeSep->addChild(createCylinder(pcConstraint->Height.getValue() * 0.8, dia/2));
            createPlacement(pShapeSep, SbVec3f(dia/2 * sin(angle), 0, dia/2 * cos(angle)), SbRotation(ax, dir));
            pShapeSep->addChild(createArrow(dia/2, dia/8));
        }
    } else if (strcmp(prop->getName(),"Diameter") == 0) {
        if (pShapeSep->getNumChildren() > 0) {
            // Change the symbol
            Base::Vector3f axis = pcConstraint->Axis.getValue();
            Base::Vector3f direction = pcConstraint->DirectionVector.getValue();
            if (direction.Length() < Precision::Confusion())
                direction = Base::Vector3f(0,1,0);
            float dia = pcConstraint->Diameter.getValue();
            float radius = pcConstraint->Radius.getValue();
            if (dia < 2 * radius)
                dia = 2 * radius;
            float angle = pcConstraint->ForceAngle.getValue() / 180 * M_PI;

            SbVec3f ax(axis.x, axis.y, axis.z);
            SbVec3f dir(direction.x, direction.y, direction.z);

            const SoSeparator* sep = static_cast<SoSeparator*>(pShapeSep->getChild(2));
            updateCylinder(sep, 0, pcConstraint->Height.getValue() * 0.8, dia/2);
            updatePlacement(pShapeSep, 3, SbVec3f(dia/2 * sin(angle), 0, dia/2 * cos(angle)), SbRotation(ax, dir));
            sep = static_cast<SoSeparator*>(pShapeSep->getChild(5));
            updateArrow(sep, 0, dia/2, dia/8);
        }
    } else if ((strcmp(prop->getName(),"DirectionVector") == 0) || (strcmp(prop->getName(),"ForceAngle") == 0))  {
        // Note: "Reversed" also triggers "DirectionVector"
        if (pShapeSep->getNumChildren() > 0) {
            // Re-orient the symbol
            Base::Vector3f axis = pcConstraint->Axis.getValue();
            Base::Vector3f direction = pcConstraint->DirectionVector.getValue();
            if (direction.Length() < Precision::Confusion())
                direction = Base::Vector3f(0,1,0);
            float dia = pcConstraint->Diameter.getValue();
            float angle = pcConstraint->ForceAngle.getValue() / 180 * M_PI;

            SbVec3f ax(axis.x, axis.y, axis.z);
            SbVec3f dir(direction.x, direction.y, direction.z);
            /*Base::Console().Error("Axis: %f, %f, %f\n", axis.x, axis.y, axis.z);
            Base::Console().Error("Direction: %f, %f, %f\n", direction.x, direction.y, direction.z);
            SbRotation rot = SbRotation(ax, dir);
            SbMatrix m;
            rot.getValue(m);
            SbMat m2;
            m.getValue(m2);
            Base::Console().Error("Matrix: %f, %f, %f, %f\n", m[0][0], m[1][0], m[2][0], m[3][0]);
            // Note: In spite of the fact that the rotation matrix takes on 3 different values if 3
            // normal directions are chosen, the resulting arrow will only point in two different
            // directions when ax = (1,0,0) (but for ax=(0,1,0) it points in 3 different directions!)
            */

            updatePlacement(pShapeSep, 3, SbVec3f(dia/2 * sin(angle), 0, dia/2 * cos(angle)), SbRotation(ax, dir));
        }
    }

    ViewProviderFemConstraint::updateData(prop);
}