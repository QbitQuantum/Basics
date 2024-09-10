void draw_tick_marks( Display_Context dtx )
{
    float verts[2][3];
    /* base and up vectors for text drawn along x,y,z axes. */
    static float bx[3] = { 0.05, 0.0, 0.0 },      ux[3] = { 0.0, 0.05, 0.05 };
    /*
    static float by[3] = { -0.035, 0.0, -0.035 },  uy[3] = { 0.0, 0.07, 0.0 };
    static float bz[3] = { -0.035, -0.035, 0.0 }, uz[3] = { 0.0, 0.0, 0.07 };
    */
    float tick_inc, i, row, col, lev;
    char str[100];

    /* set depth cueing & line color */
    /* MJK 3.29.99 */
    if (dtx->Reversed) {
        set_color( PACK_COLOR(0,0,0,255) );
    }
    else {
        set_color( dtx->BoxColor );
    }


    set_depthcue( dtx->DepthCue );

    /* go in the order.. low south side, low east side,
       go counter-clock-wise, then high south side, couterclockwise,
       then southeast side, and work coutner-clockwise, so there are
       12 sides to loop through */

    dtx->tick_do[0] = 1;
    dtx->tick_type[0] = 1;
    dtx->tick_num[0] = 10;
    if (dtx->tick_do[0]) {
        tick_inc = (float)(dtx->Nc)/(float)(dtx->tick_num[0]-1);
        row = dtx->Nr-1;
        lev = 0;
        for (i = tick_inc; i < dtx->Nc; i += tick_inc) {
            col = i;
            vis5d_gridPRIME_to_xyzPRIME(dtx->dpy_context_index, 0, 0,
                                        row, col, lev, &verts[0][0], &verts[0][1], &verts[0][2]);
            verts[1][0] = verts[0][0];
            verts[1][1] = verts[0][1] - 0.05;
            verts[1][2] = verts[0][2] - 0.062;
            polyline( verts, 2);
            if (dtx->tick_type[0] == 0) {
                float lat, lon, hgt;
                vis5d_gridPRIME_to_geo(dtx->dpy_context_index, 0, 0,
                                       row, col, lev, &lat, &lon, &hgt);
                /*float2string(lon, str); */
                if (strlen(str) <2) {
                    plot_string( str, verts[1][0]-.009, verts[1][1]-.05, verts[1][2]-0.062, bx, ux, 0);
                }
                else if (strlen(str) <4) {
                    plot_string( str, verts[1][0]-.02, verts[1][1]-.05, verts[1][2]-0.062, bx, ux, 0);
                }
                else {
                    plot_string( str, verts[1][0]-.05, verts[1][1]-.05, verts[1][2]-0.062, bx, ux, 0);
                }
            }
            else if (dtx->tick_type[0] == 1) {
                /* float2string(col, str); */
                if (strlen(str) <2) {
                    plot_string( str, verts[1][0]-.009, verts[1][1]-.05, verts[1][2]-0.062, bx, ux, 0);
                }
                else if (strlen(str) <4) {
                    plot_string( str, verts[1][0]-.02, verts[1][1]-.05, verts[1][2]-0.062, bx, ux, 0);
                }
                else {
                    plot_string( str, verts[1][0]-.05, verts[1][1]-.05, verts[1][2]-0.062, bx, ux, 0);
                }
            }
        }
    }
}