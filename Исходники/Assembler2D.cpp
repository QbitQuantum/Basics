void Assembler2D::precomputeShapeFunctionDerivatives() {
    Eigen::MatrixXd selector = Eigen::MatrixXd::Zero(3,2);
    selector << 0.0, 0.0,
             1.0, 0.0,
             0.0, 1.0;

    m_DN.resize(m_mesh->getNbrElements());
    for (size_t i=0; i<m_mesh->getNbrElements(); ++i)
    {
        VectorI idx = m_mesh->getElement(i);
        assert(idx.size() == 3);
        VectorF u[3];
        u[0] = m_mesh->getNode(idx[0]);
        u[1] = m_mesh->getNode(idx[1]);
        u[2] = m_mesh->getNode(idx[2]);

        Eigen::MatrixXd P = Eigen::MatrixXd::Zero(3,3);
        P <<     1.0,     1.0,     1.0,
        u[0][0], u[1][0], u[2][0],
        u[0][1], u[1][1], u[2][1];

        // DN is a 4x3 matrix containing the gradients of the
        // 4 shape functions (one for each node)
        //
        m_DN[i] = P.inverse() * selector /* * -1.0 */;
    }
}