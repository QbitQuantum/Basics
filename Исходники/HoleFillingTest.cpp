TEST(hole_filling_test, elliptical_hole_on_repeated_texture_should_give_good_result)
{
    Mat img = imread("test_images/brick_pavement.jpg");
    convert_for_computation(img, 0.5f);

    // Add some hole
    Mat hole_mask = Mat::zeros(img.size(), CV_8U);

    Point center(100, 110);
    Size axis(20, 5);
    float angle = 20;
    ellipse(hole_mask, center, axis, angle, 0, 360, Scalar(255), -1);
    int patch_size = 7;
    HoleFilling hf(img, hole_mask, patch_size);

    // Dump image with hole as black region.
    Mat img_with_hole_bgr;
    cvtColor(img, img_with_hole_bgr, CV_Lab2BGR);
    img_with_hole_bgr.setTo(Scalar(0,0,0), hole_mask);
    imwrite("brick_pavement_hole.exr", img_with_hole_bgr);

    // Dump reconstructed image
    Mat filled = hf.run();
    cvtColor(filled, filled, CV_Lab2BGR);
    imwrite("brick_pavement_hole_filled.exr", filled);


    // The reconstructed image should be close to the original one, in this very simple case.
    Mat img_bgr;
    cvtColor(img, img_bgr, CV_Lab2BGR);
    double ssd = norm(img_bgr, filled, cv::NORM_L2SQR);
    EXPECT_LT(ssd, 0.2);
}