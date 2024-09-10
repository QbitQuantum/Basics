bool ReadD81 (MemFile &file, std::shared_ptr<Disk> &disk)
{
	// D81 is a fixed-size image
	uint8_t ab[256];
	if (file.size() != D81_DISK_SIZE || !file.seek(D81_HEADER_OFFSET) || !file.read(&ab, sizeof(ab)))
		return false;

	// Check for 1581 signature and various check bytes
	if (ab[2] != 'D' || ab[3] || ab[0x14] != 0xa0 || ab[0x15] != 0xa0 || ab[0x1b] != 0xa0 || ab[0x1c] != 0xa0)
		return false;

	Format fmt { RegularFormat::D81 };

	// D2M stores the sides in the reverse order, so fiddle things to read it easily
	file.rewind();
	std::swap(fmt.head0, fmt.head1);
	disk->format(fmt, file.data());
	std::swap(disk->fmt.head0, disk->fmt.head1);
	disk->flip_sides();
	disk->strType = "D81";

	return true;
}