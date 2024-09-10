// --------------------------------------------------------------------------------
void QmvFormTool::displayDetails()
{
    
    slotSetBannerText( QString("%1").arg( fh->form_desc ) );

        // determine page data
    

        // prepare the details in the list.
    formDetail fd;
    QRect rect;
    QPixmap pm;
    QPainter pt;
    int x,y,w,h;
    QPoint pos;
    QSize size;
    QColor fill;
    
    for ( int row = 0; row < reln_fmdt->count(); row++ )
    {
        if (!fd.load( row, reln_fmdt) )
            continue;
        
        if ( fd.fmdt_field_type < formDetail::Label || fd.fmdt_field_type > formDetail::Special )
            continue;
        
            // the raw position from fmdt
        pos = QPoint( fd.fmdt_x_coord, fd.fmdt_y_coord );
        size = QSize( fd.fmdt_width, fd.fmdt_height );
        fill = QColor( Qt::gray );
        
            // special actions
        switch (fd.fmdt_field_type)
        {
            case formDetail::Label:
                break;
            case formDetail::Field:
                break;
            case formDetail::Line:
                fill = QColor( Qt::red );
                size.setHeight(2);
                break;
            case formDetail::Calc:
                break;
            case formDetail::Special:
                break;
            default:
                continue;
                break;
        }
        
        
            // adjust for section and margins
        switch (fd.fmdt_section)
        {
            case formDetail::ReportHeader:
            case formDetail::PageHeader:
                pos += QPoint( fh->form_mg_left, fh->form_mg_top );
                break;
            case formDetail::Detail:
                pos += QPoint( fh->form_mg_left, (fh->form_mg_top + fh->form_ph_height));
                break;
            case formDetail::PageFooter:
            case formDetail::ReportFooter:
                    // measure from bottom
                pos += QPoint( fh->form_mg_left, (pagesize.height() - fh->form_mg_bottom - fh->form_pf_height) );
                break;
        }

        if ( pos.x() < 0 || pos.y() < 0 || size.width() < 1 || size.height() < 1 )
            continue;
        
            // build a QRect for this detail
        rect.setSize( size );
            // reset origin, ready for drawing
        rect.moveTopLeft( QPoint(0,0) );
        
            // build a detail label using a pixmap
        pm.resize( rect.size() );
        pm.fill(getTransparentColor());
        pt.begin(&pm);

            // fill the background and draw the label
        pt.setPen( QPen( Qt::black, 2, SolidLine ) );
        pt.fillRect( rect, QBrush( fill, QBrush::SolidPattern ) );
        pt.setFont( QFont( fd.fmdt_ft_family, fd.fmdt_ft_size) );
        pt.drawText( rect, WordBreak|AlignCenter, fd.fmdt_text );

            // draw a border around the object
        pt.setBrush( Qt::NoBrush );
        pt.setPen(QPen( Qt::black, 2, SolidLine ) );
        pt.drawRect( rect );
        pt.end();

            // put the prepared pixmap on a canvas object
        QmvCanvasGrid * disp_obj = new QmvCanvasGrid( getCanvas(), rect.size(), getTransparentColor() );
            // use the canvas object as a key in list of displayed details
        canvas_details.insert( disp_obj, new int(row) );
        
            //disp_obj->setOpaqueFactor( 30 );
        disp_obj->drawPixmap( QPoint(0,0), pm, pm.rect() );

            // Move the object into place
        disp_obj->move( pos.x(), pos.y() );
        
        disp_obj->show();
            //pm.save( QString("tmp/%1.xpm").arg(row),"XPM" );
    }
    canvasView()->update();
}