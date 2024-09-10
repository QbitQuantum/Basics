std::vector<cv::Point> Ask_Circle(cv::Mat &src_im, cv::Point center, cv::Mat &draw_im){
    //src_im    ->  入力画像(2値価画像
    //center    ->  求める円の中心
    //draw_im   ->  描画用の画像

    // ラベリング
    cv::Mat label, state, centroids;
    int nLabels = cv::connectedComponentsWithStats(~src_im, label, state, centroids, 8);

    // 中心座標を含んだ外周を求める
    cv::Mat dst = cv::Mat::zeros(src_im.rows, src_im.cols, CV_8UC1);

    int a = 0;

    for(int i = 1; i < nLabels; i++){
        int l = state.at<int>(i, cv::CC_STAT_LEFT);
        int r = l + state.at<int>(i, cv::CC_STAT_WIDTH);
        int t = state.at<int>(i, cv::CC_STAT_TOP);
        int u = t + state.at<int>(i, cv::CC_STAT_HEIGHT);

        if(l < center.x && center.x < r && t < center.y && center.y < u){
            a++;
            if(a > 0) {
                cv::Point point = RasterScan(label, i);
                Ask_Perimeter(label, i, point, 2, dst);   //周囲辺を描画
                break;
            }
        }
    }

    cv::namedWindow("testdao", CV_WINDOW_AUTOSIZE);
    cv::imshow("testdao", org);

    // スターバースト(もどき)
    std::vector<cv::Point> iris_age;
    int min_rad = Ask_Minimum_rad(center, cv::Point(src_im.cols, src_im.rows));

    for(int theta = -50; theta <= 50; theta++){
        bool l_flg = false, r_flg = false;
        int  l_rad = 0, r_rad = 0;

        for(int rad = 1; rad < min_rad; rad++){
            int x = (int)(center.x + rad * cos(theta * (CV_PI/180)));
            int y = (int)(center.y + rad * sin(theta * (CV_PI/180)));
            int x2 = (int)(center.x - rad * cos(theta * (CV_PI/180)));
            int y2 = (int)(center.y - rad * sin(theta * (CV_PI/180)));

            if(dst.data[ y * dst.step + x * dst.elemSize()] == 200 && !r_flg){
                r_rad = rad;
                r_flg = true;
            }

            if(dst.data[ y2 * dst.step + x2 * dst.elemSize()] == 200 && !l_flg){
                l_rad = rad;
                l_flg = true;
            }

            if(r_flg && l_flg){
                //if(abs(l_rad-r_rad) < 15){
                if(r_rad > 115 && l_rad > 115){
                    x = (int)(center.x + r_rad * cos(theta * (CV_PI/180)));
                    y = (int)(center.y + r_rad * sin(theta * (CV_PI/180)));
                    x2 = (int)(center.x - l_rad * cos(theta * (CV_PI/180)));
                    y2 = (int)(center.y - l_rad * sin(theta * (CV_PI/180)));
                    iris_age.push_back(cv::Point(x,y));
                    iris_age.push_back(cv::Point(x2,y2));
                    if(&draw_im != (cv::Mat *)nullptr){
                        //cv::line(draw_im, center, cv::Point(x,y), CV_RGB(200, 0, 0));
                        //cv::line(draw_im, center, cv::Point(x2,y2), CV_RGB(200, 0, 0));
                    }
                //std::cout << r_rad << ", " << l_rad << std::endl;
                }
                break;
            }
        }
    }

    //cv::RotatedRect box = cv::fitEllipse(iris_age);
    //cv::ellipse(org, box,cv::Scalar(255,0,0),2,8);

    std::vector<cv::Point> circle_element;

    if ((int)iris_age.size() < 2) return circle_element;

    // RANSACを用いて最適解の選定
    int all_element = (int)iris_age.size();
    int sample_element = 4;
    int repeat = 100;

    int best_rad = -1;
    int min_error = 10000000;

    for(int i = 0; i < repeat; i++){
        // サンプル作成
        int sample_rad = 0;
        for(int j = 0; j < sample_element; j++){
            int sample_num = rand()%all_element;
            sample_rad += sqrt(Square(center.x-iris_age[sample_num].x) + Square(center.y-iris_age[sample_num].y));
        }

        // サンプルの平均半径を算出
        sample_rad /= sample_element;

        // 実際のデータとサンプルを比較
        int total_error = 0;
        for(int k = 0; k < all_element; k++){
            int element_rad = (int)sqrt(Square(center.x-iris_age[k].x) + Square(center.y-iris_age[k].y));
            total_error += abs(element_rad - sample_rad);
        }

        // 誤差が今までで最小なら保持
        if(total_error < min_error){
            min_error = total_error;
            best_rad = sample_rad;
        }
    }

    // 円の点群(72点)を取得
    for(int theta = 0; theta < 359; theta += 5){
        int x = (int)(center.x + best_rad * cos(theta * (CV_PI/180)));
        int y = (int)(center.y + best_rad * sin(theta * (CV_PI/180)));
        circle_element.push_back(cv::Point(x,y));
    }

    // 円の描画
    if(best_rad > 0 && &draw_im != (cv::Mat *)nullptr){
        //cv::circle(draw_im, center, best_rad, CV_RGB(0,200,0));
    }

    return circle_element;
}