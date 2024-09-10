static void test_SubtractRect(void)
{
    RECT rect1;
    RECT rect2;
    RECT rectr;
    BOOL result;

    /* source rectangles don't intersect */
    SetRect(&rect1, 50, 50, 150, 100);
    SetRect(&rect2, 250, 200, 1500, 1000);
    result = SubtractRect(&rectr, &rect1, &rect2);
    ok(result, "SubtractRect returned FALSE but subtraction should not be empty\n");
    ok(result && rectr.left == 50 && rectr.top == 50 && rectr.right ==150
        && rectr.bottom == 100, "wrong rect subtraction of SubtractRect "
        "(dest rect={%d, %d, %d, %d})\n", rectr.left, rectr.top, rectr.right, rectr.bottom);

    /* source rect 2 partially overlaps rect 1 */
    SetRect(&rect1, 2431, 626, 3427, 1608);
    SetRect(&rect2, 2499, 626, 3427, 1608);
    result = SubtractRect(&rectr, &rect1, &rect2);
    ok(result, "SubtractRect returned FALSE but subtraction should not be empty\n");
    ok(result && rectr.left == 2431 && rectr.top == 626 && rectr.right == 2499
        && rectr.bottom == 1608, "wrong rect subtraction of SubtractRect "
        "(dest rect={%d, %d, %d, %d})\n", rectr.left, rectr.top, rectr.right, rectr.bottom);

    /* source rect 2 partially overlaps rect 1 - dest is src rect 2 */
    SetRect(&rect1, 2431, 626, 3427, 1608);
    SetRect(&rect2, 2499, 626, 3427, 1608);
    result = SubtractRect(&rect2, &rect1, &rect2);
    ok(result, "SubtractRect returned FALSE but subtraction should not be empty\n");
    ok(result && rectr.left == 2431 && rectr.top == 626 && rectr.right == 2499
        && rectr.bottom == 1608, "wrong rect subtraction of SubtractRect "
        "(dest rect={%d, %d, %d, %d})\n", rectr.left, rectr.top, rectr.right, rectr.bottom);

    /* source rect 2 completely overlaps rect 1 */
    SetRect(&rect1, 250, 250, 400, 500);
    SetRect(&rect2, 50, 50, 1500, 1000);
    result = SubtractRect(&rectr, &rect1, &rect2);
    ok(!result, "SubtractRect returned TRUE but subtraction should be empty "
        "(dest rect={%d, %d, %d, %d})\n", rectr.left, rectr.top, rectr.right, rectr.bottom);

    /* source rect 2 completely overlaps rect 1 - dest is src rect 2 */
    SetRect(&rect1, 250, 250, 400, 500);
    SetRect(&rect2, 50, 50, 1500, 1000);
    result = SubtractRect(&rect2, &rect1, &rect2);
    ok(!result, "SubtractRect returned TRUE but subtraction should be empty "
        "(dest rect={%d, %d, %d, %d})\n", rect2.left, rect2.top, rect2.right, rect2.bottom);
}