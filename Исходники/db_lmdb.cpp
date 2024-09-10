		void LMDBCursor::Seek(MDB_cursor_op op) {
#ifdef _MSC_VER
			if (op != MDB_FIRST)
				VirtualUnlock(mdb_value_.mv_data, mdb_value_.mv_size);
#endif
			int mdb_status = mdb_cursor_get(mdb_cursor_, &mdb_key_, &mdb_value_, op);
			if (mdb_status == MDB_NOTFOUND) {
				valid_ = false;
			}
			else {
				MDB_CHECK(mdb_status);
				valid_ = true;
			}
		}