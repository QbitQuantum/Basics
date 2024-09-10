int TrackBallManipulator::hitSphere(int posX, int posY, Vec3 &intersect)
{
    Vec3 rayPoint;
    Vec3 rayDir;
    getSceneGraph()->getCamera()->get_project_ray(posX,posY,rayPoint,rayDir);
    rayDir.Normalize();
    Vec3 center = getSceneGraph()->getCamera()->center();
    Quat quat;
    quat.convertFromMatrix(getSceneGraph()->getCamera()->get_model_matrix());
    HomoMatrix4 inverseModelMatrix = quat.conjugate().convertToMatrix();
    Vec3 np = inverseModelMatrix * Vec3(0,0,1);
    Vec3 hitPlane;
    if(Vec3::getIntersectionRayToPlane(rayPoint,rayDir,center,np,hitPlane))
    {
        Vec3 v = hitPlane - center;
        Scalar len = v.length();
        bool isNearOne = true;
        v.Normalize();
        int k = len / this->getRadius();

        Scalar residual = len - this->getRadius() * k;
        Vec3 planePoint = hitPlane;
        if(k % 4== 0)
        {
            planePoint = center + v * residual;
        }
        else if(k % 4== 1)
        {
            planePoint = center + v * (this->getRadius() - residual);
            isNearOne = false;
        }
        else if(k % 4== 2)
        {
            planePoint = center - v * residual;
            isNearOne = false;
        }
        else
        {
            planePoint = center - v * (this->getRadius() - residual);
        }
        Vec3 dir = planePoint - rayPoint;
        dir.Normalize();
        if(getIntersectionToSphere(rayPoint,dir,intersect,isNearOne))
        {
            return k % 4;
        }
    }
    intersect = Vec3::getClosestPointFromPointToRay(center,rayPoint,rayDir);
    return -1;
}