 PassRefPtr<SimpleFontData> getFontDataForSize(float size) {
   FontDescription fontDescription;
   fontDescription.setSizeAdjust(size);
   fontDescription.setAdjustedSize(size);
   return getFontData(fontDescription);
 }