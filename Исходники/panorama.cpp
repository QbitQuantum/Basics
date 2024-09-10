Matrix RANSAC(vector <FeatureCorrespondence> listOfCorrespondences, int Niter, float epsilon) {
    // // --------- HANDOUT  PS07 ------------------------------
    // Put together the RANSAC algorithm.

    Matrix best_H = Matrix::Identity(3,3);
    int max_inliers = 0;

    for (int ransac_iter = 0; ransac_iter < Niter; ransac_iter++){
        
        vector<FeatureCorrespondence> random_corrs = sampleFeatureCorrespondences(listOfCorrespondences);
        vector<FeatureCorrespondence> listOfFeatureCorrespondences = {random_corrs[0], random_corrs[1], random_corrs[2], random_corrs[3]};
        vector<CorrespondencePair> listOfCorrespondencePairs = getListOfPairs(listOfFeatureCorrespondences);
        CorrespondencePair arrayOfCorrespondencePairs [4] = {listOfCorrespondencePairs[0], listOfCorrespondencePairs[1], listOfCorrespondencePairs[2], listOfCorrespondencePairs[3]};
        Matrix H = computeHomography(arrayOfCorrespondencePairs);
        
        //singular linear system
        if (H.determinant() == 0){
            H = Matrix::Identity(3,3);
        }

        vector<bool> inlier_vector = inliers(H, listOfFeatureCorrespondences, epsilon);
        int inlier_count = 0;

        for (bool inlier_bool : inlier_vector){
            if (inlier_bool){
                inlier_count += 1;
            }
        }

        if (inlier_count >= max_inliers) {
            max_inliers = inlier_count;
            best_H = H;
        }

    }

    return best_H;
}