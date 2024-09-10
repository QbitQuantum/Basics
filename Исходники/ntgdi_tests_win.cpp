TEST(NtGdiTests, CreatePolygonRgn) {
    /* Test i#809 */

    /* Allocate a 0-sized array, which raised a false pos in i#809 */
    POINT *points = new POINT[0];
    HRGN hrgn = CreatePolygonRgn(points, 0, ALTERNATE);
    EXPECT_EQ((HRGN)NULL, hrgn);
    delete [] points;

    points = new POINT[3];
    memset(points, 0, 3*sizeof(POINT));
    hrgn = CreatePolygonRgn(points, 3, ALTERNATE);
    EXPECT_NE((HRGN)NULL, hrgn);
    DeleteObject(hrgn);
    delete [] points;
}