// convert a VARIANT to a J array
// returns 0 on error with detail in jerr.
static A v2a(J jt, VARIANT* v, int dobstrs)
{
	A a;
	SAFEARRAY* psa;
	SAFEARRAYBOUND* pb;
	I shape[MAXRANK];
	I k=1,n,r,i;
	I* pintsnk;
#if SY_64
	int* pint32src;
#else
	long long* pint64src;
#endif
	short* pshortsrc;
	unsigned short* pboolsrc;
	char* pboolsnk;
	VARTYPE t;
	int byref;
	double* pdoublesnk;
	float* pfloatsrc;

#define OPTREF(v,field)		(byref ? *v->p##field : v->field)

	t=v->vt;
	byref = t & VT_BYREF;
	t = t & ~VT_BYREF;

	if(dobstrs && t == VT_BSTR)
	{
		BSTR bstr; int len;

		bstr = OPTREF(v,bstrVal);

		if(uniflag)
			// len=SysStringLen(bstr);
      len=WideCharToMultiByte(CP_UTF8,0,bstr,(int)SysStringLen(bstr),0,0,0,0);
		else
			len=SysStringByteLen(bstr);
		RE(a=ga(LIT, len, 1, 0));
		if(uniflag)
			toutf8n(bstr, (C*)AV(a), len);
		else
			memcpy((C*)AV(a), (C*)bstr, len);
		R a;
	}
	if(t & VT_ARRAY)
	{
		psa = OPTREF(v,parray);
		pb = psa->rgsabound;
		r=psa->cDims;
		ASSERT(r<=MAXRANK,EVRANK);
		for(i=0; i<r; ++i)
		{
			n = pb[i].cElements;
			shape[i] = n; 
			k *= n;
		}
	}
	else
		r = 0;

	switch(t)
	{
	case VT_VARIANT | VT_ARRAY:
	{
		A *boxes;
		VARIANT* pv;
		
		// fixup scalar boxes which arrive
		// as a 1-elem vector with a lower bound at -1, not 0.
		if (pb[0].lLbound == -1)
		{
			ASSERT(psa->cDims==1 && pb[0].cElements==1, EVDOMAIN);
			r = 0;
		}
		RE(a=ga(BOX, k, r, (I*)&shape));
		ASSERT(S_OK==SafeArrayAccessData(psa, &pv),EVFACE);
		boxes = AAV(a);
		while(k--)
		{
			A z;
			// Don't use a PROLOG/EPILOG during v2a.
			// The z's are not getting their reference
			// count set until everything is in place
			// and the jset() is done in Jset().
			z = *boxes++ = v2a(jt, pv++, dobstrs);
			if (!z) break;
		}
		SafeArrayUnaccessData(psa);
		if (jt->jerr) return 0;
		break;
	}
	case VT_BOOL | VT_ARRAY:
		RE(a=ga(B01, k, r, (I*)&shape));
		pboolsrc = (VARIANT_BOOL*)psa->pvData;
		pboolsnk = BAV(a);
		// J bool returned from VB boolean, a -1 and 0 mess.
		// It wouldn't be that bad if the Microsoft folks used their own macros
		// and kept an eye an sign extensions.  But the way they are
		// doing it they are returning at least some TRUEs as value 255
		// instead of VARIANT_TRUE.  Therefore, we have to compare against
		// VARIANT_FALSE which -we hope- is consistently defined (as 0).
		while(k--)
			*pboolsnk++ = (*pboolsrc++)!=VARIANT_FALSE;
		break;

	case VT_UI1 | VT_ARRAY:
		RE(a=ga(LIT, k, r, (I*)&shape));
		memcpy(AV(a), psa->pvData, k * sizeof(char));
		break;

	case VT_UI2 | VT_ARRAY:
		RE(a=ga(C2T, k, r, (I*)&shape));
		memcpy(AV(a), psa->pvData, k * sizeof(short));
		break;

	case VT_UI4 | VT_ARRAY:
		RE(a=ga(C4T, k, r, (I*)&shape));
		memcpy(AV(a), psa->pvData, k * sizeof(int));
		break;

	case VT_I2 | VT_ARRAY:
		RE(a=ga(INT, k, r, (I*)&shape));
		pshortsrc = (short*)psa->pvData;
		pintsnk = AV(a);
		while(k--)
			*pintsnk++ = *pshortsrc++;
		break;

	case VT_I4 | VT_ARRAY:
		RE(a=ga(INT, k, r, (I*)&shape));
#if SY_64
		pint32src = (long*)psa->pvData;
		pintsnk = AV(a);
		while(k--)
			*pintsnk++ = *pint32src++;
#else
		memcpy(AV(a), psa->pvData, k * sizeof(int));
#endif
		break;

	case VT_I8 | VT_ARRAY:
		RE(a=ga(INT, k, r, (I*)&shape));
#if SY_64
		memcpy(AV(a), psa->pvData, k * sizeof(I));
#else
		pint64src = (long long*)psa->pvData;
		pintsnk = AV(a);
		while(k--)
			*pintsnk++ = (I)*pint64src++;
#endif
		break;

	case VT_R4 | VT_ARRAY:
		RE(a=ga(FL, k, r, (I*)&shape));
		pfloatsrc = (float*)psa->pvData;
		pdoublesnk = (double*)AV(a);
		while(k--)
			*pdoublesnk++ = *pfloatsrc++;
		break;

	case VT_R8 | VT_ARRAY:
		RE(a=ga(FL, k, r, (I*)&shape));
		memcpy(AV(a), psa->pvData, k * sizeof(double));
		break;

	case VT_UI1:
		RE(a=ga(LIT, 1, 0, 0));
		*CAV(a) = OPTREF(v,bVal);
		break;

	case VT_UI2:
		RE(a=ga(C2T, 1, 0, 0));
		*USAV(a) = (US)OPTREF(v,iVal);
		break;

	case VT_UI4:
		RE(a=ga(C4T, 1, 0, 0));
		*C4AV(a) = (C4)OPTREF(v,lVal);
		break;

	case VT_BOOL:
		RE(a=ga(B01, 1, 0, 0));
		// array case above explains this messy phrase:
		*BAV(a) = OPTREF(v,boolVal)!=VARIANT_FALSE;
		break;

	case VT_I2:
		RE(a=ga(INT, 1, 0, 0));
		*IAV(a) = OPTREF(v,iVal);
		break;

	case VT_I4:
		RE(a=ga(INT, 1, 0, 0));
		*IAV(a) = OPTREF(v,lVal);
		break;

	case VT_I8:
		RE(a=ga(INT, 1, 0, 0));
		*IAV(a) = (I)OPTREF(v,llVal);
		break;

	case VT_R4:
		RE(a=ga(FL, 1, 0, 0));
		*DAV(a) = OPTREF(v,fltVal);
		break;

	case VT_R8:
		RE(a=ga(FL, 1, 0, 0));
		*DAV(a) = OPTREF(v,dblVal);
		break;

	default:
		ASSERT(0,EVDOMAIN);
	}
	if(1<r && jt->transposeflag)
	{
		RE(a=cant1(a));
		DO(r, AS(a)[i]=shape[r-1-i];);