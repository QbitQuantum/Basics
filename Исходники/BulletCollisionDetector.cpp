void BulletCollisionDetectorImpl::addMesh(GeometryEx* model)
{
    SgMesh* mesh = meshExtractor->currentMesh();
    const Affine3& T = meshExtractor->currentTransform();

    bool meshAdded = false;
    
    if(mesh->primitiveType() != SgMesh::MESH){
        bool doAddPrimitive = false;
        Vector3 scale;
        optional<Vector3> translation;
        if(!meshExtractor->isCurrentScaled()){
            scale.setOnes();
            doAddPrimitive = true;
        } else {
            Affine3 S = meshExtractor->currentTransformWithoutScaling().inverse() *
                meshExtractor->currentTransform();

            if(S.linear().isDiagonal()){
                if(!S.translation().isZero()){
                    translation = S.translation();
                }
                scale = S.linear().diagonal();
                if(mesh->primitiveType() == SgMesh::BOX){
                    doAddPrimitive = true;
                } else if(mesh->primitiveType() == SgMesh::SPHERE){
                    // check if the sphere is uniformly scaled for all the axes
                    if(scale.x() == scale.y() && scale.x() == scale.z()){
                        doAddPrimitive = true;
                    }
                } else if(mesh->primitiveType() == SgMesh::CYLINDER){
                    // check if the bottom circle face is uniformly scaled
                    if(scale.x() == scale.z()){
                        doAddPrimitive = true;
                    }
                } else if(mesh->primitiveType() == SgMesh::CONE){
                    if(scale.x() == scale.z()){
                        doAddPrimitive = true;
                    }
                }
            }
        }
        if(doAddPrimitive){
            bool created = false;

            btCollisionShape* primitiveShape;
            switch(mesh->primitiveType()){
            case SgMesh::BOX : {
                const Vector3& s = mesh->primitive<SgMesh::Box>().size;
                primitiveShape = new btBoxShape(btVector3(s.x() * scale.x()/2.0, s.y() * scale.y()/2.0, s.z() * scale.z()/2.0));
                created = true;
                break; }
            case SgMesh::SPHERE : {
                SgMesh::Sphere sphere = mesh->primitive<SgMesh::Sphere>();
                primitiveShape = new btSphereShape(sphere.radius * scale.x());
                created = true;
                break; }
            case SgMesh::CYLINDER : {
                SgMesh::Cylinder cylinder = mesh->primitive<SgMesh::Cylinder>();
                primitiveShape = new btCylinderShape(btVector3(cylinder.radius * scale.x(), cylinder.height * scale.y()/2.0, cylinder.radius * scale.x()));
                created = true;
                break; }
            case SgMesh::CONE : {
                SgMesh::Cone cone = mesh->primitive<SgMesh::Cone>();
                primitiveShape = new btConeShape(cone.radius * scale.x(), cone.height * scale.y());
                created = true;
                break; }
            default :
                break;
            }
            if(created){
                primitiveShape->setMargin(DEFAULT_COLLISION_MARGIN);
                btCompoundShape* compoundShape = dynamic_cast<btCompoundShape*>(model->collisionShape);
                if(!compoundShape){
                    model->collisionShape = new btCompoundShape();
                    model->collisionShape->setLocalScaling(btVector3(1.f,1.f,1.f));
                    compoundShape = dynamic_cast<btCompoundShape*>(model->collisionShape);
                }
                Affine3 T_ = meshExtractor->currentTransformWithoutScaling();
                if(translation){
                    T_ *= Translation3(*translation);
                }
                btVector3 p(T_(0,3), T_(1,3), T_(2,3));
                btMatrix3x3 R(T_(0,0), T_(0,1), T_(0,2),
                              T_(1,0), T_(1,1), T_(1,2),
                              T_(2,0), T_(2,1), T_(2,2));
                btTransform btT(R, p);
                compoundShape->addChildShape(btT, primitiveShape);
                meshAdded = true;
            }
        }
    }

    if(!meshAdded){
        if(!useHACD || model->isStatic){
            const int vertexIndexTop = model->vertices.size() / 3;

            const SgVertexArray& vertices_ = *mesh->vertices();
            const int numVertices = vertices_.size();
            for(int i=0; i < numVertices; ++i){
                const Vector3 v = T * vertices_[i].cast<Position::Scalar>();
                model->vertices.push_back((btScalar)v.x());
                model->vertices.push_back((btScalar)v.y());
                model->vertices.push_back((btScalar)v.z());
            }

            const int numTriangles = mesh->numTriangles();
            for(int i=0; i < numTriangles; ++i){
                SgMesh::TriangleRef tri = mesh->triangle(i);
                model->triangles.push_back(vertexIndexTop + tri[0]);
                model->triangles.push_back(vertexIndexTop + tri[1]);
                model->triangles.push_back(vertexIndexTop + tri[2]);
            }
        }else{
            btConvexHullShape* convexHullShape = dynamic_cast<btConvexHullShape*>(model->collisionShape);
            if(convexHullShape){
                btCompoundShape* compoundShape = new btCompoundShape();
                compoundShape->setLocalScaling(btVector3(1.f,1.f,1.f));

                btTransform T;
                T.setIdentity();
                compoundShape->addChildShape(T, convexHullShape);
                model->collisionShape = compoundShape;
            }

            std::vector< HACD::Vec3<HACD::Real> > points;
            std::vector< HACD::Vec3<long> > triangles;

            const SgVertexArray& vertices_ = *mesh->vertices();
            const int numVertices = vertices_.size();
            for(int i=0; i < numVertices; ++i){
                const Vector3 v = T * vertices_[i].cast<Position::Scalar>();
                HACD::Vec3<HACD::Real> vertex(v.x(), v.y(), v.z());
                points.push_back(vertex);
            }

            const int numTriangles = mesh->numTriangles();
            for(int i=0; i < numTriangles; ++i){
                SgMesh::TriangleRef tri = mesh->triangle(i);
                HACD::Vec3<long> triangle(tri[0], tri[1], tri[2]);
                triangles.push_back(triangle);
            }

            HACD::HACD hacd;
            hacd.SetPoints(&points[0]);
            hacd.SetNPoints(points.size());
            hacd.SetTriangles(&triangles[0]);
            hacd.SetNTriangles(triangles.size());
            hacd.SetCompacityWeight(0.1);
            hacd.SetVolumeWeight(0.0);

            size_t nClusters = 1;
            double concavity = 100;
            bool invert = false;
            bool addExtraDistPoints = false;
            bool addNeighboursDistPoints = false;
            bool addFacesPoints = false;       

            hacd.SetNClusters(nClusters);                     // minimum number of clusters
            hacd.SetNVerticesPerCH(100);                      // max of 100 vertices per convex-hull
            hacd.SetConcavity(concavity);                     // maximum concavity
            hacd.SetAddExtraDistPoints(addExtraDistPoints);   
            hacd.SetAddNeighboursDistPoints(addNeighboursDistPoints);   
            hacd.SetAddFacesPoints(addFacesPoints); 
            hacd.Compute();

            btTransform T;
            T.setIdentity();

            nClusters = hacd.GetNClusters();
            if(nClusters>1){
                btCompoundShape* compoundShape = dynamic_cast<btCompoundShape*>(model->collisionShape);
                if(!compoundShape){
                    model->collisionShape = new btCompoundShape();
                    model->collisionShape->setLocalScaling(btVector3(1.f,1.f,1.f));
                }
            }

            for(size_t i=0; i<nClusters; i++){
                size_t nPoints = hacd.GetNPointsCH(i);
                size_t nTriangles = hacd.GetNTrianglesCH(i);

                HACD::Vec3<HACD::Real> * pointsCH = new HACD::Vec3<HACD::Real>[nPoints];
                HACD::Vec3<long> * trianglesCH = new HACD::Vec3<long>[nTriangles];
                hacd.GetCH(i, pointsCH, trianglesCH);
                
                btAlignedObjectArray<btVector3> newVertices_;
                for(size_t j=0; j<nTriangles; j++){
                    long index0 = trianglesCH[j].X();
                    long index1 = trianglesCH[j].Y();
                    long index2 = trianglesCH[j].Z();
                    btVector3 vertex0(pointsCH[index0].X(), pointsCH[index0].Y(), pointsCH[index0].Z());
                    btVector3 vertex1(pointsCH[index1].X(), pointsCH[index1].Y(), pointsCH[index1].Z());
                    btVector3 vertex2(pointsCH[index2].X(), pointsCH[index2].Y(), pointsCH[index2].Z());
                    newVertices_.push_back(vertex0);
                    newVertices_.push_back(vertex1);
                    newVertices_.push_back(vertex2);
                }
                delete [] pointsCH;
                delete [] trianglesCH;

                /*
                  float collisionMargin = 0.01f;
                  btAlignedObjectArray<btVector3> planeEquations;
                  btGeometryUtil::getPlaneEquationsFromVertices(newVertices_, planeEquations);

                  btAlignedObjectArray<btVector3> shiftedPlaneEquations;
                  for (int j=0; j<planeEquations.size(); j++){
                  btVector3 plane = planeEquations[j];
                  plane[3] += collisionMargin;
                  shiftedPlaneEquations.push_back(plane);
                  }
                  btAlignedObjectArray<btVector3> shiftedVertices;
                  btGeometryUtil::getVerticesFromPlaneEquations(shiftedPlaneEquations,shiftedVertices);
                
                  btConvexHullShape* convexHullShape_ = new btConvexHullShape(&(shiftedVertices[0].getX()),shiftedVertices.size());
                */
                btConvexHullShape* convexHullShape_ = new btConvexHullShape(&(newVertices_[0].getX()), newVertices_.size());
                convexHullShape_->setMargin(DEFAULT_COLLISION_MARGIN);
                btCompoundShape* compoundShape = dynamic_cast<btCompoundShape*>(model->collisionShape);
                if(compoundShape)
                    compoundShape->addChildShape(T, convexHullShape_);
                else
                    model->collisionShape = convexHullShape_;
            }
        }
    }
}