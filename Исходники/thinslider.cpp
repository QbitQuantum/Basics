void ThinSlider::drawSlider(QPainter *p, const QRect &r)
{
    p->setRenderHint(QPainter::Antialiasing);

    const QPalette& pal = palette();
    QBrush brBack(pal.window());
    QBrush brMid(pal.mid());
    QBrush brDark(pal.dark());

    QRect cr;
    
    int ipos,dist1;
    double rpos;

    int xrad = 4;
    int yrad = 4;

    // for the empty side
    QColor e_mask_edge = pal.mid().color();
    QColor e_mask_center = pal.midlight().color();
    int e_alpha = 215;
    e_mask_edge.setAlpha(e_alpha);
    e_mask_center.setAlpha(e_alpha);
    
    QLinearGradient e_mask;
    e_mask.setColorAt(0, e_mask_edge);
    e_mask.setColorAt(0.5, e_mask_center);
    e_mask.setColorAt(1, e_mask_edge);
    
    // for the full side
    rpos = (value()  - minValue()) / (maxValue() - minValue());
    
    int f_brightness = 155 * rpos + 100;
    int f_alpha;
    int f_edge;
    if (pal.currentColorGroup() == QPalette::Disabled)
        {
        f_alpha = 185;
        f_edge = 100;
        }
    else
        {
        f_alpha = 127;
        f_edge = 0;
        }
	   
    QColor f_mask_center = QColor(f_brightness, f_brightness, f_brightness, f_alpha);
    QColor f_mask_edge = QColor(f_edge, f_edge, f_edge, f_alpha);
    QLinearGradient f_mask;
	   
    f_mask.setColorAt(0, f_mask_edge);
    f_mask.setColorAt(0.5, f_mask_center);
    f_mask.setColorAt(1, f_mask_edge);
    
    // for the thumb
    QLinearGradient thumbGrad;
    QColor thumb_edge = pal.dark().color();
    QColor thumb_center = pal.midlight().color();
    
    thumbGrad.setColorAt(0, thumb_edge);
    thumbGrad.setColorAt(0.5, thumb_center);
    thumbGrad.setColorAt(1, thumb_edge);
    
    
    if (d_orient == Qt::Horizontal)
        {

        cr.setRect(r.x(),
                   r.y() + d_mMargin,
                   r.width(),
                   r.height() - 2*d_mMargin);


        //
        // Draw background
        //
        QPainterPath bg_rect = MusECore::roundedPath(cr, 
                                           xrad, yrad, 
                                           (MusECore::Corner) (MusECore::UpperLeft | MusECore::UpperRight | MusECore::LowerLeft | MusECore::LowerRight) );
	   
        p->fillPath(bg_rect, d_fillColor);
	   
        dist1 = int(double(cr.width() - d_thumbLength) * rpos);
        ipos =  cr.x() + dist1;
        markerPos = ipos + d_thumbHalf;
	   

        //
        // Draw empty right side
        // 
	   
        e_mask.setStart(QPointF(0, cr.y()));
        e_mask.setFinalStop(QPointF(0, cr.y() + cr.height()));

        QPainterPath e_rect = MusECore::roundedPath(ipos + d_thumbLength, cr.y(), 
                                          cr.width() - d_thumbLength - dist1, cr.height(), 
                                          xrad, yrad, (MusECore::Corner) (MusECore::UpperRight | MusECore::LowerRight) );
   
        p->fillPath(e_rect, QBrush(e_mask));
   
   
        //
        // Draw full left side
        //
           
        f_mask.setStart(QPointF(0, cr.y()));
        f_mask.setFinalStop(QPointF(0, cr.y() + cr.height()));
          
        QPainterPath f_rect = MusECore::roundedPath(cr.x(), cr.y(), 
                                          ipos + 1, cr.height(),
                                          xrad, yrad, 
                                          (MusECore::Corner) (MusECore::LowerLeft | MusECore::UpperLeft) );

        p->fillPath(f_rect, QBrush(f_mask));
          
           
        //
        //  Draw thumb
        //
	   
        QPainterPath thumb_rect = MusECore::roundedPath(ipos, r.y(), 
                                              d_thumbLength, r.height(), 
                                              2, 2, 
                                              (MusECore::Corner) (MusECore::UpperLeft | MusECore::UpperRight | MusECore::LowerLeft | MusECore::LowerRight) );
   
        thumbGrad.setStart(QPointF(0, cr.y()));
        thumbGrad.setFinalStop(QPointF(0, cr.y() + cr.height()));
           
           
        p->fillPath(thumb_rect, QBrush(thumbGrad));
           
        // center line
        p->fillRect(ipos + d_thumbHalf, cr.y(), 1, cr.height(), pal.dark().color());
           

        }
    else // (d_orient == Qt::Vertical)
        {
	      
        cr.setRect(r.x() + d_mMargin,
                   r.y(),
                   r.width() - 2*d_mMargin,
                   r.height());
	    

        //
        // Draw background
        //
        QPainterPath bg_rect = MusECore::roundedPath(cr,
                                           xrad, yrad, 
                                           (MusECore::Corner) (MusECore::UpperLeft | MusECore::UpperRight | MusECore::LowerLeft | MusECore::LowerRight) );
	    
        p->fillPath(bg_rect, d_fillColor);

        dist1 = int(double(cr.height() - d_thumbLength) * (1.0 - rpos));
        ipos = cr.y() + dist1;
        markerPos = ipos + d_thumbHalf;

  
        //
        // Draw empty upper filling
        // 

        e_mask.setStart(QPointF(cr.x(), 0));
        e_mask.setFinalStop(QPointF(cr.x() + cr.width(), 0));
	    
        QPainterPath e_rect = MusECore::roundedPath(cr.x(), cr.y(), 
                                          cr.width(), ipos + 1,
                                          xrad, yrad, 
                                          (MusECore::Corner) (MusECore::UpperLeft | MusECore::UpperRight) );
	    
        p->fillPath(e_rect, QBrush(e_mask));
            
            
        //
        // Draw lower filling mask
        //

        f_mask.setStart(QPointF(cr.x(), 0));
        f_mask.setFinalStop(QPointF(cr.x() + cr.width(), 0));
            
        QPainterPath f_rect = MusECore::roundedPath(cr.x(), ipos + d_thumbLength, 
                                          cr.width(), cr.height() - d_thumbLength - dist1,
                                          xrad, yrad, (MusECore::Corner) (MusECore::LowerLeft | MusECore::LowerRight) );
	    
        p->fillPath(f_rect, QBrush(f_mask));
            
            
        //
        //  Draw thumb
        //
            
        QPainterPath thumb_rect = MusECore::roundedPath(r.x(), ipos, 
                                              r.width(), d_thumbLength,
                                              2, 2, 
                                              (MusECore::Corner) (MusECore::UpperLeft | MusECore::UpperRight | MusECore::LowerLeft | MusECore::LowerRight) );
	    
        thumbGrad.setStart(QPointF(cr.x(), 0));
        thumbGrad.setFinalStop(QPointF(cr.x() + cr.width(), 0));
            
            
        p->fillPath(thumb_rect, QBrush(thumbGrad));
            
        // center line
        p->fillRect(cr.x(), ipos + d_thumbHalf, cr.width(), 1, pal.dark().color());
            
        }

}