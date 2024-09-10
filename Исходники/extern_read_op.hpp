	bool read_data(char* data, size_type offset, size_type size, size_type& read_size)
	{
		boost::mutex::scoped_lock lock(m_notify_mutex);
		const torrent_info& info = m_handle.get_torrent_info();
		bool ret = false;

		read_size = 0;

#if defined(_DEBUG) && defined(WIN32)
		unsigned int time = GetTickCount();
#endif
		// 计算偏移所在的片.
		int index = offset / info.piece_length();
		BOOST_ASSERT(index >= 0 && index < info.num_pieces());
		if (index >= info.num_pieces() || index < 0)
			return ret;
		torrent_status status = m_handle.status();
		if (!status.pieces.empty())
		{
			if (status.state != torrent_status::downloading &&
				status.state != torrent_status::finished &&
				status.state != torrent_status::seeding)
				return ret;

			// 设置下载位置.
			std::vector<int> pieces;

			pieces = m_handle.piece_priorities();
			std::for_each(pieces.begin(), pieces.end(), boost::lambda::_1 = 1);
			pieces[index] = 7;
			m_handle.prioritize_pieces(pieces);

			if (status.pieces.get_bit(index))
			{
				// 保存参数信息.
				m_current_buffer = data;
				m_read_offset = offset;
				m_read_size = &read_size;
				m_request_size = size;

				// 提交请求.
				m_handle.read_piece(index, boost::bind(&extern_read_op::on_read, this, _1, _2, _3));

				// 等待请求返回.
				m_notify.wait(lock);

				// 读取字节数.
				if (read_size != 0)
					ret = true;
			}
		}
		else
		{
			// 直接读取文件.
			if (m_file_path.string() == "" || !m_file.is_open())
			{
				boost::filesystem::path path = m_handle.save_path();
				const file_storage& stor = info.files();
				std::string name = stor.name();
				m_file_path = path / name;
				name = convert_to_native(m_file_path.string());

				// 打开文件, 直接从文件读取数据.
				if (!m_file.is_open())
				{
					m_file.open(name.c_str(), std::ios::in | std::ios::binary);
					if (!m_file.is_open())
						return ret;
				}
			}

			if (!m_file.is_open())
				return ret;

            m_file.clear();
            m_file.seekg(offset, std::ios::beg);
            m_file.read(data, size);
            read_size = m_file.gcount();

			if (read_size != -1)
				ret = true;
		}

#if defined(_DEBUG) && defined(WIN32)
		static unsigned int cur_time = GetTickCount();
			char str_info[8192] = { 0 };
			char *ptr = (char*)str_info;
		if (GetTickCount() - cur_time >= 5000)
		{
			cur_time = GetTickCount();
			sprintf(str_info, "request: %d, size: %d, request time: %d, peers: %d\n", 
				index, (int)size, cur_time - time, status.num_peers);
			ptr = ptr + strlen(str_info);
			for (int i = 0; i < status.pieces.size() / 8; i++)
			{
				if (i % 32 == 0)
				{
					sprintf(ptr, "\n");
					ptr += 1;
				}
				sprintf(ptr, "%02X", (unsigned char)status.pieces.bytes()[i]);
				ptr += 2;
			}
			if (status.pieces.size() % 8 != 0)
			{
				sprintf(ptr, "%02X", (unsigned char)status.pieces.bytes()[status.pieces.size() / 8]);
				ptr += 2;
			}

			sprintf(ptr, "\n\n");

			// 显示当前正在下载的分片信息.
			std::string out;
			char str[500];
			std::vector<cached_piece_info> pieces;
			torrent_handle &h = m_handle;
			std::vector<partial_piece_info> queue;
			std::vector<peer_info> peers;

			m_ses.get_cache_info(h.info_hash(), pieces);
			h.get_download_queue(queue);
			h.get_peer_info(peers);

			std::sort(queue.begin(), queue.end(), boost::bind(&partial_piece_info::piece_index, _1)
				< boost::bind(&partial_piece_info::piece_index, _2));

			std::sort(pieces.begin(), pieces.end(), boost::bind(&cached_piece_info::last_use, _1)
				> boost::bind(&cached_piece_info::last_use, _2));

			for (std::vector<cached_piece_info>::iterator i = pieces.begin();
				i != pieces.end(); ++i)
			{
				partial_piece_info* pp = 0;
				partial_piece_info tmp;
				tmp.piece_index = i->piece;
				std::vector<partial_piece_info>::iterator ppi
					= std::lower_bound(queue.begin(), queue.end(), tmp
					, boost::bind(&partial_piece_info::piece_index, _1)
					< boost::bind(&partial_piece_info::piece_index, _2));
				if (ppi != queue.end() && ppi->piece_index == i->piece) pp = &*ppi;

				print_piece(pp, &*i, peers, out);

					if (pp) queue.erase(ppi);
			}

			for (std::vector<partial_piece_info>::iterator i = queue.begin()
				 , end(queue.end()); i != end; ++i)
			{
					print_piece(&*i, 0, peers, out);
			}
			snprintf(str, sizeof(str), "%s %s: read cache %s %s: downloading %s %s: cached %s %s: flushed\n"
				, esc("34;7"), esc("0") // read cache
				, esc("33;7"), esc("0") // downloading
				, esc("36;7"), esc("0") // cached
				, esc("32;7"), esc("0")); // flushed
			out += str;
			out += "___________________________________\n";

			strcat(str_info, out.c_str());

			OutputDebugStringA(str_info);
			printf(str_info);
		}
#endif

		return ret;
	}