ESR_ReturnCode SR_RecognizerResult_Destroy(SR_RecognizerResult* self)
{
  SR_RecognizerResultImpl* impl = (SR_RecognizerResultImpl*) self;
  ArrayList* semanticList;
  SR_SemanticResult* semanticResult;
  size_t nbest, i, j, num_semanticResults;
  ESR_ReturnCode rc;
  
  /* each nbest list entry has an ArrayList of Semantic Results... need to destroy them too */
  if (impl->results != NULL)
  {
    CHKLOG(rc, impl->results->getSize(impl->results, &nbest));
    for (i = 0; i < nbest; ++i)
    {
      CHKLOG(rc, impl->results->get(impl->results, 0, (void **)&semanticList));
      if (semanticList == NULL)
        continue;
        
      CHKLOG(rc, semanticList->getSize(semanticList, &num_semanticResults));
      for (j = 0; j < num_semanticResults; ++j)
      {
        LCHAR literal[256];
        size_t len;
        
        CHKLOG(rc, semanticList->get(semanticList, 0, (void **)&semanticResult));
        CHKLOG(rc, semanticList->remove(semanticList, semanticResult));
        len = sizeof(literal) / sizeof(LCHAR);
        CHKLOG(rc, semanticResult->getValue(semanticResult, "literal", (LCHAR*) &literal, &len));
        CHKLOG(rc, semanticResult->destroy(semanticResult));
      }
      CHKLOG(rc, impl->results->remove(impl->results, semanticList));
      CHKLOG(rc, semanticList->destroy(semanticList));
    }
    CHKLOG(rc, impl->results->destroy(impl->results));
    impl->results = NULL;
  }
  
  if (impl->nbestList != NULL)
  {
    CA_DeleteNBestList(impl->nbestList);
    impl->nbestList = NULL;
  }
  FREE(impl);
  return ESR_SUCCESS;
CLEANUP:
  passert(rc != ESR_BUFFER_OVERFLOW);
  return rc;
}