triState numColorsBaseModes::performProcessing(QImage* image, int numColors,
                                               int numImageColors) {

  colorTransformerPtr transformer =
    colorTransformer::createColorTransformer(flossMode());
  QVector<triC> newColors = ::chooseColors(*image, numColors,
                                           clickedColorList(),
                                           numImageColors,
                                           transformer);
  if (!newColors.empty()) {
    // remove the seed colors from newColors to create generatedColors
    const QVector<triC>& seedColors = clickedColorList();
    QVector<triC> generatedColors = newColors;
    for (int i = 0, size = seedColors.size(); i < size; ++i) {
      generatedColors.remove(generatedColors.indexOf(seedColors[i]));
    }
    setGeneratedColorList(generatedColors);
  }
  else {
    return triNoop;
  }
  if (!::segment(image, newColors, numImageColors).empty()) {
    //return triState(colorList().size() != savedColorsSize);
    return triTrue;
  }
  else {
    return triNoop;
  }
}