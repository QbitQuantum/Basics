void fuzzyAffines()
{
    std::vector<Eigen::Matrix4f> trans;
    trans.reserve(count/10);
    for( size_t i=0; i<count/10; i++ )
    {
        Eigen::Vector3f x = Eigen::Vector3f::Random();
        Eigen::Vector3f y = Eigen::Vector3f::Random();

        x.normalize();
        y.normalize();

        Eigen::Vector3f z = x.cross(y);
        z.normalize();

        y = z.cross(x);
        y.normalize();

        Eigen::Affine3f t = Eigen::Affine3f::Identity();
        Eigen::Matrix3f r = Eigen::Matrix3f::Identity();

        r.col(0) = x;
        r.col(1) = y;
        r.col(2) = z;

        t.rotate(r);
        t.translate( 0.5f * Eigen::Vector3f::Random() + Eigen::Vector3f(0.5,0.5,0.5) );

        trans.push_back( t.matrix() );
    }

    s_plot.setColor( Eigen::Vector4f(1,0,0,1) );
    s_plot.setLineWidth( 3.0 );
    s_plot( trans, nox::plot<float>::Pos | nox::plot<float>::CS );
}