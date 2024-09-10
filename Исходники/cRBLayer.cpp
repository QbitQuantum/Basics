double cRBLayer::getEnergy(VectorXd& vNodes){
    VectorXd wx_b = vNodes.transpose()*W;
    wx_b=wx_b+hb;
    double vxb = vNodes.transpose()*vb;
    VectorXd ones(h);
    ones.setOnes();
    wx_b.array().exp();
    wx_b+=ones;
    wx_b.array().log();
    return -wx_b.sum()-vxb;
}