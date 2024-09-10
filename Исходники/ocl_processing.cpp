void OCLSLAM<CR, CW>::display ()
{
    double angle = 180.0 / M_PI * 2.0 * std::atan2 (q_g.vec ().norm (), q_g.w ());  // in degrees
    Eigen::Vector3f axis = ((angle == 0.0) ? Eigen::Vector3f::Zero () : q_g.vec ().normalized ());
    std::cout << "    Time step             :    " << timeStep << std::endl;
    std::cout << "    Latency               :    " << timer.stop () << " [ms]" << std::endl;
    std::cout << "    ICP iterations        :    " << icp.k << std::endl;
    std::cout << "    ICP latency           :    " << lICP << " [ms]" << std::endl;
    std::cout << "    Localization               " << std::endl;
    std::cout << "    - Translation vector  :    " << t_g.transpose () << " [mm]" << std::endl;
    std::cout << "    - Rotation axis       :    " << axis.transpose () << std::endl;
    std::cout << "    - Rotation angle      :    " << angle << " [degrees]" << std::endl;
    std::cout << "===========================    " << std::endl;
    timer.start ();
}