void SOGP::predict(const VectorXd &state, VectorXd &prediction,
                   VectorXd &prediction_variance) {
    //check if we have initialised the system
    if (!this->initialized) {
        throw OTLException("SOGP not yet initialised");
    }

    double kstar = kernel->eval(state,state);

    //check if we not been trained
    if (this->current_size == 0) {
        prediction = VectorXd::Zero(this->output_dim);
        prediction_variance = VectorXd::Ones(this->output_dim)*
                (kstar + this->noise);
        return;
    }

    VectorXd k;
    kernel->eval(state, this->basis_vectors, k);
    //std::cout << "K: \n" << k << std::endl;
    //std::cout << "alpha: \n" << this->alpha.block(0,0,this->current_size, this->output_dim) << std::endl;

    prediction = k.transpose() *this->alpha.block(0,0,this->current_size, this->output_dim);
    prediction_variance = VectorXd::Ones(this->output_dim)*
            (k.dot(this->C.block(0,0, this->current_size, this->current_size)*k)
             + kstar + this->noise);

    return;
}