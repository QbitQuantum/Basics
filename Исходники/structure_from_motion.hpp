inline
void r_and_t(MatrixXf &rot_cw, VectorXf &pos_cw,MatrixXf start_points, MatrixXf end_points,
             MatrixXf P1w,MatrixXf P2w,MatrixXf initRot_cw,VectorXf initPos_cw,
             int maxIterNum,float TerminateTh,int nargin)
{
    if(nargin<6)
    {
        return;
    }

    if(nargin<8)
    {
        maxIterNum = 8;
        TerminateTh = 1e-5;
    }

    int n = start_points.cols();

    if(n != end_points.cols() || n!= P1w.cols() || n!= P2w.cols())
    {
        return;
    }

    if(n<4)
    {
        return;
    }

    //first compute the weight of each line and the normal of
    //the interpretation plane passing through to camera center and the line

    VectorXf w = VectorXf::Zero(n);
    MatrixXf nc = MatrixXf::Zero(3,n);

    for(int i = 0 ; i < n ; i++)
    {
        //the weight of a line is the inverse of its image length
        w[i] = 1/(start_points.col(i)-end_points.col(i)).norm();
        vfloat3 v1 = start_points.col(i);
        vfloat3 v2 = end_points.col(i);
        vfloat3 temp = v1.cross(v2);
        nc.col(i) = temp/temp.norm();
    }

    MatrixXf rot_wc = initPos_cw.transpose();
    MatrixXf pos_wc = - initRot_cw.transpose() * initPos_cw;


    for(int iter = 1 ; iter < maxIterNum ; iter++)
    {
        //construct the equation (31)
        MatrixXf A = MatrixXf::Zero(6,7);
        MatrixXf C = MatrixXf::Zero(3,3);
        MatrixXf D = MatrixXf::Zero(3,3);
        MatrixXf F = MatrixXf::Zero(3,3);
        vfloat3 c_bar = vfloat3(0,0,0);
        vfloat3 d_bar = vfloat3(0,0,0);
        for(int i = 0 ; i < n ; i++)
        {
            //for first point on line
            vfloat3 Pi = rot_wc * P1w.col(i);
            vfloat3 Ni = nc.col(i);
            float wi = w[i];
            vfloat3 bi = Pi.cross(Ni);
            C = C + wi*Ni*Ni.transpose();
            D = D + wi*bi*bi.transpose();
            F = F + wi*Ni*bi.transpose();
            vfloat3 tempi = Pi + pos_wc;
            float scale = Ni.transpose() * tempi;
            scale *= wi;
            c_bar = c_bar + scale * Ni;
            d_bar = d_bar + scale*bi;
            //for second point on line
            Pi = rot_wc * P2w.col(i);
            Ni = nc.col(i);
            wi = w[i];
            bi = Pi.cross(Ni);
            C  = C + wi*Ni*Ni.transpose();
            D  = D + wi*bi*bi.transpose();
            F  = F + wi*Ni*bi.transpose();
            scale = (Ni.transpose() * (Pi + pos_wc));
            scale *= wi;
            c_bar = c_bar + scale * Ni;
            d_bar = d_bar + scale * bi;
        }
        A.block<3,3>(0,0) = C;
        A.block<3,3>(0,3) = F;
        (A.col(6)).segment(0,2) = c_bar;
        A.block<3,3>(3,0) = F.transpose();
        A.block<3,3>(2,2) = D;
        (A.col(6)).segment(3,5) = d_bar;
        //sovle the system by using SVD;
        JacobiSVD<MatrixXf> svd(A, ComputeThinU | ComputeThinV);
        VectorXf vec(7);
        //the last column of Vmat;
        vec = (svd.matrixV()).col(6);
        //the condition that the last element of vec should be 1.
        vec = vec/vec[6];

        //update the rotation and translation parameters;
        vfloat3 dT = vec.segment(0,2);
        vfloat3 dOmiga = vec.segment(3,5);
        MatrixXf rtemp(3,3);
        rtemp << 1, -dOmiga[2], dOmiga[1], dOmiga[2], 1, -dOmiga[1], -dOmiga[1], dOmiga[0], 1;
        rot_wc = rtemp * rot_wc;
        //newRot_wc = ( I + [dOmiga]x ) oldRot_wc
        //may be we can compute new R using rodrigues(r+dr)
        pos_wc = pos_wc + dT;

        if(dT.norm() < TerminateTh && dOmiga.norm() < 0.1*TerminateTh)
        {
            break;
        }
    }
    rot_cw = rot_wc.transpose();
    pos_cw = -rot_cw * pos_wc;
}