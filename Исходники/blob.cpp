 void Blob::deleteRange(Range range)
 {
     gfx_assert(range.location < length() && range.max() < length(), str("out of bounds range"));
     
     CFDataDeleteBytes(getStorage(), range);
 }