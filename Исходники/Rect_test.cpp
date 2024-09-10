TEST_F (RectTest, intersect2) 
{
    Rect monitor (0, 0, 1440, 900);
    Rect piece (100, 100, 50, 50);
    Rect intersect;
    EXPECT_TRUE (monitor.intersects (piece, &intersect));
    EXPECT_EQ (intersect, piece) << "Hey, the piece is exactly inside the monitor";
}