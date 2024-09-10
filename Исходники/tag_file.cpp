size_t RenderV1ToFile(ID3_TagImpl& tag, fstream& file)
{
  if (!file)
  {
    return 0;
  }

  // Heck no, this is stupid.  If we do not read in an initial V1(.1)
  // header then we are constantly appending new V1(.1) headers. Files
  // can get very big that way if we never overwrite the old ones.
  //  if (ID3_V1_LEN > tag.GetAppendedBytes())   - Daniel Hazelbaker
  if (ID3_V1_LEN > tag.GetFileSize())
  {
    file.seekp(0, ios::end);
  }
  else
  {
    // We want to check if there is already an id3v1 tag, so we can write over
    // it.  First, seek to the beginning of any possible id3v1 tag
    file.seekg(0-ID3_V1_LEN, ios::end);
    char sID[ID3_V1_LEN_ID];

    // Read in the TAG characters
    file.read(sID, ID3_V1_LEN_ID);

    // If those three characters are TAG, then there's a preexisting id3v1 tag,
    // so we should set the file cursor so we can overwrite it with a new tag.
    if (memcmp(sID, "TAG", ID3_V1_LEN_ID) == 0)
    {
      file.seekp(0-ID3_V1_LEN, ios::end);
    }
    // Otherwise, set the cursor to the end of the file so we can append on
    // the new tag.
    else
    {
      file.seekp(0, ios::end);
    }
  }

  ID3_IOStreamWriter out(file);

  id3::v1::render(out, tag);

  return ID3_V1_LEN;
}