bool SAM::separateLS(vector<LinePoint*>& left, vector<LinePoint*>& right, LinePoint* split_point, LSFittedLine& line) {
        /*splits a section of points around a splitting point by rotating and translating onto the line about the splitting point
         *Pre: left and right should be empty vectors
         *		points contains all the points to be split
         *		split_point is a valid point in points
         *		line is the LSFittedLine
         *Post: left contains all points with negative transformed x-vals
         *		right contains all points with non-negative transformed x-vals (note split_point will be in right)
         *      if left or right is empty, returns false indicating no actual split occurred
        */

        //temp holder vars
        double A = line.getA();
        double B = line.getB();
        double C = line.getC();
        double x1 = split_point->x;
        double y1 = split_point->y;
        vector<LinePoint*> points = line.getPoints();
        //vector<LinePoint*> points = *points;

        left.push_back(split_point);
        right.push_back(split_point);
/*****DEBUGGING OUTPUT******/
        //printf("\nSplitting on: (%.2f,%.2f)\n",x1,y1);
/*****DEBUGGING OUTPUT******/
        if(A==0.0) {
            //horizontal line - no rotation
            //x' = x - x0
            for(unsigned int pointcounter = 0; pointcounter < points.size(); pointcounter++) {
                //check all points, calculate translated x coord
                //and place in appropriate vector
                if(!(points[pointcounter] == split_point)) {
                    if(points[pointcounter]->x < x1) {
                        //point is to the left
                        left.push_back(points[pointcounter]);
                    }
                    else {
                        right.push_back(points[pointcounter]);
                    }
                }
            }
        }
        else if(B==0.0) {
            //vertical line - 90 degree rotation
            //x' = y - y0
            for(unsigned int pointcounter = 0; pointcounter < points.size(); pointcounter++) {
                //check all points, calculate translated x coord
                //and place in appropriate vector
                if(!(points[pointcounter] == split_point)) {
                    if(points[pointcounter]->y < y1) {
                        //point is to the left
                        left.push_back(points[pointcounter]);
                    }
                    else {
                        right.push_back(points[pointcounter]);
                    }
                }
            }
        }
        else {
         // STILL TO DO: FIX MATRIX CALCS

            //sloped line
            //x' = (x - x0)cosa + (y - y0)sina
            //a = atan(-A/B)
            //(x0,y0) from [ a, b; b, -a][x; y] = [c; bx1 - ay1]
            double alpha = atan(-A/B);
            double cosalpha = cos(alpha);
            double sinalpha = sin(alpha);
            double xtrans;
            // Mx = k  ->  x = M^-1k
            //M = |A   B|
            //    |B  -A|

            // k = |    c    |
            //     | bx1-ay1 |
            double KB;
            KB = (B*x1) - (A*y1);

            //invert M
            // InvM = |-A/div  -B  |
            //        |  -B   A/div|
            // div = A*-A - B*B
            double IA, ID;
            double div = (-A)*A - (B*B);
            IA = (-A)/div;
            ID = -IA;

            //X = A*K
            //  = |-A/div  -B  |  |    c    |
            //    |  -B   A/div|  | bx1-ay1 |

            double X0 = IA*C + (-B)*KB;
            double X1 = (-B)*C + ID*KB;

            for(unsigned int pointcounter = 0; pointcounter <points.size(); pointcounter++) {
                //check all points, calculate translated x coord
                //and place in appropriate vector
                if(!(points[pointcounter] == split_point)) {
                    xtrans = (points[pointcounter]->x - X0)*cosalpha + (points[pointcounter]->y - X1)*sinalpha;
                    if(xtrans < 0) {
                        //point is to the left
                        left.push_back(points[pointcounter]);
                    }
                    else {
                        right.push_back(points[pointcounter]);
                    }
                }
            }
        }
        //if either left or right contains entire point set then there will be an
        //infinite loop
        //qDebug() << "Old line size: " << line.getPoints().size() << " Left size: " << left.size() << " Right size: " << right.size();
        if(left.size() == points.size() || right.size() == points.size())
            return false;
        return true;

}