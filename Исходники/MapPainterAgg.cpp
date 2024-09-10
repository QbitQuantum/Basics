  void MapPainterAgg::DrawContourLabel(const Projection& projection,
                                       const MapParameter& parameter,
                                       const PathTextStyle& style,
                                       const std::string& text,
                                       size_t transStart, size_t transEnd)
  {
    double       fontSize=style.GetSize();
    double       r=style.GetTextColor().GetR();
    double       g=style.GetTextColor().GetG();
    double       b=style.GetTextColor().GetB();
    double       a=style.GetTextColor().GetA();
    std::wstring wideText(UTF8StringToWString(text));

    SetOutlineFont(projection,
                   parameter,
                   fontSize);

    //renderer_bin->color(agg::rgba(r,g,b,a));
    renderer_aa->color(agg::rgba(r,g,b,a));

    agg::path_storage path;

    double length=0;
    double xo=0;
    double yo=0;

    if (coordBuffer->buffer[transStart].GetX()<coordBuffer->buffer[transEnd].GetX()) {
      for (size_t j=transStart; j<=transEnd; j++) {
        if (j==transStart) {
          path.move_to(coordBuffer->buffer[j].GetX(),
                       coordBuffer->buffer[j].GetY());
        }
        else {
          path.line_to(coordBuffer->buffer[j].GetX(),
                       coordBuffer->buffer[j].GetY());
          length+=sqrt(pow(coordBuffer->buffer[j].GetX()-xo,2)+
                       pow(coordBuffer->buffer[j].GetY()-yo,2));
        }

        xo=coordBuffer->buffer[j].GetX();
        yo=coordBuffer->buffer[j].GetY();
      }
    }
    else {
      for (size_t j=0; j<=transEnd-transStart; j++) {
        size_t idx=transEnd-j;

        if (j==0) {
          path.move_to(coordBuffer->buffer[idx].GetX(),
                       coordBuffer->buffer[idx].GetY());
        }
        else {
          path.line_to(coordBuffer->buffer[idx].GetX(),
                       coordBuffer->buffer[idx].GetY());
          length+=sqrt(pow(coordBuffer->buffer[idx].GetX()-xo,2)+
                       pow(coordBuffer->buffer[idx].GetY()-yo,2));
        }

        xo=coordBuffer->buffer[idx].GetX();
        yo=coordBuffer->buffer[idx].GetY();
      }
    }

    double width;
    double height;

    GetTextDimension(wideText,width,height);

    if (width>length) {
      return;
    }

    /*
    typedef agg::conv_bspline<agg::path_storage> conv_bspline_type;

    conv_bspline_type bspline(path);
    bspline.interpolation_step(1.0 / path.total_vertices());*/

    agg::trans_single_path tcurve;
    tcurve.add_path(path); // bspline

    typedef agg::conv_segmentator<AggTextCurveConverter> conv_font_segm_type;
    typedef agg::conv_transform<conv_font_segm_type,
    agg::trans_single_path>                              conv_font_trans_type;

    conv_font_segm_type  fsegm(*convTextCurves);
    conv_font_trans_type ftrans(fsegm, tcurve);

    fsegm.approximation_scale(3.0);

    double x=(length-width)/2;
    double y=-height/2+fontEngine->ascender();

    for (size_t i=0; i<wideText.length(); i++) {
      const agg::glyph_cache* glyph = fontCacheManager->glyph(wideText[i]);

      if (glyph!=NULL) {
        fontCacheManager->add_kerning(&x, &y);
        fontCacheManager->init_embedded_adaptors(glyph,x,y);

        if (glyph->data_type==agg::glyph_data_outline) {
          rasterizer->reset();
          rasterizer->add_path(ftrans);
          renderer_aa->color(agg::rgba(r,g,b,a));
          agg::render_scanlines(*rasterizer,
                                *scanlineP8,
                                *renderer_aa);
        }

        // increment pen position
        x += glyph->advance_x;
        y += glyph->advance_y;
      }
    }
  }