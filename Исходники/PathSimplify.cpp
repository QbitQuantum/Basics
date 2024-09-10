// fit a polyline to a bezier patch, return true is treshhold not exceeded (ie: you can continue)
// version that uses tables from the previous iteration, to minimize amount of work done
bool Path::AttemptSimplify (fitting_tables &data,double treshhold, PathDescrCubicTo & res,int &worstP)
{
    Geom::Point start,end;
    // pour une coordonnee
    Geom::Point cp1, cp2;
  
    worstP = 1;
    if (pts.size() == 2) {
        return true;
    }
  
    start[0] = data.Xk[0];
    start[1] = data.Yk[0];
    cp1[0] = data.Xk[1];
    cp1[1] = data.Yk[1];
    end[0] = data.Xk[data.nbPt - 1];
    end[1] = data.Yk[data.nbPt - 1];
    cp2 = cp1;
  
    if (pts.size()  == 3) {
        // start -> cp1 -> end
        res.start = cp1 - start;
        res.end = end - cp1;
        worstP = 1;
        return true;
    }
  
    if ( FitCubic(start, res, data.Xk, data.Yk, data.Qk, data.tk, data.nbPt) ) {
        cp1 = start + res.start / 3;
        cp2 = end - res.end / 3;
    } else {
        // aie, non-inversible
        double worstD = 0;
        worstP = -1;
        for (int i = 1; i < data.nbPt; i++) {
            Geom::Point nPt;
            nPt[Geom::X] = data.Xk[i];
            nPt[Geom::Y] = data.Yk[i];
            double nle = DistanceToCubic(start, res, nPt);
            if ( data.fk[i] ) {
                // forced points are favored for splitting the recursion; we do this by increasing their distance
                if ( worstP < 0 || 2 * nle > worstD ) {
                    worstP = i;
                    worstD = 2 * nle;
                }
            } else {
                if ( worstP < 0 || nle > worstD ) {
                    worstP = i;
                    worstD = nle;
                }
            }
        }
        return false;
    }
   
    // calcul du delta= pondere par les longueurs des segments
    double delta = 0;
    {
        double worstD = 0;
        worstP = -1;
        Geom::Point prevAppP;
        Geom::Point prevP;
        double prevDist;
        prevP[Geom::X] = data.Xk[0];
        prevP[Geom::Y] = data.Yk[0];
        prevAppP = prevP; // le premier seulement
        prevDist = 0;
#ifdef with_splotch_killer
        if ( data.nbPt <= 20 ) {
            for (int i = 1; i < data.nbPt - 1; i++) {
                Geom::Point curAppP;
                Geom::Point curP;
                double curDist;
                Geom::Point midAppP;
                Geom::Point midP;
                double midDist;
                
                curAppP[Geom::X] = N13(data.tk[i]) * cp1[Geom::X] +
                    N23(data.tk[i]) * cp2[Geom::X] +
                    N03(data.tk[i]) * data.Xk[0] +
                    N33(data.tk[i]) * data.Xk[data.nbPt - 1];
                
                curAppP[Geom::Y] = N13(data.tk[i]) * cp1[Geom::Y] +
                    N23(data.tk[i]) * cp2[Geom::Y] +
                    N03(data.tk[i]) * data.Yk[0] +
                    N33(data.tk[i]) * data.Yk[data.nbPt - 1];
                
                curP[Geom::X] = data.Xk[i];
                curP[Geom::Y] = data.Yk[i];
                double mtk = 0.5 * (data.tk[i] + data.tk[i - 1]);
                
                midAppP[Geom::X] = N13(mtk) * cp1[Geom::X] +
                    N23(mtk) * cp2[Geom::X] +
                    N03(mtk) * data.Xk[0] +
                    N33(mtk) * data.Xk[data.nbPt - 1];
                
                midAppP[Geom::Y] = N13(mtk) * cp1[Geom::Y] +
                    N23(mtk) * cp2[Geom::Y] +
                    N03(mtk) * data.Yk[0] +
                    N33(mtk) * data.Yk[data.nbPt - 1];
                
                midP = 0.5 * (curP + prevP);
        
                Geom::Point diff = curAppP - curP;
                curDist = dot(diff, diff);
                diff = midAppP - midP;
                midDist = dot(diff, diff);
        
                delta += 0.3333 * (curDist + prevDist + midDist) * data.lk[i];
                if ( curDist > worstD ) {
                    worstD = curDist;
                    worstP = i;
                } else if ( data.fk[i] && 2 * curDist > worstD ) {
                    worstD = 2*curDist;
                    worstP = i;
                }
                prevP = curP;
                prevAppP = curAppP;
                prevDist = curDist;
            }
            delta /= data.totLen;
            
        } else {
#endif
            for (int i = 1; i < data.nbPt - 1; i++) {
                Geom::Point curAppP;
                Geom::Point curP;
                double    curDist;
        
                curAppP[Geom::X] = N13(data.tk[i]) * cp1[Geom::X] +
                    N23(data.tk[i]) * cp2[Geom::X] +
                    N03(data.tk[i]) * data.Xk[0] +
                    N33(data.tk[i]) * data.Xk[data.nbPt - 1];
                
                curAppP[Geom::Y] = N13(data.tk[i]) * cp1[Geom::Y] +
                    N23(data.tk[i]) * cp2[Geom::Y] +
                    N03(data.tk[i]) * data.Yk[0] +
                    N33(data.tk[i]) * data.Yk[data.nbPt - 1];
                
                curP[Geom::X] = data.Xk[i];
                curP[Geom::Y] = data.Yk[i];
      
                Geom::Point diff = curAppP-curP;
                curDist = dot(diff, diff);
                delta += curDist;
        
                if ( curDist > worstD ) {
                    worstD = curDist;
                    worstP = i;
                } else if ( data.fk[i] && 2 * curDist > worstD ) {
                    worstD = 2*curDist;
                    worstP = i;
                }
                prevP = curP;
                prevAppP = curAppP;
                prevDist = curDist;
            }
#ifdef with_splotch_killer
        }
#endif
    }
  
    if (delta < treshhold * treshhold) {
        // premier jet
    
        // Refine a little.
        for (int i = 1; i < data.nbPt - 1; i++) {
            Geom::Point pt(data.Xk[i], data.Yk[i]);
            data.tk[i] = RaffineTk(pt, start, cp1, cp2, end, data.tk[i]);
            if (data.tk[i] < data.tk[i - 1]) {
                // Force tk to be monotonic non-decreasing.
                data.tk[i] = data.tk[i - 1];
	    }
        }
    
        if ( FitCubic(start, res, data.Xk, data.Yk, data.Qk, data.tk, data.nbPt) == false) {
            // ca devrait jamais arriver, mais bon
            res.start = 3.0 * (cp1 - start);
            res.end = 3.0 * (end - cp2 );
            return true;
        }
        
        double ndelta = 0;
        {
            double worstD = 0;
            worstP = -1;
            Geom::Point prevAppP;
            Geom::Point prevP(data.Xk[0], data.Yk[0]);
            double prevDist = 0;
            prevAppP = prevP; // le premier seulement
#ifdef with_splotch_killer
            if ( data.nbPt <= 20 ) {
                for (int i = 1; i < data.nbPt - 1; i++) {
                    Geom::Point curAppP;
                    Geom::Point curP;
                    double  curDist;
                    Geom::Point midAppP;
                    Geom::Point midP;
                    double  midDist;
          
                    curAppP[Geom::X] = N13(data.tk[i]) * cp1[Geom::X] +
                        N23(data.tk[i]) * cp2[Geom::X] +
                        N03(data.tk[i]) * data.Xk[0] +
                        N33(data.tk[i]) * data.Xk[data.nbPt - 1];
                    
                    curAppP[Geom::Y] = N13(data.tk[i]) * cp1[Geom::Y] +
                        N23(data.tk[i]) * cp2[Geom::Y] +
                        N03(data.tk[i]) * data.Yk[0] +
                        N33(data.tk[i]) * data.Yk[data.nbPt - 1];
                    
                    curP[Geom::X] = data.Xk[i];
                    curP[Geom::Y] = data.Yk[i];
                    double mtk = 0.5 * (data.tk[i] + data.tk[i - 1]);
                    
                    midAppP[Geom::X] = N13(mtk) * cp1[Geom::X] +
                        N23(mtk) * cp2[Geom::X] +
                        N03(mtk) * data.Xk[0] +
                        N33(mtk) * data.Xk[data.nbPt - 1];
                    
                    midAppP[Geom::Y] = N13(mtk) * cp1[Geom::Y] +
                        N23(mtk) * cp2[Geom::Y] +
                        N03(mtk) * data.Yk[0] +
                        N33(mtk) * data.Yk[data.nbPt - 1];
                    
                    midP = 0.5 * (curP + prevP);
          
                    Geom::Point diff = curAppP - curP;
                    curDist = dot(diff, diff);
          
                    diff = midAppP - midP;
                    midDist = dot(diff, diff);
          
                    ndelta += 0.3333 * (curDist + prevDist + midDist) * data.lk[i];
          
                    if ( curDist > worstD ) {
                        worstD = curDist;
                        worstP = i;
                    } else if ( data.fk[i] && 2 * curDist > worstD ) {
                        worstD = 2*curDist;
                        worstP = i;
                    }
                    
                    prevP = curP;
                    prevAppP = curAppP;
                    prevDist = curDist;
                }
                ndelta /= data.totLen;
            } else {
#endif
                for (int i = 1; i < data.nbPt - 1; i++) {
                    Geom::Point curAppP;
                    Geom::Point curP;
                    double    curDist;
                    
                    curAppP[Geom::X] = N13(data.tk[i]) * cp1[Geom::X] +
                        N23(data.tk[i]) * cp2[Geom::X] +
                        N03(data.tk[i]) * data.Xk[0] +
                        N33(data.tk[i]) * data.Xk[data.nbPt - 1];
                    
                    curAppP[Geom::Y] = N13(data.tk[i]) * cp1[Geom::Y] +
                        N23(data.tk[i]) * cp2[1] +
                        N03(data.tk[i]) * data.Yk[0] +
                        N33(data.tk[i]) * data.Yk[data.nbPt - 1];
                    
                    curP[Geom::X] = data.Xk[i];
                    curP[Geom::Y] = data.Yk[i];
        
                    Geom::Point diff = curAppP - curP;
                    curDist = dot(diff, diff);

                    ndelta += curDist;

                    if ( curDist > worstD ) {
                        worstD = curDist;
                        worstP = i;
                    } else if ( data.fk[i] && 2 * curDist > worstD ) {
                        worstD = 2 * curDist;
                        worstP = i;
                    }
                    prevP = curP;
                    prevAppP = curAppP;
                    prevDist = curDist;
                }
#ifdef with_splotch_killer
            }
#endif
        }
    
        if (ndelta < delta + 0.00001) {
            return true;
        } else {
            // nothing better to do
            res.start = 3.0 * (cp1 - start);
            res.end = 3.0 * (end - cp2 );
        }
        
        return true;
    }
  
  return false;
}