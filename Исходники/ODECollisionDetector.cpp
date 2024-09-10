void ODECollisionDetectorImpl::updatePosition(int geometryId, const Position& _position)
{
    GeometryExPtr& model = models[geometryId];
    if(model){
        if(model->meshGeomID){
            Vector3 p = _position.translation();
            dMatrix3 R = { _position(0,0), _position(0,1), _position(0,2), 0.0,
                           _position(1,0), _position(1,1), _position(1,2), 0.0,
                           _position(2,0), _position(2,1), _position(2,2), 0.0 };
            dGeomSetPosition(model->meshGeomID, p.x(), p.y(), p.z());
            dGeomSetRotation(model->meshGeomID, R);
        }
        for(vector<dGeomID>::iterator it = model->primitiveGeomID.begin();
            it!=model->primitiveGeomID.end(); it++)
            if(*it){
                Position position = _position * offsetMap[*it];
                Vector3 p = position.translation();
                dMatrix3 R = { position(0,0), position(0,1), position(0,2), 0.0,
                               position(1,0), position(1,1), position(1,2), 0.0,
                               position(2,0), position(2,1), position(2,2), 0.0 };
                dGeomSetPosition(*it, p.x(), p.y(), p.z());
                dGeomSetRotation(*it, R);
            }
    }
}