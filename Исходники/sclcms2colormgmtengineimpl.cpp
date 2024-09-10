ScColorTransform ScLcms2ColorMgmtEngineImpl::createProofingTransform(ScColorMgmtEngine& engine,
                                             const ScColorProfile& inputProfile , eColorFormat inputFormat,
	                                         const ScColorProfile& outputProfile, eColorFormat outputFormat,
                                             const ScColorProfile& proofProfile , eRenderIntent renderIntent, 
                                             eRenderIntent proofingIntent, long transformFlags)
{
	ScColorTransform transform(NULL);
	if (inputProfile.isNull() || outputProfile.isNull())
		return transform;
	int inputProfEngineID  = inputProfile.engine().engineID();
	int outputProfEngineID = outputProfile.engine().engineID();
	int proofProfEngineID  = proofProfile.engine().engineID();
	if ((engine.engineID()  != m_engineID) || (inputProfEngineID != m_engineID) || 
		(outputProfEngineID != m_engineID) || (proofProfEngineID != m_engineID))
		return transform;
	const ScLcms2ColorProfileImpl* lcmsInputProf    = dynamic_cast<const ScLcms2ColorProfileImpl*>(inputProfile.data());
	const ScLcms2ColorProfileImpl* lcmsOutputProf   = dynamic_cast<const ScLcms2ColorProfileImpl*>(outputProfile.data());
	const ScLcms2ColorProfileImpl* lcmsProofingProf = dynamic_cast<const ScLcms2ColorProfileImpl*>(proofProfile.data());
	if (!lcmsInputProf || !lcmsOutputProf || !lcmsProofingProf)
		return transform;

	long strategyFlags = 0;
	if (m_strategy.useBlackPointCompensation)
		strategyFlags |= Ctf_BlackPointCompensation;
	if (m_strategy.useBlackPreservation)
		strategyFlags |= Ctf_BlackPreservation;

	ScColorTransformInfo transInfo;
	transInfo.inputProfile    = inputProfile.productDescription();
	transInfo.outputProfile   = outputProfile.productDescription();
	transInfo.proofingProfile = proofProfile.productDescription();
	transInfo.inputFormat     = inputFormat;
	transInfo.outputFormat    = outputFormat;
	transInfo.renderIntent    = renderIntent;
	transInfo.proofingIntent  = proofingIntent;
	transInfo.flags = transformFlags | strategyFlags;

	cmsUInt32Number lcmsFlags     = translateFlagsToLcmsFlags(transformFlags | strategyFlags);
	cmsUInt32Number lcmsInputFmt  = translateFormatToLcmsFormat(inputFormat);
	cmsUInt32Number lcmsOutputFmt = translateFormatToLcmsFormat(outputFormat);
	int   lcmsIntent    = translateIntentToLcmsIntent(renderIntent);
	int   lcmsPrfIntent = translateIntentToLcmsIntent(proofingIntent);

	if (transInfo.inputProfile != transInfo.proofingProfile)
	{
		if (transInfo.proofingProfile == transInfo.outputProfile)
		{
			transInfo.proofingIntent = Intent_Relative_Colorimetric;
			lcmsPrfIntent = translateIntentToLcmsIntent(Intent_Relative_Colorimetric);
		}
		transform = m_transformPool->findTransform(transInfo);
		if (transform.isNull())
		{
			cmsHTRANSFORM hTransform = NULL;
			hTransform = cmsCreateProofingTransform(lcmsInputProf->m_profileHandle , lcmsInputFmt, 
													lcmsOutputProf->m_profileHandle, lcmsOutputFmt,
													lcmsProofingProf->m_profileHandle, lcmsIntent, 
													lcmsPrfIntent, lcmsFlags | cmsFLAGS_SOFTPROOFING);
			if (hTransform)
			{
				ScLcms2ColorTransformImpl* newTrans = new ScLcms2ColorTransformImpl(engine, hTransform);
				newTrans->setTransformInfo(transInfo);
				transform = ScColorTransform(dynamic_cast<ScColorTransformData*>(newTrans));
				m_transformPool->addTransform(transform, true);
			}
		}
	}
	else
	{
		transformFlags  &= (~Ctf_Softproofing);
		transformFlags  &= (~Ctf_GamutCheck);
		lcmsFlags        = translateFlagsToLcmsFlags(transformFlags | strategyFlags);
		transInfo.flags  = transformFlags | strategyFlags;
		transInfo.renderIntent   = proofingIntent;
		transInfo.proofingIntent = (eRenderIntent) 0;
		if (transInfo.inputProfile == transInfo.outputProfile)
		{
			lcmsFlags |= cmsFLAGS_NULLTRANSFORM;
			transInfo.inputProfile    = QString();
			transInfo.outputProfile   = QString();
			transInfo.proofingProfile = QString();
			transInfo.renderIntent    = (eRenderIntent) 0;
			transInfo.proofingIntent  = (eRenderIntent) 0;
			transInfo.flags = 0;
		}
		transform = m_transformPool->findTransform(transInfo);
		if (transform.isNull())
		{
			cmsHTRANSFORM hTransform = NULL;
			hTransform  = cmsCreateTransform(lcmsInputProf->m_profileHandle , lcmsInputFmt, 
										     lcmsOutputProf->m_profileHandle, lcmsOutputFmt, 
											 lcmsPrfIntent, lcmsFlags | cmsFLAGS_LOWRESPRECALC);
			if (hTransform)
			{
				ScLcms2ColorTransformImpl* newTrans = new ScLcms2ColorTransformImpl(engine, hTransform);
				newTrans->setTransformInfo(transInfo);
				transform = ScColorTransform(dynamic_cast<ScColorTransformData*>(newTrans));
				m_transformPool->addTransform(transform, true);
			}
		}
	}
	return transform;
}