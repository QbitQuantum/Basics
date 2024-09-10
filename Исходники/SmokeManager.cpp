void CSmokeManager::SetBlurredVision( const float blurAmmount, const float frameTime )
{
    float newBlurAmount = clamp(blurAmmount * kBlurStrength, 0.0f, 1.0f);

    if (m_clientBlurAmount == newBlurAmount)
        return;

    if(newBlurAmount > m_clientBlurAmount)
        {
            m_clientBlurAmount = newBlurAmount;
        }
    else
        {
            m_clientBlurAmount = LERP(m_clientBlurAmount, newBlurAmount, frameTime * kClientReduceBlurDelta);
        }

    CSceneBlurGameEffect* pSceneBlurGameEffect = g_pGame->GetSceneBlurGameEffect();
    CRY_ASSERT(pSceneBlurGameEffect != NULL);
    pSceneBlurGameEffect->SetBlurAmount(m_clientBlurAmount, CSceneBlurGameEffect::eGameEffectUsage_SmokeManager);

    gEnv->p3DEngine->SetPostEffectParam("Global_User_Brightness", LERP(1.0f,kBlurBrightness,m_clientBlurAmount));
    gEnv->p3DEngine->SetPostEffectParam("Global_User_Contrast", LERP(1.0f,kBlurContrast,m_clientBlurAmount));
}