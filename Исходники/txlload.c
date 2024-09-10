/*ARGSUSED*/
int
TXLload(GENmodel *inModel, CKTcircuit *ckt)
{
	TXLmodel *model = (TXLmodel *)inModel;
	TXLinstance *here;
	TXLine *tx, *tx2;
	int k, l;
	int time, time2;
	double h, h1, f;
	int hint;
	double hf;
	NODE *nd;
	double v, v1, g;
	int cond1;
	CKTnode	*node;
	VI_list_txl *vi, *vi_before;
	int i, before, delta;

	double gmin;	 /* dc solution	*/

	/* debug 
	printf("before txlload\n");
	SMPprint(ckt->CKTmatrix, NULL);
	*/

	h = ckt->CKTdelta;
	h1 = 0.5 * h;
	time2 =	(int) (ckt->CKTtime * 1e12);
	hint = (int)(h * 1e12);
	hf = h * 1e12;
	time = (int) ((ckt->CKTtime - ckt->CKTdelta) * 1e12);

	cond1= ckt->CKTmode & MODEDC;

	gmin = 0.1 * ckt->CKTgmin;     /* dc solution */

	for( ; model !=	NULL; model = model->TXLnextModel ) {
		for (here = model->TXLinstances; here != NULL ; 
			here=here->TXLnextInstance) { 

			tx = here->txline;

			*here->TXLposPosptr += gmin; /* dc solution */
			*here->TXLnegNegptr += gmin;
			*here->TXLnegPosptr += gmin;
			*here->TXLposNegptr += gmin;

			if (cond1 || tx->vi_head == NULL) continue;

			if (time < tx->vi_tail->time) {
				time = tx->vi_tail->time;
				hint = time2 - time;
			}

			vi_before = tx->vi_tail;
			before = tx->vi_tail->time;

			if (time > tx->vi_tail->time) {

				copy_tx(tx, here->txline2);
				add_new_vi_txl(here, ckt, time);

				delta =	time - before;

				nd = tx->in_node;
				v = vi_before->v_i;
				nd->V =	tx->vi_tail->v_i;
				v1 = nd->V;
				nd->dv = (v1 - v) / delta;

				nd = tx->out_node;
				v = vi_before->v_o;
				v1 = nd->V = tx->vi_tail->v_o;
				nd->dv = (v1 - v) / delta;

				if (tx->lsl) continue;
				update_cnv_txl(tx, delta);
				if (tx->ext) update_delayed_cnv_txl(tx,	delta);
			}
		}
	}

    model = (TXLmodel *)inModel;
    for( ; model != NULL; model	= model->TXLnextModel )	{
	for (here = model->TXLinstances; here != NULL ;	
			here=here->TXLnextInstance) { 

			tx = here->txline;
			tx2 = here->txline2;

			if (!tx->lsl &&	hf > tx->taul) {

				fprintf(stderr, "your time step is too large for TXL tau.\n");
/*				fprintf(stderr, "please decrease max time	step in	.tran card.\n");
				fprintf(stderr, ".tran tstep tstop tstart	tmax.\n");
				fprintf(stderr, "make tmax smaller than %e and try again.\n",
				tx->taul * 1e-12);
				return (1111);
*/
				fprintf(stderr,	"tmax is now set to	%e.\n", 0.9 * tx->taul * 1e-12);
				ckt->CKTmaxStep = 0.9 * tx->taul * 1e-12;

			}

			if (cond1) {
				if (here->TXLlengthgiven) 
					g = model->R * here->TXLlength;
				else g = model->R * here->TXLmodPtr->length;
				*(here->TXLposIbr1ptr) += 1.0;
				*(here->TXLnegIbr2ptr) += 1.0;
				*(here->TXLibr1Ibr1ptr)	+= 1.0;
				*(here->TXLibr1Ibr2ptr)	+= 1.0;
				*(here->TXLibr2Posptr) += 1.0;
				*(here->TXLibr2Negptr) -= 1.0;
				*(here->TXLibr2Ibr1ptr)	-= g;

				continue;

			}

			/* dc setup */
			if (here->TXLdcGiven ==	0 && !cond1) {
				nd = tx->in_node;
				for (node = ckt->CKTnodes;node;	node = node->next) {
					if (strcmp(nd->name->id, node->name) ==	0) {
						tx->dc1	= tx2->dc1 = ckt->CKTrhsOld[node->number]; 
						nd->V =	tx->dc1;
						break;
					}
				}
				nd = tx->out_node;
				for (node = ckt->CKTnodes;node;	node = node->next) {
					if (strcmp(nd->name->id, node->name) ==	0) {
						tx->dc2	= tx2->dc2 = ckt->CKTrhsOld[node->number]; 
						nd->V =	tx->dc2;
						break;
					}
				}
				here->TXLdcGiven = 1;

				vi = new_vi_txl();
				vi->time = 0;

				vi->i_i	= *(ckt->CKTrhsOld + here->TXLibr1);
				vi->i_o	= *(ckt->CKTrhsOld + here->TXLibr2);

				vi->v_i	= tx->dc1;
				vi->v_o	= tx->dc2;

				for (i = 0; i <	3; i++)	{
					tx->h1_term[i].cnv_i = 
					   - tx->dc1 * tx->h1_term[i].c	/ tx->h1_term[i].x;
					tx->h1_term[i].cnv_o = 
					   - tx->dc2 * tx->h1_term[i].c	/ tx->h1_term[i].x;
				}
				for (i = 0; i <	3; i++)	{
					tx->h2_term[i].cnv_i = 0.0;
					tx->h2_term[i].cnv_o = 0.0;
				}
				for (i = 0; i <	6; i++)	{
					tx->h3_term[i].cnv_i = 
				    - tx->dc1 *	tx->h3_term[i].c / tx->h3_term[i].x;
					tx->h3_term[i].cnv_o = 
				    - tx->dc2 *	tx->h3_term[i].c / tx->h3_term[i].x;
				}
				vi->next = NULL;
				tx->vi_tail = vi;
				tx->vi_head = vi;
				here->txline2->vi_tail = vi;
				here->txline2->vi_head = vi;

			}

			/* change 6,6	 1/18/93 
			*(here->TXLibr1Ibr1ptr)	-= 1.0;	
			*(here->TXLibr2Ibr2ptr)	-= 1.0;
	    *(here->TXLposIbr1ptr) += 1.0;
	    *(here->TXLnegIbr2ptr) += 1.0;
	    *(here->TXLibr1Posptr) += tx->sqtCdL + h1 *	tx->h1C;
			*(here->TXLibr2Negptr) += tx->sqtCdL + h1 * tx->h1C;
			*/
			*(here->TXLibr1Ibr1ptr)	= -1.0;	
			*(here->TXLibr2Ibr2ptr)	= -1.0;
	    *(here->TXLposIbr1ptr) = 1.0;
	    *(here->TXLnegIbr2ptr) = 1.0;
	    *(here->TXLibr1Posptr) = tx->sqtCdL	+ h1 * tx->h1C;
			*(here->TXLibr2Negptr) = tx->sqtCdL + h1 * tx->h1C;

			k = here->TXLibr1;
			l = here->TXLibr2;

			copy_tx(tx2, tx);

			if (right_consts_txl(tx2, time,	time2, h, h1, k, l, ckt)) {
				if (tx->lsl) {
					f = ratio[0] * tx->h3_aten;
					*(here->TXLibr1Negptr) = -f;
					*(here->TXLibr2Posptr) = -f;
					f = ratio[0] * tx->h2_aten;
					*(here->TXLibr1Ibr2ptr)	= -f;
					*(here->TXLibr2Ibr1ptr)	= -f;
				}
				else {
					tx->ext	= 1;
					tx->ratio = ratio[0];
					if (ratio[0] > 0.0) {
						f = ratio[0] * (h1 * (tx->h3_term[0].c 
							+ tx->h3_term[1].c + tx->h3_term[2].c 
							+ tx->h3_term[3].c + tx->h3_term[4].c
							+ tx->h3_term[5].c ) + tx->h3_aten);
						*(here->TXLibr1Negptr) = -f;
						*(here->TXLibr2Posptr) = -f;
						f = ratio[0] * (h1 * ( tx->h2_term[0].c	
							+ tx->h2_term[1].c + tx->h2_term[2].c )	
							+ tx->h2_aten);
						*(here->TXLibr1Ibr2ptr)	= -f;
						*(here->TXLibr2Ibr1ptr)	= -f;
					}
				}
			} 
			else tx->ext = 0;
	}
    }

	if (cond1) return (OK);

	/* debug 
	printf("after txlload\n");
	SMPprint(ckt->CKTmatrix, NULL);
	*/

    return(OK);
}