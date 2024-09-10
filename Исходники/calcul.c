void mk_minimum_displacement(struct points *p, float *rx, float *ry)
{
        struct points *n = p;
        struct points *tmp = p;
        float smallest_v = FLT_MAX;
        float v = 0;
        float x = 0, y = 0;
        int i = 0;

        while(tmp != NULL) {
                i++;
                if (tmp->next == NULL) {
                        if (tmp == p) {
                                break;
                        }
                        n = p;
                } else {
                        n = tmp->next;
                }

                get_point_on_segment(tmp, n, &x, &y);
                v = hypotf(x, y);

                if (smallest_v > v) {
                        smallest_v = v;
                        *rx = x;
                        *ry = y;
                }

                tmp = tmp->next;
        }
}