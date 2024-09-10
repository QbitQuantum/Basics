bool SpatialAverageSpotter::train(string dirPath)
{
    
    int count=0;
    vector<vector<tuple<int,Point2f> > > features;
    featureAverages.resize(codebook->size());
    for (int i =0; i<codebook->size(); i++)
        featureAverages[i]=Mat(BASE_SIZE,BASE_SIZE,CV_32F,Scalar(0));
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (dirPath.c_str())) != NULL) {
      /* print all the files and directories within directory */
//      Mat img;
      while ((ent = readdir (dir)) != NULL) {
          
          string fileName(ent->d_name);
//          cout << "examining " << fileName << endl;
          if (fileName[0] == '.' || fileName[fileName.size()-1]!='G')
              continue;
          
          Mat img = imread(dirPath+fileName, CV_LOAD_IMAGE_GRAYSCALE);
//          resize(img,img,Size(0,0),2,2);
          threshold(img,img,120.0,255,THRESH_BINARY);
//          windowWidth += img.cols;
//          windowHeight += img.rows;
//          int avg=0;
//          for (int x=0; x<img.cols; x++)
//              for (int  y=0; y<img.rows; y++)
//                  avg += (int)img.at<unsigned char>(y,x);
////          cout << "avg="<<avg<<"/"<<img.cols*img.rows<<" = "<<avg/(img.cols*img.rows)<<endl;
//          avg /= img.cols*img.rows;
          
          resize(img,img,Size(PRE_BASE_SIZE,PRE_BASE_SIZE*((0.0+img.rows)/img.cols)));
          
          
          copyMakeBorder( img, img, BORDER_SIZE, BORDER_SIZE, BORDER_SIZE, BORDER_SIZE, BORDER_CONSTANT, 255 );
          assert(img.cols > 1 && img.rows > 1);
          adjustedTrainingImages.push_back(img.clone());
          
          Point2f centerOfMass = findCenterOfMass(img);
          int offsetx=(img.cols/2)-centerOfMass.x;
          int offsety=(img.rows/2)-centerOfMass.y;
          translateImg(img,offsetx,offsety);
          
        
          vector<KeyPoint> keypoints;
          Mat desc;
          detectKeypoints( img,keypoints, desc);
          Mat out;
          cvtColor(img,out,CV_GRAY2RGB);
          circle(out,centerOfMass,1,Scalar(0,0,255));
          
          features.resize(count+1);
          //double scaling = BASE_SIZE/img
          for (int r=0; r<desc.rows; r++)
          {
              int f = codebook->quantize(desc.row(r));
              Point2f offsetPoint(keypoints[r].pt.x - centerOfMass.x, keypoints[r].pt.y - centerOfMass.y);
              features[count].push_back(make_tuple(f,offsetPoint));//we're ignoring the keypoint scale.. 
              
              
//              circle(out,keypoints[r].pt,keypoints[r].size,Scalar(colorTable[f]));
              Rect rec(keypoints[r].pt.x-(keypoints[r].size/2),keypoints[r].pt.y-(keypoints[r].size/2),keypoints[r].size,keypoints[r].size);
              rectangle(out,rec,Scalar(colorTable[f]));
              
          }
          guassColorIn(features[count]);
          
          
          imshow("learning keypoints",out);
          cout << "image "<<count<<endl;
          waitKey(5);
          
          count++;
//          img.release();
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");
      return false;
    }
    
    //We now step through adjusting the scales of the various images so the guass coloring is maximized
    //But we may still want to look at tfidf to see which ones should be weighted more, etc.
    maximizeAlignment(features);
    
    float max=0;
    float min =99999;
    float avg_max=0;
    
    int firstx=9999;
    int lastx=0;
    int firsty=9999;
    int lasty=0;
    
    for (int f=0; f<codebook->size(); f++)
    {
        float local_max=0;
        
        bool hitFirst=false;
        
        for (int x=0; x<featureAverages[f].cols; x++)
            for (int y=0; y<featureAverages[f].rows; y++)
            {
                float val = featureAverages[f].at<float>(y,x);
                if (val > 300 || val < -300)
                    cout << "val (" << x <<","<<y<<") " << val << endl;
                if (val>max) max=val;
                if (val<min) min=val;
                if (val>local_max) local_max=val;
                
                if (val>WINDOW_THRESH)
                {
                    if (!hitFirst)
                    {
                        hitFirst=true;
                        if (x<firstx) firstx=x;
                        if (y<firsty) firsty=y;
                    }
                    if (x>lastx) lastx=x;
                    if (y>lasty) lasty=y;
                }
            }
        avg_max+=local_max;
    }
//    penalty=min+(max-min)*.2;
    avg_max /= codebook->size();
    penalty=avg_max*.15;//.2
    
//    windowWidth/=count;
//    windowHeight/=count;
    windowWidth = lastx-firstx;
    windowHeight = lasty-firsty;
    cout << "window size is "<<windowWidth<<"x"<<windowHeight<<endl;
    
    //show averages
    showAverages();
    
    return true;
}