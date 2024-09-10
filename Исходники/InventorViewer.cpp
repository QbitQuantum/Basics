bool InventorViewer::computeCorrectFaceNormal(const SoPickedPoint * pick, bool ccw_face, Eigen::Vector3d& normal, int& shapeIdx)
{
    const SoDetail *pickDetail = pick->getDetail();
    if ((pickDetail != NULL) && (pickDetail->getTypeId() == SoFaceDetail::getClassTypeId()))
    {
        // Picked object is a face
        const SoFaceDetail * fd = dynamic_cast<const SoFaceDetail*>(pickDetail);
        if (!fd)
        {
            ROS_ERROR("Could not cast to face detail");
            return false;
        }

        // face index is always 0 with triangle strips
       // ROS_INFO_STREAM("Face index: "<<fd->getFaceIndex());

        if (fd->getNumPoints() < 3)
        {
            ROS_ERROR("Clicked on degenerate face, can't compute normal");
            return false;
        }
        /*else
        {
            ROS_INFO_STREAM("Clicked on face with "<<fd->getNumPoints()<<" points.");
        }*/       
        
        //ROS_INFO("Pick path:");
        //printPath(pick->getPath());

        /*SbVec3f pickNormal = pick->getNormal();
        //SbVec3f _normalObj=pick->getObjectNormal();
        float _x, _y, _z;
        pickNormal.getValue(_x, _y, _z);
        Eigen::Vector3d normalDef = Eigen::Vector3d(_x, _y, _z);
        normal = normalDef;*/

        // ROS_INFO_STREAM("Clicked on face with "<<fd->getNumPoints()<<" points.");

        int p1 = fd->getPoint(0)->getCoordinateIndex();
        int p2 = fd->getPoint(1)->getCoordinateIndex();
        int p3 = fd->getPoint(2)->getCoordinateIndex();

        // ROS_INFO_STREAM("Face part index: "<<fd->getPartIndex());

        // ROS_INFO_STREAM("First 3 coord indices: "<<p1<<", "<<p2<<", "<<p3);

        // Find the coordinate node that is used for the faces.
        // Assume that it's the last SoCoordinate3 node traversed
        // before the picked shape.
        SoSearchAction  searchCoords;
        searchCoords.setType(SoCoordinate3::getClassTypeId());
        searchCoords.setInterest(SoSearchAction::LAST);
        searchCoords.apply(pick->getPath());

        SbVec3f coord1, coord2, coord3;

        shapeIdx=pick->getPath()->getLength()-1;
        //ROS_INFO_STREAM("Len of pick path: "<<shapeIdx);

        if (searchCoords.getPath() == NULL)
        {
            // try to find SoIndexedShape instead
            // ROS_INFO("No SoCoordinate3 node found, looking for SoIndexedShape...");

            searchCoords.setType(SoIndexedShape::getClassTypeId());
            searchCoords.setInterest(SoSearchAction::LAST);
            searchCoords.apply(pick->getPath());

            if (searchCoords.getPath() == NULL)
            {
                ROS_ERROR("Failed to find coordinate node for the picked face. Returning default normal.");
                return false;
            }

            shapeIdx=searchCoords.getPath()->getLength()-1;
            // ROS_INFO_STREAM("Coords at Idx: "<<shapeIdx);

            // ROS_INFO("SearchCoords path:");
            // printPath(searchCoords.getPath());

            SoIndexedShape * vShapeNode = dynamic_cast<SoIndexedShape*>(searchCoords.getPath()->getTail());
            if (!vShapeNode)
            {
                ROS_ERROR("Could not cast SoIndexedShape");
                return false;
            }
            SoVertexProperty * vProp = dynamic_cast<SoVertexProperty*>(vShapeNode->vertexProperty.getValue());
            if (!vProp)
            {
                ROS_ERROR_STREAM("Could not cast SoVertexProperty.");
                return false;
            }
            coord1 = vProp->vertex[p1];
            coord2 = vProp->vertex[p2];
            coord3 = vProp->vertex[p3];
        }
        else
        {
            shapeIdx=searchCoords.getPath()->getLength()-1;
            
            SoCoordinate3 * coordNode = dynamic_cast<SoCoordinate3*>(searchCoords.getPath()->getTail());
            if (!coordNode)
            {
                ROS_ERROR("Could not cast SoCoordinate3");
                return false;
            }
            coord1 = coordNode->point[p1];
            coord2 = coordNode->point[p2];
            coord3 = coordNode->point[p3];
        }

        if (fd->getNumPoints() > 3)
        {
            ROS_WARN_STREAM("Face with " << fd->getNumPoints() <<
                            " points is not a triangle and may lead to wrong normal calculations.");
        }

        /*ROS_INFO_STREAM("Coords "<<p1<<", "<<p2<<", "<<p3);
        float _x, _y, _z;
        coord1.getValue(_x, _y, _z);
        ROS_INFO_STREAM("val1 "<<_x<<", "<<_y<<", "<<_z);
        coord2.getValue(_x, _y, _z);
        ROS_INFO_STREAM("val2 "<<_x<<", "<<_y<<", "<<_z);
        coord3.getValue(_x, _y, _z);
        ROS_INFO_STREAM("val3 "<<_x<<", "<<_y<<", "<<_z);*/

        SbVec3f diff1(coord2.getValue());
        diff1 -= coord1;
        SbVec3f diff2(coord3.getValue());
        diff2 -= coord1;
        SbVec3f cross = diff1.cross(diff2);
        if (!ccw_face) cross = -cross;

        float x, y, z;
        cross.getValue(x, y, z);
        double len = sqrt(x * x + y * y + z * z);
        x /= len;
        y /= len;
        z /= len;

        normal = Eigen::Vector3d(x, y, z);

        return true;
    }
    return false;
}