void CastRelation()
{
    char ignoreT[objMax];
    int i, saveRev;
    real ratio, t1, t2, t;
    real ppowerT[oNormOpt+1];
    /* Cast the first chart. */

    ciMain = ciCore;
    if (us.fRelocation && us.nRel == rcComposite) {
        OO=us.lonDef;
        AA=us.latDef ;
        NN=us.altDef;
    }
    t1 = CastChart(fTrue);
    cp1 = cp0;
    saveRev = hRevers;
    if (us.nRel == rcTransit || us.nRel == rcProgress)
        for (i = 1; i <= cObjOpt; i++) {
            cp1.dir[i] = 0.0;
            if (i > oNormOpt)
                continue;
            cp1.altdir[i] = 0.0;
        }

#ifdef GRAPH              /* Struct GS is defined with graphics.  */
    if (!gs.nAnim) {
#endif
        if (!FCreateGrid(fFalse))
            return;
        PlanetPPower();
#ifdef GRAPH
    }
#endif

    /* Cast the second chart. */

    ciCore = ciTwin;
    if (us.nRel == rcTransit) {
        for (i = 0; i <= cObjOpt; i++) {
            ignoreT[i] = ignore[i];
            if (us.fSector || us.fAstroGraph)
                ignore[i] = ignore[i] && ignore2[i];
            else
                ignore[i] = ignore2[i];
        }
    } else if (us.nRel == rcProgress) {
        us.fProgress = fTrue;
        is.JDp = MdytszToJulian(MM, DD, YY, TT, SS, ZZ)-rRound;
        ciCore = ciMain;
        for (i = 0; i <= cObjOpt; i++) {
            ignoreT[i] = ignore[i];
            if (us.fSector || us.fAstroGraph)
                ignore[i] = ignore[i] && ignore3[i];
            else
                ignore[i] = ignore3[i];
        }
    }
    if (us.fRelocation && us.nRel == rcComposite) {
        OO=us.lonDef;
        AA=us.latDef ;
        NN=us.altDef;
    }

    t2 = CastChart(fTrue);
    if (us.nRel == rcTransit) {
        for (i = 0; i <= cObjOpt; i++) {
            ignore2[i] = ignore[i];
            ignore[i] = ignoreT[i];
        }
    } else if (us.nRel == rcProgress) {
        us.fProgress = fFalse;
        for (i = 0; i <= cObjOpt; i++) {
            ignore3[i] = ignore[i];
            ignore[i] = ignoreT[i];
        }
    }
    cp2 = cp0;

    if (us.nRel == rcDual) {
        if (!FCreateGrid(fFalse))
            return;
        for (i = 0; i <= oNormOpt; i++)
            ppowerT[i] = ppower1[i];
        PlanetPPower();
        for (i = 0; i <= oNormOpt; i++) {
            ppower2[i] = ppower1[i];
            ppower1[i] = ppowerT[i];
        }
    }

    hRevers = saveRev;
    ciCore = ciMain;

    /* Now combine the two charts based on what relation we are doing.   */
    /* For the standard -r synastry chart, use the house cusps of chart1 */
    /* and the planets positions of chart2.                              */

    ratio = (real)us.nRatio1 / ((real)(us.nRatio1 + us.nRatio2));
    if (us.nRel <= rcSynastry) {
        for (i = 1; i <= cSign; i++)
            chouse[i] = cp1.cusp[i];

        /* For the -rc composite chart, take the midpoints of the planets/houses. */

    } else if (us.nRel == rcComposite) {
        if (fProgressRatio) {
            ratio=(MdytszToJulian(ciThre.mon,ciThre.day,ciThre.yea,ciThre.tim,ciThre.dst,ciThre.zon)-
                   Min(MdytszToJulian(Mon, Day, Yea, Tim, Dst, Zon),
                       MdytszToJulian(ciTwin.mon,ciTwin.day,ciTwin.yea,ciTwin.tim,ciTwin.dst,ciTwin.zon)))/
                  RAbs(MdytszToJulian(Mon, Day, Yea, Tim, Dst, Zon)-
                       MdytszToJulian(ciTwin.mon,ciTwin.day,ciTwin.yea,ciTwin.tim,ciTwin.dst,ciTwin.zon));
        }
        for (i = 0; i <= cObjOpt; i++) {
            planet[i] = Ratio(cp1.obj[i], cp2.obj[i], ratio);
            if (RAbs(cp2.obj[i] - cp1.obj[i]) > rDegHalf)
                planet[i] = Mod(planet[i] + rDegMax*ratio);
            planetalt[i] = Ratio(cp1.alt[i], cp2.alt[i], ratio);
            ret[i] = Ratio(cp1.dir[i], cp2.dir[i], ratio);
            altret[i] = Ratio(cp1.altdir[i], cp2.altdir[i], ratio);
            planetdis[i] = Ratio(cp1.dis[i], cp2.dis[i], ratio);
            disret[i] = Ratio(cp1.disdir[i], cp2.disdir[i], ratio);
        }
        for (i = 1; i <= cSign; i++) {
            chouse[i] = Ratio(cp1.cusp[i], cp2.cusp[i], ratio);
            if (RAbs(cp2.cusp[i] - cp1.cusp[i]) > rDegHalf)
                chouse[i] = Mod(chouse[i] + rDegMax*ratio);
        }

        /* Make sure we don't have any 180 degree errors in house cusp    */
        /* complement pairs, which may happen if the cusps are far apart. */

        for (i = 1; i <= cSign; i++)
            if (MinDistance(chouse[sCap], Mod(chouse[i]-ZFromS(i+3))) > rDegQuad)
                chouse[i] = Mod(chouse[i]+rDegHalf);
        for (i = 1; i <= cSign; i++)
            if (RAbs(MinDistance(chouse[i], planet[oAsc - 1 + i])) > rDegQuad)
                planet[oAsc - 1 + i] = Mod(planet[oAsc - 1 + i]+rDegHalf);

        ciMain.loc="";
        if (!us.fGraphics)
            ciMain.nam=strdup(strcat(strcat(ciMain.nam," and "),ciTwin.nam));

        /* For the -rm time space midpoint chart, calculate the midpoint time and */
        /* place between the two charts and then recast for the new chart info.   */

    } else if (us.nRel == rcMidpoint) {
        if (!is.fDavison) {
            is.T = Ratio(t1, t2, ratio);
            t = (is.T*36525.0)+rRound;
            is.JD = RFloor(t)+2415020.0;
            TT = RFract(t)*24.0;
            /*  ZZ = Ratio(DecToDeg(Zon), DecToDeg(ciTwin.zon), ratio);
              SS = Ratio(DecToDeg(Dst), DecToDeg(ciTwin.dst), ratio);
              TT -= ZZ - SS;
              if (TT < 0.0) {
                TT += 24.0; is.JD -= 1.0;
              }
              if (TT >= 24.0) {
                TT -= 24.0; is.JD += 1.0;
              }*/
            JulianToMdy(is.JD, &MM, &DD, &YY);
            OO = Ratio(DecToDeg(Lon), DecToDeg(ciTwin.lon), ratio);
            if (RAbs(ciTwin.lon-Lon) > rDegHalf)
                OO = Mod(OO+rDegMax*ratio);
            AA = Ratio(DecToDeg(Lat), DecToDeg(ciTwin.lat), ratio);
            NN = Ratio(DecToDeg(Alt), DecToDeg(ciTwin.alt), ratio);
            TT = DegToDec(TT);
            SS=ZZ=0.0; /*SS = DegToDec(SS); ZZ = DegToDec(ZZ);*/
            OO = DegToDec(OO);
            AA = DegToDec(AA);
            ciCore.loc="";
            if (!us.fGraphics)
                ciCore.nam=strdup(strcat(strcat(ciMain.nam," and "),ciTwin.nam));
            ciMain = ciCore;
        }
        else is.T=t1;
        CastChart(fFalse);
        is.fDavison=fTrue;
        /* There are a couple of non-astrological charts, which only require the */
        /* number of days that have passed between the two charts to be done.    */

    } else
        is.JD = RAbs(t2-t1)*36525.0;
    ComputeInHouses();
}