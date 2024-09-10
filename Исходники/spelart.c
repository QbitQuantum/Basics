/* ********************************************************************** */
 int16_t checkart1 (SOBJ * obj, int16_t pi1, int16_t pi2, struct artstr * a)

{  int16_t  type;
 switch (a->cond_sr1)
  { case  BAD_S : if(obj->pos[pi1].orig.attr>PROB_TO_BRK)
		      return(No);
		  break;
    case  DEL_S:  if((type=symcode((char  *)&(obj->pos[pi1].orig.code)))
		     !=E_DL)if(type!=_APF) return(No);
		  break;
  }
 switch(a->cond_sr2)
  { case  BAD_S : if(obj->pos[pi2].orig.attr>PROB_TO_BRK)
		      return(No);
		  break;
    case  DEL_S:  if(type=symcode((char  *)&(obj->pos[pi2].orig.code))
		     !=E_DL) if(type!=_APF)return(No);
		  break;
    // Le + Vova    01-24-94 03:45pm
    case  WID_S:  if (!(MEMCHR(wide_let,
                            *((char  *)&(obj->pos[pi2].orig.code))
                            ,sizeof wide_let )) ||
                            language != LANG_RUSSIAN ) return (No);
                  break;
  }
 switch(a->cond_sr12)
  {
    case EMB_S :  if((int16_t)obj->pos[pi2].tif_ref.col-
		     (int16_t)obj->pos[pi1].tif_ref.col -
		     (int16_t)obj->pos[pi1].tif_ref.width>1) return(No);
		  break;
    case FAX_M :  if (!fax1x2) return(No);
		  break;
  }
 /*
    The following euristic prevents merging of last 's' with
       previous low-attribute symbol.
                        08/06/92 03:15pm, L.
  */
if ( a->sr2)
   if(
      (
        (obj -> pos[pi2].orig.code == 'S')
       ||
        (obj ->pos[pi2].orig.code == 's')
       )
        &&
       ( pi2 == obj->part -> lth)
        &&
       (obj ->pos[pi2].orig.attr >= PROB_TO_BRK)
    )                                             return NO;


   return(Ok);
}