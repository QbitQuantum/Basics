// Heightfield2 Method Definitions
Heightfield2::Heightfield2(const Transform *o2w, const Transform *w2o,
        bool ro, int x, int y, const float *zs)
    : Shape(o2w, w2o, ro) {
    nx = x;
    ny = y;
    z = new float[nx*ny];
    point = new Point[nx*ny];
    normal = new Normal[nx * ny];
    memcpy(z, zs, nx*ny*sizeof(float));

    nVoxels[0] = x-1;
    nVoxels[1] = y-1;
    bounds = ObjectBound();
    for (int axis = 0; axis < 2; ++axis) {
        width[axis] = 1.f / nVoxels[axis];
        invWidth[axis] = (width[axis] == 0.f) ? 0.f : 1.f / width[axis];
    }

    int index = 0;
    for(int _y = 0; _y < y; _y++){
        for(int _x = 0; _x < x; _x++){
            point[index] = Point(_x * width[0], _y * width[1], z[index]);
            normal[index] = Normal(0, 0, 0);
            index++;
        }
    }

    for (int _y = 0; _y < nVoxels[1]; _y++) {
        for (int _x = 0; _x < nVoxels[0]; _x++) {
            int index1 = _x + _y*nx;
            int index2 = _x+1 + _y*nx;
            int index3 = _x+1 + (_y+1)*nx;
            int index4 = _x + (_y+1)*nx;

            const Point &p1 = point[index1];
            const Point &p2 = point[index2];
            const Point &p3 = point[index3];
            const Point &p4 = point[index4];
            
            Normal &normal1 = normal[index1];
            Normal &normal2 = normal[index2];
            Normal &normal3 = normal[index3];
            Normal &normal4 = normal[index4];
            Normal normal;

            normal = Normal(Normalize(Cross(p2 - p1, p3 - p1)));
            normal1 += normal;
            normal2 += normal;
            normal3 += normal;

            normal = Normal(Normalize(Cross(p3 - p1, p4 - p1)));
            normal1 += normal;
            normal3 += normal;
            normal4 += normal;
        }
    }

    for (int i = 0; i < nx*ny; i++) {
        normal[i] = Normalize(normal[i]);
    }
}