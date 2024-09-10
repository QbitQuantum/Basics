BlocksInfo blocks(const std::vector<Path2d>& boundaries, double side, bool oddeven)
{
    std::vector<Path2d> paths;
    std::vector<Path2d> grid;
    int h, w;
    int x0, y0, x1, y1;
    P2d p0, p1, po, pa, pb;

    for (int j=0,m=boundaries.size(); j<m; j++)
    {
        Path2d path = boundaries[j] / side;
        path.boundingBox(p0, p1, j!=0);
        paths.push_back(path);
    }

    x0 = int(floor(p0.x - side));
    y0 = int(floor(p0.y - side));
    x1 = int(ceil(p1.x + side));
    y1 = int(ceil(p1.y + side));

    po.x = x0;
    po.y = y0;
    for (int j=0,m=paths.size(); j<m; j++)
    {
        paths[j] -= po; /* align to image origin */
    }

    w = x1 - x0;
    h = y1 - y0;
    Image<int> image(w, h);
    image.fastBox(0, 0, w, h, 0); /* zero fill */

    if (oddeven) {
        polyFill(image, 1, paths);
        polyDraw(image, 1, paths);
    } else {
        /* vogliamo solo marcare le aree coperte dai perimetri esterni
         * senza considerare eventuali fori */
        std::vector<Path2d> spath(1);
        for (int j=0,m=paths.size(); j<m; j++)
        {
            spath[0] = paths[j];
            polyFill(image, 1, spath);
            polyDraw(image, 1, spath);
        }
    }

    paths.clear();

    int num=0;
    for(int x=-1; x<w; ++x) {
        for (int y=-1; y<h; ++y) {
            if (image.pixel(x, y, 0) != 0)
            {
                std::vector<P2d> points;
                pa.x = (x0 + x) * side;
                pa.y = (y0 + y) * side;
                pb.x = pa.x;
                pb.y = pa.y + side;
                points.push_back(pa);
                points.push_back(pb);
                pa.x = pb.x + side;
                pa.y = pb.y;
                points.push_back(pa);
                pb.x = pa.x;
                pb.y = pa.y - side;
                points.push_back(pb);
                pa.x = pb.x - side;
                pa.y = pb.y;
                points.push_back(pa);
                Path2d block(points);
                grid.push_back(block);
                num++;
            }
            /* due pixel accanto diversi*/
            if (image.pixel(x, y, 0) != image.pixel(x+1, y, 0)) {
                std::vector<P2d> points;
                pa.x = (x0 + x + 1) * side;
                pa.y = (y0 + y) * side;
                pb.x = pa.x;
                pb.y = pa.y + side;
                points.push_back(pa);
                points.push_back(pb);
                Path2d block(points);
                paths.push_back(block);
                /* due pixel uno sopra l'altro diversi*/
            }
            if (image.pixel(x, y, 0) != image.pixel(x, y+1, 0)) {
                std::vector<P2d> points;
                pa.x = (x0 + x) * side;
                pa.y = (y0 + y + 1) * side;
                pb.x = pa.x + side;
                pb.y = pa.y;
                points.push_back(pa);
                points.push_back(pb);
                Path2d block(points);
                paths.push_back(block);
            }
        }
    }
    BlocksInfo iblocks(num, paths, grid);
    return iblocks;
}