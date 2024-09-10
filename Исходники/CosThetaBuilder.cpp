void CosThetaBuilder::buildArcCap(MixedSource& M, unsigned int zside, unsigned int nseg) {
    
    for(unsigned int xside = 0; xside < 2; xside++) {
        for(unsigned int yside = 0; yside < 2; yside++) {
            for(unsigned int i=0; i<ncoils-1; i++) {
                if(yside == zside)
                    M.arc(getEndp(i,xside,yside,zside),getEndp(i+1,xside,yside,zside),(i+1)*j_total/double(ncoils),nseg);
                else
                    M.arc(getEndp(i+1,xside,yside,zside),getEndp(i,xside,yside,zside),(i+1)*j_total/double(ncoils),nseg);
            }
        }
        M.arc(getEndp(ncoils-1,xside,zside,zside),getEndp(ncoils-1,xside,!zside,zside),j_total,nseg);
    }
}