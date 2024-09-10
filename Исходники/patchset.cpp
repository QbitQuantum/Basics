int Patches::add(Image& image, PatchType type, Point2f position, float weight)
{

  Ptr<Patch> pch;

  switch (type)
    {
    case HISTOGRAM:
      pch = new HistogramPatch(count++, 10, bufferlimit, psize, psize);
      break;
    case RGBPIXEL:
      pch = new RGBPatch(count++, 10, bufferlimit);
      break;
    case HSPIXEL:
      pch = new HSPatch(count++, 10, bufferlimit);
      break;
    case SSD:
      pch = new SSDPatch(count++, 10, bufferlimit, psize, psize);
      break;
    default:
      throw LegitException("Unknown type");
    }

  pch->push();
  pch->set_position(position);
  pch->set_weight(weight);

  pch->initialize(image, position);

  //calculate_histogram(image, position, psize, pch->histogram);

  patches.push_back(pch);

  return patches.size();
}