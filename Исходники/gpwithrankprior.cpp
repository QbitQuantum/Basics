MatrixXd GPWithRankPrior::filterData(
    MatrixXd &dataMatrix,                   // Data matrix to filter.
    std::vector<int> sequence,              // Sequence.
    double variance                         // Filtering variance.
    )
{
    MatrixXd result = dataMatrix;
    result.setZero(result.rows(),result.cols());

    int start = 0;
    for (std::vector<int>::iterator itr = sequence.begin(); itr != sequence.end(); ++itr)
    { // Step over each entry in sequence.
        int send = *itr;
        for (int t = start; t < send; t++)
        { // Step over each frame.
            int fstart = (int)floor((double)t-variance*3.0);
            int fend = (int)ceil((double)t+variance*3.0);
            if (fstart < start) fstart = start;
            if (fend >= send) fend = send-1;
            double totalw = 0.0;

            // Step over each frame to add in here.
            for (int tt = fstart; tt < fend; tt++)
            {
                double w = exp(-(1.0/variance)*pow((double)tt - (double)t,2));
                totalw += w;
                result.block(t,0,1,result.cols()) +=
                    dataMatrix.block(tt,0,1,result.cols())*w;
            }
            
            // Normalize.
            result.block(t,0,1,result.cols()) *= (1.0/totalw);
        }
        start = send;
    }

    // Return filtered result.
    return result;
}