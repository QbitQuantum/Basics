int CPlateDetect::plateDetect(Mat src, vector<CPlate>& resultVec,
                              bool showDetectArea, int index) {
  vector<Mat> resultPlates;

  vector<CPlate> color_Plates;
  vector<CPlate> sobel_Plates;
  vector<CPlate> color_result_Plates;
  vector<CPlate> sobel_result_Plates;

  vector<CPlate> all_result_Plates;

  //如果颜色查找找到n个以上（包含n个）的车牌，就不再进行Sobel查找了。
  const int color_find_max = m_maxPlates;

  m_plateLocate->plateColorLocate(src, color_Plates, index);
  m_plateJudge->plateJudge(color_Plates, color_result_Plates);

  // for (int i=0;i<color_Plates.size();++i)
  //{
  //	color_result_Plates.push_back(color_Plates[i]);
  //}

  for (size_t i = 0; i < color_result_Plates.size(); i++) {
    CPlate plate = color_result_Plates[i];

    plate.setPlateLocateType(COLOR);
    all_result_Plates.push_back(plate);
  }

  //颜色和边界闭操作同时采用
  {
    m_plateLocate->plateSobelLocate(src, sobel_Plates, index);
    m_plateJudge->plateJudge(sobel_Plates, sobel_result_Plates);

    /*for (int i=0;i<sobel_Plates.size();++i)
    {
            sobel_result_Plates.push_back(sobel_Plates[i]);
    }*/

    for (size_t i = 0; i < sobel_result_Plates.size(); i++) {
      CPlate plate = sobel_result_Plates[i];

      if (0) {
        imshow("plate_mat", plate.getPlateMat());
        waitKey(0);
        destroyWindow("plate_mat");
      }

      plate.bColored = false;
      plate.setPlateLocateType(SOBEL);

      all_result_Plates.push_back(plate);
    }
  }

  for (size_t i = 0; i < all_result_Plates.size(); i++) {
    // 把截取的车牌图像依次放到左上角
    CPlate plate = all_result_Plates[i];
    resultVec.push_back(plate);
  }
  return 0;
}