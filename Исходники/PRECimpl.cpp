// Assumes lx1 != lx2 || ly1 != ly2.
static bool precise_collision_line(int intersection_left, int intersection_right, int intersection_top, int intersection_bottom,
                                double x1, double y1,
                                double xscale1, double yscale1,
                                double ia1,
                                unsigned char* pixels1,
                                int w1, int h1,
                                int xoffset1, int yoffset1,
                                int lx1, int ly1, int lx2, int ly2)
{
    if (xscale1 != 0.0 && yscale1 != 0.0) {

        const double pi_half = M_PI/2.0;

        const double arad1 = ia1*M_PI/180.0;

        const double cosa1 = cos(-arad1);
        const double sina1 = sin(-arad1);
        const double cosa90_1 = cos(-arad1 + pi_half);
        const double sina90_1 = sin(-arad1 + pi_half);

        if (lx1 != lx2 && abs(lx1-lx2) >= abs(ly1-ly2)) { // The slope is defined and in [-1;1].
            const int minX = max(min(lx1, lx2), intersection_left),
                       maxX = min(max(lx1, lx2), intersection_right);

            const double denom = lx2 - lx1;
            for (int gx = minX; gx <= maxX; gx++)
            {
                int gy = (int)round((gx - lx1)*(ly2-ly1)/denom + ly1);
                if (gy < intersection_top || gy > intersection_bottom) {
                    continue;
                }
                // Test for single image.
                const int bx1 = (gx - x1);
                const int by1 = (gy - y1);
                const int px1 = (int)((bx1*cosa1 + by1*sina1)/xscale1 + xoffset1);
                const int py1 = (int)((bx1*cosa90_1 + by1*sina90_1)/yscale1 + yoffset1);
                const bool p1 = px1 >= 0 && py1 >= 0 && px1 < w1 && py1 < h1 && pixels1[py1*w1 + px1] != 0;

                if (p1) {
                    return true;
                }
            }
        }
        else { // ly1 != ly2.
            const int minY = max(min(ly1, ly2), intersection_top),
                       maxY = min(max(ly1, ly2), intersection_bottom);

            const double denom = ly2 - ly1;
            for (int gy = minY; gy <= maxY; gy++)
            {
                int gx = (int)round((gy - ly1)*(lx2-lx1)/denom + lx1);
                if (gx < intersection_left || gx > intersection_right) {
                    continue;
                }
                // Test for single image.
                const int bx1 = (gx - x1);
                const int by1 = (gy - y1);
                const int px1 = (int)((bx1*cosa1 + by1*sina1)/xscale1 + xoffset1);
                const int py1 = (int)((bx1*cosa90_1 + by1*sina90_1)/yscale1 + yoffset1);
                const bool p1 = px1 >= 0 && py1 >= 0 && px1 < w1 && py1 < h1 && pixels1[py1*w1 + px1] != 0;

                if (p1) {
                    return true;
                }
            }
        }
    }
    return false;
}