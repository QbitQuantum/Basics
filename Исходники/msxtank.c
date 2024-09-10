void  MSXtank_mix2(int i, double vIn, double cIn[], long dt)
/*
**   Purpose: 2-compartment tank model                      
**
**   Input:   i = tank index
**            vIn = volume of inflow to tank (ft3)
**            cIn[] = concen. of inflow to tank
**            dt = current WQ time step (sec)
*/
{
    int     k, m, n;
    long    tstep,                     // Actual time step taken
            tstar;                     // Time to fill or drain a zone
    double  qIn,                       // Inflow rate
            qOut,                      // Outflow rate
            qNet;                      // Net flow rate
    double  c, c1, c2;                 // Species concentrations
    Pseg    seg1,                      // Mixing zone segment
            seg2;                      // Ambient zone segment

// --- find inflows & outflows 

    n = MSX.Tank[i].node;
    qNet = MSX.D[n];
    qIn = vIn/(double)dt;
    qOut = qIn - qNet;

// --- get segments for each zone

    k = MSX.Nobjects[LINK] + i;
    seg1 = MSX.FirstSeg[k];
    seg2 = MSX.LastSeg[k];

// --- case of no net volume change

    if ( fabs(qNet) < TINY ) return;

// --- case of net filling (qNet > 0)

    else if (qNet > 0.0)
    {

    // --- case where ambient zone empty & mixing zone filling 

        if (seg2->v <= 0.0)
        {
        // --- time to fill mixing zone
            tstar = (long) ((MSX.Tank[i].vMix - (seg1->v))/qNet);
            tstep = MIN(dt, tstar);

            for (m=1; m<=MSX.Nobjects[SPECIES]; m++)
            {
                if ( MSX.Species[m].type != BULK ) continue;

            // --- new quality in mixing zone
                c = seg1->c[m]; 
                if (seg1->v > 0.0) seg1->c[m] += qIn*tstep*(cIn[m]-c)/(seg1->v);
                else seg1->c[m] = cIn[m];
                seg1->c[m] = MAX(0.0, seg1->c[m]);
                seg2->c[m] = 0.0;
            }

        // --- new volume of mixing zone
            seg1->v += qNet*tstep;

        // --- time during which ambient zone fills
            dt -= tstep;
        }

    // --- case where mixing zone full & ambient zone filling 
        if (dt > 1)
        {
            for (m=1; m<=MSX.Nobjects[SPECIES]; m++)
            {
                if ( MSX.Species[m].type != BULK ) continue;

            // --- new quality in mixing zone
                c1 = seg1->c[m]; 
                seg1->c[m] += qIn * dt * (cIn[m] - c1) / (seg1->v);
                seg1->c[m] = MAX(0.0, seg1->c[m]);

            // --- new quality in ambient zone
		        c2 = seg2->c[m];
                if (seg2->v <= 0.0)
                    seg2->c[m] = seg1->c[m];
                else
                    seg2->c[m] += qNet * dt * ((seg1->c[m]) - c2) / (seg2->v);
                seg2->c[m] = MAX(0.0, seg2->c[m]);
	        }

        // --- new volume of ambient zone
            seg2->v += qNet*dt;
        }
        if ( seg1->v > 0.0 ) MSXchem_equil(NODE, seg1->c);
        if ( seg2->v > 0.0 ) MSXchem_equil(NODE, seg2->c);
    }

// --- case of net emptying (qnet < 0)

    else if ( qNet < 0.0 && seg1->v > 0.0 )
    {

    // --- case where mixing zone full & ambient zone draining

        if ((seg2->v) > 0.0)
        {

        // --- time to drain ambient zone
            tstar = (long)(seg2->v/-qNet);
            tstep = MIN(dt, tstar);

            for (m=1; m<=MSX.Nobjects[SPECIES]; m++)
            {
                if ( MSX.Species[m].type != BULK ) continue;
	            c1 = seg1->c[m];
	            c2 = seg2->c[m];

            // --- new mizing zone quality (affected by both external inflow
            //     and drainage from the ambient zone
                seg1->c[m] += (qIn*cIn[m] - qNet*c2 - qOut*c1)*tstep/(seg1->v);
                seg1->c[m] = MAX(0.0, seg1->c[m]);
	        }

        // --- new ambient zone volume
            seg2->v += qNet*tstep;
            seg2->v = MAX(0.0, seg2->v);

        // --- time during which mixing zone empties
            dt -= tstep;
        }

    // --- case where ambient zone empty & mixing zone draining

        if (dt > 1)
        {
            for (m=1; m<=MSX.Nobjects[SPECIES]; m++)
            {
                if ( MSX.Species[m].type != BULK ) continue;

            // --- new mixing zone quality (affected by external inflow only)
		        c = seg1->c[m];
                seg1->c[m] += qIn*dt*(cIn[m]-c)/(seg1->v);
                seg1->c[m] = MAX(0.0, seg1->c[m]);
                seg2->c[m] = 0.0;
	        }

        // --- new volume of mixing zone
            seg1->v += qNet*dt;
            seg1->v = MAX(0.0, seg1->v);
        }
        if ( seg1->v > 0.0 ) MSXchem_equil(NODE, seg1->c);
    }

// --- use quality of mixed compartment (seg1) to represent quality
//     of tank since this is where outflow begins to flow from

    for (m=1; m<=MSX.Nobjects[SPECIES]; m++) MSX.Tank[i].c[m] = seg1->c[m];
}