PDIRTY_ASN1_SEQUENCE_EASY kuhl_m_kerberos_ticket_createSequencePrimaryName(PKERB_EXTERNAL_NAME name)
{
	PDIRTY_ASN1_SEQUENCE_EASY Seq_ExternalName, Ctx_root, Seq_Names;
	UCHAR integer1 = (UCHAR) name->NameType;
	USHORT i;
	ANSI_STRING aString;

	if(Seq_ExternalName = KULL_M_ASN1_CREATE_SEQ())
	{
		kull_m_asn1_append_ctx_and_data_to_seq(&Seq_ExternalName, ID_CTX_PRINCIPALNAME_NAME_TYPE, kull_m_asn1_create(DIRTY_ASN1_ID_INTEGER, &integer1, sizeof(UCHAR), NULL));
		if(Ctx_root = KULL_M_ASN1_CREATE_CTX(ID_CTX_PRINCIPALNAME_NAME_STRING))
		{
			if(Seq_Names = KULL_M_ASN1_CREATE_SEQ())
			{
				for(i = 0; i < name->NameCount; i++)
				{
					if(NT_SUCCESS(RtlUnicodeStringToAnsiString(&aString, &name->Names[i], TRUE)))
					{
						kull_m_asn1_create(DIRTY_ASN1_ID_GENERAL_STRING, aString.Buffer, aString.Length, &Seq_Names);
						RtlFreeAnsiString(&aString);
					}
				}
				kull_m_asn1_append(&Ctx_root, Seq_Names);
			}		
			kull_m_asn1_append(&Seq_ExternalName, Ctx_root);
		}
	}
	return Seq_ExternalName;
}