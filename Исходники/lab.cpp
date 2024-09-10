void moveObj() {
    if(last_point == path.size()) {
        cout << "Out of moves" << endl;
        return; //No more moves
    }

    if(last_point > 0) {
      trSize = path[last_point].point - path[last_point - 1].point;
    } else {
      trSize = path[0].point - initial;
    }

    Point p = path[last_point].point;
    Point t = path[last_point++].tangent;
    Point e = t - p;
    os = initial.cross(e);
    angleDeg = initial.angle(e);
    moveV = p;
 }