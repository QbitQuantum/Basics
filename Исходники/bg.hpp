void background(Mat &img, Mat &fore, Mat &back)
{
  bg.operator()(img, fore);
  bg.getBackgroundImage(back);

  erode(fore, fore, Mat());
  return ;
}