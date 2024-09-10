void ProtoSpline3::parallelTransport() {
    // double up first and last verts
    //verts.insert(verts.begin(), verts.at(0));
    //verts.push_back(verts.at(verts.size() - 1));
    
    //frenetFrames.push_back(FrenetFrame(verts.at(0), Vec3f(1,0,0), Vec3f(0,-1,0), Vec3f(0,0,-1))); // add first vert
    // std::cout << "in createFrenetFrame():  verts.size() = " << verts.size() << std::endl;
    std::vector<Vec3f> tans;
    float theta = 0.0;
    Vec3f cp0, cp1, cp2;
    Vec3f tan, biNorm, norm, nextBiNorm, nextNorm;
    
    
    for (int i = 0; i < verts.size(); i++) {
        if (i == 0) {
            //cp0 = verts[verts.size() - 1];
            cp0 = verts.at(i);
            cp1 = verts.at(i);
            cp2 = verts.at(i + 1);
            
        } else if (i == verts.size() - 1) {
            cp0 = verts.at(i - 1);
            cp1 = verts.at(i);
            cp2 = verts.at(i); // 0, circled back here? changed to i
            
        } else {
            cp0 = verts.at(i - 1);
            cp1 = verts.at(i);
            cp2 = verts.at(i + 1);
            
            //std::cout << "i = = " << i << std::endl;
            //            std::cout << "cp0 " << cp0 << std::endl;
            
            //            std::cout << "cp1 " << cp1 << std::endl;
            //            std::cout << "cp2 " << cp2 << std::endl;
            //            std::cout << "cross(cp1, cp2) " << cross(cp1, cp2) << std::endl;
            //std::cout << "cp2 " << cp2 << std::endl;
        }
        // fill tangents
        tan = cp2 - cp0;
        tan.normalize();
        tans.push_back(tan);
        
        // collect initial frame
        if (i == 1) {
            // fix biNorm for parralel vectors
            biNorm = cp1.cross(cp2);
            
            // uh-oh parallel vecs
            // ! HACK ! avoids problems with orthonormal tubes.
            if (biNorm.mag() == 0) {
                
                if (cp1.x !=0 && cp2.x !=0){
                    biNorm = Vec3f(0, 1, 0);
                }
                if (cp1.y !=0 && cp2.y !=0){
                    biNorm = Vec3f(0, 0, -1);
                }
                if (cp1.z !=0 && cp2.z !=0){
                    biNorm = Vec3f(1, 0, 0);
                }
                
            }
            //std::cout << "biNorm pre = " << biNorm << std::endl;
            //std::cout << "biNorm.mag() = " << biNorm.mag() << std::endl;
            biNorm.normalize();
            //            biNorm.x = 1;
            //            biNorm.y = 0;
            //            biNorm.z = 0;
            //            std::cout << "cp1 " << cp1 << std::endl;
            //            std::cout << "cp2 " << cp2 << std::endl;
            //            std::cout << "biNorm post = " << biNorm << std::endl;
            
            norm = biNorm.cross(tan);
            norm.normalize();
        }
    }
    // rotate frame
    
    //  std::cout << "tans.size() = " << tans.size() << std::endl;
    for (int i = 0; i < tans.size() - 1; i++) {
        
        
        if (biNorm.mag() == 0) {
            nextNorm = norm;
            //frenetFrames.push_back(FrenetFrame(verts.at(i), Vec3f(1,1,1), Vec3f(1,1,1), Vec3f(1,1,1)));
            // std::cout << "norm = " << norm << std::endl;
        } else {
            theta = acos(tans.at(i).dot(tans.at(i + 1)));
            Vec3f axis = tans.at(i);
            //std::cout << "tans.at(i + 1) = " << tans.at(i + 1) << std::endl;
            //std::cout << i << std::endl;
            axis = axis.cross(tans.at(i + 1));
            //std::cout << "axis = " << axis << std::endl;
            axis.normalize();
            
            
            
            ProtoMatrix3f m;
            nextNorm = m.getRotate(theta, axis, norm);
            //std::cout << "axis = " << axis << std::endl;
            
            nextBiNorm = tans.at(i + 1);
            nextBiNorm = nextBiNorm.cross(nextNorm);
            
            
            
            // std::cout << "nextNorm = " << nextNorm << std::endl;
            // std::cout << "norm = " << norm << std::endl;
            
        }
        
        //biNorm.normalize();
        //norm.normalize();
        //        std::cout <<i<<std::endl;
        //        std::cout << "tans.at(i) = " << tans.at(i) << std::endl;
        //        std::cout << "biNorm = " << biNorm << std::endl;
        //        std::cout << "norm = " << norm << std::endl;
        frenetFrames.push_back(ProtoFrenetFrame(verts.at(i), tans.at(i), biNorm, norm));
        norm = nextNorm;
        biNorm = nextBiNorm;
        
        //std::cout << "verts = " << verts.at(i) << std::endl;
    }
    // std::cout << "in createFrenetFrame():  frenetFrames.size() = " << frenetFrames.size() << std::endl;
    
}