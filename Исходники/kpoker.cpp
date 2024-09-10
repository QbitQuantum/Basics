void kpok::paintEvent( QPaintEvent *)
{
   /* This was shamelessy stolen from the "hello world" example coming with Qt
      Thanks to the Qt-Guys for doing such a cool example 8-)
   */
   
   
   QString t;

   if (!waveActive) {
      return;
   }

   t = wonLabel->text();

   static int sin_tbl[16] = {
      0, 38, 71, 92, 100, 92, 71, 38,  0, -38, -71, -92, -100, -92, -71, -38};

   if ( t.isEmpty() )
      return;


   QFont wonFont("Helvetica", 18, QFont::Bold);
   
   QFontMetrics fm = QFontMetrics(wonFont);

   int w = fm.width(t) + 20;
   int h = fm.height() * 2;
   
   int pmx = this->width() / 2 - w / 2;
   int pmy = wonLabelVDist - h / 4;

   QPixmap pm( w, h );
   pm.fill( this, pmx, pmy );

   if (fCount == -1) { /* clear area */
      bitBlt( this, pmx, pmy, &pm );
      return;
   }

   QPainter p;
   int x = 10;
   int y = h/2 + fm.descent();
   int i = 0;
   p.begin( &pm );
   p.setFont( wonFont );
   p.setPen( QColor(0,0,0) );
   
   while ( t[i] ) {
      int i16 = (fCount+i) & 15;
      
      p.drawText( x, y-sin_tbl[i16]*h/800, &t[i], 1 );
      x += fm.width( t[i] );
      i++;
   }
   p.end();

// 4: Copy the pixmap to the Hello widget
   bitBlt( this, pmx, pmy, &pm );

}