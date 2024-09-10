void sprintf_hb(char * o_str, int i, int j, struct vect nearest, float d, float ha, float daaa_ang, float haaa_ang)
{
    char      bndtyp[3], acctyp[4], dontyp[4], space=' ';
    int       ca_d, ri, rj, gap;
    char buf1[20],buf2[20]; /* buffers for atomid routines */
    float     tmp;
        
    /*we have a hydrogen bond!*/
    
    bndtyp[0] = bndtyp[1] = '?';
    acctyp[3] = dontyp[3] = bndtyp[2] = '\0';
    
    if (atom[i].aacode == TOTNAA || atom[i].hetflg )
	bndtyp[0] = 'H';
    else
    {
	if (atom[i].aacode <STDAA)
	{
	    bndtyp[0] = (atom[i].atmtyp <=3) ? 'M' : 'S';
	}
	else
	{
	    bndtyp[0] = (atom[i].atmtyp <=3) ? 'm' : 's';
	}
    }
    if (atom[j].aacode == TOTNAA || atom[j].hetflg )
	bndtyp[1] = 'H';
    else
    {
	if (atom[j].aacode <STDAA)
	{
	    bndtyp[1] = (atom[j].atmtyp <=3) ? 'M' : 'S';
	}
	else
	{
	    bndtyp[1] = (atom[j].atmtyp <=3) ? 'm' : 's';
	}
    }
 		
    ri = atom[i].caindex;
    rj = atom[j].caindex;
    
    gap=find_gap( ri, rj);
		
#if 0 		
    if (atom[i].aacode==TOTNAA || (ri == -99) || !residue[ri].ca ||                       atom[j].aacode==TOTNAA || (rj == -99) || !residue[rj].ca  )
	gap = -1;
    else
    {
	gap = cagap(ri,rj);
    }
#endif 		
    if (atom[i].aacode==TOTNAA || (ri == -99) || !residue[ri].ca ||  
	atom[j].aacode==TOTNAA || (rj == -99) || !residue[rj].ca  )
	ca_d = -1.0;
    else
    {
	ca_d = length_squared( to(*(residue[ri].ca),*(residue[rj].ca)) );
	
	if (ca_d > SQR(CAWARN) && debug)
	{
	    printf("WARNING: unusual CA-CA distance of %5.2f for",sqrt(ca_d));
	    printf("%s number ??\n", (nnbflg)?" interaction":" H-bond"/*,nhb*/);
	    printf("         between %s and %s\n", atomid(i,buf1),atomid(j,buf2));
	    
	}
    }
#if 0
    printf("%4s",   brcode);
    printf("%c",    (atom[i].chnid == '-') ? space : atom[i].chnid);
    printf("%4s/",  brcode);
    printf("%c",    atom[i].chnid);
    printf("%04d",  atom[i].aanum);
    if(OMLINSERT && atom[i].hetflg)
	printf("h");
    else
	printf("%c",    atom[i].inscode);
    /* printf("%3s",   dontyp);               */
    printf("%3s",   atom[i].resnam);
    printf("%4s",   atom[i].atmnam);
    printf("%c",    atom[i].strucsum);
    printf("%c",    (atom[j].chnid == '-') ? space : atom[j].chnid);
		printf("%4s/",  brcode);
		printf("%c",    atom[j].chnid);
		printf("%04d",  atom[j].aanum);
    if(OMLINSERT && atom[j].hetflg)
	printf("h");
    else
	printf("%c",    atom[j].inscode);
    /* printf("%3s",   acctyp);               */
		printf("%3s",   atom[j].resnam);
		printf("%4s",   atom[j].atmnam);
		printf("%c",    atom[j].strucsum);
		printf("%4.1f", sqrt(d));
		printf(" %2s",   bndtyp);
    printf("%4d",   gap);
    printf("%4.1f", (ca_d <= 0.0) ? -1.0 : sqrt(ca_d));
    printf("%6.1d", 180/3.1415927*angle(atom[i].p,nearest,atom[j].p) );
    printf("%4.1d", d);
    printf("%6d\n", nhb);
		
#endif
    *o_str = 0 ; 

/*This isn't neccessary if the longoutput format is used, but if the short
  format is used, then the first output must (i) include a 'strlen' in case
  it is part of a 'long format' output, and (ii) have some way of knowing
  where to begin in case of a 'short format' output. */
    
    if (longoutflg)  
 		{
 		    /* start to output the line, *.hhb format */
 		    sprintf(o_str              , "%4s",   brcode);
 		    sprintf(o_str+strlen(o_str), "%c",    (atom[i].chnid == '-') ? space : 
 			    atom[i].chnid);
 		    sprintf(o_str+strlen(o_str), "%4s/",  brcode);
 		}
 		sprintf(o_str+strlen(o_str), "%c",    atom[i].chnid);
 		sprintf(o_str+strlen(o_str), "%04d",  atom[i].aanum);
if(OMLINSERT && atom[i].hetflg) /*v3.13*/
    sprintf(o_str+strlen(o_str), "h");
else
    sprintf(o_str+strlen(o_str), "%c",    atom[i].inscode);
		/* sprintf(o_str+strlen(o_str), "%3s",   dontyp);               */
/* Amendment. RAL 14 Jun 2012 --> */
// 		if (atom[i].aacode==Cys && atom[i].atmtyp == 5 & cssflg)
 		if (atom[i].aacode==Cys && atom[i].atmtyp == 5 && cssflg)
/* <-- Amendment. RAL 14 Jun 2012 */
 		{
 		    if (atom[i].ssflg) 
 			sprintf(o_str+strlen(o_str),"CSS");
 		    else 
 			sprintf(o_str+strlen(o_str),"CYH");    }
 		else
 		    sprintf(o_str+strlen(o_str), "%3s",   atom[i].resnam);
 		sprintf(o_str+strlen(o_str), "%4s",   atom[i].atmnam);
 		if (longoutflg)  
 		{
 		    
 		    sprintf(o_str+strlen(o_str), "%c",    atom[i].strucsum);
 		    sprintf(o_str+strlen(o_str), "%c",    (atom[j].chnid == '-') ? space : 
 			    atom[j].chnid);
 		    sprintf(o_str+strlen(o_str), "%4s/",  brcode);
 		}
 		else
 		    sprintf(o_str+strlen(o_str), " ");
 		
 		sprintf(o_str+strlen(o_str), "%c",    atom[j].chnid);
                sprintf(o_str+strlen(o_str), "%04d",  atom[j].aanum);
    if(OMLINSERT && atom[j].hetflg) /*v3.13 start*/
	sprintf(o_str+strlen(o_str),"h");
    else /*v3.13 end*/
 		sprintf(o_str+strlen(o_str), "%c",    atom[j].inscode);
 		/* sprintf(o_str+strlen(o_str), "%3s",   acctyp);               */
 		if (atom[j].aacode==Cys && atom[j].atmtyp == 5 && cssflg)
 		{
 		    if (atom[j].ssflg) 
 			sprintf(o_str+strlen(o_str),"CSS");
 		    else 
 			sprintf(o_str+strlen(o_str),"CYH");    }
 		else
 		    sprintf(o_str+strlen(o_str), "%3s",   atom[j].resnam);
 		sprintf(o_str+strlen(o_str), "%4s",   atom[j].atmnam);
 		if (longoutflg) 
 		    sprintf(o_str+strlen(o_str), "%c",    atom[j].strucsum);
 		sprintf(o_str+strlen(o_str), "%5.2f", sqrt(d));
 		if (!longoutflg) 
 		    sprintf(o_str+strlen(o_str), " ");
 		sprintf(o_str+strlen(o_str), "%2s",  bndtyp);
 		sprintf(o_str+strlen(o_str), "%4d",   gap);
 		if (!longoutflg) 
 		    sprintf(o_str+strlen(o_str), " ");
 		sprintf(o_str+strlen(o_str), "%5.2f", (ca_d <= 0.0) ? -1.0 : sqrt(ca_d));
 		if (!longoutflg) 
 		    sprintf(o_str+strlen(o_str), " ");
 		if (atom[i].nh && h_atm[atom[i].h_ptr].typ)
 		{
 		    /* if it has hydrogens and if they have been placed */
		    tmp = angle(atom[i].p,nearest,atom[j].p);
		    
 		    sprintf(o_str+strlen(o_str), "%5.1f", (180.0/3.1415927)* tmp );
		    if (!longoutflg) 
			sprintf(o_str+strlen(o_str), " ");
 		    sprintf(o_str+strlen(o_str), "%5.2f", ha);
		    if (!longoutflg)
			sprintf(o_str+strlen(o_str), " ");
 		    if (haaa_ang>-50.0)
 			sprintf(o_str+strlen(o_str),"%5.1f", 180/3.1415927* (float) acos(haaa_ang) );
 		    else
 			sprintf(o_str+strlen(o_str),"%5.1f", -1.0);
		    
 		}
 		else
 		    if (longoutflg) 
 			sprintf(o_str+strlen(o_str), "%5.1f%5.2f%5.1f", -1.0, -1.0, -1.0);
 		    else
 			sprintf(o_str+strlen(o_str), "%5.1f %5.2f %5.1f", -1.0, -1.0, -1.0);
 		if (daaa_ang>-50.0)
 		    sprintf(o_str+strlen(o_str),"%6.1f", 180/3.1415927*acos(daaa_ang) );
 		else
 		    sprintf(o_str+strlen(o_str),"%6.1f", -1.0);
		
 		if (debug)
 		{
 		    sprintf(o_str+strlen(o_str), "D " );
 		    sprintf(o_str+strlen(o_str), TF,VXYZ(atom[i].p) );
 		    sprintf(o_str+strlen(o_str), " H " );
 		    sprintf(o_str+strlen(o_str), TF,VXYZ(nearest) );
 		    sprintf(o_str+strlen(o_str), " A " );
 		    sprintf(o_str+strlen(o_str), TF, VXYZ(atom[j].p) );
 		}
 		
/* 		sprintf(o_str+strlen(o_str), "%6d\n", nhb);
		THIS IS DONE BY THE CALLING ROUTINE */

 		/* end of outputting the line, *.hhb format */

    return;

}