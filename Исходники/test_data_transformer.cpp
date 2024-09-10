TYPED_TEST(DataTransformTest, TestEmptyTransformUniquePixels) {
  TransformationParameter transform_param;
  const bool unique_pixels = true;  // pixels are consecutive ints [0,size]
  const int label = 0;
  const int channels = 3;
  const int height = 4;
  const int width = 5;

  Datum datum;
  FillDatum(label, channels, height, width, unique_pixels, &datum);
  Blob<TypeParam>* blob = new Blob<TypeParam>(1, 3, 4, 5);
  DataTransformer<TypeParam>* transformer =
      new DataTransformer<TypeParam>(transform_param, TEST);
  transformer->InitRand();
  transformer->Transform(datum, blob);
  EXPECT_EQ(blob->num(), 1);
  EXPECT_EQ(blob->channels(), datum.channels());
  EXPECT_EQ(blob->height(), datum.height());
  EXPECT_EQ(blob->width(), datum.width());
  for (int j = 0; j < blob->count(); ++j) {
    EXPECT_EQ(blob->cpu_data()[j], j);
  }
}