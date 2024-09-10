void OTSubcredential::UpdateMasterPublicToString(OTString & strAppendTo) // Used in UpdateContents.
{
    OT_ASSERT(NULL != m_pOwner);
    OTASCIIArmor ascMaster(m_pOwner->GetPubCredential());
    strAppendTo.Concatenate("<masterPublic>\n%s</masterPublic>\n\n",
                            ascMaster.Get());
}