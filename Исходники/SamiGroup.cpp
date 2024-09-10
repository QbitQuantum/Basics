JsonObject*
SamiGroup::asJsonObject() {
    JsonObject *pJsonObject = new JsonObject();
    pJsonObject->Construct();

    
    JsonString *p_idKey = new JsonString(L"_id");
    pJsonObject->Add(p_idKey, toJson(getPId(), "String", ""));

    
    JsonString *pNameKey = new JsonString(L"name");
    pJsonObject->Add(pNameKey, toJson(getPName(), "String", ""));

    
    JsonString *pIs_defaultKey = new JsonString(L"is_default");
    pJsonObject->Add(pIs_defaultKey, toJson(getPIsDefault(), "Boolean", ""));

    
    JsonString *pIs_hiddenKey = new JsonString(L"is_hidden");
    pJsonObject->Add(pIs_hiddenKey, toJson(getPIsHidden(), "Boolean", ""));

    
    JsonString *pNew_weekly_mailer_contentKey = new JsonString(L"new_weekly_mailer_content");
    pJsonObject->Add(pNew_weekly_mailer_contentKey, toJson(getPNewWeeklyMailerContent(), "String", ""));

    
    JsonString *pNewsletter_subjectKey = new JsonString(L"newsletter_subject");
    pJsonObject->Add(pNewsletter_subjectKey, toJson(getPNewsletterSubject(), "String", ""));

    
    JsonString *pAutopublishKey = new JsonString(L"autopublish");
    pJsonObject->Add(pAutopublishKey, toJson(getPAutopublish(), "Boolean", ""));

    
    JsonString *pNumber_articles_per_groupKey = new JsonString(L"number_articles_per_group");
    pJsonObject->Add(pNumber_articles_per_groupKey, toJson(getPNumberArticlesPerGroup(), "Integer", ""));

    
    JsonString *pNumber_articles_per_newsletterKey = new JsonString(L"number_articles_per_newsletter");
    pJsonObject->Add(pNumber_articles_per_newsletterKey, toJson(getPNumberArticlesPerNewsletter(), "Integer", ""));

    
    return pJsonObject;
}