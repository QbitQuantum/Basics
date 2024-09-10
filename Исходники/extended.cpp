//evaluates the ELBO for an individual who is a stayer
double getStayerProb(mm_modelExt model){
    int stayerID = model.getStayerID();

    double t1,t2,t3,t4;
    double phi_sum = 0.0;
    double elbo;
    int j,k,r,n;
    int K = model.getK();
    int J = model.getJ();
    double back_term;
    double dg_phi_sum;
    double phi_ik, delta_ijrnk;

    //Calculate first line and second line
    t1 = 0.0;
    t2 = 0.0;
    t3 = 0.0;
    t4 = 0.0;


    t1 = lgamma(sum(model.getAlpha())) - sum(lgamma(model.getAlpha()));

    for(k = 0; k < K; k++) {
        phi_sum += model.getPhi(stayerID,k);
    }
    dg_phi_sum = boost::math::digamma(phi_sum);

    t4 += lgamma(phi_sum);
    for(k = 0; k < K; k++) {
        phi_ik = model.getPhi(stayerID,k);
        back_term = (boost::math::digamma(phi_ik) - dg_phi_sum);
        t1+= (model.getAlpha(k) - 1.0) * back_term;

        t4 += -lgamma(phi_ik);
        t4 += (phi_ik - 1.0) * back_term;

        for(j = 0; j < J; j++) {
            for(r = 0; r < model.getR(j); r++) {
                for(n = 0; n < model.getN(stayerID, j, r); n++) {
                    delta_ijrnk = model.getDelta(stayerID, j, r, n, k);
                    t2 += delta_ijrnk*back_term;
                    t4 += delta_ijrnk*log(delta_ijrnk);
                }
            }
        }
    }

//compute 3rd line
    t3 = getStayer_logf(model, stayerID);

    elbo = t1 + t2 + t3 - t4;
    return elbo;
}