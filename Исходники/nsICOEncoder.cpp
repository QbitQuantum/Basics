// Parses the encoder options and sets the bits per pixel to use and PNG or BMP
// See InitFromData for a description of the parse options
nsresult
nsICOEncoder::ParseOptions(const nsAString& aOptions, uint32_t* bpp, 
                           bool *usePNG)
{
  // If no parsing options just use the default of 24BPP and PNG yes
  if (aOptions.Length() == 0) {
    if (usePNG) {
      *usePNG = true;
    }
    if (bpp) {
      *bpp = 24;
    }
  }

  // Parse the input string into a set of name/value pairs.
  // From format: format=<png|bmp>;bpp=<bpp_value>
  // to format: [0] = format=<png|bmp>, [1] = bpp=<bpp_value>
  nsTArray<nsCString> nameValuePairs;
  if (!ParseString(NS_ConvertUTF16toUTF8(aOptions), ';', nameValuePairs)) {
    return NS_ERROR_INVALID_ARG;
  }

  // For each name/value pair in the set
  for (int i = 0; i < nameValuePairs.Length(); ++i) {

    // Split the name value pair [0] = name, [1] = value
    nsTArray<nsCString> nameValuePair;
    if (!ParseString(nameValuePairs[i], '=', nameValuePair)) {
      return NS_ERROR_INVALID_ARG;
    }
    if (nameValuePair.Length() != 2) {
      return NS_ERROR_INVALID_ARG;
    }

    // Parse the format portion of the string format=<png|bmp>;bpp=<bpp_value>
    if (nameValuePair[0].Equals("format", nsCaseInsensitiveCStringComparator())) {
      if (nameValuePair[1].Equals("png", nsCaseInsensitiveCStringComparator())) {
        *usePNG = true;
      }
      else if (nameValuePair[1].Equals("bmp", nsCaseInsensitiveCStringComparator())) {
        *usePNG = false;
      }
      else {
        return NS_ERROR_INVALID_ARG;
      }
    }

    // Parse the bpp portion of the string format=<png|bmp>;bpp=<bpp_value>
    if (nameValuePair[0].Equals("bpp", nsCaseInsensitiveCStringComparator())) {
      if (nameValuePair[1].Equals("24")) {
        *bpp = 24;
      }
      else if (nameValuePair[1].Equals("32")) {
        *bpp = 32;
      }
      else {
        return NS_ERROR_INVALID_ARG;
      }
    }
  }

  return NS_OK;
}