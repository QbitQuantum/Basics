Mat CascadeDSController::IntegrateTrajectory(realtype dt, realtype speed_threshold, realtype t_max)
{
    int n_max = int(t_max/dt);
    Mat traj(dim_,n_max);
    Vec rpos = filt_pos_-ds_origin_;
    Vec rvel = rpos;
    rvel.setZero();
    int n = 0;
    while(n<n_max){
        traj.col(n)=rpos+ds_origin_;
        rvel = task_dynamics_(rpos);
        if(rvel.norm()<speed_threshold){
            traj.resize(dim_,n+1);
            break;
        }
        rpos += rvel*dt;
        n++;
    }
    return traj;
}