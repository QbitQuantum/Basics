ESR_ReturnCode SR_NametagsRemoveImpl(SR_Nametags* self, const LCHAR* id)
{
  SR_NametagsImpl* impl = (SR_NametagsImpl*) self;
  HashMap* nametags = impl->value;
  ESR_ReturnCode rc;

  CHKLOG(rc, nametags->remove(nametags, id));

  CHKLOG(rc, SR_EventLogToken_BASIC(impl->eventLog, impl->logLevel, L("id"), id));
  CHKLOG(rc, SR_EventLogEvent_BASIC(impl->eventLog, impl->logLevel, L("SR_NametagsRemove")));
  return ESR_SUCCESS;
CLEANUP:
  return rc;
}