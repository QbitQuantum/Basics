void __lio_winev_output(IN tt_logio_t *lio,
                        IN const tt_char_t *data,
                        IN tt_u32_t data_len)
{
    tt_logio_winev_t *lio_winev = TT_LOGIO_CAST(lio, tt_logio_winev_t);

#ifdef TT_HAVE_WINDOWS_EVENT_LOG
    if (!ReportEventA(lio_winev->source,
                      lio_winev->type,
                      lio_winev->category,
                      lio_winev->ev_id,
                      NULL,
                      1,
                      0,
                      &data,
                      NULL)) {
        TT_ERROR_NTV("fail to report event: %s", data);
    }
#endif
}