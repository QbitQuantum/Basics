bool ReadSCP (MemFile &file, std::shared_ptr<Disk> &disk)
{
	SCP_FILE_HEADER fh {};

	if (!file.rewind() || !file.read(&fh, sizeof(fh)) || std::string(fh.signature, 3) != "SCP")
		return false;

	/*if (!(fh.flags & FLAG_INDEX))
		throw util::exception("not an index-synchronised image");
	else*/ if (fh.revolutions == 0 || fh.revolutions > 10)
		throw util::exception("invalid revolution count (", fh.revolutions, ")");
	else if (fh.bitcell_width != 0 && fh.bitcell_width != 16)
		throw util::exception("unsupported bit cell width (", fh.bitcell_width, ")");
	else if (fh.start_track > fh.end_track)
		throw util::exception("start track (", fh.start_track, ") > end track (", fh.end_track, ")");

	std::vector<uint32_t> tdh_offsets(fh.end_track + 1);
	if (!file.read(tdh_offsets))
		throw util::exception("short file reading track offset index");

	auto scp_disk = std::make_shared<SCPDisk>();

	for (auto tracknr = fh.start_track; tracknr <= fh.end_track; ++tracknr)
	{
		TRACK_DATA_HEADER tdh;
		auto cyl = tracknr >> 1;
		auto head = tracknr & 1;
		CylHead cylhead(cyl, head);

		if (!tdh_offsets[tracknr])
			continue;

		if (!file.seek(tdh_offsets[tracknr]) || !file.read(&tdh, sizeof(tdh)))
			throw util::exception("short file reading ", cylhead, " track header");
		else if (std::string(tdh.signature, 3) != "TRK")
			throw util::exception("invalid track signature on ", cylhead);
		else if (tdh.tracknr != tracknr)
			throw util::exception("track number mismatch (", tdh.tracknr, " != ", tracknr, ") in ", cylhead, " header");

		std::vector<uint32_t> rev_index(fh.revolutions * 3);
		if (!file.read(rev_index))
			throw util::exception("short file reading ", cylhead, " track index");

		std::vector<std::vector<uint16_t>> revs_data;
		revs_data.reserve(fh.revolutions);

		for (uint8_t rev = 0; rev < fh.revolutions; ++rev)
		{
//			auto index_time  = util::letoh<uint32_t>(rev_index[rev * 3 + 0]);
			auto flux_count = util::letoh<uint32_t>(rev_index[rev * 3 + 1]);
			auto data_offset = util::letoh<uint32_t>(rev_index[rev * 3 + 2]);

			std::vector<uint16_t> flux_data(flux_count);
			if (!file.seek(tdh_offsets[tracknr] + data_offset) || !file.read(flux_data))
				throw util::exception("short error reading ", cylhead, " data");

			revs_data.push_back(std::move(flux_data));
		}

		scp_disk->add_track_data(cylhead, std::move(revs_data));
	}

	scp_disk->strType = "SCP";
	disk = scp_disk;

	return true;
}