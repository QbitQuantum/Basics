void ManipTool::update_nv(Eigen::Vector3d lv,Eigen::Vector3d& n_hat,Eigen::Vector3d& nv_dot_fb){
    P_bar = Eigen::Matrix3d::Identity()-n_hat*n_hat.transpose();
    nv_dot = -1*Gama_n*P_bar*L_n*n_hat;
    nv_dot_fb = nv_dot;
    L_n_dot = -beta_n*L_n+(1/(1+pow(lv.norm(),2)))*lv*lv.transpose();
    n_hat = n_hat+nv_dot;
    n_hat = n_hat/n_hat.norm();
    L_n = L_n + L_n_dot;

}