void pnorm(struct pnorm_state_t *state, uint16_t length, struct complex_sample *in,
            struct complex_sample *out, float *ests, float *gains) {
    int i ;
    float power;
    int32_t temp;
    float gain, est;

    for( i = 0 ; i < length ; i++ ) {
        /* Power IIR filter */
        if( state->hold == false ) {
            //New estimate of power (normalized)
            est = state->est = state->alpha*state->est +
                state->invalpha*(in[i].i*in[i].i + in[i].q*in[i].q)/(SAMP_MAX_ABS*SAMP_MAX_ABS);
        } else {
            est = state->est ;
        }

        /* Ideal power is 1.0, so to get x to 1.0, we need to multiply by 1/est */
        gain = 1.0f/sqrtf(state->est) ;

        /* Check below min gain */
        if( gain < state->min_gain ) {
            gain = state->min_gain ;
        }

        /* Check above max gain */
        if( gain > state->max_gain ) {
            gain = state->max_gain ;
        }

        /* Apply gain */
        //Use temp int32_t in case this number goes outside 16bit range
        temp = (int32_t) round(in[i].i * gain);
        //Clamp
        if (temp > CLAMP_VAL_ABS){
            temp = CLAMP_VAL_ABS;
        }else if (temp < -CLAMP_VAL_ABS){
            temp = -CLAMP_VAL_ABS;
        }
        out[i].i = (int16_t) temp;

        temp = (int32_t) round(in[i].q * gain);
        //Clamp
        if (temp > CLAMP_VAL_ABS){
            temp = CLAMP_VAL_ABS;
        }else if (temp < -CLAMP_VAL_ABS){
            temp = -CLAMP_VAL_ABS;
        }
        out[i].q = (int16_t) temp;

        /* Blank impulse power */
        power = (out[i].i * out[i].i + out[i].q * out[i].q)/(float)(SAMP_MAX_ABS*SAMP_MAX_ABS);
        if (power >= 10.0f) {
            out[i].i = out[i].q = 0;
        }

        //Write to debug buffers
        if (ests != NULL){
            ests[i] = est;
        }
        if (gains != NULL){
            gains[i] = gain;
        }
    }
    return ;
}