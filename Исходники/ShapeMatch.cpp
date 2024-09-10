void ShapeMatch::setTarget(std::vector<double> &target_vec)
{
    target_mat = Eigen::Map<Eigen::Matrix3Xd>(&target_vec[0], 3, target_vec.size()/3);

    target_center = Eigen::Vector3d(target_mat.row(0).mean(), target_mat.row(0).mean(), target_mat.row(0).mean());
    target_mat.row(0) = (target_mat.row(0).array() - target_center(0)).matrix();
    target_mat.row(1) = (target_mat.row(1).array() - target_center(1)).matrix();
    target_mat.row(2) = (target_mat.row(2).array() - target_center(2)).matrix();

    // do icp alignment first
    //Eigen::MatrixXd C_n = Eigen::MatrixXd::Identity(target_mat.cols(), target_mat.cols()) - Eigen::MatrixXd::Ones(target_mat.cols(), target_mat.cols()) / target_mat.cols();
    Eigen::Matrix3d H = target_mat*template_mat.transpose();
    Eigen::Matrix3f H_float = H.cast<float>();
    Eigen::Matrix3f Ui;
    Eigen::Vector3f Wi;
    Eigen::Matrix3f Vi;
    wunderSVD3x3(H_float, Ui, Wi, Vi);
    Eigen::Matrix3d R = (Vi * Ui.transpose()).cast<double>();
    Eigen::Vector3d t = template_center - R*target_center;
    target_mat = R*target_mat + t*Eigen::MatrixXd::Ones(1, target_mat.cols());

    target_center = Eigen::Vector3d(target_mat.row(0).mean(), target_mat.row(0).mean(), target_mat.row(0).mean());
    target_mat.row(0) = (target_mat.row(0).array() - target_center(0)).matrix();
    target_mat.row(1) = (target_mat.row(1).array() - target_center(1)).matrix();
    target_mat.row(2) = (target_mat.row(2).array() - target_center(2)).matrix();

    target_vec = std::vector<double>(target_mat.data(), target_mat.data()+target_mat.cols()*target_mat.rows());
}