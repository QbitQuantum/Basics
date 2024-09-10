int computeMaxZoomHeight(QSize scrollSize, QSize imageSize,
                         int scrollBarDimension) {

  scrollSize.transpose();
  imageSize.transpose();
  return computeMaxZoomWidth(scrollSize, imageSize, scrollBarDimension);
}