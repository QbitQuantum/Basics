Vector<double> AncillaryMethods::PlaneToCam(const Camera& camera)
{
    Vector<double> plane = camera.get_GP();

    Vector<double> pv(plane(0), plane(1), plane(2));

    Matrix<double> cam_rot_trans = Transpose(camera.get_R());

    pv = cam_rot_trans * pv;

    Vector<double> t = cam_rot_trans * camera.get_t();

    double d = plane(3) + pv(0)*t(0) + pv(1)*t(1) + pv(2)*t(2);

    Vector<double> gp_in_camera(4);
    gp_in_camera(0) = pv(0);
    gp_in_camera(1) = pv(1);
    gp_in_camera(2) = pv(2);
    gp_in_camera(3) = d;

    return gp_in_camera;
}