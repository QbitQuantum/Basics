Vec RQR_Multiply(const VECTOR &v,
                 const SparseKalmanMatrix &RQR,
                 const SparseVector &Z,
                 double H) {
    int state_dim = Z.size();
    if(v.size() != state_dim + 2) {
        report_error("wrong sizes in RQR_Multiply");
    }
    // Partition v = [eta, epsilon, 0]
    ConstVectorView eta(v, 0, state_dim);
    double epsilon = v[state_dim];

    // Partition this
    Vec RQRZ = RQR * Z.dense();
    double ZRQRZ_plus_H = Z.dot(RQRZ) + H;

    Vec ans(v.size());
    VectorView(ans, 0, state_dim) = (RQR * eta).axpy(RQRZ, epsilon);
    ans[state_dim] = RQRZ.dot(eta) + ZRQRZ_plus_H * epsilon;
    return ans;
}