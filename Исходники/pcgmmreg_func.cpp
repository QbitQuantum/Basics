double PCGMMReg_func::weight_l2(PCObject &model, PCObject &scene)
{
    // reference :
    // Robust Point Set Registration Using Gaussian Mixture Models
    // Bing Jina, and Baba C. Vemuri
    // IEEE Transactions on Pattern Analysis and Machine Intelligence 2010

    double energy1 = 0.;
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            Eigen::Matrix3d cov = model.gmm.at(i).covariance + model.gmm.at(j).covariance;
            Eigen::Vector3d mean = model.gmm.at(i).mean - model.gmm.at(j).mean;
            Eigen::Matrix3d invij = cov.inverse();
            double a = mean.transpose()*invij*mean;
            double gauss = 1./sqrt(pow(2*pi,3)*cov.determinant())*exp(-0.5*a);
            energy1 += model.gmm.at(i).weight*model.gmm.at(j).weight*gauss;
        }
    }
//    cout<<"m "<<m<<endl;
//    cout<<"s "<<s<<endl;
    double energy2 = 0.;
    for(int i=0;i<m;i++){
        double sum[3] = {0.,0.,0.};
        for(int j=0;j<s;j++){
            Eigen::Matrix3d cov = model.gmm.at(i).covariance + scene.gmm.at(j).covariance;
            Eigen::Vector3d mean = model.gmm.at(i).mean - scene.gmm.at(j).mean;
            Eigen::Matrix3d invij = cov.inverse();
            double a = mean.transpose()*invij*mean;
            double gauss = 1./sqrt(pow(2*pi,3)*cov.determinant())*exp(-0.5*a);
            energy2 += model.gmm.at(i).weight*scene.gmm.at(j).weight*gauss;
//            cout<<"weight i "<<model.gmm.at(i).weight<<endl;
//            cout<<"weight j "<<scene.gmm.at(j).weight<<endl;
//            cout<<"a "<<a<<endl;
//            cout<<"gauss "<<gauss<<endl;


            // gradient [m,d]
            double derv_x = -0.5*(2*mean[0]*invij(0,0) + mean[1]*(invij(0,1)+invij(1,0)) + mean[2]*(invij(0,2)+invij(2,0)));
            double derv_y = -0.5*(mean[0]*(invij(1,0)+invij(0,1)) + 2*mean[1]*invij(1,1) + mean[2]*(invij(1,2)+invij(2,1)));
            double derv_z = -0.5*(mean[0]*(invij(2,0)+invij(0,2)) + mean[1]*(invij(2,1)+invij(1,2)) + 2*mean[2]*invij(2,2));

            sum[0] += scene.gmm.at(j).weight*gauss*derv_x;
            sum[1] += scene.gmm.at(j).weight*gauss*derv_y;
            sum[2] += scene.gmm.at(j).weight*gauss*derv_z;

        }
        gradient[i][0] = -2.*model.gmm.at(i).weight*sum[0];
        gradient[i][1] = -2.*model.gmm.at(i).weight*sum[1];
        gradient[i][2] = -2.*model.gmm.at(i).weight*sum[2];
    }
    double energy3 = 0.;
    for(int i=0;i<s;i++){
        for(int j=0;j<s;j++){
            Eigen::Matrix3d cov = scene.gmm.at(i).covariance + scene.gmm.at(j).covariance;
            Eigen::Vector3d mean = scene.gmm.at(i).mean - scene.gmm.at(j).mean;
            Eigen::Matrix3d invij = cov.inverse();
            double a = mean.transpose()*invij*mean;
            double gauss = 1./sqrt(pow(2*pi,3)*cov.determinant())*exp(-0.5*a);
            energy3 += scene.gmm.at(i).weight*scene.gmm.at(j).weight*gauss;
        }
    }
    return energy1 - 2*energy2 + energy3;
//    cout<<"energy2 "<<energy2<<endl;
//    return -2*energy2;
}