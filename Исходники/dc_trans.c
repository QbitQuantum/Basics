void rtgui_dc_trans_get_new_wh(struct rtgui_dc_trans *dct,
                               int *new_wp,
                               int *new_hp)
{
    struct rtgui_rect rect;
    struct rtgui_point topleft, topright, bottomright;

    RT_ASSERT(dct);

    if (!new_wp && !new_hp)
        return;

    rtgui_dc_get_rect(dct->owner, &rect);

    /* We ignore the movement components in the matrix. */
    /* Transform result of (0, h). */
    rtgui_matrix_mul_point_nomove(&topleft, 0, rect.y2,
                                  &dct->m);
    /* Transform result of (w, h). */
    rtgui_matrix_mul_point_nomove(&topright, rect.x2, rect.y2,
                                  &dct->m);
    /* Transform result of (w, 0). */
    rtgui_matrix_mul_point_nomove(&bottomright,
                                   rect.x2, 0, &dct->m);
    /* Transform result of (0, 0) is always (0, 0). */

#define NORMALIZE(x) do { if (x < 0) x = 0; } while (0)
    if (new_wp)
    {
        int neww;

        /* Ignore the nagtive parts. */
        NORMALIZE(topright.x);
        NORMALIZE(topleft.x);
        NORMALIZE(bottomright.x);

        neww = _UI_MAX(topright.x, _UI_ABS(topleft.x - bottomright.x))
            + dct->m.m[4] + 1;
        NORMALIZE(neww);

        *new_wp = neww;
    }
    if (new_hp)
    {
        int newh;

        NORMALIZE(topright.y);
        NORMALIZE(topleft.y);
        NORMALIZE(bottomright.y);

        newh = _UI_MAX(topright.y, _UI_ABS(topleft.y - bottomright.y))
            + dct->m.m[5] + 1;
        NORMALIZE(newh);

        *new_hp = newh;
    }
#undef NORMALIZE
}