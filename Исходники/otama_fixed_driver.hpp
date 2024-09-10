		virtual otama_status_t
		drop_database(void)
		{
			otama_status_t ret;

#ifdef _OPENMP
			OMPLock lock(this->m_lock);
#endif
			ret = DBIDriver<T>::drop_database();
	
			if (ret == OTAMA_STATUS_OK) {
				ret = m_mmap->unlink();
			}
			return ret;
		}