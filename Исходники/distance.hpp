    Scalar calculateGradientSecond(Geometry1& point, Geometry2& line, Derivative2& dline) {
        if(dist.norm() == 0)
            return 1.;

        const Vector3 d_diff = dline.point();
        const Vector3 d_n  = dline.direction();
        const Vector3 d_dist = d_diff - ((d_diff.dot(line.direction())+diff.dot(d_n))*line.direction() + diff.dot(line.direction())*d_n);
        const Scalar res = dist.dot(d_dist)/dist.norm();
#ifdef DCM_USE_LOGGING
        if(!boost::math::isfinite(res))
            BOOST_LOG_SEV(log, details::error) << "Unnormal second cluster gradient detected: "<<res
                           <<" with point: "<<point.point().transpose()<<", line: "<< line.point().transpose()
                           << line.direction().transpose()<< ", and dline: "<<dline.point().transpose() 
                           << dline.direction().transpose();
#endif
        return res;
    };