double cosangle(VectorXd a, VectorXd b) {
    if (a.norm() < 1e-6 || b.norm() < 1e-6) {
        return 1;
    } else {
        return a.dot(b) / (a.norm() * b.norm());
    }
}