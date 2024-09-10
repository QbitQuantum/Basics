/**
 * qla2x00_rsnn_nn() - SNS Register Symbolic Node Name (RSNN_NN) of the HBA.
 * @ha: HA context
 *
 * Returns 0 on success.
 */
int
qla2x00_rsnn_nn(scsi_qla_host_t *ha)
{
	int		rval;
	uint8_t		*snn;
	uint8_t		version[20];

	ms_iocb_entry_t	*ms_pkt;
	struct ct_sns_req	*ct_req;
	struct ct_sns_rsp	*ct_rsp;

	if (IS_QLA2100(ha) || IS_QLA2200(ha)) {
		DEBUG2(printk("scsi(%ld): RSNN_ID call unsupported on "
		    "ISP2100/ISP2200.\n", ha->host_no));
		return (QLA_SUCCESS);
	}

	/* Issue RSNN_NN */
	/* Prepare common MS IOCB */
	/*   Request size adjusted after CT preparation */
	ms_pkt = ha->isp_ops.prep_ms_iocb(ha, 0, RSNN_NN_RSP_SIZE);

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_req(&ha->ct_sns->p.req, RSNN_NN_CMD,
	    RSNN_NN_RSP_SIZE);
	ct_rsp = &ha->ct_sns->p.rsp;

	/* Prepare CT arguments -- node_name, symbolic node_name, size */
	memcpy(ct_req->req.rsnn_nn.node_name, ha->node_name, WWN_SIZE);

	/* Prepare the Symbolic Node Name */
	/* Board type */
	snn = ct_req->req.rsnn_nn.sym_node_name;
	strcpy(snn, ha->model_number);
	/* Firmware version */
	strcat(snn, " FW:v");
	sprintf(version, "%d.%02d.%02d", ha->fw_major_version,
	    ha->fw_minor_version, ha->fw_subminor_version);
	strcat(snn, version);
	/* Driver version */
	strcat(snn, " DVR:v");
	strcat(snn, qla2x00_version_str);

	/* Calculate SNN length */
	ct_req->req.rsnn_nn.name_len = (uint8_t)strlen(snn);

	/* Update MS IOCB request */
	ms_pkt->req_bytecount =
	    cpu_to_le32(24 + 1 + ct_req->req.rsnn_nn.name_len);
	ms_pkt->dseg_req_length = ms_pkt->req_bytecount;

	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(ha, ha->ms_iocb, ha->ms_iocb_dma,
	    sizeof(ms_iocb_entry_t));
	if (rval != QLA_SUCCESS) {
		/*EMPTY*/
		DEBUG2_3(printk("scsi(%ld): RSNN_NN issue IOCB failed (%d).\n",
		    ha->host_no, rval));
	} else if (qla2x00_chk_ms_status(ha, ms_pkt, ct_rsp, "RSNN_NN") !=
	    QLA_SUCCESS) {
		rval = QLA_FUNCTION_FAILED;
	} else {
		DEBUG2(printk("scsi(%ld): RSNN_NN exiting normally.\n",
		    ha->host_no));
	}

	return (rval);
}