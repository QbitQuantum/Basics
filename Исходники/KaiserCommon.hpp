        virtual Matrix4 interp (const Matrix4 &src,const Matrix4 &dst, DTfloat t) {
            
            DTfloat t1 = t;
            DTfloat t2 = t1 * t1;
            DTfloat t3 = t1 * t2;
        
            // interpolate via Hermite spline
            // See Realtime Rendering, 2nd Ed., Page 492
            Vector3 p1,p2,p3,p4;
            p1 = src.translation() * (2.0F * t3 - 3.0F * t2 + 1.0F);
            p2 = Vector3(0.0F,3.0F,0.0F) * (t3 - 2.0F * t2 + t1);

            p3 = Vector3(0.0F,-3.0F,-0.0F) * (t3 - t2);
            p4 = dst.translation() * (-2.0F * t3 + 3.0F * t2);
            
            return Matrix4( Matrix3(Quaternion::slerp(Quaternion(src.orientation()), Quaternion(dst.orientation()), t)),
                            p1 + p2 + p3 + p4);
        }