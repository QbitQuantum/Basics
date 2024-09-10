static void LIQSS2_recomputeNextTimes(uinteger STATES, LIQSS2_quantizerState p, modelica_real t, modelica_real ft, int dt_index){
    modelica_real diffQ = 0, timeaux = 0;
    uinteger i =0, j =0;
    for(j=0;j<p->nSD[dt_index];j++){
        i= p->SD[dt_index][j];
    // for(j=0;j<STATES;j++){
    //     i=j;
        // if(t>0.00001 && t<0.00001001){
        //     printf("i:  %d\n", i);
        //     printf("t:  %.20f\n", t);
        //     printf("p->nTime[i]:   %.20f \n", p->nTime[i]);
        // }
        if(1){
            // printf("LIQSS2_recomputeNextTimes\n");
            // printf("i:   %d\n", i);
            // printf("t:   %.20f\n", t);
            // printf("p->nTime[i]:   %.20f\n", p->nTime[i]);
            // printf("p->q[i][1]:   %.20f \n", p->q[i][1]);
            // printf("p->x[i][1]:   %.20f \n", p->x[i][1]);
        }
        if(p->ltq[i] == t){
            diffQ = p->q[i][0] - p->qAux[i];
            if(fabs(diffQ) > p->lqu[i] * 1e-6){
                p->a[i] = (p->x[i][1] - p->oldDx[i]) / diffQ;
                if(p->a[i] > 0)
                    p->a[i] = 0;

                // printf("! a[var]: %.20f\n", p->a[i]);
                // printf("! x[cf1]: %.20f\n", p->x[i][1]);
                // printf("! oldDx[var]: %.20f\n", p->oldDx[i]);
                // printf("! diffQ: %.20f\n", diffQ);
            }
        }
        else
            p->flag3[i] = false;

        p->u0[i] = p->x[i][1] - p->q[i][0] * p->a[i];
        p->u1[i] = 2 * p->x[i][2] - p->q[i][1] * p->a[i];
        p->lt[i] = t;
        if(p->flag4[i])
            p->nTime[i] = t;
        else{
            p->diffxq[i][1] = p->q[i][1] - p->x[i][1];
        //     if(1){
            // printf("p->q[i][1] %.20f\n", p->q[i][1]);
            // printf("p->x[i][1] %.20f\n", p->x[i][1]);
        //     printf("p->diffxq[i][1] %.20f\n", p->diffxq[i][1]);
        // }
            p->diffxq[i][2] = -p->x[i][2];
            p->diffxq[i][0] = p->q[i][0] - p->dq[i] + p->lqu[i] - p->x[i][0];
            p->nTime[i] = t + minRootPos(p->diffxq,i,2);
            // printf("nTime[var]: %.20f\n", p->nTime[i]);
            p->diffxq[i][0] = p->q[i][0] - p->dq[i] - p->lqu[i] - p->x[i][0];
            timeaux = t + minRootPos(p->diffxq,i,2);
            // printf("timeaux: %.20f\n", timeaux);
            if(timeaux < p->nTime[i])
                p->nTime[i] = timeaux;
            if(p->a[i] != 0 && fabs(p->x[i][2]) > 1e-10 && !p->flag3[i] && !p->flag2[i]){
                modelica_real coeff[2];
                coeff[0] = p->a[i] * p->a[i] * p->q[i][0] + p->a[i] * p->u0[i] + p->u1[i];
                coeff[1] = p->a[i] * p->a[i] * p->q[i][1] + p->a[i] * p->u1[i];
                // printf("coeff[0] %.20f\n", coeff[0]);
                // printf("coeff[1] %.20f\n", coeff[1]);
                timeaux = t + minRootPosCoeff(&coeff, i, 1);
                // printf("??timeaux: %.20f\n", timeaux);
                if(timeaux < p->nTime[i]){
                    p->flag2[i] = true;
                    p->nTime[i] = timeaux;
                    p->lquOld[i] = p->lqu[i];
                }
            }
            else
                p->flag2[i] = false;

            if(p->nTime[i] > ft)
                p->nTime[i] = ft;

            modelica_real err1 = p->q[i][0] - p->x[i][0] + (p->diffxq[i][1] * (p->nTime[i] - t) / 2) + p->diffxq[i][2] * pow ((p->nTime[i] - t) / 2, 2);
            if (fabs (err1) > 3 * fabs (p->lqu[i])){
                // printf("var: %d\n", i);
                // printf("err1 %.20f\n", err1);

                // printf("t %.20f\n\n", t);
                // printf("lqu[var] %.20f\n", p->lqu[i]);
        	    p->nTime[i] = t + ft * 1.0e-14;
        	}
        }
        // if(t>0.00001 && t<0.00001001){
        //     //printf("Now we are in LIQSS2_recomputeNextTimes\n");
        //     //printf("We are considering the case where i=6\n");
        //     printf("p->nTime[i]:   %.20f \n", p->nTime[i]);
        //     printf("p->diffxq[i][1]:   %.20f \n", p->diffxq[i][1]);
        //     printf("p->diffxq[i][2]:   %.20f \n", p->diffxq[i][2]);
        //     printf("p->diffxq[i][0]:   %.20f \n", p->q[i][0] - p->dq[i] + p->lqu[i] - p->x[i][0]);
        //     printf("p->diffxq[i][0]:   %.20f \n", p->q[i][0] - p->dq[i] - p->lqu[i] - p->x[i][0]);
        // }
        if(1){
            //printf("Now we are in LIQSS2_recomputeNextTimes\n");
            //printf("We are considering the case where i=6\n");
            // printf("p->q[i][0]:   %.20f \n", p->q[i][0]);
            // printf("p->dq[i]:   %.20f \n", p->dq[i]);
            // printf("p->lqu[i]:   %.20f \n", p->lqu[i]);
            // printf("p->x[i][0]:   %.20f \n", p->x[i][0]);
            // //
            // printf("p->nTime[i]:   %.20f \n", p->nTime[i]);
            // printf("p->diffxq[i][1]:   %.20f \n", p->diffxq[i][1]);
            // printf("p->diffxq[i][2]:   %.20f \n", p->diffxq[i][2]);
            // printf("p->diffxq[i][0]:   %.20f \n", p->q[i][0] - p->dq[i] + p->lqu[i] - p->x[i][0]);
            // printf("p->diffxq[i][0]:   %.20f \n\n", p->q[i][0] - p->dq[i] - p->lqu[i] - p->x[i][0]);
        }
    }
}