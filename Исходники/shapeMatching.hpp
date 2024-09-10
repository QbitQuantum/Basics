void ShapeMatching<PFP>::shapeMatch()
{
    // p_{i}
    std::vector<Eigen::Vector3d> m_p;

    m_p.reserve(m_position.nbElements());

    //1.
    Eigen::Vector3d xcm = massCenter();

    for(unsigned int i = m_position.begin() ; i < m_position.end() ; m_position.next(i))
    {
        Eigen::Vector3d tmp ;
        for (unsigned int j = 0 ; j < 3 ; ++j)
            tmp(j) = m_position[i][j] ;

        Eigen::Vector3d pi = tmp - xcm ;

        m_p.push_back(pi) ; //p_{i} = x_{i} - x_{cm}

    }

    //2.
    Eigen::Matrix3d apq = Eigen::Matrix3d::Zero();

    for(unsigned int i=0 ; i < m_p.size() ; ++i)
    {
        apq(0,0) += m_p[i][0] * m_q[i][0];
        apq(0,1) += m_p[i][0] * m_q[i][1];
        apq(0,2) += m_p[i][0] * m_q[i][2];

        apq(1,0) += m_p[i][1] * m_q[i][0];
        apq(1,1) += m_p[i][1] * m_q[i][1];
        apq(1,2) += m_p[i][1] * m_q[i][2];

        apq(2,0) += m_p[i][2] * m_q[i][0];
        apq(2,1) += m_p[i][2] * m_q[i][1];
        apq(2,2) += m_p[i][2] * m_q[i][2];
    }

    Eigen::Matrix3d S = apq.transpose() * apq ; //symmetric matrix

    //3. Jacobi Diagonalisation
    Eigen::EigenSolver<Eigen::Matrix3d> es(S);

    //V * D * V^(-1)
    Eigen::Matrix3d D =  es.pseudoEigenvalueMatrix();
    Eigen::Matrix3d U =  es.pseudoEigenvectors() ;

    for(int j = 0; j < 3; j++)
    {
        if(D(j,j) <= 0)
        {
            D(j,j) = 0.05f;
        }
        D(j,j) = 1.0f/sqrt(D(j,j));
    }

    S = U * D * U.transpose();

    // Now we can get the rotation part
    Eigen::Matrix3d R = apq * S; //S^{-1}

    //4.
    for(unsigned int i = m_goal.begin() ; i < m_goal.end() ; m_goal.next(i))
    {
       Eigen::Vector3d tmp = R * m_q[i] + xcm; // g_{i} = R * q_i + x_{cm}

       VEC3 g;
       for (unsigned int j = 0 ; j < 3 ; ++j)
            g[j] = tmp(j);

       m_goal[i] = g;
    }
}