void uhc_summarize_results(
    int num_genes,
    int num_chromosomes,
    int num_genomes,
    int circular,
    struct genome_struct *genome_list_in,
    int nsegs,
    int *seg_list,

    /* output */
    struct uhc_mem *uhcmem,
    struct genome_struct *out_genome
)
{
    int d;

    int count;
    int s1, s2;
    int bestd, num_best;
    int k;

    int *curseg;
    int cur_len;
    int cur_genome_num;
    struct genome_struct *cur_genome = (struct genome_struct *) 0;

    int *sign_groups;

    int i1,i2,max_entry;
    int *dmat = uhcmem->dmat;

    /**********************************************************************
     * Calc sign groups
     **********************************************************************/
    //printf("uhc_summarize_results\n");
    sign_groups = (int *) e_malloc(nsegs * sizeof(int),
                                   "uhc_summarize_results: sign_groups");
    calc_sign_groups(sign_groups,
                     uhcmem);



    //printf("STOP_1\n");
    /**********************************************************************
     * # runs at each distance
     **********************************************************************/

    //f//printf(outfile, "\n# trials giving each score:\n");
    /*f//printf(outfile, "%*s  # times\n",
    uhcmem->width_score2, "score");*/
    for (d=0; d < uhcmem->max_dist_possible; d++) {
    if (uhcmem->dist_counts[d] > 0) {
            /*f//printf(outfile, "%*d  %d\n",
            uhcmem->width_score2, d,
                   uhcmem->dist_counts[d]);*/
        }
    }
    if (uhcmem->dist_counts[uhcmem->max_dist_possible] != 0) {
        /* TODO: improve handling of this for arbitrary weight matrices */
        /*f//printf(outfile, "%*s  %d\n",
        uhcmem->width_score2, "other",
        uhcmem->dist_counts[uhcmem->max_dist_possible]);*/
    }

    //printf("STOP_2\n");
    /**********************************************************************
     * at best dist: sign pattern
     **********************************************************************/

    bestd = uhcmem->best_dist;
    num_best = uhcmem->dist_counts[bestd];

    //f//printf(outfile, "\n");
    //printf("STOP_3\n");
    /**********************************************************************
     * at best dist: perfect correlation groups
     **********************************************************************/

    //f//printf(outfile, "\n");
    //printf("STOP_4\n");
    /**********************************************************************
     * at best dist: sign counts
     **********************************************************************/

    //f//printf(outfile,"\nSign counts and perfect correlations:\n");
    cur_genome_num = -1;
    for (s1 = 0; s1 < nsegs; s1++) {
    curseg = USEG(seg_list, s1);

        /* print genome name if switched genomes */
        if (curseg[0] != cur_genome_num) {
            cur_genome_num = curseg[0];
            cur_genome = &genome_list_in[cur_genome_num];
            if (cur_genome->gnamePtr != (char *) 0) {
                //f//printf(outfile, ">%s\n", cur_genome->gnamePtr);
            } else {
                //f//printf(outfile, ">genome%d\n", cur_genome_num + 1);
            }
        }

        cur_len = curseg[2];

        //f//printf(outfile, "S%-*d  [", uhcmem->width_segnum, s1);
        for (k=0; k<cur_len; k++) {
            //f//printf(outfile, " %d", cur_genome->genes[cur_start+k]);
        }
        //f//printf(outfile," ]   ");

        count = uhcmem->dist_corr[s1*nsegs+s1];
        /*f//printf(outfile,
        "%d+  %d-  "
        ,
        count, num_best-count);*/

        count = sign_groups[s1];
        if (count == -1-nsegs) {
        //f//printf(outfile, "sign -");
    } else if (count == nsegs) {
        //f//printf(outfile, "sign +");
    } else if (count == s1) {
    } else if (count >= 0) {
        //f//printf(outfile, "sign same as S%d", count);
    } else if (count < 0) {
        //f//printf(outfile, "sign same as -S%d", -1-count);
    }

    //f//printf(outfile, "\n");
}
//printf("STOP_5\n");
/**********************************************************************
 * at best dist: detailed correlations
 **********************************************************************/

//f//printf(outfile,"\nCorrelations: Number of times segments have same sign:\n");
for (s1=0; s1<nsegs; s1++) {
    //f//printf(outfile, "S%-*d  ", uhcmem->width_segnum, s1);
    for (s2=0; s2<nsegs; s2++) {
            if (s1 == s2) {
                count = num_best;
            } else if (s2<s1) {
                count = uhcmem->dist_corr[s2*nsegs+s1];
            } else {
                count = uhcmem->dist_corr[s1*nsegs+s2];
            }
            //f//printf(outfile, " %*d", uhcmem->width_run, count);
        }
        //f//printf(outfile, "\n");
    }
//printf("STOP_6\n");
    /**********************************************************************
     * at best dist: one particular signage
     **********************************************************************/

    //f//printf(outfile,"\nA best scoring solution:\n");

    uhc_setsigns(num_genes, num_chromosomes, num_genomes,
                 genome_list_in,
                 nsegs, seg_list, uhcmem->bestsigns,
                 uhcmem);

    /* Set the output genome */
    ////printf ("Genome list %u ", uhcmem);
    ////printf ("Genome list %d ", uhcmem->genome_list + 1);
    memcpy(out_genome, uhcmem->genome_list + 1, sizeof(struct genome_struct));
    out_genome->genes = malloc(sizeof(int) * num_genes);
    copy_genes((uhcmem->genome_list + 1)->genes, out_genome->genes, num_genes);

//printf("STOP_7\n");
    /**********************************************************************
     * and the pairwise matrix for that signage
     **********************************************************************/

    max_entry = 0;
    for (i1=0; i1<num_genomes; i1++) {
    dmat[num_genomes*i1 + i1] = 0;
        for (i2=0; i2<i1; i2++) {
            d =
                dmat[num_genomes*i1 + i2] =
                    dmat[num_genomes*i2 + i1] =
                        uhc_dist(uhcmem, i1, i2,
                                 num_genes, num_chromosomes, circular);
            if (d > max_entry) {
                max_entry = d;
            }
        }
    }
//printf("STOP_8\n");
    /* TODO: should integrate this with the other matrix printing routines */

    //DEBUG: deleted code here
}