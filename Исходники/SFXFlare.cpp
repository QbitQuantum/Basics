ALERROR CFlareEffectCreator::OnEffectCreateFromXML (SDesignLoadCtx &Ctx, CXMLElement *pDesc, const CString &sUNID)

//	OnEffectCreateFromXML
//
//	Initializes from XML

{
    CString sStyle = pDesc->GetAttribute(STYLE_ATTRIB);
    if (strEquals(sStyle, STYLE_FADING_BLAST))
        m_iStyle = styleFadingBlast;
    else if (strEquals(sStyle, STYLE_FLICKER))
        m_iStyle = styleFlicker;
    else if (sStyle.IsBlank() || strEquals(sStyle, STYLE_PLAIN))
        m_iStyle = stylePlain;
    else
    {
        Ctx.sError = strPatternSubst(CONSTLIT("Invalid Flare style: %s"), sStyle);
        return ERR_FAIL;
    }

    m_iRadius = pDesc->GetAttributeIntegerBounded(RADIUS_ATTRIB, 0, -1, 100);
    m_iLifetime = pDesc->GetAttributeIntegerBounded(LIFETIME_ATTRIB, 0, -1, 1);
    m_rgbPrimaryColor = ::LoadRGBColor(pDesc->GetAttribute(PRIMARY_COLOR_ATTRIB));

    CString sAttrib;
    if (pDesc->FindAttribute(SECONDARY_COLOR_ATTRIB, &sAttrib))
        m_rgbSecondaryColor = ::LoadRGBColor(sAttrib);
    else
        m_rgbSecondaryColor = m_rgbPrimaryColor;

    return NOERROR;
}