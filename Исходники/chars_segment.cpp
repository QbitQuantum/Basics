//! 字符分割与排序
int CCharsSegment::charsSegment(Mat input, vector<Mat>& resultVec, Color color) {
  if (!input.data) return 0x01;

  Mat input_grey;
  cvtColor(input, input_grey, CV_BGR2GRAY);

  if (0) {
    imshow("plate", input_grey);
    waitKey(0);
    destroyWindow("plate");
  }

  Mat img_threshold;

  // 二值化
  // 根据车牌的不同颜色使用不同的阈值判断方法
  // TODO：使用MSER来提取这些轮廓

  //if (BLUE == plateType) {
  //  // cout << "BLUE" << endl;
  //  img_threshold = input_grey.clone();

  //  int w = input_grey.cols;
  //  int h = input_grey.rows;
  //  Mat tmp = input_grey(Rect_<double>(w * 0.1, h * 0.1, w * 0.8, h * 0.8));
  //  int threadHoldV = ThresholdOtsu(tmp);
  //  threshold(input_grey, img_threshold, threadHoldV, 255, CV_THRESH_BINARY);

  //} else if (YELLOW == plateType) {
  //  // cout << "YELLOW" << endl;
  //  img_threshold = input_grey.clone();
  //  int w = input_grey.cols;
  //  int h = input_grey.rows;
  //  Mat tmp = input_grey(Rect_<double>(w * 0.1, h * 0.1, w * 0.8, h * 0.8));
  //  int threadHoldV = ThresholdOtsu(tmp);
  //  // utils::imwrite("resources/image/tmp/inputgray2.jpg", input_grey);

  //  threshold(input_grey, img_threshold, threadHoldV, 255,
  //            CV_THRESH_BINARY_INV);

  //} else if (WHITE == plateType) {
  //  // cout << "WHITE" << endl;

  //  threshold(input_grey, img_threshold, 10, 255,
  //            CV_THRESH_OTSU + CV_THRESH_BINARY_INV);
  //} else {
  //  // cout << "UNKNOWN" << endl;
  //  threshold(input_grey, img_threshold, 10, 255,
  //            CV_THRESH_OTSU + CV_THRESH_BINARY);
  //}

  Color plateType = color;

  img_threshold = input_grey.clone();
  spatial_ostu(img_threshold, 8, 2, plateType);

  if (0) {
    imshow("plate", img_threshold);
    waitKey(0);
    destroyWindow("plate");
  }

  // 去除车牌上方的柳钉以及下方的横线等干扰
  // 并且也判断了是否是车牌
  // 并且在此对字符的跳变次数以及字符颜色所占的比重做了是否是车牌的判别条件
  // 如果不是车牌，返回ErrorCode=0x02

  if (!clearLiuDing(img_threshold)) return 0x02;
  //clearLiuDing(img_threshold);

  // 在二值化图像中提取轮廓

  Mat img_contours;
  img_threshold.copyTo(img_contours);

  vector<vector<Point> > contours;
  findContours(img_contours,
               contours,               // a vector of contours
               CV_RETR_EXTERNAL,       // retrieve the external contours
               CV_CHAIN_APPROX_NONE);  // all pixels of each contours

  vector<vector<Point> >::iterator itc = contours.begin();
  vector<Rect> vecRect;

  // 将不符合特定尺寸的字符块排除出去

  while (itc != contours.end()) {
    Rect mr = boundingRect(Mat(*itc));
    Mat auxRoi(img_threshold, mr);

    if (verifyCharSizes(auxRoi)) vecRect.push_back(mr);
    ++itc;
  }

  // 如果找不到任何字符块，则返回ErrorCode=0x03

  if (vecRect.size() == 0) return 0x03;

  // 对符合尺寸的图块按照从左到右进行排序;
  // 直接使用stl的sort方法，更有效率

  vector<Rect> sortedRect(vecRect);
  std::sort(sortedRect.begin(), sortedRect.end(),
            [](const Rect& r1, const Rect& r2) { return r1.x < r2.x; });

  size_t specIndex = 0;

  // 获得特殊字符对应的Rectt,如苏A的"A"

  specIndex = GetSpecificRect(sortedRect);

  // 根据特定Rect向左反推出中文字符
  // 这样做的主要原因是根据findContours方法很难捕捉到中文字符的准确Rect，因此仅能
  // 退过特定算法来指定

  Rect chineseRect;
  if (specIndex < sortedRect.size())
    chineseRect = GetChineseRect(sortedRect[specIndex]);
  else
    return 0x04;

  if (0) {
    rectangle(img_threshold, chineseRect, Scalar(255));
    imshow("plate", img_threshold);
    waitKey(0);
    destroyWindow("plate");
  }

  //新建一个全新的排序Rect
  //将中文字符Rect第一个加进来，因为它肯定是最左边的
  //其余的Rect只按照顺序去6个，车牌只可能是7个字符！这样可以避免阴影导致的“1”字符

  vector<Rect> newSortedRect;
  newSortedRect.push_back(chineseRect);
  RebuildRect(sortedRect, newSortedRect, specIndex);

  if (newSortedRect.size() == 0) return 0x05;

  // 开始截取每个字符
  bool useSlideWindow = true;

  bool useAdapThreshold = true;
  //bool useAdapThreshold = CParams::instance()->getParam1b();

  for (size_t i = 0; i < newSortedRect.size(); i++) {
    Rect mr = newSortedRect[i];

    // Mat auxRoi(img_threshold, mr);

    // 使用灰度图来截取图块，然后依次对每个图块进行大津阈值来二值化

    Mat auxRoi(input_grey, mr);
    Mat newRoi;

    if (i == 0) {
      if (useSlideWindow) {
        float slideLengthRatio = 0.1f;
        //float slideLengthRatio = CParams::instance()->getParam1f();
        if (!slideChineseWindow(input_grey, mr, newRoi, plateType, slideLengthRatio, useAdapThreshold))
          judgeChinese(auxRoi, newRoi, plateType);
      }
      else
        judgeChinese(auxRoi, newRoi, plateType);
    }
    else {
      if (BLUE == plateType) {  
        threshold(auxRoi, newRoi, 0, 255, CV_THRESH_BINARY + CV_THRESH_OTSU);
      }
      else if (YELLOW == plateType) {
        threshold(auxRoi, newRoi, 0, 255, CV_THRESH_BINARY_INV + CV_THRESH_OTSU);
      }
      else if (WHITE == plateType) {
        threshold(auxRoi, newRoi, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY_INV);
      }
      else {
        threshold(auxRoi, newRoi, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
      }

      // 归一化大小
      newRoi = preprocessChar(newRoi);
    }
     
    if (0) {
      if (i == 0) {
        imshow("input_grey", input_grey);
        waitKey(0);
        destroyWindow("input_grey");
      }
      if (i == 0) {
        imshow("newRoi", newRoi);
        waitKey(0);
        destroyWindow("newRoi");
      }
    }

    // 每个字符图块输入到下面的步骤进行处理
    resultVec.push_back(newRoi);
  }

  return 0;
}