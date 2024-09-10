void Deformable::projectPositions()
{
    if (mNumVertices <= 1) return;
    int i;//,j,k;
    
    // center of mass
    Eigen::Vector2d cm, originalCm;
    cm.setZero(); originalCm.setZero();
    double mass = 0.0;
    
    for (i = 0; i < mNumVertices; i++) {
        double m = mMasses(i,0);
        if (mFixed(i,0)) m *= 1000.0;
        mass += m;
        cm += mNewPos.row(i) * m;
        originalCm += mOriginalPos.row(i) * m;
        
    }
    //std::cout<<std::endl;
    cm /= mass;
    
    originalCm /= mass;
    
    Eigen::Matrix2d Apq;
    Eigen::Matrix2d Aqq;
    Eigen::Vector2d p;
    Eigen::Vector2d q;
    Apq.setZero();
    Aqq.setZero();
    
    for (i = 0; i < mNumVertices; i++) {
        p(0) = mNewPos(i,0) - cm(0);
        p(1) = mNewPos(i,1) - cm(1);
        
        q(0) = mOriginalPos(i,0) - originalCm(0);
        q(1) = mOriginalPos(i,1) - originalCm(1);
        double m = mMasses(i,0);
        Apq += m*p*q.transpose();
        Aqq += m*q*q.transpose();
    }
  
    /*if (!params.allowFlip && Apq.determinant() < 0.0f) {  	// prevent from flipping
        Apq(0,1) = -Apq(0,1);
        Apq(1,1) = -Apq(1,1);
    }*/
    
    //std::cout<<Apq<<std::endl;
    
    Eigen::Matrix2d R;
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(Apq, Eigen::ComputeThinU | Eigen::ComputeThinV);
    Eigen::MatrixXd U = svd.matrixU();
    Eigen::MatrixXd V = svd.matrixV();
    R = U*V.transpose();
    if (!params.quadraticMatch) {	// --------- linear match
        
        
        Eigen::Matrix2d A = Aqq;
        

        Eigen::Matrix2d A_=A.inverse();
        /*std::cout<<A_.row(0)<<std::endl;
        std::cout<<A_.row(1)<<std::endl;*/
        A = Apq*A_;
        
        if (params.volumeConservation) {
            double det = A.determinant();
            if(det<0) det=-det;
            if (det != 0.0) {
                det = 1.0 / sqrt(fabs(det));
                if (det > 2.0) det = 2.0;
                A *= det;
            }
        }
        float one_beta =1.0 - params.beta;
        Eigen::Matrix2d T = R * one_beta;
        
        
        A=A*params.beta;
        T = T + A;
        
        
        for (i = 0; i < mNumVertices; i++) {
            if (mFixed(i)) continue;
            q(0) = mOriginalPos(i,0) - originalCm(0);
            q(1) = mOriginalPos(i,1) - originalCm(1);
            Eigen::Vector2d Tq = T*q;
            mGoalPos(i,0) = Tq(0)+cm(0);
            mGoalPos(i,1) = Tq(1)+cm(1);
            //mGoalPos.row(i)=(R * (1.0f - params.beta) + A * params.beta)*q+cm;
            mNewPos.row(i) += (mGoalPos.row(i) - mNewPos.row(i)) * params.alpha;
            
            //std::cout<<T.row(0)<<std::endl;
            //std::cout<<T.row(1)<<std::endl;
        }
    }
}