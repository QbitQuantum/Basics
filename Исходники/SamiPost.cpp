JsonObject*
SamiPost::asJsonObject() {
    JsonObject *pJsonObject = new JsonObject();
    pJsonObject->Construct();

    
    JsonString *p_idKey = new JsonString(L"_id");
    pJsonObject->Add(p_idKey, toJson(getPId(), "String", ""));

    
    JsonString *pCreated_atKey = new JsonString(L"created_at");
    pJsonObject->Add(pCreated_atKey, toJson(getPCreatedAt(), "String", ""));

    
    JsonString *pUpdated_atKey = new JsonString(L"updated_at");
    pJsonObject->Add(pUpdated_atKey, toJson(getPUpdatedAt(), "String", ""));

    
    JsonString *pExternal_urlKey = new JsonString(L"external_url");
    pJsonObject->Add(pExternal_urlKey, toJson(getPExternalUrl(), "String", ""));

    
    JsonString *pExternal_url_sourceKey = new JsonString(L"external_url_source");
    pJsonObject->Add(pExternal_url_sourceKey, toJson(getPExternalUrlSource(), "String", ""));

    
    JsonString *pExternal_url_typeKey = new JsonString(L"external_url_type");
    pJsonObject->Add(pExternal_url_typeKey, toJson(getPExternalUrlType(), "String", ""));

    
    JsonString *pImage_pathKey = new JsonString(L"image_path");
    pJsonObject->Add(pImage_pathKey, toJson(getPImagePath(), "String", ""));

    
    JsonString *pImage_urlKey = new JsonString(L"image_url");
    pJsonObject->Add(pImage_urlKey, toJson(getPImageUrl(), "String", ""));

    
    JsonString *pImage_heightKey = new JsonString(L"image_height");
    pJsonObject->Add(pImage_heightKey, toJson(getPImageHeight(), "String", ""));

    
    JsonString *pImage_widthKey = new JsonString(L"image_width");
    pJsonObject->Add(pImage_widthKey, toJson(getPImageWidth(), "String", ""));

    
    JsonString *pLogo_urlKey = new JsonString(L"logo_url");
    pJsonObject->Add(pLogo_urlKey, toJson(getPLogoUrl(), "String", ""));

    
    JsonString *pSquare_logo_urlKey = new JsonString(L"square_logo_url");
    pJsonObject->Add(pSquare_logo_urlKey, toJson(getPSquareLogoUrl(), "String", ""));

    
    JsonString *pNeeds_sanitizeKey = new JsonString(L"needs_sanitize");
    pJsonObject->Add(pNeeds_sanitizeKey, toJson(getPNeedsSanitize(), "String", ""));

    
    JsonString *pSummaryKey = new JsonString(L"summary");
    pJsonObject->Add(pSummaryKey, toJson(getPSummary(), "String", ""));

    
    JsonString *pTopicKey = new JsonString(L"topic");
    pJsonObject->Add(pTopicKey, toJson(getPTopic(), "String", ""));

    
    JsonString *pApproval_statusKey = new JsonString(L"approval_status");
    pJsonObject->Add(pApproval_statusKey, toJson(getPApprovalStatus(), "String", ""));

    
    JsonString *pApproval_transactionsKey = new JsonString(L"approval_transactions");
    pJsonObject->Add(pApproval_transactionsKey, toJson(getPApprovalTransactions(), "String", "array"));

    
    JsonString *pGroup_idsKey = new JsonString(L"group_ids");
    pJsonObject->Add(pGroup_idsKey, toJson(getPGroupIds(), "String", "array"));

    
    JsonString *pSlugKey = new JsonString(L"slug");
    pJsonObject->Add(pSlugKey, toJson(getPSlug(), "String", ""));

    
    JsonString *pArticle_idKey = new JsonString(L"article_id");
    pJsonObject->Add(pArticle_idKey, toJson(getPArticleId(), "String", ""));

    
    JsonString *pCommentKey = new JsonString(L"comment");
    pJsonObject->Add(pCommentKey, toJson(getPComment(), "String", ""));

    
    JsonString *pNewsletter_idsKey = new JsonString(L"newsletter_ids");
    pJsonObject->Add(pNewsletter_idsKey, toJson(getPNewsletterIds(), "String", "array"));

    
    JsonString *pIs_featuredKey = new JsonString(L"is_featured");
    pJsonObject->Add(pIs_featuredKey, toJson(getPIsFeatured(), "Boolean", ""));

    
    JsonString *pAdvisor_idKey = new JsonString(L"advisor_id");
    pJsonObject->Add(pAdvisor_idKey, toJson(getPAdvisorId(), "String", ""));

    
    JsonString *pIs_publishedKey = new JsonString(L"is_published");
    pJsonObject->Add(pIs_publishedKey, toJson(getPIsPublished(), "Boolean", ""));

    
    JsonString *pIs_responsiveKey = new JsonString(L"is_responsive");
    pJsonObject->Add(pIs_responsiveKey, toJson(getPIsResponsive(), "Boolean", ""));

    
    JsonString *pIs_proxy_neededKey = new JsonString(L"is_proxy_needed");
    pJsonObject->Add(pIs_proxy_neededKey, toJson(getPIsProxyNeeded(), "Boolean", ""));

    
    JsonString *pIs_mobile_proxy_neededKey = new JsonString(L"is_mobile_proxy_needed");
    pJsonObject->Add(pIs_mobile_proxy_neededKey, toJson(getPIsMobileProxyNeeded(), "Boolean", ""));

    
    JsonString *pProxy_urlKey = new JsonString(L"proxy_url");
    pJsonObject->Add(pProxy_urlKey, toJson(getPProxyUrl(), "String", ""));

    
    JsonString *pVideoKey = new JsonString(L"video");
    pJsonObject->Add(pVideoKey, toJson(getPVideo(), "String", ""));

    
    JsonString *pPdf_attachment_urlKey = new JsonString(L"pdf_attachment_url");
    pJsonObject->Add(pPdf_attachment_urlKey, toJson(getPPdfAttachmentUrl(), "String", ""));

    
    JsonString *pPost_dateKey = new JsonString(L"post_date");
    pJsonObject->Add(pPost_dateKey, toJson(getPPostDate(), "String", ""));

    
    JsonString *pDisplay_dateKey = new JsonString(L"display_date");
    pJsonObject->Add(pDisplay_dateKey, toJson(getPDisplayDate(), "String", ""));

    
    JsonString *pSuitability_scoreKey = new JsonString(L"suitability_score");
    pJsonObject->Add(pSuitability_scoreKey, toJson(getPSuitabilityScore(), "String", ""));

    
    JsonString *pVideo_idKey = new JsonString(L"video_id");
    pJsonObject->Add(pVideo_idKey, toJson(getPVideoId(), "String", ""));

    
    JsonString *pDisplay_tagKey = new JsonString(L"display_tag");
    pJsonObject->Add(pDisplay_tagKey, toJson(getPDisplayTag(), "String", ""));

    
    JsonString *pDisplay_summaryKey = new JsonString(L"display_summary");
    pJsonObject->Add(pDisplay_summaryKey, toJson(getPDisplaySummary(), "String", ""));

    
    JsonString *pVestorly_urlKey = new JsonString(L"vestorly_url");
    pJsonObject->Add(pVestorly_urlKey, toJson(getPVestorlyUrl(), "String", ""));

    
    JsonString *pTitleKey = new JsonString(L"title");
    pJsonObject->Add(pTitleKey, toJson(getPTitle(), "String", ""));

    
    return pJsonObject;
}