void RPG_LevelInfo::PreloadFmodEventProject(VString const& projectFilename)
{
  VASSERT_MSG(!projectFilename.IsEmpty(), "No FMod Event Project was specified.");

  FMOD::EventProject* eventProject = VFmodManager::GlobalManager().LoadEventProject(projectFilename.AsChar());
#if !(RPG_FMOD_SUPPRESS_NONNULL_ASSERTS)
  VVERIFY_MSG(eventProject != NULL, "Specified FMod Event Project failed to load.");
#endif
  if(!eventProject)
    return;

  int numGroups;
  eventProject->getNumGroups(&numGroups);

  for(int index = 0; index < numGroups; ++index)
  {
    FMOD::EventGroup* eventGroup;
    eventProject->getGroupByIndex(index, true, &eventGroup);

    //eventGroup->loadEventData(FMOD_EVENT_RESOURCE_STREAMS_AND_SAMPLES, FMOD_EVENT_NONBLOCKING);
    eventGroup->loadEventData(FMOD_EVENT_RESOURCE_STREAMS_AND_SAMPLES, FMOD_EVENT_DEFAULT);
  }
}