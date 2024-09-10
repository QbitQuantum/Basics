/* static */ nsresult
SRICheck::IntegrityMetadata(const nsAString& aMetadataList,
                            const nsIDocument* aDocument,
                            SRIMetadata* outMetadata)
{
  NS_ENSURE_ARG_POINTER(outMetadata);
  NS_ENSURE_ARG_POINTER(aDocument);
  MOZ_ASSERT(outMetadata->IsEmpty()); // caller must pass empty metadata

  if (!Preferences::GetBool("security.sri.enable", false)) {
    SRILOG(("SRICheck::IntegrityMetadata, sri is disabled (pref)"));
    return NS_ERROR_SRI_DISABLED;
  }

  // put a reasonable bound on the length of the metadata
  NS_ConvertUTF16toUTF8 metadataList(aMetadataList);
  if (metadataList.Length() > SRICheck::MAX_METADATA_LENGTH) {
    metadataList.Truncate(SRICheck::MAX_METADATA_LENGTH);
  }
  MOZ_ASSERT(metadataList.Length() <= aMetadataList.Length());

  // the integrity attribute is a list of whitespace-separated hashes
  // and options so we need to look at them one by one and pick the
  // strongest (valid) one
  nsCWhitespaceTokenizer tokenizer(metadataList);
  nsAutoCString token;
  for (uint32_t i=0; tokenizer.hasMoreTokens() &&
         i < SRICheck::MAX_METADATA_TOKENS; ++i) {
    token = tokenizer.nextToken();

    SRIMetadata metadata(token);
    if (metadata.IsMalformed()) {
      NS_ConvertUTF8toUTF16 tokenUTF16(token);
      const char16_t* params[] = { tokenUTF16.get() };
      nsContentUtils::ReportToConsole(nsIScriptError::warningFlag,
                                      NS_LITERAL_CSTRING("Sub-resource Integrity"),
                                      aDocument,
                                      nsContentUtils::eSECURITY_PROPERTIES,
                                      "MalformedIntegrityHash",
                                      params, ArrayLength(params));
    } else if (!metadata.IsAlgorithmSupported()) {
      nsAutoCString alg;
      metadata.GetAlgorithm(&alg);
      NS_ConvertUTF8toUTF16 algUTF16(alg);
      const char16_t* params[] = { algUTF16.get() };
      nsContentUtils::ReportToConsole(nsIScriptError::warningFlag,
                                      NS_LITERAL_CSTRING("Sub-resource Integrity"),
                                      aDocument,
                                      nsContentUtils::eSECURITY_PROPERTIES,
                                      "UnsupportedHashAlg",
                                      params, ArrayLength(params));
    }

    nsAutoCString alg1, alg2;
    if (MOZ_LOG_TEST(SRILogHelper::GetSriLog(), mozilla::LogLevel::Debug)) {
      outMetadata->GetAlgorithm(&alg1);
      metadata.GetAlgorithm(&alg2);
    }
    if (*outMetadata == metadata) {
      SRILOG(("SRICheck::IntegrityMetadata, alg '%s' is the same as '%s'",
              alg1.get(), alg2.get()));
      *outMetadata += metadata; // add new hash to strongest metadata
    } else if (*outMetadata < metadata) {
      SRILOG(("SRICheck::IntegrityMetadata, alg '%s' is weaker than '%s'",
              alg1.get(), alg2.get()));
      *outMetadata = metadata; // replace strongest metadata with current
    }
  }

  if (MOZ_LOG_TEST(SRILogHelper::GetSriLog(), mozilla::LogLevel::Debug)) {
    if (outMetadata->IsValid()) {
      nsAutoCString alg;
      outMetadata->GetAlgorithm(&alg);
      SRILOG(("SRICheck::IntegrityMetadata, using a '%s' hash", alg.get()));
    } else if (outMetadata->IsEmpty()) {
      SRILOG(("SRICheck::IntegrityMetadata, no metadata"));
    } else {
      SRILOG(("SRICheck::IntegrityMetadata, no valid metadata found"));
    }
  }
  return NS_OK;
}