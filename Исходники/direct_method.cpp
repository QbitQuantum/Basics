void DirectPoseEstimationSingleLayer(
        const cv::Mat &img1,
        const cv::Mat &img2,
        const VecVector2d &px_ref,
        const vector<double> depth_ref,
        Sophus::SE3 &T21
) {

    // parameters
    int half_patch_size = 4;
    int iterations = 100;

    double cost = 0, lastCost = 0;
    int nGood = 0;  // good projections
    VecVector2d goodProjection;

    for (int iter = 0; iter < iterations; iter++) {
        nGood = 0;
        goodProjection.clear();

        // Define Hessian and bias
        Matrix6d H = Matrix6d::Zero();  // 6x6 Hessian
        Vector6d b = Vector6d::Zero();  // 6x1 bias

        for (size_t i = 0; i < px_ref.size(); i++) {

            // compute the projection in the second image
            // TODO START YOUR CODE HERE
            float u =0, v = 0;
            Eigen::Vector2d p1 = px_ref[i];

            Eigen::Vector3d pw((p1(0) - cx) / fx * depth_ref[i], (p1(1) - cy) / fy * depth_ref[i], depth_ref[i]);
            Eigen::Vector3d pc = T21 * pw;
            Eigen::Vector2d p2(fx * pc(0) / pc(2) + cx, fy * pc(1) / pc(2) + cy);

            u = p2(0);
            v = p2(1);

            if(u <= half_patch_size + 1 || u >=img2.cols - half_patch_size - 1 || v <= half_patch_size - 1 || v >= img2.rows - half_patch_size - 1)
            {
                continue;
            }
            nGood++;
            goodProjection.push_back(Eigen::Vector2d(u, v));

            // and compute error and jacobian
            for (int x = -half_patch_size; x < half_patch_size; x++)
                for (int y = -half_patch_size; y < half_patch_size; y++) {

                    double error = GetPixelValue(img1, p1(0)+x, p1(1)+y) - GetPixelValue(img2, p2(0)+x, p2(1)+y);
                    double Z = depth_ref[i];
                    double X = (p1(0) + x - cx) / fx * Z;
                    double Y = (p1(1) + y - cy) / fy * Z;

                    Matrix26d J_pixel_xi;   // pixel to \xi in Lie algebra
                    J_pixel_xi(0, 0) = fx / Z;
                    J_pixel_xi(0, 1) = 0;
                    J_pixel_xi(0, 2) = -fx * X / Z / Z;
                    J_pixel_xi(0, 3) = -fx * X * Y / Z / Z;
                    J_pixel_xi(0, 4) = fx + fx * X * X / Z / Z;
                    J_pixel_xi(0, 5) = -fx * Y / Z;
                    J_pixel_xi(1, 0) = 0;
                    J_pixel_xi(1, 1) = fy / Z;
                    J_pixel_xi(1, 2) = -fy * Y / Z / Z;
                    J_pixel_xi(1, 3) = -fy - fy * Y * Y / Z / Z;
                    J_pixel_xi(1, 4) = fy * X * Y / Z / Z;
                    J_pixel_xi(1, 5) = fy * X / Z;
                    Eigen::Vector2d J_img_pixel;    // image gradients
                    J_img_pixel[0] = (GetPixelValue(img2, p2(0)+x+1, p2(1)+y) - GetPixelValue(img2,p2(0)+x-1,p2(1)+y))/2;
                    J_img_pixel[1] = (GetPixelValue(img2, p2(0)+x, p2(1)+y+1) - GetPixelValue(img2,p2(0)+x,p2(1)+y-1))/2;

                    // total jacobian
                    Vector6d J= -J_img_pixel.transpose() * J_pixel_xi;

                    H += J * J.transpose();
                    b += -error * J;
                    cost += error * error;
                }
            // END YOUR CODE HERE
        }

        // solve update and put it into estimation
        // TODO START YOUR CODE HERE
        Vector6d update = H.inverse() * b;
        T21 = Sophus::SE3::exp(update) * T21;
        // END YOUR CODE HERE

        cost /= nGood;

        if (isnan(update[0])) {
            // sometimes occurred when we have a black or white patch and H is irreversible
            cout << "update is nan" << endl;
            break;
        }
        if (iter > 0 && cost > lastCost) {
            cout << "cost increased: " << cost << ", " << lastCost << endl;
            break;
        }
        lastCost = cost;
        cout << "cost = " << cost << ", good = " << nGood << endl;
    }
    cout << "good projection: " << nGood << endl;
    cout << "T21 = \n" << T21.matrix() << endl;

    // in order to help you debug, we plot the projected pixels here
    cv::Mat img1_show, img2_show;
    cv::cvtColor(img1, img1_show, CV_GRAY2BGR);
    cv::cvtColor(img2, img2_show, CV_GRAY2BGR);
    for (auto &px: px_ref) {
        cv::rectangle(img1_show, cv::Point2f(px[0] - 2, px[1] - 2), cv::Point2f(px[0] + 2, px[1] + 2),
                      cv::Scalar(0, 250, 0));
    }
    for (auto &px: goodProjection) {
        cv::rectangle(img2_show, cv::Point2f(px[0] - 2, px[1] - 2), cv::Point2f(px[0] + 2, px[1] + 2),
                      cv::Scalar(0, 250, 0));
    }
    cv::imshow("reference", img1_show);
    cv::imshow("current", img2_show);
    cv::waitKey();
}