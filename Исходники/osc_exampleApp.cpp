void drawBuffer(const std::deque<int8_t>& buffer, const Rectf &bounds, bool drawFrame, const ci::ColorA &color, float scaleFactor )
{
  gl::ScopedGlslProg glslScope( getStockShader( gl::ShaderDef().color() ) );
  
  gl::color( color );
  
  const float waveHeight = bounds.getHeight();
  const float xScale = bounds.getWidth() / (float)buffer.size();
  
  float yOffset = bounds.y1;
  PolyLine2f waveform;
  float x = bounds.x1;
  for( size_t i = 0; i < buffer.size(); i++ ) {
    x += xScale;
    float y = ( 1.0f - ( buffer[i] * scaleFactor + 0.5f) ) * waveHeight + yOffset;
    waveform.push_back( vec2( x, y ) );
  }
  
  if( ! waveform.getPoints().empty() )
    gl::draw( waveform );
  
  if( drawFrame ) {
    gl::color( color.r, color.g, color.b, color.a * 0.6f );
    gl::drawStrokedRect( bounds );
  }
}