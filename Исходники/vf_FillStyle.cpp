void FillStyle::operator() (Image destImage, Image fillImage)
{
  copyImage (
    destImage,
    Point <int> (0, 0),
    fillImage,
    fillImage.getBounds (),
    mode,
    opacity);
}