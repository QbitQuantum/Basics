    PathIterBench(bool raw)  {
        fName.printf("pathiter_%s", raw ? "raw" : "consume");
        fRaw = raw;

        SkRandom rand;
        for (int i = 0; i < 1000; ++i) {
            SkPoint pts[4];
            int n = rand_pts(rand, pts);
            switch (n) {
                case 1:
                    fPath.moveTo(pts[0]);
                    break;
                case 2:
                    fPath.lineTo(pts[1]);
                    break;
                case 3:
                    fPath.quadTo(pts[1], pts[2]);
                    break;
                case 4:
                    fPath.cubicTo(pts[1], pts[2], pts[3]);
                    break;
            }
        }
    }