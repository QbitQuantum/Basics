    bool calcLegAngles(double** out_q) {

        rpy = rpyFromRot(R);

        cy = cos(rpy[2]);
        sy = sin(rpy[2]);
        cp = cos(rpy[1]);
        sp = sin(rpy[1]);
        cr = cos(rpy[0]);
        sr = sin(rpy[0]);

        Vector3 O1(0.0, sign * robot->l0, -robot->l1);
        const Vector3& F = p;
        Vector3 V1 = F - O1;
        Vector3 XF(cy * cp, sy * cp, -sp);
        Vector3 V1xXF = V1.cross(XF);
        Vector3 Z2 = -sign * V1xXF / V1xXF.norm();

        q[0] = atan2(-sign * Z2[0], sign * Z2[1]);
        q[1] = asin(-sign * Z2[2]);

        double c1 = cos(q[0]);
        double s1 = sin(q[0]);
        double c2 = cos(q[1]);
        double s2 = sin(q[1]);
        double s1s2 = s1 * s2;
        double c1s2 = c1 * s2;
        slo1 = sign * robot->lo1;

        TB2 <<
            s1s2, -sign * c1, -sign * s1 * c2,  slo1 * s1 + robot->l2 * c1 + robot->lo2 * s1s2,
            -c1s2, -sign * s1,  sign * c1 * c2,  sign * robot->l0 - slo1 * c1 + robot->l2 * s1 - robot->lo2 * c1s2,
            -c2,    0.0,      -sign * s2,      -robot->l1 - robot->lo2 * c2,
            0.0,   0.0,       0.0,            1.0;

        Vector3 V2 = (TB2.inverse() * Vector4d(F[0], F[1], F[2], 1.0)).head(3);
        double D = (V2.squaredNorm() - robot->l3 * robot->l3 - robot->l4 * robot->l4) / (2.0 * robot->l3 * robot->l4);

        if(fabs(D) > 1.0){
            return false;
        }

        q[3] = atan2(-sign * sqrt(1.0 - D * D), D);
        double c4 = cos(q[3]);
        double s4 = sin(q[3]);
        
        double beta = atan2(-V2[1], sqrt(V2[0] * V2[0] + V2[2] * V2[2]));
        double alpha = atan2(robot->l4 * s4, robot->l3 + robot->l4 * c4);
        q[2] = -(beta - alpha);
        
        q[3] = -q[3];
        
        double c3 = cos(q[2]);
        double s3 = sin(q[2]);
        double q2q3 = q[2] + q[3];
        double c34 = cos(q2q3);
        double s34 = sin(q2q3);
        
        Matrix4d T24;
        T24 <<
            c34,  s34,  0, robot->l3 * c3 + robot->l4 * c34,
            s34, -c34,  0, robot->l3 * s3 + robot->l4 * s34,
            0.0,  0.0, -1, 0.0,
            0.0,  0.0,  0, 1.0;
        
        TB4.noalias() = TB2 * T24;

        double spsr = sp * sr;
        double spcr = sp * cr;
    
        TBF <<
            cy * cp, -sy * cr + cy * spsr,  sy * sr + cy * spcr, p.x(),
            sy * cp,  cy * cr + sy * spsr, -cy * sr + sy * spcr, p.y(),
            -sp,       cp * sr,              cp * cr,             p.z(),
            0,        0,                    0,                   1.0;
        
        Matrix4d T4F;
        T4F.noalias() = TB4.inverse() * TBF;

        q[4] = atan2(-sign * T4F(0,0),  sign * T4F(1,0));
        q[5] = atan2( sign * T4F(2,2), -sign * T4F(2,1));

        // Numerical refining
        
        TB0 <<
            0.0, -1.0, 0.0, 0.0,
            1.0,  0.0, 0.0, sign * robot->l0,
            0.0,  0.0, 1.0, 0.0,
            0.0,  0.0, 0.0, 1.0;
        
        Af <<
            0.0, 1.0, 0.0, 0.0,
            -1.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0;

        bool solved = false;

        int i;
        for(i=0; i < 30; ++i){

            if(calcEndPositionDifference()){
                solved = true;
                break;
            }

            // Jacobian Calculation

            Vector3 Z0 = TB0.block<3,1>(0,2);
            Vector3 Z1 = TB1.block<3,1>(0,2);
            Vector3 Z2 = TB2.block<3,1>(0,2);
            Vector3 Z3 = TB3.block<3,1>(0,2);
            Vector3 Z4 = TB4.block<3,1>(0,2);
            Vector3 Z5 = TB5.block<3,1>(0,2);
            
            Vector3 O0 = TB0.block<3,1>(0,3);
            Vector3 O1 = TB1.block<3,1>(0,3);
            Vector3 O2 = TB2.block<3,1>(0,3);
            Vector3 O3 = TB3.block<3,1>(0,3);
            Vector3 O4 = TB4.block<3,1>(0,3);
            Vector3 O5 = TB5.block<3,1>(0,3);
            Vector3 O6 = TB6.block<3,1>(0,3);
            
            Matrix6 J;
            J <<
                Z0.cross(O6 - O0), Z1.cross(O6 - O1), Z2.cross(O6 - O2), Z3.cross(O6 - O3), Z4.cross(O6 - O4), Z5.cross(O6 - O5),
                Z0,                Z1,                Z2,                Z3,                Z4,                Z5               ;
            
            // Levenberg-Marquardt Method
            
            const double lambda = 0.001;
            
            Matrix6 C;
            C.noalias() = J.transpose() * (J * J.transpose() + Matrix6::Identity() * lambda * lambda).inverse();
            
            dq.noalias() = C * dp;
            q += dq;

            if(dq.norm() <= 1.0e-5){
                break;
            }
        }

        if(!solved){
            solved = calcEndPositionDifference();
        }

        if(solved){
            *out_q[0] = q[0];
            *out_q[1] = q[1];
            *out_q[2] = q[2] + sign * robot->q2q3offset;
            *out_q[3] = q[3] - sign * robot->q2q3offset;
            *out_q[4] = q[4];
            *out_q[5] = q[5];
        }
        return solved;
    }