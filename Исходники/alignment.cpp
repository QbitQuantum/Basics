void alignment(std::vector<cv::Mat> images, std::vector<cv::Point>& out)
{
  int num = images.size();
  out.resize(num);
  
  int i, j, m, n, x, y;
  for (m = 0; m < num-1; m++){
    long int same_counter, max_same;
    int shift_xoffset = 0, shift_yoffset = 0, answer = 4; //the initial of answer is 4
    IplImage *input, *comparison;
    IplImage *bitmap, *comparison_bitmap;
    IplImage *exbitmap, *comparison_exbitmap;
    IplImage *shifted_bitmap, *shifted_exbitmap ,*tmp;
    IplImage *grade;
    memset(offset, 0, 2*sizeof(int));
    
    //input = cvLoadImage(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat input_gray;
    cv::cvtColor(images[0], input_gray, cv::COLOR_BGR2GRAY);
    IplImage input_inst = input_gray;
    input = &input_inst;
    if (!input){
      //printf("%s doesn't exist!", argv[n+1]);
      exit(0);
    }
    //comparison = cvLoadImage(argv[m+2], CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat comparison_gray;
    cv::cvtColor(images[m+1], comparison_gray, cv::COLOR_BGR2GRAY);
    IplImage comparison_inst = comparison_gray;
    comparison = &comparison_inst;
    if (!comparison){
      //printf("%s doesn't exist!", argv[n+2]);
      exit(0);
    }
    
    int loop = (int)(log2f(std::min(input->width, input->height)));
    for (n = 0; n < loop; n++){
      //--------------------generate MTB from original input 2 images-----------------------
      bitmap = cvCreateImage(cvSize(input->width/pow(2, loop-1-n), input->height/pow(2, loop-1-n)), 8, 1);
      exbitmap = cvCreateImage(cvSize(input->width/pow(2, loop-1-n), input->height/pow(2, loop-1-n)), 8, 1);
      GenerateMTB(input, bitmap, exbitmap);
      
      comparison_bitmap = cvCreateImage(cvSize(comparison->width/pow(2, loop-1-n), comparison->height/pow(2, loop-1-n)), 8, 1);
      comparison_exbitmap = cvCreateImage(cvSize(comparison->width/pow(2, loop-1-n), comparison->height/pow(2, loop-1-n)), 8, 1);
      GenerateMTB(comparison, comparison_bitmap, comparison_exbitmap);
      //--------------------generating over-------------------------------------------------
      
      //Use shifted_exbitmap to find the most accurate offset.
      shifted_bitmap = cvCreateImage(cvSize(comparison->width/pow(2, loop-1-n), comparison->height/pow(2, loop-1-n)), 8, 1);
      shifted_exbitmap = cvCreateImage(cvSize(comparison->width/pow(2, loop-1-n), comparison->height/pow(2, loop-1-n)), 8, 1);
      
      //Use grade to calculate minimum inaccuracy offset.
      grade = cvCreateImage(cvSize(comparison->width/pow(2, loop-1-n), comparison->height/pow(2, loop-1-n)), 8, 1);
      
      max_same = 0;
      for (x = -1; x <= 1; x++){
        for (y = -1; y <= 1; y++){
          ShiftBitmap(comparison_bitmap, shifted_bitmap, x+shift_xoffset, y+shift_yoffset);
          ShiftBitmap(comparison_exbitmap, shifted_exbitmap, x+shift_xoffset, y+shift_yoffset);
          
          //XOR bitmap and comparison_bitmap
          for (i = 0; i < grade->height/1; i++)
            for (j = 0; j < grade->width/1; j++)
              grade->imageData[i*grade->widthStep+j] = bitmap->imageData[i*bitmap->widthStep+j] ^ shifted_bitmap->imageData[i*shifted_bitmap->widthStep+j];
          
          //AND with exbitmap (first one)
          for (i = 0; i < grade->height/1; i++)
            for (j = 0; j < grade->width/1; j++)
              grade->imageData[i*grade->widthStep+j] = grade->imageData[i*grade->widthStep+j] & exbitmap->imageData[i*exbitmap->widthStep+j];
          
          //AND with comparison_exbitmap (second one)
          for (i = 0; i < grade->height/1; i++)
            for (j = 0; j < grade->width/1; j++)
              grade->imageData[i*grade->widthStep+j] = grade->imageData[i*grade->widthStep+j] & shifted_exbitmap->imageData[i*shifted_exbitmap->widthStep+j];
          
          //Count how many sames are there
          same_counter = 0;
          for (i = 0; i < grade->height/1; i++){
            for (j = 0; j < grade->width/1; j++){
              if (grade->imageData[i*grade->widthStep+j] == 0)
                same_counter++;
            }
          }
          //same[3*x+y+4] = same_counter; // (-1, -1)=[0] ... (1, 1)=[8]
          if (same_counter > max_same){
            max_same = same_counter;
            answer = 3*x+y+4;
          }
        }
      }
      
      offset[0] += (answer/3 - 1) * pow(2, 5-n);
      offset[1] += (answer%3 - 1) * pow(2, 5-n);
      
      shift_xoffset += answer/3 - 1;
      shift_yoffset += answer%3 - 1;
      shift_xoffset *= 2;
      shift_yoffset *= 2;
      
      //printf("offset is %d %d %d\n", answer, offset[0], offset[1]);
    }
    total_offset[0][m] = offset[0];
    total_offset[1][m] = offset[1];
  }
  
  out[0].x = 0, out[0].y = 0;
  for (i = 0; i < m; i++) {
    out[i+1].x = total_offset[0][i];
    out[i+1].y = total_offset[1][i];
  }
}