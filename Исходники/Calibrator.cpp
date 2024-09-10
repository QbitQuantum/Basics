void Calibrator::update(int time, Vector v)
{
    const float SIMILARITY = 0.8f; /* 36 degrees' deviation, 10 vectors per circle */

    float vl = v.length();
    if (vl == 0.0f) {
        return;
    }

    Vector nv = v.divide(vl);

    /* Require sampled vectors to point to fairly different directions
     * before accepting another. */
    float similarity = nv.dot(old_nv);
    if (similarity > SIMILARITY) {
        return;
    }
    old_nv = nv;

    /* Check if we already have a vector nearly to same direction,
     * if so replace that one. This helps in not destroying our
     * history of vectors if user just jiggles device back and forth. */
    for (int i = 0; i < PCR; i ++) {
        if (point_cloud[i].time < time - validity) {
            idx = i;
            break;
        }

        Vector c = point_cloud[idx].v;
        Vector nc = c.divide(c.length());

        float similarity = nv.dot(nc);
        if (similarity > SIMILARITY) {
            idx = i;
            break;
        }
        
    }

    point_cloud[idx].time = time;
    point_cloud[idx].v = v;
    /* Round-robin vector reuse */
    idx = (idx + 1) & (PCR - 1);
}