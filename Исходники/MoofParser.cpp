void
MoofParser::ParseEncrypted(Box& aBox)
{
  for (Box box = aBox.FirstChild(); box.IsAvailable(); box = box.Next()) {
    // Some MP4 files have been found to have multiple sinf boxes in the same
    // enc* box. This does not match spec anyway, so just choose the first
    // one that parses properly.
    if (box.IsType("sinf")) {
      mSinf = Sinf(box);

      if (mSinf.IsValid()) {
        break;
      }
    }
  }
}