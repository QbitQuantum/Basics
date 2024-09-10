void nes_disksys_device::load_disk(device_image_interface &image)
{
	int header = 0;
	m_fds_sides = 0;

	if (image.length() % 65500)
		header = 0x10;

	m_fds_sides = (image.length() - header) / 65500;

	if (!m_fds_data)
		m_fds_data = std::make_unique<UINT8[]>(m_fds_sides * 65500);

	// if there is an header, skip it
	image.fseek(header, SEEK_SET);
	image.fread(m_fds_data.get(), 65500 * m_fds_sides);
	return;
}