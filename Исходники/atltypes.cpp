static void test_CRect()
{
    CRect empty;
    ok(empty.left == 0, "Expected left to be 0, was %ld\n", empty.left);
    ok(empty.top == 0, "Expected top to be 0, was %ld\n", empty.top);
    ok(empty.Width() == 0, "Expected Width to be 0, was %i\n", empty.Width());
    ok(empty.Height() == 0, "Expected Height to be 0, was %i\n", empty.Height());

    CRect rect(0, 0, 100, 50);
    ok(rect.Width() == 100, "Expected Width to be 100, was %i\n", rect.Width());
    ok(rect.Height() == 50, "Expected Height to be 50, was %i\n", rect.Height());

    RECT sdkRect;
    sdkRect.left = 0;
    sdkRect.top = 0;
    sdkRect.right = 100;
    sdkRect.bottom = 50;

    CRect rect2(sdkRect);
    CRect rect3(&sdkRect);
    ok_rect(rect2, rect);
    ok_rect(rect3, rect);

    CPoint pt(0, 0);
    CSize sz(100, 50);
    CRect rect4(pt, sz);
    ok_rect(rect4, rect2);

    CPoint ptBottomRight(100, 50);
    CRect rect5(pt, ptBottomRight);
    ok_rect(rect5, rect4);

    rect = CRect(210, 150, 350, 900);
    CPoint ptDown;

    ptDown = rect.BottomRight();

    pt = CPoint(350, 900);
    ok_point(ptDown, pt);

    rect2 = CRect(10, 10, 350, 350);
    CPoint ptLow(180, 180);

    rect2.BottomRight() = ptLow;

    rect = CRect(10, 10, 180, 180);
    ok_rect(rect2, rect);

    pt = CPoint(95, 95);
    CPoint pt2 = rect2.CenterPoint();
    ok_point(pt2, pt);

    pt2 = rect2.BottomRight();
    pt = CPoint(180, 180);
    ok_point(pt2, pt);

    pt2 = rect2.TopLeft();
    pt = CPoint(10, 10);
    ok_point(pt2, pt);

    rect2.TopLeft().Offset(3, 3);
    rect3 = CRect(13, 13, 180, 180);
    ok_rect(rect3, rect2);

    CRect rectSource(35, 10, 125, 10);
    CRect rectDest;

    rectDest.CopyRect(&rectSource);

    RECT rectSource2;
    rectSource2.left = 0;
    rectSource2.top = 0;
    rectSource2.bottom = 480;
    rectSource2.right = 640;

    rectDest.CopyRect(&rectSource2);

    rect = CRect(10, 10, 50, 50);

    rect.DeflateRect(1, 2);

    rect2 = CRect(11, 12, 49, 48);
    ok_rect(rect2, rect);

    rect2 = CRect(10, 10, 50, 50);
    CRect rectDeflate(1, 2, 3, 4);

    rect2.DeflateRect(&rectDeflate);
    rect = CRect(11, 12, 47, 46);
    ok_rect(rect2, rect);

    rect2.DeflateRect(sz);
    rect = CRect(111, 62, -53, -4);
    ok_rect(rect2, rect);

    rect2.OffsetRect(sz);
    rect = CRect(211, 112, 47, 46);
    ok_rect(rect2, rect);

    CRect rect1(35, 150, 10, 25);
    rect2 = CRect(35, 150, 10, 25);
    rect3 = CRect(98, 999, 6, 3);

    ok(rect1.EqualRect(rect2), "Expected EqualRect to return TRUE for %s, %s\n", wine_dbgstr_rect(&rect1), wine_dbgstr_rect(&rect2));
    ok(!rect1.EqualRect(rect3), "Expected EqualRect to return FALSE for %s, %s\n", wine_dbgstr_rect(&rect1), wine_dbgstr_rect(&rect3));

    RECT test;
    test.left = 35;
    test.top = 150;
    test.right = 10;
    test.bottom = 25;

    ok(rect1.EqualRect(&test), "Expected EqualRect to return TRUE for %s, %s\n", wine_dbgstr_rect(&rect1), wine_dbgstr_rect(&test));

    rect = test;
    rect2 = CRect(35, 150, 10, 25);
    ok_rect(rect, rect2);

    rect = CRect(0, 0, 300, 300);
    rect.InflateRect(50, 200);

    rect2 = CRect(-50, -200, 350, 500);
    ok_rect(rect, rect2);

    rect.InflateRect(sz);
    rect2 = CRect(-150, -250, 450, 550);
    ok_rect(rect, rect2);

    rect = CRect(20, 30, 80, 70);

    int nHt = rect.Height();

    ok(nHt == 40, "Expected nHt to be 40, was %i\n", nHt);

    CRect rectOne(125, 0, 150, 200);
    CRect rectTwo(0, 75, 350, 95);
    CRect rectInter;

    rectInter.IntersectRect(rectOne, rectTwo);

    rect = CRect(125, 75, 150, 95);
    ok_rect(rectInter, rect);

    CRect rectInter2 = rectOne;
    rectInter2 &= rectTwo;
    rect = CRect(125, 75, 150, 95);
    ok_rect(rectInter2, rect);

    CRect rectNone(0, 0, 0, 0);
    CRect rectSome(35, 50, 135, 150);

    ok(rectNone.IsRectEmpty(), "Expected IsRectEmpty to return TRUE for %s\n", wine_dbgstr_rect(&rectNone));
    ok(!rectSome.IsRectEmpty(), "Expected IsRectEmpty to return FALSE for %s\n", wine_dbgstr_rect(&rectSome));

    CRect rectEmpty(35, 35, 35, 35);
    ok(rectEmpty.IsRectEmpty(), "Expected IsRectEmpty to return TRUE for %s\n", wine_dbgstr_rect(&rectEmpty));

    ok(rectNone.IsRectNull(), "Expected IsRectNull to return TRUE for %s\n", wine_dbgstr_rect(&rectNone));
    ok(!rectSome.IsRectNull(), "Expected IsRectNull to return FALSE for %s\n", wine_dbgstr_rect(&rectSome));

    CRect rectNotNull(0, 0, 35, 50);
    ok(!rectNotNull.IsRectNull(), "Expected IsRectNull to return FALSE for %s\n", wine_dbgstr_rect(&rectNotNull));

    rect1 = CRect(35, 150, 10, 25);
    rect2 = CRect(35, 150, 10, 25);
    rect3 = CRect(98, 999, 6, 3);

    ok_rect(rect1, rect2);

    test.left = 35;
    test.top = 150;
    test.right = 10;
    test.bottom = 25;

    ok_rect(rect1, test);

    nok_rect(rect1, rect3);
    nok_rect(rect3, test);

    rect1 = CRect(100, 235, 200, 335);
    pt = CPoint(35, 65);
    rect2 = CRect(135, 300, 235, 400);

    rect1 += pt;

    ok_rect(rect1, rect2);

    rect1 = CRect(100, 235, 200, 335);
    rect2 = rect1 + pt;
    CRect rectResult(135, 300, 235, 400);
    ok_rect(rectResult, rect2);

    rect2 = rect1 + &test;
    rectResult = CRect(65, 85, 210, 360);
    ok_rect(rectResult, rect2);

    rect2 = rect1 - (LPCRECT)&test;
    rectResult = CRect(135, 385, 190, 310);
    ok_rect(rectResult, rect2);

    rect2 = rect1 - pt;
    rectResult = CRect(65, 170, 165, 270);

    ok_rect(rect2, rectResult);

    rect1 -= pt;
    ok_rect(rect1, rectResult);

    rect1 = CRect(100, 0, 200, 300);
    rect2 = CRect(0, 100, 300, 200);

    rect3 = rect1 & rect2;

    rectResult = CRect(100, 100, 200, 200);
    ok_rect(rectResult, rect3);

    rect3 = rect1 | rect2;
    rectResult = CRect(0, 0, 300, 300);
    ok_rect(rectResult, rect3);

    rect1 |= rect2;
    ok_rect(rectResult, rect1);

    rect1 += sz;
    rectResult = CRect(100, 50, 400, 350);
    ok_rect(rectResult, rect1);

    rect1 += &test;
    rectResult = CRect(65, -100, 410, 375);
    ok_rect(rectResult, rect1);

    rect1 -= sz;
    rectResult = CRect(-35, -150, 310, 325);
    ok_rect(rectResult, rect1);

    rect1 -= &test;
    rectResult = CRect(0, 0, 300, 300);
    ok_rect(rectResult, rect1);

    rect2 = rect1 + sz;
    rectResult = CRect(100, 50, 400, 350);
    ok_rect(rectResult, rect2);

    rect2 = rect1 - sz;
    rectResult = CRect(-100, -50, 200, 250);
    ok_rect(rectResult, rect2);
}