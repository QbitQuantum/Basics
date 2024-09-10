void
Valve::processReplacing (float **inputs,
								float **outputs,
								int sampleFrames)
{
    int i;

    float l, r, lout, rout, fx;
	param->PERIOD = sampleFrames;
	param->fPERIOD = param->PERIOD;

    if (Pstereo != 0) {
        //Stereo
        for (i = 0; i < param->PERIOD; i++) {
            outputs[0][i] = inputs[0][i] * inputvol;
            outputs[1][i] = inputs[1][i] * inputvol;
        };
    } else {
        for (i = 0; i < param->PERIOD; i++) {
            outputs[0][i] =
                (inputs[0][i]  +  inputs[1][i] ) * inputvol;
        };
    };

    harm->harm_out(outputs[0],outputs[1]);


    if (Pprefiltering != 0)
        applyfilters (outputs[0], outputs[1]);

    if(Ped) {
        for (i =0; i<param->PERIOD; i++) {
            outputs[0][i]=Wshape(outputs[0][i]);
            if (Pstereo != 0) outputs[1][i]=Wshape(outputs[1][i]);
        }
    }

    for (i =0; i<param->PERIOD; i++) { //soft limiting to 3.0 (max)
        fx = outputs[0][i];
        if (fx>1.0f) fx = 3.0f - 2.0f/sqrtf(fx);
        outputs[0][i] = fx;
        fx = outputs[1][i];
        if (fx>1.0f) fx = 3.0f - 2.0f/sqrtf(fx);
        outputs[1][i] = fx;
    }

    if (q == 0.0f) {
        for (i =0; i<param->PERIOD; i++) {
            if (outputs[0][i] == q) fx = fdist;
            else fx =outputs[0][i] / (1.0f - powf(2.0f,-dist * outputs[0][i] ));
            otml = atk * otml + fx - itml;
            itml = fx;
            outputs[0][i]= otml;
        }
    } else {
        for (i = 0; i < param->PERIOD; i++) {
            if (outputs[0][i] == q) fx = fdist + qcoef;
            else fx =(outputs[0][i] - q) / (1.0f - powf(2.0f,-dist * (outputs[0][i] - q))) + qcoef;
            otml = atk * otml + fx - itml;
            itml = fx;
            outputs[0][i]= otml;

        }
    }


    if (Pstereo != 0) {

        if (q == 0.0f) {
            for (i =0; i<param->PERIOD; i++) {
                if (outputs[1][i] == q) fx = fdist;
                else fx = outputs[1][i] / (1.0f - powf(2.0f,-dist * outputs[1][i] ));
                otmr = atk * otmr + fx - itmr;
                itmr = fx;
                outputs[1][i]= otmr;

            }
        } else {
            for (i = 0; i < param->PERIOD; i++) {
                if (outputs[1][i] == q) fx = fdist + qcoef;
                else fx = (outputs[1][i] - q) / (1.0f - powf(2.0f,-dist * (outputs[1][i] - q))) + qcoef;
                otmr = atk * otmr + fx - itmr;
                itmr = fx;
                outputs[1][i]= otmr;

            }
        }

    }



    if (Pprefiltering == 0)
        applyfilters (outputs[0], outputs[1]);

    if (Pstereo == 0) memcpy (outputs[1] , outputs[0], param->PERIOD * sizeof(float));


    float level = dB2rap (60.0f * (float)Plevel / 127.0f - 40.0f);

    for (i = 0; i < param->PERIOD; i++) {
        lout = outputs[0][i];
        rout = outputs[1][i];


        l = lout * (1.0f - lrcross) + rout * lrcross;
        r = rout * (1.0f - lrcross) + lout * lrcross;

        lout = l;
        rout = r;

        outputs[0][i] = lout * 2.0f * level * panning;
        outputs[1][i] = rout * 2.0f * level * (1.0f -panning);

    };



};