void randomUnitSphere(Eigen::Vector3d &sp) {
    static boost::random::mt19937 rng(time(NULL));
    static boost::random::normal_distribution<> normal;

    do {
        sp(0) = normal(rng);
        sp(1) = normal(rng);
        sp(2) = normal(rng);
    } while (sp.norm() < 0.00001);
    sp.normalize();
}