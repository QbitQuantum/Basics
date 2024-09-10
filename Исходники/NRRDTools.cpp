void NRRDTools::saveNRRDFile(const cleaver::FloatField *field, const std::string &name) {
  auto dims = field->dataBounds().size;
  ImageType::Pointer img = ImageType::New();
  itk::Index<3> start; start.Fill(0);
  ImageType::SizeType size;
  size[0] = static_cast<size_t>(dims[0]);
  size[1] = static_cast<size_t>(dims[1]);
  size[2] = static_cast<size_t>(dims[2]);
  ImageType::RegionType region(start, size);
  img->SetRegions(region);
  img->Allocate();
  img->FillBuffer(0);
  for (size_t i = 0; i < dims[0]; i++) {
    for (size_t j = 0; j < dims[1]; j++) {
      for (size_t k = 0; k < dims[2]; k++) {
        ImageType::IndexType pixelIndex;
        pixelIndex[0] = i;
        pixelIndex[1] = j;
        pixelIndex[2] = k;
        auto data = ((cleaver::FloatField*)field)->data();
        img->SetPixel(pixelIndex, data[i + size[0] * j + size[0] * size[1] * k]);
      }
    }
  }
  WriterType::Pointer write = WriterType::New();
  write->SetFileName(name + ((name.find_first_of(".nrrd") == std::string::npos) ? ".nrrd" : ""));
  write->SetInput(img);
  write->Update();
}