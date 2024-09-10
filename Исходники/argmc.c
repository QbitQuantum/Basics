void volume_move(){
    total_vol_moves+=1.0;
    float old_e = total_energy(old_argons);
    float old_vol = powf(L,3);
    float new_vol = expf(logf(old_vol) + (random() - 0.5)*VOL_MOVE);
    float new_L = cbrtf(new_vol);
    for(size_t i = NA; i>0;i--){
        new_argons[i].x*=(new_L/L);
        new_argons[i].y*=(new_L/L);
        new_argons[i].z*=(new_L/L);
    }
    float new_e = total_energy(new_argons);
    if (random()<expf(-(1.0/(KB *TEMPERATURE))*((new_e - old_e) + (PRESSURE*(new_vol- old_vol)) - ((NA+1)*(KB*TEMPERATURE)*logf(new_vol/old_vol))))){
        accepted_vol_moves +=1.0;
        memcpy(old_argons, new_argons, sizeof(new_argons));
        L=new_L;
    } else{
        memcpy(new_argons,old_argons,sizeof(new_argons));
    }
}