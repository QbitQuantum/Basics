/*************************************************************************
            KppDestroyRuleRelations
 *************************************************************************/
void PEXPORT KppDestroyRuleRelations (GLOBALHANDLE hRuleRel)
{
#ifdef INFERENCE
#ifndef RUNTIME
  LPRULEREL lpRuleRel;

  if (!hRuleRel)
    return;

  lpRuleRel = (LPRULEREL) GLOBALLOCK (hRuleRel);
  GLOBALUNLOCK (RRHIF(lpRuleRel));
  GLOBALFREE (RRHIF(lpRuleRel));
  GLOBALUNLOCK (RRHTHEN(lpRuleRel));
  GLOBALFREE (RRHTHEN(lpRuleRel));

  while (GLOBALUNLOCK (hRuleRel));
  /* Do it twice 
  GLOBALUNLOCK (hRuleRel);
*/
  GLOBALFREE (hRuleRel);

#endif
#endif
}