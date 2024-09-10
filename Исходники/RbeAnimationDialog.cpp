void RbeAnimationDialog::drawMask()
{
  
  //draw the mask file
  QString path = QString::fromStdString(rbeEngine->getMaskPath());                        
  QPixmap pixmap(path);
  
  QImage image = pixmap.toImage();
  QRgb pixColor;
  
  //tranform color
  for (int i = 0; i < pixmap.width(); ++i)
  {
    for (int j = 0; j < pixmap.height(); ++j)
    {
      pixColor = image.pixel(i, j);                    
      bool value = false;
      
      for(unsigned k = 0 ; k < rbeEngine->getContexts().size(); k++)
      {
        if(rbeEngine->getContexts()[k]->getType() == Rbe::Context::AREA)
        {
          Rbe::ContextArea *area = static_cast<Rbe::ContextArea *>(rbeEngine->getContexts()[k]);
          if(QColor::fromRgb(pixColor) == area->getColor())   
          {
            value = true;
          }
        }        
      }
      
      if(value == false)
      {
        image.setPixel(i, j, qRgb(255,255,155));
      }          
    }
  }
  pixmap = pixmap.fromImage(image);
  gScene->addPixmap(pixmap);
  gScene->setBackgroundBrush(QBrush(pixmap));
  
}