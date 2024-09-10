auto pardot(Eigen::MatrixBase<V1> const& A, Eigen::MatrixBase<V2> const& B, int chunkSize = 1024) {

    if(A.rows() < 10*chunkSize) {
        return A.dot(B);
    }

    using T = std::decay_t<decltype(A(0))>;
    struct r_struct{T val{0};};

    SmallVector<ReductionVariable<r_struct>, 8> S(yafel::config::num_cores, r_struct{0});

    parfor(0, A.rows(), [&](auto i) {
        auto id = worker_global::worker_id;
        S[id].val += A(i)*B(i);
    },getGlobalScheduler(), chunkSize);

    T total{0};
    for(auto &s : S){
        total += s.val;
    }
    return total;
}