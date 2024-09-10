    Eigen::Matrix <double,6,3> se3Action (const SE3 & m) const
    {
        Eigen::Matrix <double,6,3> X_subspace;
        X_subspace.block <3,3> (Motion::LINEAR, 0) = skew (m.translation ()) * m.rotation ();
        X_subspace.block <3,3> (Motion::ANGULAR, 0) = m.rotation ();

        return X_subspace;
    }