boolean Graphic31::intersects_gs (BoxObj& userb, Graphic31* gs) { 
    Coord* convx, *convy;
    Coord ll, bb, rr, tt;
    getbounds_gs(ll, bb, rr, tt, gs);
    BoxObj b(ll, bb, rr, tt);;
    boolean result = false;

    if (!_curved && !_fill) {
        if (b.Intersects(userb)) {
            convx = new Coord[_ctrlpts+1];
            convy = new Coord[_ctrlpts+1];
            Xform_gs(_x, _y, _ctrlpts, convx, convy, gs);
            if (_closed) {
                convx[_ctrlpts] = *convx;
                convy[_ctrlpts] = *convy;
                MultiLineObj ml(convx, convy, _ctrlpts+1);
                result = ml.Intersects(userb);
            } else {
                MultiLineObj ml(convx, convy, _ctrlpts);
                result = ml.Intersects(userb);
            }
            delete convx;
            delete convy;
        }
        return result;

    } else if (!_curved && _fill) {
        if (b.Intersects(userb)) {
            convx = new Coord[_ctrlpts];
            convy = new Coord[_ctrlpts];
            Xform_gs(_x, _y, _ctrlpts, convx, convy, gs);
            FillPolygonObj fp (convx, convy, _ctrlpts);
            result = fp.Intersects(userb);
            delete convx;
            delete convy;
        }
        return result;    

    } else if (_curved && !_fill) {
        if (b.Intersects(userb)) {
            convx = new Coord[_ctrlpts];
            convy = new Coord[_ctrlpts];
            Xform_gs(_x, _y, _ctrlpts, convx, convy, gs);
            MultiLineObj ml;
            if (_closed) {
                ml.ClosedSplineToPolygon(convx, convy, _ctrlpts);
            } else {
                ml.SplineToMultiLine(convx, convy, _ctrlpts);
            }
            result = ml.Intersects(userb);
            delete convx;
            delete convy;
        }
        return result;

    } else {
        if (b.Intersects(userb)) {
            convx = new Coord[_ctrlpts];
            convy = new Coord[_ctrlpts];
            Xform_gs(_x, _y, _ctrlpts, convx, convy, gs);
            FillPolygonObj fp;
            fp.ClosedSplineToPolygon(convx, convy, _ctrlpts);
            result = fp.Intersects(userb);
            delete convx;
            delete convy;
        }
        return result;
    }
}