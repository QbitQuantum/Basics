 WLMS(const MatrixXd & dataset, const MatrixXd & label, const MatrixXd& weight, double sigma_noise = 0.1)
 :sample_weight(weight.cols(), weight.cols())
 {
     for(auto i=0; i<weight.cols(); ++i)
     {
         sample_weight(i, i) = weight(i);
     }
     
     linear = (dataset.transpose() * sample_weight * dataset
               + sigma_noise * MatrixXd::Identity(dataset.cols(), dataset.cols())).inverse()
     * dataset.transpose() * sample_weight * label;
 }