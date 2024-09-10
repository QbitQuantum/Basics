void mld_interface::handle_mldv2_membership_report(const in6_addr &src,
						   mldv2_report *mldhdr,
						   int len) {
	m_stats.counter(ReportV2Count, RX)++;
	mld->stats().counter(ReportV2Count, RX)++;

	mldv2_mrec *mrec = mldhdr->mrecs();
	int clen = 0;

	int reccount = ntoh(mldhdr->nmrecs());

	for (int i = 0; i < reccount && clen < len; i++, mrec = mrec->next()) {
		clen += sizeof(mldv2_mrec);
		if (clen <= len)
			clen += sizeof(in6_addr) * ntoh(mrec->nsrcs);
	}

	if (clen > len) {
		if (should_log(MESSAGE_ERR))
			log().writeline("Dropped badly formed MLDv2 Membership");

		m_stats.counter(ReportV2Count, Bad)++;
		mld->stats().counter(ReportV2Count, Bad)++;
		return;
	}

	mrec = mldhdr->mrecs();
	for (int i = 0; i < reccount; i++, mrec = mrec->next()) {
		if (!IN6_IS_ADDR_MULTICAST(&mrec->mca) ||
		     IN6_IS_ADDR_MC_NODELOCAL(&mrec->mca) ||
		     IN6_IS_ADDR_MC_LINKLOCAL(&mrec->mca))
			continue;

		address_set sources;
		in6_addr *srcs = mrec->sources();
		for (uint16_t j = 0; j < ntoh(mrec->nsrcs); j++)
			sources += srcs[j];

		handle_mode_change_for_group(2, src, mrec->mca, mrec->type, sources);
	}
}