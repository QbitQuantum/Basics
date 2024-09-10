static void create_pixmaps()
{
    if(pixmaps_created)
        return;
    pixmaps_created = true;

    titleHeight = QFontMetrics(options()->font(true)).height();
    if (titleHeight < handleSize) titleHeight = handleSize;
    titleHeight &= ~1; // Make title height even
    if (titleHeight < 14) titleHeight = 14;

    btnWidth1 = titleHeight + 3;
    btnWidth2 = 3*titleHeight/2 + 6;

    // titlebar
    QPainter p;
    QPainter maskPainter;
    int i, x, y;
    titlePix = new QPixmap(33, 12);
    titlePix->fill( Qt::transparent );
    QBitmap mask(33, 12);
    mask.fill(Qt::color0);

    p.begin(titlePix);
    maskPainter.begin(&mask);
    maskPainter.setPen(Qt::color1);
    for(i=0, y=2; i < 3; ++i, y+=4){
        for(x=1; x <= 33; x+=3){
            p.setPen(options()->color(KDecoration::ColorTitleBar, true).light(150));
            p.drawPoint(x, y);
            maskPainter.drawPoint(x, y);
            p.setPen(options()->color(KDecoration::ColorTitleBar, true).dark(150));
            p.drawPoint(x+1, y+1);
            maskPainter.drawPoint(x+1, y+1);
        }
    }
    p.end();
    maskPainter.end();
    titlePix->setMask(mask);

    if(QPixmap::defaultDepth() > 8){
        aUpperGradient = new QPixmap(32, titleHeight+2);
        iUpperGradient = new QPixmap(32, titleHeight+2);
        QColor bgColor = options()->color(KDecoration::ColorTitleBar, true);
	gradientFill(aUpperGradient, bgColor.light(120), bgColor.dark(120));
        bgColor = options()->color(KDecoration::ColorTitleBar, false);
	gradientFill(iUpperGradient, bgColor.light(120), bgColor.dark(120));
    }
    // buttons (active/inactive, sunken/unsunken, 2 sizes each)
    QPalette g = options()->palette(KDecoration::ColorButtonBg, true);
    g.setCurrentColorGroup( QPalette::Active );
    QColor c = g.color( QPalette::Background );
    btnPix1 = new QPixmap(btnWidth1, titleHeight);
    btnDownPix1 = new QPixmap(btnWidth1, titleHeight);
    btnPix2 = new QPixmap(btnWidth2, titleHeight);
    btnDownPix2 = new QPixmap(btnWidth2, titleHeight);
    iBtnPix1 = new QPixmap(btnWidth1, titleHeight);
    iBtnDownPix1 = new QPixmap(btnWidth1, titleHeight);
    iBtnPix2 = new QPixmap(btnWidth2, titleHeight);
    iBtnDownPix2 = new QPixmap(btnWidth2, titleHeight);
    if(QPixmap::defaultDepth() > 8){
        gradientFill(btnPix1, c.light(120), c.dark(130), true);
        gradientFill(btnPix2, c.light(120), c.dark(130), true);
        gradientFill(btnDownPix1, c.light(120), c.dark(130), true);
        gradientFill(btnDownPix2, c.light(120), c.dark(130), true);
        g = options()->palette(KDecoration::ColorButtonBg, false);
        g.setCurrentColorGroup( QPalette::Active );
        c = g.color(QPalette::Background);
        gradientFill(iBtnPix1, c.light(120), c.dark(130), true);
        gradientFill(iBtnPix2, c.light(120), c.dark(130), true);
        gradientFill(iBtnDownPix1, c.light(120), c.dark(130), true);
        gradientFill(iBtnDownPix2, c.light(120), c.dark(130), true);
    }
    else{
        btnPix1->fill(c.rgb());
        btnDownPix1->fill(c.rgb());
        btnPix2->fill(c.rgb());
        btnDownPix2->fill(c.rgb());
        g = options()->palette(KDecoration::ColorButtonBg, false);
        g.setCurrentColorGroup( QPalette::Active );
        c = g.background().color();
        iBtnPix1->fill(c.rgb());
        iBtnDownPix1->fill(c.rgb());
        iBtnPix2->fill(c.rgb());
        iBtnDownPix2->fill(c.rgb());
    }
    g = options()->palette(KDecoration::ColorButtonBg, true);
    g.setCurrentColorGroup( QPalette::Active );
    c = g.background().color();
    drawButtonFrame(btnPix1, g, false);
    drawButtonFrame(btnDownPix1, g, true);
    drawButtonFrame(btnPix2, g, false);
    drawButtonFrame(btnDownPix2, g, true);
    g = options()->palette(KDecoration::ColorButtonBg, false);
    g.setCurrentColorGroup( QPalette::Active );
    c = g.background().color();
    drawButtonFrame(iBtnPix1, g, false);
    drawButtonFrame(iBtnDownPix1, g, true);
    drawButtonFrame(iBtnPix2, g, false);
    drawButtonFrame(iBtnDownPix2, g, true);

    if(qGray(options()->color(KDecoration::ColorButtonBg, true).rgb()) > 128)
        btnForeground = Qt::black;
    else
        btnForeground = Qt::white;
}