 // /////////////////////////////////////////////////////////////////
 //
 // /////////////////////////////////////////////////////////////////
 void SliderControl::VSetColor(const Vector4 &colorRef)
 {
     ControlWidget::VSetColor(colorRef);
     Vector4 oldButtonColor = m_sliderButPtr->VGetColor();
     oldButtonColor.SetW(colorRef.GetW());
     m_sliderButPtr->VSetColor(oldButtonColor);
     m_lineColor.SetW(colorRef.GetW());
 }