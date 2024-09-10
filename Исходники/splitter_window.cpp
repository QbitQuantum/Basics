int splitter_window_impl::override_size(unsigned & panel, int delta)
{
	//console::formatter() << "Overriding " << panel << " by " << delta;
	struct t_min_max_info
	{
		unsigned min_height;
		unsigned max_height;
		unsigned height;
		//unsigned caption_height;
	};

	unsigned count = m_panels.get_count();
	if (count)
	{
		save_sizes();
		if (panel + 1 < count)
		{
			unsigned n = 0;

			unsigned the_caption_height = g_get_caption_size();
			pfc::array_t<t_min_max_info> minmax;
			minmax.set_size(count);

			//minmax.fill(0);
			memset(minmax.get_ptr(), 0, minmax.get_size()*sizeof(t_min_max_info));

			for (n = 0; n<count; n++)
			{
				unsigned caption_height = m_panels[n]->m_show_caption && m_panels[n]->m_caption_orientation != get_orientation() ? the_caption_height : 0;
				unsigned min_height = m_panels[n]->m_hidden ? 0 : get_orientation() == vertical ? m_panels[n]->m_size_limits.min_height : m_panels[n]->m_size_limits.min_width;
				unsigned max_height = m_panels[n]->m_hidden ? 0 : get_orientation() == vertical ? m_panels[n]->m_size_limits.max_height : m_panels[n]->m_size_limits.max_width;

				if (min_height < (unsigned)(0 - caption_height)) min_height += caption_height;
				if (max_height < (unsigned)(0 - caption_height)) max_height += caption_height;

				if (get_orientation() == horizontal && m_panels[n]->m_show_toggle_area && !m_panels[n]->m_autohide)
				{
					if (max_height < unsigned(pfc_infinite) - 1)
						max_height++;
					if (min_height < unsigned(pfc_infinite) - 1)
						min_height++;
					caption_height++;
				}

				//minmax[n].caption_height = caption_height;
				minmax[n].min_height = min_height;
				minmax[n].max_height = max_height;
				minmax[n].height = m_panels[n]->m_hidden ? caption_height : m_panels[n]->m_size;
			}

			bool is_up = delta < 0;//new_height < m_panels[panel].height;
			bool is_down = delta > 0;//new_height > m_panels[panel].height;

			if (is_up /*&& !m_panels[panel].locked*/)
			{

				unsigned diff_abs = 0, diff_avail = abs(delta);

				unsigned n = panel + 1;
				while (n < count && diff_abs < diff_avail)
				{
					{
						unsigned height = minmax[n].height + (diff_avail - diff_abs);//(diff_avail-diff_abs > m_panels[n]->height ? 0 : m_panels[n]->height-(diff_avail-diff_abs));

						unsigned min_height = minmax[n].min_height;
						unsigned max_height = minmax[n].max_height;

						if (height < min_height)
						{
							height = min_height;
						}
						else if (height > max_height)
						{
							height = max_height;
						}

						diff_abs += height - minmax[n].height;
					}
					n++;
				}

				n = panel + 1;
				unsigned obtained = 0;
				while (n>0 && obtained < diff_abs)
				{
					n--;
					//					if (!m_panels[n]->locked)
					{
						unsigned height = (diff_abs - obtained > minmax[n].height ? 0 : minmax[n].height - (diff_abs - obtained));

						//unsigned caption_height = m_panels[n]->m_show_caption ? the_caption_height : 0;

						unsigned min_height = minmax[n].min_height;
						unsigned max_height = minmax[n].max_height;


						if (height < min_height)
						{
							height = min_height;
						}
						else if (height > max_height)
						{
							height = max_height;
						}

						obtained += minmax[n].height - height;
						minmax[n].height = height;
						if (!m_panels[n]->m_hidden) m_panels[n]->m_size = height;

					}
				}
				n = panel;
				unsigned obtained2 = obtained;

				while (n < count - 1 && obtained2)
				{
					n++;
					unsigned height = (minmax[n].height);

					unsigned min_height = minmax[n].min_height;
					unsigned max_height = minmax[n].max_height;

					height += obtained2;

					if (height < min_height)
					{
						height = min_height;
					}
					else if (height > max_height)
					{
						height = max_height;
					}

					obtained2 -= height - minmax[n].height;
					minmax[n].height = height;
					if (!m_panels[n]->m_hidden) m_panels[n]->m_size = height;
				}
				return (abs(delta) - obtained);


			}
			else if (is_down /*&& !m_panels[panel].locked*/)
			{
				unsigned diff_abs = 0, diff_avail = abs(delta);

				n = panel + 1;
				while (n >0 && diff_abs < diff_avail)
				{
					n--;
					{
						unsigned height = minmax[n].height + (diff_avail - diff_abs);//(diff_avail-diff_abs > m_panels[n]->height ? 0 : m_panels[n]->height-(diff_avail-diff_abs));
						//console::formatter() << "1: " << height << " " << minmax[n].height << " " << (diff_avail-diff_abs);

						unsigned min_height = minmax[n].min_height;
						unsigned max_height = minmax[n].max_height;

						if (height < min_height)
						{
							height = min_height;
						}
						else if (height > max_height)
						{
							height = max_height;
						}


						diff_abs += height - minmax[n].height;
					}
				}
				n = panel;
				unsigned obtained = 0;
				while (n < count - 1 && obtained < diff_abs)
				{
					n++;
					//				if (!m_panels[n]->locked)
					{
						unsigned height = (diff_abs - obtained > minmax[n].height ? 0 : minmax[n].height - (diff_abs - obtained));
						//console::formatter() << "2: " << height << " " << minmax[n].height << " " << (diff_abs-obtained);

						//unsigned caption_height = minmax[n].caption_height;
						unsigned min_height = minmax[n].min_height;
						unsigned max_height = minmax[n].max_height;


						if (height < min_height)
						{
							height = min_height;
						}
						else if (height > max_height)
						{
							height = max_height;
						}

						obtained += minmax[n].height - height;
						minmax[n].height = height;
						if (!m_panels[n]->m_hidden) m_panels[n]->m_size = height;

					}
				}
				n = panel + 1;
				unsigned obtained2 = obtained;
				while (n >0 && obtained2)
				{
					n--;
					unsigned height = (minmax[n].height);
					unsigned min_height = minmax[n].min_height;
					unsigned max_height = minmax[n].max_height;

					height += obtained2;

					if (height < min_height)
					{
						height = min_height;
					}
					else if (height > max_height)
					{
						height = max_height;
					}

					obtained2 -= height - minmax[n].height;

					minmax[n].height = height;

					if (!m_panels[n]->m_hidden) m_panels[n]->m_size = height;
				}
				//console::formatter() << "3: " << abs(delta) << " " << obtained;
				return 0 - (abs(delta) - obtained);

			}

		}
	}
	return 0;
}