int audio_event_parameter(parameter_id id, float value)
{
  FMOD::EventParameter* p = idToParameter(id);
  if(p)
  {
    result = p->setValue(value);
    return EXIT_SUCCESS;
  }
  else
    return EXIT_FAILURE;
}