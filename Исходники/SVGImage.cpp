//----------------------------------------------------------------------------//
SVGImage::SVGImage(const String& name, SVGData& svg_data) :
    Image(name,
          glm::vec2(0.0f, 0.0f),
          Rectf(glm::vec2(0.0f, 0.0f),
                glm::vec2(svg_data.getWidth(), svg_data.getHeight())),
          ASM_Disabled,
          Sizef(640, 480)),
    d_svgData(&svg_data),
    d_useGeometryAntialiasing(true)
{
}