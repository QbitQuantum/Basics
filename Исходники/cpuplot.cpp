        virtual void draw( QPainter *painter,
                const QwtScaleMap &, const QwtScaleMap &yMap,
                const QRectF &canvasRect ) const {
            QColor c( Qt::white );
            QRectF r = canvasRect;

            for ( int i = 100; i > 0; i -= 10 ) {
                r.setBottom( yMap.transform( i - 10 ) );
                r.setTop( yMap.transform( i ) );
                painter->fillRect( r, c );

                c = c.dark( 110 );
            }
        }