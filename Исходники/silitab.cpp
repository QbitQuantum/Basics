QPainterPath Previewer::magnifierPath( const QSize & top , const QRect & rct , int padding ) const
{
    QPainterPath path;
        path.setFillRule( Qt::WindingFill );
        /*! ======= Draw Top of the Magnifier ======= */
        path.moveTo( (rct.width()-top.width())/2 , padding+top.height() );
        path.lineTo( rct.width()/2 , padding );
        path.lineTo( (rct.width()+top.width())/2 , padding+top.height() );
        /*! ========================================= */
        /*! ===== Draw Bottom of the Magnifier ====== */
        path.lineTo( rct.width()-padding-ROUNDED_PIXEL , padding+top.height() );
        path.quadTo( rct.width()-padding , padding+top.height() , rct.width()-padding , padding+top.height()+ROUNDED_PIXEL );
        path.lineTo( rct.width()-padding , rct.height()-padding-ROUNDED_PIXEL );
        path.quadTo( rct.width()-padding , rct.height()-padding , rct.width()-padding-ROUNDED_PIXEL , rct.height()-padding );
        path.lineTo( padding+ROUNDED_PIXEL , rct.height()-padding );
        path.quadTo( padding , rct.height()-padding , padding , rct.height()-padding-ROUNDED_PIXEL );
        path.lineTo( padding , padding+top.height()+ROUNDED_PIXEL );
        path.quadTo( padding , padding+top.height() , padding+ROUNDED_PIXEL , padding+top.height() );
        path.lineTo( (rct.width()-top.width())/2 , padding+top.height() );
        /*! ========================================= */

    return path;
}