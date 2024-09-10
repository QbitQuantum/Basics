static void DoWebAccessible(HWND w,IAccessible *pAccessible,T_SUIVI_ACCESSIBLE *ptSuivi)
#endif
{
	TRACE((TRACE_ENTER,_F_, ""));

	UNREFERENCED_PARAMETER(w);
	
	HRESULT hr;
	IAccessible *pChild=NULL;
	VARIANT vtChild;
	VARIANT vtState,vtRole;
	long l,lCount;
	long returnCount;
	VARIANT* pArray = NULL;
	
#ifdef TRACES_ACTIVEES
	char szTab[200];
	strcpy_s(szTab,sizeof(szTab),paramszTab);
	if (strlen(szTab)<sizeof(szTab)-5) strcat_s(szTab,sizeof(szTab),"  ");
#endif
	
	// si fini ou erreur, on termine la récursivité
	if (ptSuivi->iErreur!=0) goto end;

	// parcours de la suite : combien de fils ?
	hr=pAccessible->get_accChildCount(&lCount);
	if (FAILED(hr)) goto end;
	TRACE((TRACE_DEBUG,_F_,"%sget_accChildCount()==%ld",szTab,lCount));

	// plus de fils ou lu assez de champs, on termine !
	if (lCount==0)
	{
		TRACE((TRACE_INFO,_F_,"%sPas de fils",szTab));
		goto end;
	}
	if (ptSuivi->iTextFieldIndex>MAX_TEXT_FIELDS)
	{
		TRACE((TRACE_INFO,_F_,"Trop de champs, on arrête la recherche dans la page (lCount=%d ptSuivi->iTextFieldIndex=%d)",lCount,ptSuivi->iTextFieldIndex));
		goto end;
	}
	if (ptSuivi->iPwdIndex!=-1 && (ptSuivi->iTextFieldIndex - ptSuivi->iPwdIndex)>10) // optimisation : on ne lit pas plus de 10 champs après le mdp
	{
		TRACE((TRACE_INFO,_F_,"Fin de la recherche dans la page (ptSuivi->iTextFieldIndex=%d ptSuivi->iPwdIndex=%d)",ptSuivi->iTextFieldIndex,ptSuivi->iPwdIndex));
		goto end;
	}

	pArray = new VARIANT[lCount];
	hr = AccessibleChildren(pAccessible, 0L, lCount, pArray, &returnCount);
	if (FAILED(hr))
	{
		TRACE((TRACE_DEBUG,_F_,"%sAccessibleChildren()=0x%08lx",szTab,hr));
	}
	else
	{
		TRACE((TRACE_DEBUG,_F_,"%sAccessibleChildren() returnCount=%d",szTab,returnCount));
		for (l=0;l<lCount;l++)
		{
			VARIANT *pVarCurrent = &pArray[l];
			VariantInit(&vtRole);
			VariantInit(&vtState);
			pChild=NULL;
				
			TRACE((TRACE_DEBUG,_F_,"%s --------------------------------- l=%ld vt=%d lVal=0x%08lx",szTab,l,pVarCurrent->vt,pVarCurrent->lVal));
			if (pVarCurrent->vt!=VT_DISPATCH) goto suivant;
			if (pVarCurrent->lVal==NULL) goto suivant; // ISSUE#80 0.96B2 
			((IDispatch*)(pVarCurrent->lVal))->QueryInterface(IID_IAccessible, (void**) &pChild);
			if (FAILED(hr)) { TRACE((TRACE_ERROR,_F_,"%sQueryInterface(IID_IAccessible)=0x%08lx",szTab,hr)); goto suivant; }
			TRACE((TRACE_DEBUG,_F_,"%sQueryInterface(IID_IAccessible)=0x%08lx -> pChild=0x%08lx",szTab,hr,pChild));
			
			vtChild.vt=VT_I4;
			vtChild.lVal=CHILDID_SELF;
			hr=pChild->get_accState(vtChild,&vtState);
			if (FAILED(hr)) { TRACE((TRACE_ERROR,_F_,"get_accState()=0x%08lx",hr)); goto suivant; }
			TRACE((TRACE_DEBUG,_F_,"%sget_accState() vtState.lVal=0x%08lx",szTab,vtState.lVal));

			hr=pChild->get_accRole(vtChild,&vtRole);
			if (FAILED(hr)) { TRACE((TRACE_ERROR,_F_,"get_accRole()=0x%08lx",hr)); goto suivant; }
			TRACE((TRACE_DEBUG,_F_,"%sget_accRole() vtRole.lVal=0x%08lx",szTab,vtRole.lVal));
			
			//hr=pChild->get_accName(vtChild,&bstrName);
			//if (FAILED(hr)) { TRACE((TRACE_ERROR,_F_,"get_accName()=0x%08lx",hr)); goto suivant; }
			//TRACE((TRACE_DEBUG,_F_,"%sget_accName() name=%S",szTab,bstrName));
			
			// Reconnaissance du champ mot de passe : Nième champ ayant pour role et state les valeurs suivantes :
			// - Role = ROLE_SYSTEM_TEXT
			// - State = (STATE_SYSTEM_FOCUSABLE | STATE_SYSTEM_FOCUSED) & STATE_SYSTEM_PROTECTED

			// Reconnaissance du champ identifiant : Nième champ précédant le champ mot de passe et ayant pour role et state les valeurs suivantes :
			// - Role = ROLE_SYSTEM_TEXT
			// - State = (STATE_SYSTEM_FOCUSABLE | STATE_SYSTEM_FOCUSED)

			// ISSUE#279 : cas spécifique IE
			// TRACE((TRACE_DEBUG,_F_,"%sptSuivi->iBrowser=%d",szTab,ptSuivi->iBrowser));
			if (ptSuivi->iBrowser!=BROWSER_IE)
			{
				if ((vtRole.lVal == ROLE_SYSTEM_TEXT) && 
					((vtState.lVal & STATE_SYSTEM_FOCUSED) || (vtState.lVal & STATE_SYSTEM_FOCUSABLE)))
				{
					// c'est un champ de saisie, s'il est protégé c'est le mdp sinon c'est un id
					if (vtState.lVal & STATE_SYSTEM_PROTECTED)
					{
						TRACE((TRACE_INFO,_F_,"Champ mot de passe trouve (ROLE_SYSTEM_TEXT + STATE_SYSTEM_FOCUS* + STATE_SYSTEM_PROTECTED)"));
						pChild->AddRef();
						ptSuivi->pTextFields[ptSuivi->iTextFieldIndex]=pChild;
						ptSuivi->iNbPwdFound++; 
						TRACE((TRACE_INFO,_F_,"Champ mot de passe trouve : c'est le %dieme, on attendait le %d",ptSuivi->iNbPwdFound,atoi(gptActions[ptSuivi->iAction].szPwdName)));
						if (ptSuivi->iNbPwdFound==atoi(gptActions[ptSuivi->iAction].szPwdName)) 
						{
							ptSuivi->iPwdIndex=ptSuivi->iTextFieldIndex;
						}
						ptSuivi->iTextFieldIndex++;
					}
					else
					{
						TRACE((TRACE_INFO,_F_,"Un champ id trouve (ROLE_SYSTEM_TEXT + STATE_SYSTEM_FOCUS*)"));
						pChild->AddRef();
						ptSuivi->pTextFields[ptSuivi->iTextFieldIndex]=pChild;
						ptSuivi->iTextFieldIndex++;
					}
				}
				else
				{
	#ifdef TRACES_ACTIVEES
					DoWebAccessible(szTab,NULL,pChild,ptSuivi);
	#else
					DoWebAccessible(NULL,pChild,ptSuivi);
	#endif
				}
			}
			else // ISSUE#279 : IE
			{
				if ((vtRole.lVal == ROLE_SYSTEM_TEXT) && !(vtState.lVal & STATE_SYSTEM_READONLY))
				{
					// c'est un champ de saisie, s'il est protégé c'est le mdp sinon c'est un id
					if (vtState.lVal & STATE_SYSTEM_PROTECTED)
					{
						TRACE((TRACE_INFO,_F_,"Champ mot de passe trouve (ROLE_SYSTEM_TEXT + STATE_SYSTEM_FOCUS* + STATE_SYSTEM_PROTECTED)"));
						pChild->AddRef();
						ptSuivi->pTextFields[ptSuivi->iTextFieldIndex]=pChild;
						ptSuivi->iNbPwdFound++; 
						TRACE((TRACE_INFO,_F_,"Champ mot de passe trouve : c'est le %dieme, on attendait le %d",ptSuivi->iNbPwdFound,atoi(gptActions[ptSuivi->iAction].szPwdName)));
						if (ptSuivi->iNbPwdFound==atoi(gptActions[ptSuivi->iAction].szPwdName)) 
						{
							ptSuivi->iPwdIndex=ptSuivi->iTextFieldIndex;
						}
						ptSuivi->iTextFieldIndex++;
					}
					else
					{
						TRACE((TRACE_INFO,_F_,"Un champ id trouve (ROLE_SYSTEM_TEXT + STATE_SYSTEM_FOCUS*)"));
						pChild->AddRef();
						ptSuivi->pTextFields[ptSuivi->iTextFieldIndex]=pChild;
						ptSuivi->iTextFieldIndex++;
					}
				}
				else
				{
	#ifdef TRACES_ACTIVEES
					DoWebAccessible(szTab,NULL,pChild,ptSuivi);
	#else
					DoWebAccessible(NULL,pChild,ptSuivi);
	#endif
				}

			}
suivant:
			if (pChild!=NULL) { pChild->Release(); pChild=NULL; }
		}
	}
	
end:
	if (pArray!=NULL) delete[] pArray;
	TRACE((TRACE_LEAVE,_F_, ""));
}