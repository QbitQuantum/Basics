void CHaoyuView::OnLButtonUp ( UINT nFlags, CPoint point ) {
    // TODO: Add your message handler code here and/or call default

    CView::OnLButtonUp ( nFlags, point );
    this->STA = point;
    CDC* pDC = GetDC();

    int i, j;
    int tx, ty, tsta, tfin, dx, dy;
    double k = 0, d, dd;
    if ( this->STA.x > this->FIN.x ) {
        CPoint tpoint;
        tpoint = this->STA;
        this->STA = this->FIN;
        this->FIN = tpoint;
    }
    if ( ( this->STA.x == this->FIN.x ) || ( this->STA.y == this->FIN.y ) ) {
        if ( this->STA.x == this->FIN.x ) {
            tsta = min ( this->STA.y, this->FIN.y );
            tfin = max ( this->STA.y, this->FIN.y );
            tx = this->STA.x;
            for ( j = tsta; j < tfin; j++ ) {
                pDC->SetPixelV ( tx, j, RGB ( 0, 0, 0 ) );
            }
        }

        if ( this->STA.y == this->FIN.y ) {
            tsta = this->STA.x;
            tfin = this->FIN.x;
            ty = this->STA.y;
            for ( i = tsta; i < tfin; i++ ) {
                pDC->SetPixelV ( i, ty, RGB ( 0, 0, 0 ) );
            }
        }
    } else {
        dx = this->FIN.x - this->STA.x;
        dy = this->FIN.y - this->STA.y;
        k = ( double ) dy / ( double ) dx;
		if (abs(dx)==abs(dy)){
			tsta = this->STA.x;
            tfin = this->FIN.x;
			ty=ty = this->STA.y;
			int delta;
			delta=(dy<0?-1:1);
			for (i=tsta;i<tfin;i++){
				pDC->SetPixelV ( i, ty, RGB ( 0, 0, 0 ) );
				ty+=delta;
			}
		}else{
			 if ( abs ( dx ) >= abs ( dy ) ) {
            tsta = this->STA.x;
            tfin = this->FIN.x;
            ty = this->STA.y;
			d=0;
            if ( dy > 0 ) {
                for ( i = tsta; i < tfin; i++ ) {
					pDC->SetPixelV(i,ty,RGB ( 255*d, 255*d, 255*d ));
					pDC->SetPixelV(i,ty+1,RGB ( 255*(1-d), 255*(1-d), 255*(1-d) ));
					d=d+k;
					if (d>=1){
						d=d-1;
						ty++;
					}
                }
            } else {
                for ( i = tsta; i < tfin; i++ ) {
					pDC->SetPixelV(i,ty,RGB ( 255*d, 255*d, 255*d ));
					pDC->SetPixelV(i,ty+1,RGB ( 255*(1-d), 255*(1-d), 255*(1-d) ));
					d=d+k;
					if (d<=-1){
						d=d+1;
						ty--;
					}
                }
            }
        } else {
			tsta = this->STA.y;
            tfin = this->FIN.y;
            tx = this->STA.x;
			d=0;
			if ( dy >= 0 ) {
                for ( i = tsta; i < tfin; i++ ) {
					pDC->SetPixelV(tx,i,RGB ( 255*d, 255*d, 255*d ));
					pDC->SetPixelV(tx+1,i,RGB ( 255*(1-d), 255*(1-d), 255*(1-d) ));
					d=d+(1/k);
                    if (d>1){
						d=d-1;
						tx++;
					}
                }
            } else {
                for ( i = tsta; i > tfin; i-- ) {
					pDC->SetPixelV(tx+1,i,RGB ( 255*d, 255*d, 255*d ));
					pDC->SetPixelV(tx,i,RGB ( 255*(1-d), 255*(1-d), 255*(1-d) ));
					d=d+(1/k);
                    if (d<=-1){
						d=d+1;
						tx++;
					}
                }
            }
        }
		}

    }
	//pDC->SetPixelV ( this->FIN.x, this->FIN.y, RGB ( 0, 0, 0 ) );
    ReleaseDC ( pDC );
}