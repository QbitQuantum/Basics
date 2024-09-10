/*
 * pj_event_pulse()
 */
PJ_DEF(pj_status_t) pj_event_pulse(pj_event_t *event)
{
    PJ_CHECK_STACK();
    PJ_ASSERT_RETURN(event, PJ_EINVAL);

    PJ_LOG(6, (event->obj_name, "Pulsing event"));

    if (PulseEvent(event->hEvent))
        return PJ_SUCCESS;
    else
        return PJ_RETURN_OS_ERROR(GetLastError());
}