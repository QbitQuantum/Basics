wxImage ScaleImage(wxImage image, double source_scale_factor, double content_scale_factor,
                   wxSize output_size, wxRect usable_rect, LSIFlags flags,
                   const wxColour& fill_color)
{
  if (!image.IsOk())
  {
    wxFAIL_MSG("WxUtils::ScaleImage expects a valid image.");
    return image;
  }

  if (content_scale_factor != 1.0)
  {
    output_size *= content_scale_factor;
    usable_rect.SetPosition(usable_rect.GetPosition() * content_scale_factor);
    usable_rect.SetSize(usable_rect.GetSize() * content_scale_factor);
  }

  // Fix the output size if it's unset.
  wxSize img_size = image.GetSize();
  if (output_size.GetWidth() < 1)
    output_size.SetWidth(
        static_cast<int>(img_size.GetWidth() * (content_scale_factor / source_scale_factor)));
  if (output_size.GetHeight() < 1)
    output_size.SetHeight(
        static_cast<int>(img_size.GetHeight() * (content_scale_factor / source_scale_factor)));

  // Fix the usable rect. If it's empty then the whole canvas is usable.
  if (usable_rect.IsEmpty())
  {
    // Constructs a temp wxRect 0,0->output_size then move assigns it.
    usable_rect = output_size;
  }
  else if (!usable_rect.Intersects(output_size))
  {
    wxFAIL_MSG("Usable Zone Rectangle is not inside the canvas. Check the output size is correct.");
    image.Create(1, 1, false);
    image.SetRGB(0, 0, fill_color.Red(), fill_color.Green(), fill_color.Blue());
    if (fill_color.Alpha() == wxALPHA_TRANSPARENT)
      image.SetMaskColour(fill_color.Red(), fill_color.Green(), fill_color.Blue());
    usable_rect = output_size;
  }

  // Step 1: Scale the image
  if ((flags & LSI_SCALE) != LSI_SCALE_NONE)
  {
    if (flags & LSI_SCALE_NO_ASPECT)
    {
      // Stretch scale without preserving the aspect ratio.
      bool scale_width = (img_size.GetWidth() > usable_rect.GetWidth() && flags & LSI_SCALE_DOWN) ||
                         (img_size.GetWidth() < usable_rect.GetWidth() && flags & LSI_SCALE_UP);
      bool scale_height =
          (img_size.GetHeight() > usable_rect.GetHeight() && flags & LSI_SCALE_DOWN) ||
          (img_size.GetHeight() < usable_rect.GetHeight() && flags & LSI_SCALE_UP);
      if (scale_width || scale_height)
      {
        // NOTE: Using BICUBIC instead of HIGH because it's the same internally
        //   except that downscaling uses a box filter with awful obvious aliasing
        //   for non-integral scale factors.
        image.Rescale(scale_width ? usable_rect.GetWidth() : img_size.GetWidth(),
                      scale_height ? usable_rect.GetHeight() : img_size.GetHeight(),
                      wxIMAGE_QUALITY_BICUBIC);
      }
    }
    else
    {
      // Scale while preserving the aspect ratio.
      double scale = std::min(static_cast<double>(usable_rect.GetWidth()) / img_size.GetWidth(),
                              static_cast<double>(usable_rect.GetHeight()) / img_size.GetHeight());
      int target_width = static_cast<int>(img_size.GetWidth() * scale);
      int target_height = static_cast<int>(img_size.GetHeight() * scale);
      // Bilinear produces sharper images when upscaling, bicubic tends to smear/blur sharp edges.
      if (scale > 1.0 && flags & LSI_SCALE_UP)
        image.Rescale(target_width, target_height, wxIMAGE_QUALITY_BILINEAR);
      else if (scale < 1.0 && flags & LSI_SCALE_DOWN)
        image.Rescale(target_width, target_height, wxIMAGE_QUALITY_BICUBIC);
    }
    img_size = image.GetSize();
  }

  // Step 2: Resize the canvas to match the output size.
  // NOTE: If NOT using LSI_SCALE_DOWN then this will implicitly crop the image
  if (img_size != output_size || usable_rect.GetPosition() != wxPoint())
  {
    wxPoint base = usable_rect.GetPosition();
    if (flags & LSI_ALIGN_HCENTER)
      base.x += (usable_rect.GetWidth() - img_size.GetWidth()) / 2;
    else if (flags & LSI_ALIGN_RIGHT)
      base.x += usable_rect.GetWidth() - img_size.GetWidth();
    if (flags & LSI_ALIGN_VCENTER)
      base.y += (usable_rect.GetHeight() - img_size.GetHeight()) / 2;
    else if (flags & LSI_ALIGN_BOTTOM)
      base.y += usable_rect.GetHeight() - img_size.GetHeight();

    int r = -1, g = -1, b = -1;
    if (fill_color.Alpha() != wxALPHA_TRANSPARENT)
    {
      r = fill_color.Red();
      g = fill_color.Green();
      b = fill_color.Blue();
    }
    image.Resize(output_size, base, r, g, b);
  }

  return image;
}