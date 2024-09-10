void MontageView::drawPoints(const QPointArray& pa, QValueList<int>& corners, int correct)
{
  if(ccv::debug) std::cerr << "MontageView::drawPoints - pa = " << pa.count() << " corners = " << corners.count() << "\n";

  QIconViewItem* item = firstItem();
  if( !item )
    return;

  m_dirty = true;

  QImage img = item->pixmap()->convertToImage();
  
  int item_nr = 0;

  bool failed = corners[item_nr] != correct;

  for( uint i=0; i<pa.count()+1; ++i ){

    if( corners[item_nr] == 0 ) {

      QPixmap pm(img);
      item->setPixmap( pm );
      item = item->nextItem();
      if( !item )
	return;

      img = item->pixmap()->convertToImage();

      item_nr++;
      failed = corners[item_nr] != correct;
    }    

    if(ccv::debug) std::cerr << " Point: " << i << " Image: " << item_nr 
			     << " (" << pa[i].x() << "," << pa[i].y() << ")" 
			     << " Corners: " << corners[item_nr] << "\n"; 

    if( !failed ) {
      img.setPixel( pa[i].x()  , pa[i].y()-1, qRgb(255,255,0) );
      img.setPixel( pa[i].x()-1, pa[i].y()  , qRgb(255,255,0) );
      img.setPixel( pa[i].x()  , pa[i].y()  , qRgb(255,0,0)   );
      img.setPixel( pa[i].x()+1, pa[i].y()  , qRgb(255,255,0) );
      img.setPixel( pa[i].x()  , pa[i].y()+1, qRgb(255,255,0) );
    }
    else {
      img.setPixel( pa[i].x()  , pa[i].y()-1, qRgb(255,0,0)   );
      img.setPixel( pa[i].x()-1, pa[i].y()  , qRgb(255,0,0)   );
      img.setPixel( pa[i].x()  , pa[i].y()  , qRgb(255,255,0) );
      img.setPixel( pa[i].x()+1, pa[i].y()  , qRgb(255,0,0)   );
      img.setPixel( pa[i].x()  , pa[i].y()+1, qRgb(255,0,0)   );
    }
    corners[item_nr]--;
  }
}