void ARAPTerm::updateRotation()
{
    Solver::DeformPetal& deform_petal = Solver::deform_petals_[petal_id_];
    Solver::PetalMatrix& origin_petal = deform_petal._origin_petal;
    Solver::PetalMatrix& petal_matrix = deform_petal._petal_matrix;
    Solver::RotList& rot_list = deform_petal._R_list;
    Solver::ScaleList& scale_list = deform_petal._S_list;
    Solver::AdjList& adj_list = deform_petal._adj_list;
    Solver::WeightMatrix& weight_matrix = deform_petal._weight_matrix;

    Eigen::Matrix3f Si;
    Eigen::MatrixXd Di;

    Eigen::Matrix3Xd Pi_Prime;
    Eigen::Matrix3Xd Pi;

    for (size_t i = 0, i_end = rot_list.size(); i < i_end; ++i) 
    {
        Di = Eigen::MatrixXd::Zero(adj_list[i].size(), adj_list[i].size());
        Pi_Prime.resize(3, adj_list[i].size());
        Pi.resize(3, adj_list[i].size());

        for (size_t j = 0, j_end = adj_list[i].size(); j < j_end; ++j) 
        {
            Di(j, j) = weight_matrix.coeffRef(i, adj_list[i][j]);
            Pi.col(j) = origin_petal.col(i) - origin_petal.col(adj_list[i][j]);
            Pi_Prime.col(j) = petal_matrix.col(i) - petal_matrix.col(adj_list[i][j]);
        }
        Si = Pi.cast<float>() * Di.cast<float>() * Pi_Prime.transpose().cast<float>();
        Eigen::Matrix3f Ui;
        Eigen::Vector3f Wi;
        Eigen::Matrix3f Vi;
        wunderSVD3x3(Si, Ui, Wi, Vi);
        rot_list[i] = Vi.cast<double>() * Ui.transpose().cast<double>();

        if (rot_list[i].determinant() < 0)
            std::cout << "determinant is negative!" << std::endl;

        double s = 0;
        for (size_t j = 0, j_end = adj_list[i].size(); j < j_end; ++j) 
        {
            s += Di(j, j) * Pi.col(j).squaredNorm();
        }

       // scale_list[i] = Wi.trace() / s;

       /* if (scale_list[i] < 0.95 )
            scale_list[i] = 0.95;
        else if (scale_list[i] > 1.05)
            scale_list[i] = 1.05;*/
    }

    /*if (petal_id_ == 0) std::cout << "vertex: " << 0 << "  " << scale_list[0] << std::endl;*/
}