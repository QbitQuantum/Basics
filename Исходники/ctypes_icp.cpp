inline float cosine(Matrix<float, 1, 2> a, Matrix<float, 1, 2> b) {
    return a.dot(b.transpose()) / (a.norm() * b.norm());
    //return dot(a1, a2, b1, b2) / (norm(a1, a2) * norm(b1, b2));
}