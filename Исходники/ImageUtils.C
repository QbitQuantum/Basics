WPoint ImageUtils::getSize(const std::vector<unsigned char>& header)
{
  /*
   * Contributed by Daniel Derr @ ArrowHead Electronics Health-Care
   */
  std::string mimeType = identifyMimeType(header);

  if (mimeType == "image/png") {
    int width = ( ( ( toUnsigned(header[16]) << 8
		      | toUnsigned(header[17])) << 8
		    | toUnsigned(header[18])) << 8
		  | toUnsigned(header[19]));
    int height = ( ( ( toUnsigned(header[20]) << 8
		       | toUnsigned(header[21])) << 8
		     | toUnsigned(header[22])) << 8
		   | toUnsigned(header[23]));
    return WPoint(width, height);
  } else if (mimeType == "image/gif") {
    int width = toUnsigned(header[7]) << 8 | toUnsigned(header[6]);
    int height = toUnsigned(header[9]) << 8 | toUnsigned(header[8]);
    return WPoint(width, height);
  } else
    return WPoint();
}