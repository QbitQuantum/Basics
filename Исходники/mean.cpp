// Mean Shift Algorithm
void meanShift(Mat& img1, Mat& img2, Ptr<DescriptorMatcher>& descriptorMatcher, int matcherFilterType, vector<KeyPoint>& tpkeypoints,
               Mat& tpdescriptors, vector<KeyPoint>& keypoints2, Mat& descriptors2, Mat& clusters1, Point2f &cp, int& flag,
               vector<Point2f>& MP1, Mat& img2ROI, vector<KeyPoint>& bkeypoints, Mat& bdescriptors, Mat& temp,
               int& FG_mp, int&FG, int& BG_mp, int& BG, int& FG_BG, int& msI)
{
    size_t i,j;
    // Mat temp=img2.clone();
    int converged = 0, semiConverged = 0;
    Mat img1ROI, labels1_;
    Point2f lastCenter(box.x+box.width/2,box.y+box.height/2);
    float scale = 1;

    img1ROI = img1(boxOrg);
    vector<Point2f> points1, bmp;
    KeyPoint::convert(tpkeypoints, points1);
    searchBin(tpdescriptors, clusters1, labels1_); // clustering based on Kmeans centers obatined earlier

//vector<Point2f> np;
//    Mat newimg = img1ROI.clone();
//     KeyPoint::convert(tpkeypoints, np);
//    for(size_t i=0;i<np.size();i++)
//        circle(newimg, np[i], 2, Scalar(255,0,255),2);

//     imshow( "msimg", newimg );
//    np.clear();

//    waitKey(0);


    vector<float> prevPDF(NOC); // pdf of source
    weightedPDF( points1, boxOrg, labels1_, NOC, prevPDF); // Making histogram/pdf by normalizing the data and applying weights based on positions

    // Iterations for finding the object

    Point2f zBCmax(0,0); // center corspndng to the iteration with max BC
    float BC, BCmax=0, BCprev=0, BCnow=0; // Bhattachrya coefficient, max val for an image, previous and current val for an iteration
    int stopCount=0; // MS iterations must converege for stopCount < ManualSetThreshold
    vector<Point2f> matchedPoints1, matchedPoints2;
    while ( !converged )
    {
       // ofstream tempF;
        //tempF.open("tempF.txt", ios::out);
        matchedPoints1.clear(); matchedPoints2.clear();

        Mat matchedDesc1, matchedDesc2;
        vector<int> queryIdxs, trainIdxs;

        cv::Rect expandedBox;

#ifdef DEBUG
        cout << "iteration in while = \t" << ++iter << endl;
#endif

        if (EXPANDED_BOX)
        {
            expandedBox = Rect(box.x-25, box.y-25, box.width+50, box.height+50);
            boundaryCheckRect(expandedBox);
            img2ROI = img2(expandedBox);
        }
        else
        {
          //  cout << box.br() << "\t" << box.tl() << "\t" << img2.cols << endl;
            img2ROI = img2(box);
        }

        vector<KeyPoint> tempkey;
       // Mat pointsTransed21;
        MP1.clear();

        doIteration(img1ROI, img2ROI, queryIdxs, trainIdxs,descriptorMatcher, matcherFilterType, tpkeypoints,tpdescriptors,
                    keypoints2,descriptors2, matchedDesc1, matchedDesc2,  matchedPoints1, matchedPoints2, MP1,tempkey);

        if(matchedPoints2.size() < 1)
        {
            FG=0; BG=0;FG_mp=0;BG_mp=0;FG_BG=0; msI=0;
            break;

        }
        //  mdescriptors = matchedDesc2;

        //   KeyPoint::convert(keypoints2, points2);


        if (EXPANDED_BOX)
            shiftPoints(matchedPoints2, expandedBox);
        else
            shiftPoints(matchedPoints2, box);


        // shiftPoints(matchedPoints1,boxOrg);
        vector<float> predPDF(NOC,0);

        Mat labels2, labels2_; // depending on PDF_OF_WHOLE
        Point2f z(0,0);


        //==================== Edited at 8th april =======================//
        bmp.clear();
        Mat tmatchedDesc2, tmatchedDesc1;
        vector<Point2f> tmatchedPoints2;
        msI = stopCount;
        FG_mp = matchedPoints2.size();

        vector<KeyPoint> tempbk;
        Mat tempBd;
        vector<DMatch> filteredMatches;
        crossCheckMatching( descriptorMatcher, bdescriptors, descriptors2, filteredMatches, 1 );
        trainIdxs.clear();    queryIdxs.clear();

        for( i = 0; i < filteredMatches.size(); i++ )
        {
            queryIdxs.push_back(filteredMatches[i].queryIdx);
            trainIdxs.push_back(filteredMatches[i].trainIdx);
        }


        vector<Point2f> points1; KeyPoint::convert(bkeypoints, points1, queryIdxs);
        vector<Point2f> points2;   KeyPoint::convert(keypoints2, points2, trainIdxs);
        vector<char> matchesMask( filteredMatches.size(), 0 );
        /////
        Mat H12;
        Mat drawImg;
        if (points2.size() < 4 )
        {
            cout << "backpoints less than 4, hence prev ROI is retained" << endl;
            return;
            for(i=0;i<points2.size();i++)
            {
                bmp.push_back( points2[i]);
                tempBd.push_back(bdescriptors.row(queryIdxs[i]));
                tempbk.push_back(keypoints2[trainIdxs[i]]);
                tempBd.push_back(descriptors2.row(trainIdxs[i]));
                tempbk.push_back(keypoints2[trainIdxs[i]]);
            }
        }
        else
        {
            H12 = findHomography( Mat(points1), Mat(points2), CV_RANSAC, RANSAC_THREHOLD );

            if( !H12.empty() )
            {
                Mat points1t; perspectiveTransform(Mat(points1), points1t, H12);

                for( size_t i1 = 0; i1 < points1.size(); i1++ )
                {
                    double diff = norm(points2[i1] - points1t.at<Point2f>((int)i1,0));
                    if(diff  <= 20)
                    {
                        matchesMask[i1]=1;
                        bmp.push_back( points2[i1]);
                        tempBd.push_back(bdescriptors.row(queryIdxs[i1]));
                        tempbk.push_back(keypoints2[trainIdxs[i1]]);
                        tempBd.push_back(descriptors2.row(trainIdxs[i1]));
                        tempbk.push_back(keypoints2[trainIdxs[i1]]);

                    }
                }

                drawMatches( img1ROI, bkeypoints, img2ROI, keypoints2, filteredMatches, drawImg, CV_RGB(0, 255, 0), CV_RGB(0, 0, 255), matchesMask
             #if DRAW_RICH_KEYPOINTS_MODE
                             , DrawMatchesFlags::DRAW_RICH_KEYPOINTS
             #endif
                             );

            }
        }
        imshow("bm",drawImg);

        //============edit part ====
        shiftPoints(bmp, box);
        vector<int> bflag(bmp.size(),0);

        for(i=0;i<bmp.size();i++)
            bflag[i]=0;

        vector<int> ft(matchedPoints2.size(),0);

        for(i=0;i<matchedPoints2.size();i++)
        {
            ft[i]=0;
            for(j=0; j< bmp.size(); j++)
            {
                double diff = norm (matchedPoints2[i] - bmp[j]);
                // cout << diff << endl;
                if(diff < 0.5)
                {
                    bflag[j]=1;
                    ft[i]=1;
                    break;
                }
            }
            if(ft[i]==0)
            {
                tmatchedPoints2.push_back(matchedPoints2[i]);
                tmatchedDesc1.push_back(matchedDesc1.row(i));
                tmatchedDesc2.push_back(matchedDesc2.row(i));
            }

        }




        //=================================================================//


        // allot descriptors to the clusters to make histogram
        searchBin(tmatchedDesc1, clusters1, labels1_);
        searchBin( tmatchedDesc2, clusters1, labels2);
        if (PDF_OF_WHOLE)
            searchBin( descriptors2, clusters1, labels2_);

        // find the PDF for the above histogram as per weights
        if (PDF_OF_WHOLE)
            weightedPDF( points2, box, labels2_, NOC, predPDF);
        else
            weightedPDF( tmatchedPoints2, box, labels2, NOC, predPDF);

        // find weights for each IPoint as per the values of weighted PDFs
        vector<float> weights(labels2.rows,0);
        Mat imgTemp = img2.clone();
        findWeights( prevPDF, predPDF, labels1_, labels2, weights, queryIdxs, tmatchedDesc1, tmatchedDesc2);

        // find new ROI center as per above weights
        findNewCenter(tmatchedPoints2, weights, box, z);

        lastCenter = Point2f (box.x+box.width/2, box.y+box.height/2);

        // if current BC is less than previous BC, then take mean of the prev and current centers
        BCnow = findBC(predPDF,prevPDF);
        if (BCnow < BCprev)
            z = 0.5*(z+lastCenter);
        BCprev = BCnow;

        // check if ROI centers converge to same pixel
        if ( (norm(z - lastCenter) < 3))
        {
            semiConverged = 1;
            if (!SHOW_FINAL_ROI)
                rectangle(temp, box, Scalar(0,0,255),2);
        }
        else
        {
            // keep iterating
            stopCount++;

            if (stopCount >= MAX_MS_ITER)
            {
                semiConverged = 1;
                flag = 0;
                if (!SHOW_FINAL_ROI)
                    rectangle(temp, box, Scalar(0,0,255),2);
                z = zBCmax;
            }

            box.x = z.x - box.width/2;
            box.y = z.y - box.height/2;
            boundaryCheckRect(box);

            if (stopCount < MAX_MS_ITER)
                if (!SHOW_FINAL_ROI)
                    ;// rectangle(temp, box, Scalar(0,255,0), 2);
        }

        // store values of max BC and corresponding center z
        if ( BCnow > BCmax)
        {
            BCmax = BC;
            zBCmax = z;
        }

        if (semiConverged)
        {
            converged = 1;

            //   FG_mp, FG, BG_mp, BG, FG_BG, msI ;
            //==========edited on 5april ========
            bdescriptors.release();
            bkeypoints.clear();
            for(i=0;i<tempBd.rows;i++)
            {
                bdescriptors.push_back(tempBd.row(i));
                bkeypoints.push_back(tempbk[i]);

            }


            tpdescriptors.release();
            tpkeypoints.clear();
            //============================================//

            for(i=0;i<matchedPoints2.size();i++)
            {
                if(ft[i]==0)
                {
                    tpdescriptors.push_back(matchedDesc1.row(i));
                    tpkeypoints.push_back(tempkey[i]);

                    tpdescriptors.push_back(matchedDesc2.row(i));
                    tpkeypoints.push_back(tempkey[i]);

                }
            }


//=================================
            box.x = z.x - box.width/2;
            box.y = z.y - box.height/2;

           // imgTemp.release();

            trajectory << z.x << "\t" << z.y << "\t" << box.width << "\t" << box.height << endl;

            cp =z;


            cv::circle(temp, z, 3, Scalar(0,255,255), 3);
            cv::rectangle(temp, box, Scalar(255,0,0),2);

            cout << "MP1 \t" << MP1.size() <<"\t" << "bmp \t"  <<bmp.size() << endl;

            for(size_t i=0;i<MP1.size();i++)
            {//circle(temp, MP1[i], 3, Scalar(255,255,255),3);
              circle(temp, matchedPoints2[i], 3, Scalar(255,0,255),3);
            }

            // shiftPoints(bmp,box);
           for(size_t i=0;i<bmp.size();i++)
             { circle(temp, bmp[i], 2, Scalar(0,0,0),2);
              // cout << bmp[i] << endl;
           }

        }

        char c = (char)waitKey(10);
        if( c == '\x1b' ) // esc
        {
            cout << "Exiting from while iterator..." << endl;
            break;
        }
    }




    cv::imshow("Iter", temp);
  //  waitKey(0);
    eachIter.close();

}