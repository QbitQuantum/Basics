/* 
 **************************************************************
 * Prototype: ZOLTAN_NUM_EDGES_MULTI_FN
 * Return the number of edges for each vertex in the ID lists.
 * For graph methods.
 **************************************************************
 */
static void get_num_edges_list(void *data, int sizeGID, int sizeLID,
                               int num_obj,
                               ZOLTAN_ID_PTR globalID, ZOLTAN_ID_PTR localID,
                               int *numEdges, int *ierr)
{
    UZData *uz = (UZData *) data;
    int i, id, r, c, r2, c2, edgecnt, e;
    
    if ( (sizeGID != 1) || (sizeLID != 1)){
        *ierr = ZOLTAN_FATAL;
        return;
    }
    
    for (i=0;  i < num_obj ; ++i){
        id = globalID[i];
        r = getR(id);
        c = getC(id);

        if (r==0 || c==0 || r==(uz->meshR-1) || c==(uz->meshC-1)) {
            /* we can probably do much smarter thing bu since
               we're not going to time graph generation time,
               simply run through over edges and see how many edges
               it will have. */
            edgecnt = 0;
            for (e=0; e<uz->stencil; ++e) {
                r2 = r+neig[e].r;
                c2 = c+neig[e].c;
                
                if (r2>=0 && r2<uz->meshR &&
                    c2>=0 && c2<uz->meshC)
                    ++edgecnt;
            }
            numEdges[i] = edgecnt;
        } else /* internal vertices always have all the edges */
            numEdges[i] = uz->stencil;
        if (uz->redgeto && (uz->redgeto[i]>=0))
            ++numEdges[i];        
    }
    
    *ierr = ZOLTAN_OK;
}