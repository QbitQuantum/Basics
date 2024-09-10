void taskwrenchEllipsoid::sampleComEllipsoid()
{

    //sampleParametricForm, might make more sense to sample more in one direction

    //also sample over mass from m-delta -> m=delta

    int iMax=10;
    int jMax=10;
    int lMax=4;
    int k=0;



    for(int i=0; i < iMax; i++){
        for(int j=0; j < jMax; j++){
            for(int l=0; l<lMax;l++){

                //u von -Pi/2 bis Pi/2
                //v von -Pi bis Pi


                double u=-M_PI/2 + ((double) i / (double) iMax)*M_PI;
                double v=-M_PI + ((double) j / (double) jMax)*2*M_PI;
                double w=mass_ - sigmaMass_ + ((double) l / (double) lMax)*2*sigmaMass_;

                Eigen::Vector3d currentCom; //parametrized in PCA frame
                Eigen::Vector3d force;
                Eigen::Vector3d torque;
                Eigen::Vector3d comInRotFrame;

                currentCom(0)=sigmaCom_(0)*cos(u)*cos(v);
                currentCom(1)=sigmaCom_(1)*cos(u)*sin(v);
                currentCom(2)=sigmaCom_(2)*sin(u);

                //std::cout << currentCom << std::endl;
                //std::cout << u << std::endl;
                //std::cout << v << std::endl;

                force=-9.81*w*gripperRot_*gravityNormal_;//use SI Units for now, transform into hand frame, not sure about pose!
                //comInRotFrame=comRotFrame_*currentCom; // sampling done in the pca frame!

                if(l==0){force_min=force;}
                if(l==lMax-1){force_max=force;}


                torque=currentCom.cross(force);
                comEllipse_.col(k)=comInRotFrame;
                sampledPointsEllipse_.col(k)=torque;
                k++;
                //
            }

        }
    }
}