void plotCubicBezierSegAA(int x0, int y0, double x1, double y1,
                          double x2, double y2, int x3, int y3)
{                           /* plot limited anti-aliased cubic Bezier segment */
    int f, fx, fy, leg = 1;
    int sx = x0 < x3 ? 1 : -1, sy = y0 < y3 ? 1 : -1;        /* step direction */
    double xc = -fabs(x0+x1-x2-x3), xa = xc-4*sx*(x1-x2), xb = sx*(x0-x1-x2+x3);
    double yc = -fabs(y0+y1-y2-y3), ya = yc-4*sy*(y1-y2), yb = sy*(y0-y1-y2+y3);
    double ab, ac, bc, ba, xx, xy, yy, dx, dy, ex, px, py, ed, ip, EP = 0.01;
    
    /* check for curve restrains */
    /* slope P0-P1 == P2-P3     and  (P0-P3 == P1-P2      or  no slope change) */
    assert((x1-x0)*(x2-x3) < EP && ((x3-x0)*(x1-x2) < EP || xb*xb < xa*xc+EP));
    assert((y1-y0)*(y2-y3) < EP && ((y3-y0)*(y1-y2) < EP || yb*yb < ya*yc+EP));
    
    if (xa == 0 && ya == 0) {                              /* quadratic Bezier */
        sx = (int) floor((3*x1-x0+1)/2); sy = (int) floor((3*y1-y0+1)/2);   /* new midpoint */
        return plotQuadBezierSegAA(x0,y0, sx,sy, x3,y3);
    }
    x1 = (x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)+1;                    /* line lengths */
    x2 = (x2-x3)*(x2-x3)+(y2-y3)*(y2-y3)+1;
    do {                                                /* loop over both ends */
        ab = xa*yb-xb*ya; ac = xa*yc-xc*ya; bc = xb*yc-xc*yb;
        ip = 4*ab*bc-ac*ac;                   /* self intersection loop at all? */
        ex = ab*(ab+ac-3*bc)+ac*ac;       /* P0 part of self-intersection loop? */
        f = (int) (ex > 0 ? 1 : sqrt(1+1024/x1));               /* calculate resolution */
        ab *= f; ac *= f; bc *= f; ex *= f*f;            /* increase resolution */
        xy = 9*(ab+ac+bc)/8; ba = 8*(xa-ya);  /* init differences of 1st degree */
        dx = 27*(8*ab*(yb*yb-ya*yc)+ex*(ya+2*yb+yc))/64-ya*ya*(xy-ya);
        dy = 27*(8*ab*(xb*xb-xa*xc)-ex*(xa+2*xb+xc))/64-xa*xa*(xy+xa);
        /* init differences of 2nd degree */
        xx = 3*(3*ab*(3*yb*yb-ya*ya-2*ya*yc)-ya*(3*ac*(ya+yb)+ya*ba))/4;
        yy = 3*(3*ab*(3*xb*xb-xa*xa-2*xa*xc)-xa*(3*ac*(xa+xb)+xa*ba))/4;
        xy = xa*ya*(6*ab+6*ac-3*bc+ba); ac = ya*ya; ba = xa*xa;
        xy = 3*(xy+9*f*(ba*yb*yc-xb*xc*ac)-18*xb*yb*ab)/8;
        
        if (ex < 0) {         /* negate values if inside self-intersection loop */
            dx = -dx; dy = -dy; xx = -xx; yy = -yy; xy = -xy; ac = -ac; ba = -ba;
        }                                     /* init differences of 3rd degree */
        ab = 6*ya*ac; ac = -6*xa*ac; bc = 6*ya*ba; ba = -6*xa*ba;
        dx += xy; ex = dx+dy; dy += xy;                    /* error of 1st step */
        
        for (fx = fy = f; x0 != x3 && y0 != y3; ) {
            y1 = fmin(fabs(xy-dx),fabs(dy-xy));
            ed = fmax(fabs(xy-dx),fabs(dy-xy));    /* approximate error distance */
            ed = f*(ed+2*ed*y1*y1/(4*ed*ed+y1*y1));
            y1 = 255*fabs(ex-(f-fx+1)*dx-(f-fy+1)*dy+f*xy)/ed;
            if (y1 < 256)
                ;//setPixelAA(x0, y0, y1);                  /* plot curve */
            px = fabs(ex-(f-fx+1)*dx+(fy-1)*dy);       /* pixel intensity x move */
            py = fabs(ex+(fx-1)*dx-(f-fy+1)*dy);       /* pixel intensity y move */
            y2 = y0;
            do {                                  /* move sub-steps of one pixel */
                if (ip >= -EP)               /* intersection possible? -> check.. */
                    if (dx+xx > xy || dy+yy < xy) goto exit;   /* two x or y steps */
                y1 = 2*ex+dx;                    /* save value for test of y step */
                if (2*ex+dy > 0) {                                  /* x sub-step */
                    fx--; ex += dx += xx; dy += xy += ac; yy += bc; xx += ab;
                } else if (y1 > 0) goto exit;                 /* tiny nearly cusp */
                if (y1 <= 0) {                                      /* y sub-step */
                    fy--; ex += dy += yy; dx += xy += bc; xx += ac; yy += ba;
                }
            } while (fx > 0 && fy > 0);                       /* pixel complete? */
            if (2*fy <= f) {                           /* x+ anti-aliasing pixel */
                if (py < ed)
                    ;//setPixelAA(x0+sx, y0, 255*py/ed);      /* plot curve */
                y0 += sy; fy += f;                                      /* y step */
            }
            if (2*fx <= f) {                           /* y+ anti-aliasing pixel */
                if (px < ed)
                    ;//setPixelAA(x0, y2+sy, 255*px/ed);      /* plot curve */
                x0 += sx; fx += f;                                      /* x step */
            }
        }
        break;                                          /* finish curve by line */
    exit:
        if (2*ex < dy && 2*fy <= f+2) {         /* round x+ approximation pixel */
            if (py < ed)
                ;//setPixelAA(x0+sx, y0, 255*py/ed);         /* plot curve */
            y0 += sy;
        }
        if (2*ex > dx && 2*fx <= f+2) {         /* round y+ approximation pixel */
            if (px < ed)
                ;//setPixelAA(x0, y2+sy, 255*px/ed);         /* plot curve */
            x0 += sx;
        }
        xx = x0; x0 = x3; x3 = (int) xx; sx = -sx; xb = -xb;             /* swap legs */
        yy = y0; y0 = y3; y3 = (int) yy; sy = -sy; yb = -yb; x1 = x2;
    } while (leg--);                                          /* try other end */
    plotLineAA(x0,y0, x3,y3);     /* remaining part in case of cusp or crunode */
}