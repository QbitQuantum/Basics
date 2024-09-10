void ModuleBuildings::addBuildingWallLevel(Vec2f pos1, Vec2f pos2, int level, int bNum, float elevation) {
    srand(bNum); //seed for random windows
    float len = (pos2 - pos1).length();
    Vec2f wallDir = (pos2 - pos1);
    wallDir.normalize();

    float wall_segment = Config::get()->WINDOW_DOOR_WIDTH;
    float FLOOR_HEIGHT = Config::get()->BUILDING_FLOOR_HEIGHT;

    int segN = floor(len / wall_segment);
    segN = max(segN, 1);
    wall_segment = len / segN;

    float low = level * FLOOR_HEIGHT + elevation;
    float high = low + FLOOR_HEIGHT;

    // insert a door at a random place (when on level 0 && there is enough room)
    int doorIndex = -1;
    if (level == 0 && segN > 2) doorIndex = bNum % segN;

    int N = 4;
    float _N = 1./N;
    float e = 0.01;

    int di = N*float(rand()) / RAND_MAX;
    int wi = N*float(rand()) / RAND_MAX;
    int fi = N*float(rand()) / RAND_MAX;

    float d_tc1 = di * _N + e;
    float d_tc2 = di * _N - e + _N;
    float w_tc1 = wi * _N + e;
    float w_tc2 = wi * _N - e + _N;
    float f_tc1 = fi * _N + e;
    float f_tc2 = fi * _N - e + _N;

    for (int i=0; i<segN; i++) {
        Vec2f w1 = pos1 + (wallDir * (i*wall_segment));
        Vec2f w2 = pos1 + (wallDir * ((i+1)*wall_segment));

        Vec2f wallVector = w2-w1;
        Vec3f normal = Vec3f(-wallVector.getValues()[1], 0, wallVector.getValues()[0]);

        b_geo_d->pos->addValue(Vec3f(w1.getValues()[0], low, w1.getValues()[1]));
        b_geo_d->pos->addValue(Vec3f(w2.getValues()[0], low, w2.getValues()[1]));
        b_geo_d->pos->addValue(Vec3f(w2.getValues()[0], high, w2.getValues()[1]));
        b_geo_d->pos->addValue(Vec3f(w1.getValues()[0], high, w1.getValues()[1]));

        for (int k=0; k<4; k++) {
            b_geo_d->inds->addValue(b_geo_d->inds->size());
            b_geo_d->norms->addValue(normal);
        }

        if (i == doorIndex) { // door
            b_geo_d->texs2->addValue(Vec2f(d_tc1, 0.5+e));
            b_geo_d->texs2->addValue(Vec2f(d_tc2, 0.5+e));
            b_geo_d->texs2->addValue(Vec2f(d_tc2, 0.75-e));
            b_geo_d->texs2->addValue(Vec2f(d_tc1, 0.75-e));
        } else { // window
            b_geo_d->texs2->addValue(Vec2f(w_tc1, 0.25+e));
            b_geo_d->texs2->addValue(Vec2f(w_tc2, 0.25+e));
            b_geo_d->texs2->addValue(Vec2f(w_tc2, 0.5-e));
            b_geo_d->texs2->addValue(Vec2f(w_tc1, 0.5-e));
        }

        // wall
        b_geo_d->texs->addValue(Vec2f(f_tc1, e));
        b_geo_d->texs->addValue(Vec2f(f_tc2, e));
        b_geo_d->texs->addValue(Vec2f(f_tc2, 0.25-e));
        b_geo_d->texs->addValue(Vec2f(f_tc1, 0.25-e));
    }
}