int main(int argc, char* argv[])
{
  bool bAlignment = false;
  int arg_base = 1;
  
  for (;arg_base < argc; ++arg_base) {
    const char *a = argv[arg_base];
    
    if (a[0] != '-')
      break;
    
    if (std::strcmp(a+1, "alignment") == 0) {
      bAlignment = true;
    }
  }
  
  const char * outputFilePath = argv[arg_base];
  const char * const * inputFilePaths = argv + arg_base + 1;
  int numInputs = argc - arg_base - 1;
  if (numInputs < 1)
    usage(argc, argv);
  
  // Read Images
  for (int i = 0; i < numInputs; ++i) {
    float shutter;
    if (!readExif(inputFilePaths[i], shutter)) {
      std::printf("%s : shutter ?\n > ", inputFilePaths[i]);
      std::scanf("%f", &shutter);
    }
    
    cv::Mat img = cv::imread(inputFilePaths[i], cv::IMREAD_COLOR);
    
    sourceImages.push_back(img);
    exposureTimes.push_back(shutter);
    indirectIndex.push_back(i);
  }
  
  // Sort by exposure time
  auto cmp = [](int a, int b){ return exposureTimes[a] < exposureTimes[b]; };
  std::sort(indirectIndex.begin(), indirectIndex.end(), cmp);
  if (0) {
    char buf[128];
    for (int i = 0; i < numInputs; ++i) {
      sprintf(buf, "input-%d", i);
      cv::imshow(buf, getImage(i));
    }
    cv::waitKey(0);
  }
  
  // Perform Alignment
  if (bAlignment) {
    std::vector<cv::Mat> imgs(numInputs);
    for (int i = 0; i < numInputs; ++i) {
      imgs[i] = getImage(i);
    }
    
    std::vector<cv::Point> offsets;
    alignment(imgs, offsets);
    
    cv::Size minsize = getImage(0).size();
    
    for (int i = 0; i < numInputs; ++i) {
      std::printf("offset[%d] = %d %d\n", i, offsets[i].x, offsets[i].y);
      
      imgs[i] = cv::Mat(imgs[i], offsetRect(offsets[i], i));
      
      cv::Size sz = imgs[i].size();
      
      minsize.width = std::min(minsize.width, sz.width);
      minsize.height = std::min(minsize.height, sz.height);
    }
    
    std::printf("minsize = %d %d\n", minsize.width, minsize.height);
    
    for (int i = 0; i < numInputs; ++i) {
      cv::Rect rect(cv::Point(0,0), minsize);
      sourceImages[indirectIndex[i]] = imgs[i](rect).clone();
    }
  }
  
  // Recover Response Curve
  cv::Mat rc = recoverResponseCurve();
  if (0) {
    std::printf("response curve:\n");
    for (int i = 0; i < 256; ++i) {
      std::printf("%d, %f\n", i, rc.at<float>(i, 0));
    }
  }
  
  // Generate Radiance Map
  cv::Mat hdr = generateRadianceMap(rc);
  
  // Write Output
  writeHDR(outputFilePath, hdr);
  
  if (1) {
    showHDR(hdr);
    cv::waitKey(0);
  }
  
  return 0;
}