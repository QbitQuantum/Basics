	void disk_buffer_pool::free_buffer_impl(char* buf, mutex::scoped_lock& l)
	{
		TORRENT_ASSERT(buf);
		TORRENT_ASSERT(m_magic == 0x1337);
		TORRENT_ASSERT(m_settings_set);
		TORRENT_ASSERT(is_disk_buffer(buf, l));

#if TORRENT_USE_MLOCK
		if (m_lock_disk_cache)
		{
#ifdef TORRENT_WINDOWS
			VirtualUnlock(buf, m_block_size);
#else
			munlock(buf, m_block_size);
#endif
		}
#endif

#if TORRENT_HAVE_MMAP
		if (m_cache_pool)
		{
			TORRENT_ASSERT(buf >= m_cache_pool);
			TORRENT_ASSERT(buf <  m_cache_pool + boost::uint64_t(m_max_use) * 0x4000);
			int slot_index = (buf - m_cache_pool) / 0x4000;
			m_free_list.push_back(slot_index);
#if defined MADV_FREE
			// tell the virtual memory system that we don't actually care
			// about the data in these pages anymore. If this block was
			// swapped out to the SSD, it (hopefully) means it won't have
			// to be read back in once we start writing our new data to it
			madvise(buf, 0x4000, MADV_FREE);
#elif defined MADV_DONTNEED && defined TORRENT_LINUX
			// rumor has it that MADV_DONTNEED is in fact destructive
			// on linux (i.e. it won't flush it to disk or re-read from disk)
			// http://kerneltrap.org/mailarchive/linux-kernel/2007/5/1/84410
			madvise(buf, 0x4000, MADV_DONTNEED);
#endif
		}
		else
#endif
		{
#if defined TORRENT_DISABLE_POOL_ALLOCATOR

#if TORRENT_USE_PURGABLE_CONTROL
		vm_deallocate(
			mach_task_self(),
			reinterpret_cast<vm_address_t>(buf),
			0x4000
			);
#else
		page_aligned_allocator::free(buf);
#endif // TORRENT_USE_PURGABLE_CONTROL

#else
		if (m_using_pool_allocator)
			m_pool.free(buf);
		else
			page_aligned_allocator::free(buf);
#endif // TORRENT_DISABLE_POOL_ALLOCATOR
		}

#if defined TORRENT_DEBUG
		std::set<char*>::iterator i = m_buffers_in_use.find(buf);
		TORRENT_ASSERT(i != m_buffers_in_use.end());
		m_buffers_in_use.erase(i);
#endif

		--m_in_use;

#ifndef TORRENT_DISABLE_POOL_ALLOCATOR
		// should we switch which allocator to use?
		if (m_in_use == 0 && m_want_pool_allocator != m_using_pool_allocator)
		{
			m_pool.release_memory();
			m_using_pool_allocator = m_want_pool_allocator;
		}
#endif
	}