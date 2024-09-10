//void MeshViewer::draw_density_colorbar(QPainter *painter) 
//{
//	const int barwidth = 20;
//	const int barheight = 200;
//	painter->save();
//    painter->translate(0.8*width(), 0.7*height());
//	painter->save();
//	int h1, s1, v1;
//    int h2, s2, v2;
//	int color[3];
//	color[0] = 250;
//	color[1] = 0;
//	color[2] = 250;
//	QColor d_light(color[0], color[1], color[2]);
//
//	color[0] = 0;
//	color[1] = 127;
//	color[2] = 0;
//    QColor d_dark(color[0], color[1], color[2]);
//    d_light.getHsv( &h1, &s1, &v1 );
//    d_dark.getHsv( &h2, &s2, &v2 );
//	QRect rect(0, -100, barwidth, barheight);
//    painter->setClipRect( rect );
//    painter->setClipping( true );
//
//    painter->fillRect( rect, d_dark );
//
//    const int sectionSize = 4;
//
//    int numIntervals;
//    numIntervals = rect.height() / sectionSize;
//
//    for ( int i = 0; i < numIntervals; i++ )
//    {
//        QRect colorsection;
//        colorsection.setRect( rect.x(), rect.y() + i * sectionSize,
//            rect.width(), sectionSize );
//
//        const double ratio = i / static_cast<double>( numIntervals );
//        QColor c;
//        c.setHsv( h1 + qRound( ratio * ( h2 - h1 ) ),
//            s1 + qRound( ratio * ( s2 - s1 ) ),
//            v1 + qRound( ratio * ( v2 - v1 ) ) );
//		/*int color[3];
//		c.getRgb(&color[0], &color[1], &color[2]);*/
//        painter->fillRect( colorsection, c );
//    }
//	painter->restore();
//}
//
void MeshViewer::draw_curvature_colorbar(QPainter *painter) 
{
	const int barwidth = 20;
	const int barheight = 200;
	painter->save();
    painter->translate(0.8*width(), 0.7*height());
	painter->save();
	int h1, s1, v1;
    int h2, s2, v2;
	int color[3];
	color[0] = 250;
	color[1] = 0;
	color[2] = 0;
	QColor d_light(color[0], color[1], color[2]);

	color[0] = 0;
	color[1] = 0;
	color[2] = 255;
    QColor d_dark(color[0], color[1], color[2]);
    d_light.getHsv( &h1, &s1, &v1 );
    d_dark.getHsv( &h2, &s2, &v2 );
	QRect rect(0, -100, barwidth, barheight);
    painter->setClipRect( rect );
    painter->setClipping( true );

    painter->fillRect( rect, d_dark );

    int sectionSize = 4;

    int numIntervals;
    numIntervals = rect.height() / sectionSize;

    for ( int i = 0; i < numIntervals; i++ )
    {
        QRect colorsection;
        colorsection.setRect( rect.x(), rect.y() + i * sectionSize,
            rect.width(), sectionSize );

        const double ratio = i / static_cast<double>( numIntervals );
        QColor c;
        c.setHsv( h1 + qRound( ratio * ( h2 - h1 ) ),
            s1 + qRound( ratio * ( s2 - s1 ) ),
            v1 + qRound( ratio * ( v2 - v1 ) ) );
		/*int color[3];
		c.getRgb(&color[0], &color[1], &color[2]);*/
        painter->fillRect( colorsection, c );
    }
	painter->restore();
	sectionSize = 8;
	painter->translate(barwidth, 0);
	QFont font("Times", 10);
	painter->setPen(Qt::black);
	painter->setFont(font);
	double max_curve=surfacedata->get_max_meancurvature();
	double min_curve=surfacedata->get_min_meancurvature();
	double cur_step = (max_curve-min_curve)/ sectionSize;
	for ( int i = 0; i <= sectionSize; i++ )
	{
		QString str = QString::number(i*cur_step+min_curve);
		painter->drawText(5, barheight/2-barheight/8*i, str);
	}
	painter->restore();
}