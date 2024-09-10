bool PixlyFormat::onLoad(FileOp* fop)
{
  try {
    // load XML metadata
    XmlDocumentRef doc = open_xml(fop->filename());
    TiXmlHandle xml(doc.get());
    fop->setProgress(0.25);

    TiXmlElement* xmlAnim = check(xml.FirstChild("PixlyAnimation").ToElement());
    double version = check_number<double>(xmlAnim->Attribute("version"));
    if (version < 1.5) {
      throw Exception("version 1.5 or above required");
    }

    TiXmlElement* xmlInfo = check(xmlAnim->FirstChild("Info"))->ToElement();

    int layerCount  = check_number<int>(xmlInfo->Attribute("layerCount"));
    int frameWidth  = check_number<int>(xmlInfo->Attribute("frameWidth"));
    int frameHeight = check_number<int>(xmlInfo->Attribute("frameHeight"));

    UniquePtr<Sprite> sprite(new Sprite(IMAGE_RGB, frameWidth, frameHeight, 0));

    TiXmlElement* xmlFrames = check(xmlAnim->FirstChild("Frames"))->ToElement();
    int imageCount = check_number<int>(xmlFrames->Attribute("length"));

    if (layerCount <= 0 || imageCount <= 0) {
      throw Exception("No cels found");
    }

    int frameCount = imageCount / layerCount;
    sprite->setTotalFrames(frame_t(frameCount));
    sprite->setDurationForAllFrames(200);

    for (int i=0; i<layerCount; i++) {
      sprite->folder()->addLayer(new LayerImage(sprite));
    }

    // load image sheet
    Document* sheet_doc = load_document(nullptr, base::replace_extension(fop->filename(),"png").c_str());
    fop->setProgress(0.5);

    if (sheet_doc == NULL) {
      throw Exception("Pixly loader requires a valid PNG file");
    }

    Image* sheet = sheet_doc->sprite()->layer(0)->cel(0)->image();

    if (sheet->pixelFormat() != IMAGE_RGB) {
      throw Exception("Pixly loader requires a RGBA PNG");
    }

    int sheetWidth = sheet->width();
    int sheetHeight = sheet->height();

    // slice cels from sheet
    std::vector<int> visible(layerCount, 0);

    TiXmlElement* xmlFrame = check(xmlFrames->FirstChild("Frame"))->ToElement();
    while (xmlFrame) {
      TiXmlElement* xmlRegion = check(xmlFrame->FirstChild("Region"))->ToElement();
      TiXmlElement* xmlIndex = check(xmlFrame->FirstChild("Index"))->ToElement();

      int index = check_number<int>(xmlIndex->Attribute("linear"));
      frame_t frame(index / layerCount);
      LayerIndex layer_index(index % layerCount);
      Layer *layer = sprite->indexToLayer(layer_index);

      const char * duration = xmlFrame->Attribute("duration");
      if (duration) {
        sprite->setFrameDuration(frame, base::convert_to<int>(std::string(duration)));
      }

      visible[(int)layer_index] += (int)(std::string(check(xmlFrame->Attribute("visible"),"false")) == "true");

      int x0 = check_number<int>(xmlRegion->Attribute("x"));
      int y0_up = check_number<int>(xmlRegion->Attribute("y")); // inverted

      if (y0_up < 0 || y0_up + frameHeight > sheetHeight || x0 < 0 || x0 + frameWidth > sheetWidth) {
        throw Exception("looking for cels outside the bounds of the PNG");
      }

      // read cel images
      ImageRef image(Image::create(IMAGE_RGB, frameWidth, frameHeight));

      for (int y = 0; y < frameHeight; y++) {
        // RGB_ALPHA
        int y0_down = sheetHeight-1 - y0_up - (frameHeight-1) + y;
        uint32_t* src_begin = (uint32_t*)sheet->getPixelAddress(x0           , y0_down);
        uint32_t* src_end   = (uint32_t*)sheet->getPixelAddress(x0+frameWidth, y0_down);
        uint32_t* dst_begin = (uint32_t*)image->getPixelAddress(0, y);

        std::copy(src_begin, src_end, dst_begin);
      }

      // make cel trimmed or empty
      gfx::Rect bounds;
      if (algorithm::shrink_bounds(image.get(), bounds, image->maskColor())) {
        ImageRef trim_image(crop_image(image.get(),
                                  bounds.x, bounds.y,
                                  bounds.w, bounds.h,
                                  image->maskColor()));


        Cel* cel = NULL;
        if ((int)frame > 0) {
          // link identical neighbors
          Cel *prev_cel = static_cast<LayerImage*>(layer)->cel(frame-1);
          if (prev_cel && prev_cel->x() == bounds.x && prev_cel->y() == bounds.y) {
            Image *prev_image = prev_cel->image();
            if (prev_image && doc::count_diff_between_images(prev_image, trim_image.get()) == 0) {
              cel = Cel::createLink(prev_cel);
              cel->setFrame(frame);
            } // count_diff_between_images
          } // prev_cel
        } // frame > 0

        if (cel == NULL) {
          cel = new Cel(frame, trim_image);
          cel->setPosition(bounds.x, bounds.y);
        }

        static_cast<LayerImage*>(layer)->addCel(cel);

      }

      xmlFrame = xmlFrame->NextSiblingElement();
      fop->setProgress(0.5 + 0.5 * ((float)(index+1) / (float)imageCount));
    }

    for (int i=0; i<layerCount; i++) {
      LayerIndex layer_index(i);
      Layer *layer = sprite->indexToLayer(layer_index);
      layer->setVisible(visible[i] > frameCount/2);
    }

    fop->createDocument(sprite);
    sprite.release();
  }
  catch(Exception &e) {
    fop->setError((std::string("Pixly file format: ")+std::string(e.what())+"\n").c_str());
    return false;
  }

  return true;
}