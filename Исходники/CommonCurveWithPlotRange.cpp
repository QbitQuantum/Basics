void CommonCurveWithPlotRange::makePlotRange() {
    int bigDataNum = 500;
    double *x = new double[bigDataNum];
    double *y = new double[bigDataNum];
    for (int i = 0; i < bigDataNum; i++) {
        x[i] = xmin + (xmax - xmin) * i / (bigDataNum - 1);
    }
    f->getArrayData(x, y, bigDataNum);
    ArrayList<Point2d*> vert;
    ArrayList<double> d;
    for (int i = 0; i < bigDataNum; i++) {
        vert.add(new Point2d(x[i], y[i]));
    }
    delete x;
    delete y;
    ymin = vert[0]->y;
    ymax = vert[0]->y;
    for (int i = 0; i < vert.size(); i++) {
        if (vert[i]->y > ymax) ymax = vert[i]->y;
        if (vert[i]->y < ymin) ymin = vert[i]->y;
    }
    spx = xmax - xmin;
    spy = ymax - ymin;
    graphScale = spy / spx;
    dx = spx / LARGE;
    for (unsigned int i = 0; i < vert.size(); i++) {
        d.add(f->getDerivative(vert[i]->x, dx));
    }
    bool vrm = true; //vert removed
    int count = 0;
    while (vrm) {
        vrm = false;
        for (unsigned int i = 0; i < vert.size(); i++) {
            if (abs(d[i]) / graphScale > MAX_DERIVATIVE) {
                vert.remove(i);
                d.remove(i);
                vrm = true;
            }
        }
        ymin = vert[0]->y;
        ymax = vert[0]->y;
        for (int i = 0; i < vert.size(); i++) {
            if (vert[i]->y > ymax) ymax = vert[i]->y;
            if (vert[i]->y < ymin) ymin = vert[i]->y;
        }
        spy = ymax - ymin;
        graphScale = spy / spx;
        count++;
    }
}