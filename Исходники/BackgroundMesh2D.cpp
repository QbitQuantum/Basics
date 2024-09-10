void frameFieldBackgroundMesh2D::computeCrossField(simpleFunction<double> &eval_diffusivity)
{
    angles.clear();

    DoubleStorageType _cosines4,_sines4;

    list<GEdge*> e;
    GFace *face = dynamic_cast<GFace*>(gf);
    if(!face) {
        Msg::Error("Entity is not a face in background mesh");
        return;
    }

    replaceMeshCompound(face, e);

    list<GEdge*>::const_iterator it = e.begin();

    for( ; it != e.end(); ++it ) {
        if (!(*it)->isSeam(face)) {
            for(unsigned int i = 0; i < (*it)->lines.size(); i++ ) {
                MVertex *v[2];
                v[0] = (*it)->lines[i]->getVertex(0);
                v[1] = (*it)->lines[i]->getVertex(1);
                SPoint2 p1,p2;
                reparamMeshEdgeOnFace(v[0],v[1],face,p1,p2);
                Pair<SVector3, SVector3> der = face->firstDer((p1+p2)*.5);
                SVector3 t1 = der.first();
                SVector3 t2 = der.second();
                SVector3 n = crossprod(t1,t2);
                n.normalize();
                SVector3 d1(v[1]->x()-v[0]->x(),v[1]->y()-v[0]->y(),v[1]->z()-v[0]->z());
                t1.normalize();
                d1.normalize();
                double _angle = myAngle (t1,d1,n);
                normalizeAngle (_angle);
                for (int i=0; i<2; i++) {
                    DoubleStorageType::iterator itc = _cosines4.find(v[i]);
                    DoubleStorageType::iterator its = _sines4.find(v[i]);
                    if (itc != _cosines4.end()) {
                        itc->second  = 0.5*(itc->second + cos(4*_angle));
                        its->second  = 0.5*(its->second + sin(4*_angle));
                    }
                    else {
                        _cosines4[v[i]] = cos(4*_angle);
                        _sines4[v[i]] = sin(4*_angle);
                    }
                }
            }
        }
    }

    propagateValues(_cosines4,eval_diffusivity,false);
    propagateValues(_sines4,eval_diffusivity,false);

    std::map<MVertex*,MVertex*>::iterator itv2 = _2Dto3D.begin();
    for ( ; itv2 != _2Dto3D.end(); ++itv2) {
        MVertex *v_2D = itv2->first;
        MVertex *v_3D = itv2->second;
        double angle = atan2(_sines4[v_3D],_cosines4[v_3D]) / 4.0;
        normalizeAngle (angle);
        angles[v_2D] = angle;
    }
}