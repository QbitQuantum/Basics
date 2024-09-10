STDMETHODIMP CScdSpVector::get_Vector(/*[in]*/ VARIANT_BOOL EnthalpyBasis, /*[out, retval]*/ SAFEARRAY **pVal)
  {
  dllSCD_COMENTRYGET(long, pVal)
    {
    SAFEARRAY *pSA=NULL;
    SAFEARRAYBOUND bound[1]={SDB.Count()+3,0};
    pSA=SafeArrayCreate(VT_R8, 1, bound);

    double d;
    long Cnt=bound[0].cElements;
    for (long i=0; i<SDB.Count(); i++)
      {
      d=m_pOwn->Model()->VMass[i];
      SafeArrayPutElement(pSA, &i, &d);
      }

    // NBNB EnthalpyBasis is ignored on "get"
    d=m_pOwn->Model()->totHz(som_ALL, m_pOwn->Model()->Temp(), m_pOwn->Model()->Press());
    SafeArrayPutElement(pSA, &i, &d);

    i++;
    d=m_pOwn->Model()->Temp();
    SafeArrayPutElement(pSA, &i, &d);

    i++;
    d=m_pOwn->Model()->Press();
    SafeArrayPutElement(pSA, &i, &d);

    *pVal=pSA;
    }