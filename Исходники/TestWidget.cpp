void
TestWidget::DrawStuff
(
    JPainter& p
)
{
    JIndex i;

    JXColormap* colormap = GetColormap();

    p.SetPenColor(colormap->GetGreenColor());
    JRect ellipseRect(100,50,150,300);
    p.Ellipse(ellipseRect);

    p.SetPenColor(colormap->GetBlackColor());

    if (itsFillFlag)
    {
        p.SetFilling(kJTrue);
    }

    JRect ap = GetAperture();
    p.Line(ap.topLeft(), ap.bottomRight());
    p.Line(ap.topRight(), ap.bottomLeft());

    p.SetLineWidth(2);
    p.SetFontName(JXGetTimesFontName());
    p.SetFontSize(18);

    p.Image(*itsHomeImage, itsHomeImage->GetBounds(), itsHomeRect);

    its2Rect = JRect(150, 5, 200, 30);
    p.SetPenColor(colormap->GetRedColor());
    p.Rect(its2Rect);
    p.SetFontStyle(colormap->GetRedColor());
    p.String(its2Rect.topLeft(), "2",
             its2Rect.width(),  JPainter::kHAlignCenter,
             its2Rect.height(), JPainter::kVAlignCenter);

    its3Rect = JRect(10, 150, 40, 200);
    p.SetPenColor(colormap->GetBlueColor());
    p.Rect(its3Rect);
    p.SetFontStyle(colormap->GetBlueColor());
    p.String(its3Rect.topLeft(), "3",
             its3Rect.width(),  JPainter::kHAlignCenter,
             its3Rect.height(), JPainter::kVAlignCenter);

    p.SetLineWidth(1);
    p.SetFont(JGetDefaultFontName(), kJXDefaultFontSize, colormap->GetBlackColor());

    p.ShiftOrigin(10,10);

    p.Point(0,0);
    for (i=1; i<=itsRandPointCount; i++)
    {
        p.Point(itsRNG.UniformLong(0,200), itsRNG.UniformLong(0,200));
    }

    p.SetPenColor(colormap->GetRedColor());
    p.Line(10,0, 0,10);
    p.SetPenColor(colormap->GetGreenColor());
    p.LineTo(10,20);
    p.SetPenColor(colormap->GetBlueColor());
    p.LineTo(0,30);

    p.ShiftOrigin(2,0);

    JPoint textPt(40,30);
    p.String(  0.0, textPt, "Hello");
    p.String( 90.0, textPt, "Hello");
    p.String(180.0, textPt, "Hello");
    p.String(270.0, textPt, "Hello");

    p.Rect(310, 70, 80, 80);
    p.String(  0.0, 310, 70, "Hello", 80, JPainter::kHAlignCenter,
               80, JPainter::kVAlignCenter);
    p.String( 90.0, 310,150, "Hello", 80, JPainter::kHAlignCenter,
              80, JPainter::kVAlignCenter);
    p.String(180.0, 390,150, "Hello", 80, JPainter::kHAlignCenter,
             80, JPainter::kVAlignCenter);
    p.String(270.0, 390, 70, "Hello", 80, JPainter::kHAlignCenter,
             80, JPainter::kVAlignCenter);

    p.Rect(200, 10, 100, 50);
    p.String(200, 10, "Hello", 100, JPainter::kHAlignLeft);
    p.String(200, 10+p.GetLineHeight(), "Hello", 100, JPainter::kHAlignCenter);
    p.String(200, 10+2*p.GetLineHeight(), "Hello", 100, JPainter::kHAlignRight);

    p.SetPenColor(colormap->GetYellowColor());
    JRect r(0,11,80,91);
    p.Rect(r);
    r.Shrink(1,1);
    p.SetPenColor(colormap->GetBlueColor());
    p.Ellipse(r);
    r.Shrink(1,1);
    p.SetPenColor(colormap->GetRedColor());
    p.Arc(r, 270.0-45.0, -270.0);

    JPolygon poly;
    poly.AppendElement(JPoint(0,85));
    poly.AppendElement(JPoint(10,85));
    poly.AppendElement(JPoint(5,95));
    p.Polygon(poly);

    p.Line(0,100, 2,98);
    p.LineTo(4,100);
    p.LineTo(2,102);
    p.LineTo(0,100);

    poly.SetElement(1, JPoint(0,5));
    poly.SetElement(2, JPoint(2,0));
    poly.SetElement(3, JPoint(4,5));
    p.Polygon(2,105, poly);

    // test filling rule

    p.SetPenColor(colormap->GetRedColor());
    p.SetFilling(kJTrue);

    JPolygon fillRulePoly;
    fillRulePoly.AppendElement(JPoint(175,45));
    fillRulePoly.AppendElement(JPoint(165,65));
    fillRulePoly.AppendElement(JPoint(190,50));
    fillRulePoly.AppendElement(JPoint(160,50));
    fillRulePoly.AppendElement(JPoint(185,65));
    p.Polygon(fillRulePoly);

    p.SetFilling(kJFalse);

    // dashed lines

    p.DrawDashedLines(kJTrue);

    p.SetPenColor(colormap->GetBlackColor());

    JArray<JSize> dashList;			// pixel rulers
    dashList.AppendElement(1);
    dashList.AppendElement(1);
    p.SetDashList(dashList);
    p.Line(100,110, 200,110);
    p.Line(100,114, 200,114);
    p.Line(100,118, 200,118);

    dashList.SetElement(1, 2);		// simple pattern
    dashList.SetElement(2, 3);
    p.SetDashList(dashList);
    p.Line(100,112, 200,112);

    p.SetFontStyle(JFontStyle(kJFalse, kJFalse, 1, kJFalse));
    p.String(130,155, "underline without dashes");

    p.SetDashList(dashList, 3);		// test offset
    p.Line(100,116, 200,116);

    dashList.SetElement(1, 1);		// example with odd # of values from X manuals
    dashList.SetElement(2, 2);
    dashList.AppendElement(3);
    p.SetDashList(dashList);
    p.Line(100,120, 200,120);

    dashList.SetElement(1, 5);		// dash-dot pattern
    dashList.SetElement(2, 2);
    dashList.SetElement(3, 1);
    dashList.AppendElement(2);
    p.SetDashList(dashList);
    p.Line(100,122, 200,122);

    p.Ellipse(210,110, 20,20);
    p.DrawDashedLines(kJFalse);
    p.Ellipse(213,113, 14,14);
    p.Rect(207,107, 26,26);
    p.SetPenColor(colormap->GetYellowColor());
    p.DrawDashedLines(kJTrue);
    p.Ellipse(213,113, 14,14);

    // animated colors

    p.SetFilling(kJTrue);

    JCoordinate x = 25;
    const JSize animColorCount = itsAnimColorList->GetElementCount();
    for (i=1; i<=animColorCount; i++)
    {
        p.SetPenColor(itsAnimColorList->GetElement(i));
        p.Rect(x, 150, 10, 10);
        x += 10;
    }

    // icons

    p.Image(*itsXPMImage, itsXPMImage->GetBounds(), 33,110);
    p.Image(*itsPartialXPMImage, itsXPMImage->GetBounds(), 50,121);

    // *NEVER* do this in your code!  I do it here ONLY to test JXColormap.
    // (Besides, look at how messy it is!)

    unsigned long xPixel;
    if (colormap->CalcPreallocatedXPixel(62720, 56832, 45824, &xPixel))
    {
        JXDisplay* display = GetDisplay();
        Display* xdisplay  = display->GetXDisplay();
        GC gc = DefaultGC(xdisplay, display->GetScreen());
        XSetForeground(xdisplay, gc, xPixel);
        XFillRectangle(xdisplay, (GetWindow())->GetXWindow(), gc, 110,40, 20,20);
    }
}