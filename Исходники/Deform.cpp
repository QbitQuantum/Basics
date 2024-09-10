void Deform::update_Ri()
{
    Matrix3f Si;
    MatrixXf Di;
    Matrix3Xf Pi_Prime;
    Matrix3Xf Pi;
    for (int i = 0; i != P_Num; ++i) {
        Di = MatrixXf::Zero(adj_list[i].size(), adj_list[i].size());
        Pi_Prime.resize(3, adj_list[i].size());
        Pi.resize(3, adj_list[i].size());
        // if there is not any single unconnected point this for loop can have a more efficient representation
        for (decltype(adj_list[i].size()) j = 0; j != adj_list[i].size(); ++j) {
            Di(j, j) = Weight.coeffRef(i, adj_list[i][j]);
            Pi.col(j) = P.col(i) - P.col(adj_list[i][j]);
            Pi_Prime.col(j) = P_Prime.col(i) - P_Prime.col(adj_list[i][j]);
        }
        Si = Pi * Di * Pi_Prime.transpose();
        Matrix3f Ui;
        Vector3f Wi;
        Matrix3f Vi;
        wunderSVD3x3(Si, Ui, Wi, Vi);
        R[i] = Vi * Ui.transpose();

        if (R[i].determinant() < 0)
            std::cout << "determinant is negative!" << std::endl;
    }
}