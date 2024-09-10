void JoinPBX::bridge(void)
{
	struct join_relation *relation;
	struct lcr_msg *message;
	int numconnect = 0, relations = 0;
	class Endpoint *epoint;
	struct port_list *portlist;
	class Port *port;
	unsigned int bridge_id;
	class Join *join_3pty;
	class JoinPBX *joinpbx_3pty;
#ifdef DEBUG_COREBRIDGE
	int allmISDN = 0; // never set for debug purpose
#else
	int allmISDN = 1; // set until a non-mISDN relation is found
#endif

	/* bridge id is the serial of join
	 * if we have a 3pty with another join, we always use the lowest brigde id.
	 * this way we use common ids, so both joins share same bridge */
	if (j_3pty && j_3pty < j_serial)
		bridge_id = j_3pty;
	else
		bridge_id = j_serial;

	relation = j_relation;
	while(relation) {
		/* count all relations */
		relations++;

		/* check for relation's objects */
		epoint = find_epoint_id(relation->epoint_id);
		if (!epoint) {
			PERROR("software error: relation without existing endpoints.\n");
			relation = relation->next;
			continue;
		}
		portlist = epoint->ep_portlist;
		if (!portlist) {
			PDEBUG(DEBUG_JOIN, "join%d ignoring relation without port object.\n", j_serial);
//#warning testing: keep on hold until single audio stream available
			relation->channel_state = 0;
			relation = relation->next;
			continue;
		}
		if (portlist->next) {
			PDEBUG(DEBUG_JOIN, "join%d ignoring relation with ep%d due to port_list.\n", j_serial, epoint->ep_serial);
//#warning testing: keep on hold until single audio stream available
			relation->channel_state = 0;
			relation = relation->next;
			continue;
		}
		port = find_port_id(portlist->port_id);
		if (!port) {
			PDEBUG(DEBUG_JOIN, "join%d ignoring relation without existing port object.\n", j_serial);
			relation = relation->next;
			continue;
		}
		if ((port->p_type&PORT_CLASS_MASK)!=PORT_CLASS_mISDN) {
			PDEBUG(DEBUG_JOIN, "join%d ignoring relation ep%d because it's port is not mISDN.\n", j_serial, epoint->ep_serial);
			if (allmISDN) {
				PDEBUG(DEBUG_JOIN, "join%d not all endpoints are mISDN.\n", j_serial);
				allmISDN = 0;
			}
			relation = relation->next;
			continue;
		}

		relation = relation->next;
	}

	/* check if 3pty members have no mISDN, so bridging via mISDN/lcr will be selected correctly */
	join_3pty = find_join_id(j_3pty);
	if (join_3pty && join_3pty->j_type == JOIN_TYPE_PBX) {
		joinpbx_3pty = (class JoinPBX *)join_3pty;
		relation = joinpbx_3pty->j_relation;
		while(relation) {

#if 0
no need to count, because j_3pty is taken into account below when checking relations
			/* count all relations */
			relations++;
#endif

			/* check for relation's objects */
			epoint = find_epoint_id(relation->epoint_id);
			if (!epoint) {
				PERROR("software error: relation without existing endpoints.\n");
				relation = relation->next;
				continue;
			}
			portlist = epoint->ep_portlist;
			if (!portlist) {
				PDEBUG(DEBUG_JOIN, "other 3pty join %d: ignoring relation without port object.\n", joinpbx_3pty->j_serial);
//#warning testing: keep on hold until single audio stream available
				relation->channel_state = 0;
				relation = relation->next;
				continue;
			}
			if (portlist->next) {
				PDEBUG(DEBUG_JOIN, "other 3pty join %d: ignoring relation with ep%d due to port_list.\n", joinpbx_3pty->j_serial, epoint->ep_serial);
//#warning testing: keep on hold until single audio stream available
				relation->channel_state = 0;
				relation = relation->next;
				continue;
			}
			port = find_port_id(portlist->port_id);
			if (!port) {
				PDEBUG(DEBUG_JOIN, "other 3pty join %d: ignoring relation without existing port object.\n", joinpbx_3pty->j_serial);
				relation = relation->next;
				continue;
			}
			if ((port->p_type&PORT_CLASS_MASK)!=PORT_CLASS_mISDN) {
				PDEBUG(DEBUG_JOIN, "other 3pty join %d: ignoring relation ep%d because it's port is not mISDN.\n", joinpbx_3pty->j_serial, epoint->ep_serial);
				if (allmISDN) {
					PDEBUG(DEBUG_JOIN, "other 3pty join %d: not all endpoints are mISDN.\n", joinpbx_3pty->j_serial);
					allmISDN = 0;
				}
				relation = relation->next;
				continue;
			}

			relation = relation->next;
		}
	}

	PDEBUG(DEBUG_JOIN, "join%d members=%d %s\n", j_serial, relations, (allmISDN)?"(all are mISDN-members)":"(not all are mISDN-members)");
	/* we notify all relations about rxdata. */
	relation = j_relation;
	while(relation) {
		/* count connected relations */
		if ((relation->channel_state == 1)
		 && (relation->rx_state != NOTIFY_STATE_SUSPEND)
		 && (relation->rx_state != NOTIFY_STATE_HOLD))
			numconnect ++;

		/* remove unconnected parties from conference, also remove remotely disconnected parties so conference will not be disturbed. */

		/* mISDN */
		if (relation->channel_state == 1
		 && relation->rx_state != NOTIFY_STATE_HOLD
		 && relation->rx_state != NOTIFY_STATE_SUSPEND
		 && relations>1 // no conf with one member
		 && allmISDN) { // no conf if any member is not mISDN
			message = message_create(j_serial, relation->epoint_id, JOIN_TO_EPOINT, MESSAGE_mISDNSIGNAL);
			message->param.mISDNsignal.message = mISDNSIGNAL_CONF;
			message->param.mISDNsignal.conf = (bridge_id << 16) | j_pid;
			PDEBUG(DEBUG_JOIN, "join%d EP%d +on+ id: 0x%08x\n", j_serial, relation->epoint_id, message->param.mISDNsignal.conf);
			message_put(message);
		} else {
			message = message_create(j_serial, relation->epoint_id, JOIN_TO_EPOINT, MESSAGE_mISDNSIGNAL);
			message->param.mISDNsignal.message = mISDNSIGNAL_CONF;
			message->param.mISDNsignal.conf = 0;
			PDEBUG(DEBUG_JOIN, "join%d EP%d +off+ id: 0x%08x\n", j_serial, relation->epoint_id, message->param.mISDNsignal.conf);
			message_put(message);
		}

		/* core bridge */
		if (relation->channel_state == 1
		 && relation->rx_state != NOTIFY_STATE_HOLD
		 && relation->rx_state != NOTIFY_STATE_SUSPEND
		 && relations>1 // no bridge with one member
		 && !allmISDN) { // no bridge if all members are mISDN
			message = message_create(j_serial, relation->epoint_id, JOIN_TO_EPOINT, MESSAGE_BRIDGE);
			message->param.bridge_id = bridge_id;
			PDEBUG(DEBUG_JOIN, "join%u EP%u requests bridge=%u\n", j_serial, relation->epoint_id, bridge_id);
			message_put(message);
		} else {
			message = message_create(j_serial, relation->epoint_id, JOIN_TO_EPOINT, MESSAGE_BRIDGE);
			message->param.bridge_id = 0;
			PDEBUG(DEBUG_JOIN, "join%u EP%u drop bridge=%u\n", j_serial, relation->epoint_id, bridge_id);
			message_put(message);
		}

		relation = relation->next;
	}

	/* two people just exchange their states */
	if (!j_3pty && relations==2 && !j_partyline) {
		PDEBUG(DEBUG_JOIN, "join%d 2 relations / no partyline\n", j_serial);
		relation = j_relation;
		relation->tx_state = notify_state_change(j_serial, relation->epoint_id, relation->tx_state, relation->next->rx_state);
		relation->next->tx_state = notify_state_change(j_serial, relation->next->epoint_id, relation->next->tx_state, relation->rx_state);
	} else
	/* one member in a join, so we put her on hold */
	if (!j_3pty && (relations==1 || numconnect==1)/* && !j_partyline_jingle*/) {
		PDEBUG(DEBUG_JOIN, "join%d 1 member or only 1 connected, put on hold\n", j_serial);
		relation = j_relation;
		while(relation) {
			if ((relation->channel_state == 1)
			 && (relation->rx_state != NOTIFY_STATE_SUSPEND)
			 && (relation->rx_state != NOTIFY_STATE_HOLD))
				relation->tx_state = notify_state_change(j_serial, relation->epoint_id, relation->tx_state, NOTIFY_STATE_HOLD);
			relation = relation->next;
		}
	} else {
	/* if conference/partyline (or more than two members and more than one is connected), so we set conference state */ 
		PDEBUG(DEBUG_JOIN, "join%d %d members, %d connected, signal conference\n", j_serial, relations, numconnect);
		relation = j_relation;
		while(relation) {
			if ((relation->channel_state == 1)
			 && (relation->rx_state != NOTIFY_STATE_SUSPEND)
			 && (relation->rx_state != NOTIFY_STATE_HOLD))
				relation->tx_state = notify_state_change(j_serial, relation->epoint_id, relation->tx_state, NOTIFY_STATE_CONFERENCE);
			relation = relation->next;
		}
	}
}