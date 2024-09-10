    void function(const Eigen::Ref<const Eigen::VectorXd> &x, Eigen::Ref<Eigen::VectorXd> out) const override
    {
        if (chains_ == 2)
        {
            out[0] = (getTip(x, 0) - getTip(x, 1)).norm() - radius_ * 2;
            return;
        }

        unsigned int idx = 0;

        Eigen::Vector3d centroid = Eigen::Vector3d::Zero();
        for (unsigned int i = 0; i < chains_; ++i)
            centroid += getTip(x, i);
        centroid /= chains_;

        for (unsigned int i = 0; i < chains_; ++i)
            out[idx++] = (centroid - getTip(x, i)).norm() - radius_;

        for (unsigned int i = 0; i < chains_ - 3; ++i)
        {
            const Eigen::Vector3d ab = getTip(x, i + 1) - getTip(x, i);
            const Eigen::Vector3d ac = getTip(x, i + 2) - getTip(x, i);
            const Eigen::Vector3d ad = getTip(x, i + 3) - getTip(x, i);

            out[idx++] = ad.dot(ab.cross(ac));
        }
    }