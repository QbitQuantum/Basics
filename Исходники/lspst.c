void process(pst_item *outeritem, pst_desc_tree *d_ptr)
{
    struct file_ll ff;
    pst_item *item = NULL;
    char *result = NULL;
    size_t resultlen = 0;

    DEBUG_ENT("process");
    memset(&ff, 0, sizeof(ff));
    create_enter_dir(&ff, outeritem);

    while (d_ptr) {
        if (!d_ptr->desc) {
            DEBUG_WARN(("ERROR item's desc record is NULL\n"));
            ff.skip_count++;
        }
        else {
            DEBUG_INFO(("Desc Email ID %"PRIx64" [d_ptr->d_id = %"PRIx64"]\n", d_ptr->desc->i_id, d_ptr->d_id));

            item = pst_parse_item(&pstfile, d_ptr, NULL);
            DEBUG_INFO(("About to process item @ %p.\n", item));
            if (item) {
                if (item->message_store) {
                    // there should only be one message_store, and we have already done it
                    DIE(("A second message_store has been found. Sorry, this must be an error.\n"));
                }

                if (item->folder && d_ptr->child) {
                    // if this is a folder, we want to recurse into it
                    pst_convert_utf8(item, &item->file_as);
                    printf("Folder \"%s\"\n", item->file_as.str);
                    process(item, d_ptr->child);

                } else if (item->contact && (item->type == PST_TYPE_CONTACT)) {
                    if (!ff.type) ff.type = item->type;
                    // Process Contact item
                    if (ff.type != PST_TYPE_CONTACT) {
                        DEBUG_INFO(("I have a contact, but the folder isn't a contacts folder. Processing anyway\n"));
                    }
                    printf("Contact");
                    if (item->contact->fullname.str)
                        printf("\t%s", pst_rfc2426_escape(item->contact->fullname.str, &result, &resultlen));
                    printf("\n");

                } else if (item->email && ((item->type == PST_TYPE_NOTE) || (item->type == PST_TYPE_SCHEDULE) || (item->type == PST_TYPE_REPORT))) {
                    if (!ff.type) ff.type = item->type;
                    // Process Email item
                    if ((ff.type != PST_TYPE_NOTE) && (ff.type != PST_TYPE_SCHEDULE) && (ff.type != PST_TYPE_REPORT)) {
                        DEBUG_INFO(("I have an email, but the folder isn't an email folder. Processing anyway\n"));
                    }
                    printf("Email");
                    if (item->email->outlook_sender_name.str)
                        printf("\tFrom: %s", item->email->outlook_sender_name.str);
                    if (item->subject.str)
                        printf("\tSubject: %s", item->subject.str);
                    printf("\n");

                } else if (item->journal && (item->type == PST_TYPE_JOURNAL)) {
                    if (!ff.type) ff.type = item->type;
                    // Process Journal item
                    if (ff.type != PST_TYPE_JOURNAL) {
                        DEBUG_INFO(("I have a journal entry, but folder isn't specified as a journal type. Processing...\n"));
                    }
                    if (item->subject.str)
                        printf("Journal\t%s\n", pst_rfc2426_escape(item->subject.str, &result, &resultlen));

                } else if (item->appointment && (item->type == PST_TYPE_APPOINTMENT)) {
                    char time_buffer[30];
                    if (!ff.type) ff.type = item->type;
                    // Process Calendar Appointment item
                    DEBUG_INFO(("Processing Appointment Entry\n"));
                    if (ff.type != PST_TYPE_APPOINTMENT) {
                        DEBUG_INFO(("I have an appointment, but folder isn't specified as an appointment type. Processing...\n"));
                    }
                    printf("Appointment");
                    if (item->subject.str)
                        printf("\tSUMMARY: %s", pst_rfc2426_escape(item->subject.str, &result, &resultlen));
                    if (item->appointment->start)
                        printf("\tSTART: %s", pst_rfc2445_datetime_format(item->appointment->start, sizeof(time_buffer), time_buffer));
                    if (item->appointment->end)
                        printf("\tEND: %s", pst_rfc2445_datetime_format(item->appointment->end, sizeof(time_buffer), time_buffer));
                    printf("\tALL DAY: %s", (item->appointment->all_day==1 ? "Yes" : "No"));
                    printf("\n");

                } else {
                    ff.skip_count++;
                    DEBUG_INFO(("Unknown item type. %i. Ascii1=\"%s\"\n",
                                      item->type, item->ascii_type));
                }
                pst_freeItem(item);
            } else {
                ff.skip_count++;
                DEBUG_INFO(("A NULL item was seen\n"));
            }
        }
        d_ptr = d_ptr->next;
    }
    close_enter_dir(&ff);
    if (result) free(result);
    DEBUG_RET();
}