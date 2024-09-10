static void
dirashik(		/* compute source contribution */
	COLOR  cval,		/* returned coefficient */
	void  *nnp,		/* material data */
	FVECT  ldir,		/* light source direction */
	double  omega		/* light source size */
)
{
	ASHIKDAT *np = nnp;
	double  ldot;
	double  dtmp, dtmp1, dtmp2;
	FVECT  h;
	COLOR  ctmp;

	setcolor(cval, 0.0, 0.0, 0.0);

	ldot = DOT(np->pnorm, ldir);

	if (ldot < 0.0)
		return;		/* wrong side */

	/*
	 *  Compute and add diffuse reflected component to returned
	 *  color.
	 */
	copycolor(ctmp, np->mcolor);
	dtmp = ldot * omega * (1.0/PI) * (1. - schlick_fres(ldot));
	scalecolor(ctmp, dtmp);		
	addcolor(cval, ctmp);

	if ((np->specfl & (SPA_REFL|SPA_BADU)) != SPA_REFL)
		return;
	/*
	 *  Compute specular reflection coefficient
	 */
					/* half vector */
	VSUB(h, ldir, np->rp->rdir);
	normalize(h);
					/* ellipse */
	dtmp1 = DOT(np->u, h);
	dtmp1 *= dtmp1 * np->u_power;
	dtmp2 = DOT(np->v, h);
	dtmp2 *= dtmp2 * np->v_power;
					/* Ashikhmin-Shirley model*/
	dtmp = DOT(np->pnorm, h);
	dtmp = pow(dtmp, (dtmp1+dtmp2)/(1.-dtmp*dtmp));
	dtmp *= sqrt((np->u_power+1.)*(np->v_power+1.));
	dtmp /= 8.*PI * DOT(ldir,h) * MAX(ldot,np->pdot);
					/* worth using? */
	if (dtmp > FTINY) {
		copycolor(ctmp, np->scolor);
		dtmp *= ldot * omega;
		scalecolor(ctmp, dtmp);
		addcolor(cval, ctmp);
	}
}