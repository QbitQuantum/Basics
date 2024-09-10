/*
 * Connection established.
 * We get here for both outgoing and incoming connection.
 */
void
rdsv3_ib_cm_connect_complete(struct rdsv3_connection *conn,
    struct rdma_cm_event *event)
{
	const struct rdsv3_ib_connect_private *dp = NULL;
	struct rdsv3_ib_connection *ic = conn->c_transport_data;
	struct rdsv3_ib_device *rds_ibdev =
	    ib_get_client_data(ic->i_cm_id->device, &rdsv3_ib_client);
	struct ib_qp_attr qp_attr;
	int err;

	RDSV3_DPRINTF2("rdsv3_ib_cm_connect_complete",
	    "Enter conn: %p event: %p", conn, event);

	if (event->param.conn.private_data_len >= sizeof (*dp)) {
		dp = event->param.conn.private_data;

		/* make sure it isn't empty data */
		if (dp->dp_protocol_major) {
			rdsv3_ib_set_protocol(conn,
			    RDS_PROTOCOL(dp->dp_protocol_major,
			    dp->dp_protocol_minor));
			rdsv3_ib_set_flow_control(conn,
			    ntohl(dp->dp_credit));
		}
	}

	if (conn->c_version < RDS_PROTOCOL(3, 1)) {
		RDSV3_DPRINTF2("rdsv3_ib_cm_connect_complete",
		    "RDS/IB: Connection to %u.%u.%u.%u version %u.%u failed",
		    NIPQUAD(conn->c_faddr),
		    RDS_PROTOCOL_MAJOR(conn->c_version),
		    RDS_PROTOCOL_MINOR(conn->c_version));
		rdsv3_conn_destroy(conn);
		return;
	} else {
		RDSV3_DPRINTF2("rdsv3_ib_cm_connect_complete",
		    "RDS/IB: connected to %u.%u.%u.%u version %u.%u%s",
		    NIPQUAD(conn->c_faddr),
		    RDS_PROTOCOL_MAJOR(conn->c_version),
		    RDS_PROTOCOL_MINOR(conn->c_version),
		    ic->i_flowctl ? ", flow control" : "");
	}

	ASSERT(ic->i_soft_cq == NULL);
	ic->i_soft_cq = rdsv3_af_intr_thr_create(rdsv3_ib_tasklet_fn,
	    (void *)ic, SCQ_INTR_BIND_CPU, rds_ibdev->aft_hcagp,
	    ic->i_cq->ibt_cq);
	if (rdsv3_enable_snd_cq) {
		ic->i_snd_soft_cq = rdsv3_af_intr_thr_create(
		    rdsv3_ib_snd_tasklet_fn,
		    (void *)ic, SCQ_INTR_BIND_CPU, rds_ibdev->aft_hcagp,
		    ic->i_snd_cq->ibt_cq);
	}
	/* rdsv3_ib_refill_fn is expecting i_max_recv_alloc set */
	ic->i_max_recv_alloc = rdsv3_ib_sysctl_max_recv_allocation;
	ic->i_refill_rq = rdsv3_af_thr_create(rdsv3_ib_refill_fn, (void *)conn,
	    SCQ_WRK_BIND_CPU, rds_ibdev->aft_hcagp);
	rdsv3_af_grp_draw(rds_ibdev->aft_hcagp);

	(void) ib_req_notify_cq(ic->i_cq, IB_CQ_SOLICITED);
	if (rdsv3_enable_snd_cq) {
		(void) ib_req_notify_cq(ic->i_snd_cq, IB_CQ_NEXT_COMP);
	}

	/*
	 * Init rings and fill recv. this needs to wait until protocol
	 * negotiation
	 * is complete, since ring layout is different from 3.0 to 3.1.
	 */
	rdsv3_ib_send_init_ring(ic);
	rdsv3_ib_recv_init_ring(ic);
	/*
	 * Post receive buffers - as a side effect, this will update
	 * the posted credit count.
	 */
	(void) rdsv3_ib_recv_refill(conn, 1);

	/* Tune RNR behavior */
	rdsv3_ib_tune_rnr(ic, &qp_attr);

	qp_attr.qp_state = IB_QPS_RTS;
	err = ib_modify_qp(ic->i_cm_id->qp, &qp_attr, IB_QP_STATE);
	if (err)
		RDSV3_DPRINTF2("rdsv3_ib_cm_connect_complete",
		    "ib_modify_qp(IB_QP_STATE, RTS): err=%d", err);

	/* update ib_device with this local ipaddr & conn */
	err = rdsv3_ib_update_ipaddr(rds_ibdev, conn->c_laddr);
	if (err)
		RDSV3_DPRINTF2("rdsv3_ib_cm_connect_complete",
		    "rdsv3_ib_update_ipaddr failed (%d)", err);
	rdsv3_ib_add_conn(rds_ibdev, conn);

	/*
	 * If the peer gave us the last packet it saw, process this as if
	 * we had received a regular ACK.
	 */
	if (dp && dp->dp_ack_seq)
		rdsv3_send_drop_acked(conn, ntohll(dp->dp_ack_seq), NULL);

	rdsv3_connect_complete(conn);

	RDSV3_DPRINTF2("rdsv3_ib_cm_connect_complete",
	    "Return conn: %p event: %p",
	    conn, event);
}