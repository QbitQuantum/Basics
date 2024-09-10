void FeatureEval::computeCorrelation(float * data, int vector_size, int size, std::vector<int> & big_to_small, int stride, int offset){

    stride = stride ? stride : vector_size;

    if(ll_->getSelection().size() == 0)
        return;

    std::set<uint16_t> labels;
    for(boost::weak_ptr<Layer> wlayer: ll_->getSelection()){
        for(uint16_t label : wlayer.lock()->getLabelSet())
            labels.insert(label);
    }

    std::vector<float> layer = get_scaled_layer_mask(cl_->active_->labels_,
                          labels,
                          big_to_small,
                          size);

    Eigen::MatrixXf correlation_mat = multi_correlate(layer, data, vector_size, size, stride, offset);
    Eigen::MatrixXf Rxx = correlation_mat.topLeftCorner(vector_size, vector_size);
    Eigen::VectorXf c = correlation_mat.block(0, vector_size, vector_size, 1);

    //std::cout << correlation_mat << std::endl;

    float R = c.transpose() * (Rxx.inverse() * c);

    qDebug() << "R^2: " << R;
    //qDebug() << "R: " << sqrt(R);

    reportResult(R, c.data(), vector_size);

    //Eigen::VectorXf tmp = (Rxx.inverse() * c);

    qDebug() << "Y -> X correlation <<<<<<<<<<<<<";
    std::cout << c << std::endl;
    //qDebug() << "Coefs <<<<<<<<<<<<<";
    //std::cout << tmp << std::endl;

}