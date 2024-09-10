/* Determine current transaction
 *
 *                   Found      Not Found     Error (e.g. parsing)
 *  Return Value     1          0             -1
 *  T                ptr        0             T_UNDEFINED
 */
int t_check( struct sip_msg* p_msg , int *param_branch )
{
	int local_branch;

	/* is T still up-to-date ? */
	LM_DBG("start=%p\n", T);
	if ( T==T_UNDEFINED )
	{
		/* transaction lookup */
		if ( p_msg->first_line.type==SIP_REQUEST ) {
			/* force parsing all the needed headers*/
			if (parse_headers(p_msg, HDR_EOH_F, 0 )==-1) {
				LM_ERR("parsing error\n");
				return -1;
			}
			/* in case, we act as UAS for INVITE and reply with 200,
			 * we will need to run dialog-matching for subsequent
			 * ACK, for which we need From-tag; We also need from-tag
			 * in case people want to have proxied e2e ACKs accounted
			 */
			if (p_msg->REQ_METHOD==METHOD_INVITE
							&& parse_from_header(p_msg)<0) {
				LM_ERR("from parsing failed\n");
				return -1;
			}
			t_lookup_request( p_msg , 0 /* unlock before returning */ );
		} else {
			/* we need Via for branch and Cseq method to distinguish
			   replies with the same branch/cseqNr (CANCEL)
			*/
			if ( parse_headers(p_msg, HDR_VIA1_F|HDR_CSEQ_F, 0 )==-1
			|| !p_msg->via1 || !p_msg->cseq ) {
				LM_ERR("reply cannot be parsed\n");
				return -1;
			}

			/* if that is an INVITE, we will also need to-tag
			   for later ACK matching */
			if ( get_cseq(p_msg)->method_id==METHOD_INVITE ) {
					if (parse_headers(p_msg, HDR_TO_F, 0)==-1 || !p_msg->to)  {
						LM_ERR("INVITE reply cannot be parsed\n");
						return -1;
					}
			}

			t_reply_matching( p_msg ,
				param_branch!=0?param_branch:&local_branch );

		}
#ifdef EXTRA_DEBUG
		if ( T && T!=T_UNDEFINED && T->damocles) {
			LM_ERR("transaction %p scheduled for deletion "
				"and called from t_check\n", T);
			abort();
		}
#endif
		LM_DBG("end=%p\n",T);
	} else {
		if (T)
			LM_DBG("transaction already found!\n");
		else
			LM_DBG("transaction previously sought and not found\n");
	}

	return T ? (T==T_UNDEFINED ? -1 : 1 ) : 0;
}