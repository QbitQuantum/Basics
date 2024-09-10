//----------------------------------------------------
bool CPhoto::IsPosOnView( const QPoint& pos)
{
    QRect  cViewRect ;
    QRect  cPosRect ;

    cPosRect.setBottomLeft( pos) ;
    cPosRect.setTopRight( pos) ;
    cViewRect = ui->ImgView->rect() ;

    return cViewRect.intersects( cPosRect) ;
}