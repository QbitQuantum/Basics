static int filledges(int lid, int *adjID, int *adjProc, UZData *uz)
{
    int *nextID = adjID, *ptr;
    int *nextProc = adjProc;
    int gid = gIDfLID(lid);
    int r = getR(gid), r2;
    int c = getC(gid), c2, e, j;

    /* printf(" %d (%d,%d) : ", id, r, c); */
    for (e=0; e<uz->stencil; ++e) {
        r2 = r+neig[e].r;
        c2 = c+neig[e].c;
            
        if (r2>=0 && r2<uz->meshR &&
            c2>=0 && c2<uz->meshC) {
            *nextID++ = gID(r2, c2);
            if (adjProc)
                *nextProc++ = pID(r2/(uz->meshR/uz->procR), c2/(uz->meshC/uz->procC));
                /* printf(" %d (%d, %d) [%d] ", *(nextID-1), r2, c2, *(nextProc-1)); */
            }
            
    }
    if (uz->redgeto && (uz->redgeto[lid]>=0)) {
        for (ptr=adjID; ptr<nextID && *ptr!=uz->redgeto[lid]; ++ptr);
        if (ptr>=nextID) {
            r2 = getR(uz->redgeto[lid]);
            c2 = getC(uz->redgeto[lid]);
            
            *nextID++ = uz->redgeto[lid];
            if (adjProc)
                *nextProc++ = pID(r2/(uz->meshR/uz->procR), c2/(uz->meshC/uz->procC));
            /* printf(" %d (%d, %d) [%d] ", *(nextID-1), r2, c2, *(nextProc-1)); */
        }
    }

    if (xadj) {
        for (j=xadj[lid]; j<xadj[lid+1]; ++j) {
            for (ptr=adjID; ptr<nextID && *ptr!=uz->redgeto[lid]; ++ptr);
            if (ptr>=nextID) {
                *nextID++ = adj[j];
                if (adjProc)
                    *nextProc++ = pIDfGID(adj[j]);
            }
        }
    }

    /* printf("\n"); */
    return nextID-adjID;
}