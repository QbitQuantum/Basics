/*
 *******************************************************************
 * Function: CKERROR CreatePrototype( CKBehaviorPrototype** behaviorPrototypePtr )
 *
 * Description : The prototype creation function will be called the first time 
 *               a behavior must be created to create the CKBehaviorPrototype 
 *               that contains the description of the behavior.
 *
 * Parameters :
 *    behaviorPrototypePtr        Pointer to a CKBehaviorPrototype object that 
 *                                describes the behavior's internal structure 
 *                                and relationships with other objects.
 *
 * Returns : CKERROR
 *
 *******************************************************************
 */
CKERROR GBLCOBGWrapper::CreatePrototype( CKBehaviorPrototype** behaviorPrototypePtr )
	{

#if GBL_RUNTIME	
	// Not editable from Virtools Dev
	CKBehaviorPrototype *behaviorPrototype = CreateCKBehaviorPrototypeRunTime( "GBLCOBGWrapper" );
#elif GBL_GAMEDEVELOPER 
	// Edition depend on the BB.
	CKBehaviorPrototype *behaviorPrototype = CreateCKBehaviorPrototype( "GBLCOBGWrapper" );
#else					
	// Editable from Virtools Dev
	CKBehaviorPrototype *behaviorPrototype = CreateCKBehaviorPrototype( "GBLCOBGWrapper" );
#endif 

	
	if ( !behaviorPrototype ) 
        return CKERR_OUTOFMEMORY;

    //----	Local Parameters Declaration
	behaviorPrototype->DeclareLocalParameter("BG Script", CKPGUID_BEHAVIOR );

    //----	Settings Declaration
	behaviorPrototype->DeclareSetting("BG filename", CKPGUID_STRING ,"path undefined.(BGWrapper Settings)");

	behaviorPrototype->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);

	behaviorPrototype->SetBehaviorFlags((CK_BEHAVIOR_FLAGS)(CKBEHAVIOR_INTERNALLYCREATEDINPUTS |
												CKBEHAVIOR_INTERNALLYCREATEDINPUTPARAMS |
												CKBEHAVIOR_INTERNALLYCREATEDOUTPUTS |
												CKBEHAVIOR_INTERNALLYCREATEDOUTPUTPARAMS));

	behaviorPrototype->SetBehaviorCallbackFct(BGWrapperCB,
												CKCB_BEHAVIORLOAD |
												CKCB_BEHAVIORRESET |
												CKCB_BEHAVIORSETTINGSEDITED |
												CKCB_BEHAVIORDETACH |
												CKCB_BEHAVIORDEACTIVATESCRIPT
												, NULL);

    behaviorPrototype->SetFunction( GBLCOBGWrapper::BehaviourFunction );
    
    *behaviorPrototypePtr = behaviorPrototype;
    return CK_OK;
}