static void ValidateTreePointers(nsTArray<RefPtr<Layer> >& aLayers) {
  for (uint32_t i = 0; i < aLayers.Length(); i++) {
    ValidateTreePointers(aLayers[i]);
  }
}