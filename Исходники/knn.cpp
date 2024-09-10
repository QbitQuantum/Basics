/* D = distance(training_data, testing_data) computes the Euclidean distance matrix D
 * Arguments:
 *    training_data: dxn data matrix with n column-vectors of dimensionality d
 *    testing_data: dxm data matrix with m column-vectors of dimensionality d
 * Return:
 *    n x m matrix D; D(i,j) is the Euclidean distance of X(:,i) and Z(:,j)
 */
MatrixXf distance(MatrixXd training_data, MatrixXd testing_data) {
    int n = training_data.cols();
    int m = testing_data.cols();

    //cout << "training_data: " << endl << training_data << endl;
    //cout << "testing_data: " << endl << testing_data << endl;

    // Matlab sum(A,2) is a column vector containing the sum of each row.
    // S_vector = sum(X' .* X', 2);
    MatrixXd xTr_transpose = training_data.transpose(); // n x d
    //cout << "xTr_transpose: " << endl << xTr_transpose << endl;
    MatrixXd xTr_squared = xTr_transpose.cwiseProduct(xTr_transpose);
    //cout << "xTr_squared: " << endl << xTr_squared << endl;
    MatrixXd xTr_vector;
    xTr_vector.resize(n,1);
    for (int i = 0; i < n; i++) {
        xTr_vector(i,0) = xTr_squared.row(i).sum();
    }
    //cout << "xTr_vector: " << endl << xTr_vector << endl;


    MatrixXd xTe_transpose = testing_data.transpose(); // m x d
    //cout << "xTe_transpose: " << endl << xTe_transpose << endl;
    MatrixXd xTe_squared = xTe_transpose.cwiseProduct(xTe_transpose);
    //cout << "xTe_squared: " << endl << xTe_squared << endl;
    MatrixXd xTe_vector;
    xTe_vector.resize(m,1);
    for (int i = 0; i < m; i++) {
        xTe_vector(i,0) = xTe_squared.row(i).sum();
    }
    //cout << "xTe_vector: " << endl << xTe_vector << endl;

    // D = sqrt(repmat(S_vector, 1, m) - 2 * X' * Z + repmat(R_vector', n, 1));
    MatrixXd D_squared1;
    D_squared1.resize(n,m);
    for (int i = 0; i < m; i++) {
        D_squared1.col(i) = xTr_vector;
    }
    //cout << "D_squared1: " << endl << D_squared1 << endl;

    MatrixXd D_squared2 = - 2 * xTr_transpose * testing_data;
    //cout << "D_squared2: " << endl << D_squared2 << endl;

    MatrixXd D_squared3;
    D_squared3.resize(n,m);
    for (int i = 0; i < n; i++) {
        D_squared3.row(i) = xTe_vector.transpose();
    }
    //cout << "D_squared3: " << endl << D_squared3 << endl;

    MatrixXd D_squared = D_squared1 + D_squared2 + D_squared3;

    // Cast the component-wise square root to a dynamic float matrix
    return D_squared.cwiseSqrt().cast<float>();
}