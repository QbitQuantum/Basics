/*
 * handle all the APDU's that are common to all CAC applets
 */
static VCardStatus
passthru_process_apdu(VCard *card, VCardAPDU *apdu, VCardResponse **response)
{
    LONG rv;
    unsigned char buf[MAX_RESPONSE_LENGTH];
    uint32_t len = MAX_RESPONSE_LENGTH;
    VCardAppletPrivate *applet_private = NULL;
    SCARD_IO_REQUEST receive_io;

    applet_private = vcard_get_current_applet_private(card, 0);
    if (applet_private == NULL) {
       *response = vcard_make_response(VCARD7816_STATUS_EXC_ERROR);
       return VCARD_DONE;
    }

    rv = SCardTransmit(applet_private->hCard, applet_private->send_io,
                       apdu->a_data, apdu->a_len, &receive_io, buf, &len);
    if (rv != SCARD_S_SUCCESS) {
       *response = vcard_make_response(VCARD7816_STATUS_EXC_ERROR);
       return VCARD_DONE;
    }

    *response = vcard_response_new_data(buf,len);
    if (*response == NULL) {
       *response =
            vcard_make_response(VCARD7816_STATUS_EXC_ERROR_MEMORY_FAILURE);
    } else {
       (*response)->b_total_len = (*response)->b_len;
    }
    return VCARD_DONE;
}