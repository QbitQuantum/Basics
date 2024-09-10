		void prepared_statement_t::_bind_timestamp_parameter(size_t index, const SQL_TIMESTAMP_STRUCT* value, bool is_null) {
			if(_handle->debug) {
				std::cerr << "ODBC debug: binding date_time parameter"
				" at index: " << index << ", being " << (is_null ? std::string() : "not") << " null" << std::endl;
			}
			SQLLEN indPtr(is_null ? SQL_NULL_DATA : 0);
			auto rc = SQLBindParameter(_handle->stmt, 
									   index, 
									   SQL_PARAM_INPUT, 
									   SQL_C_TYPE_TIMESTAMP, 
									   SQL_TYPE_TIMESTAMP, 
									   29,
									   0, 
									   (SQLPOINTER)value, 
									   sizeof(SQL_DATE_STRUCT), 
									   &indPtr);
			if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
				throw sqlpp::exception("ODBC error: couldn't bind date parameter: "+detail::odbc_error(_handle->stmt, SQL_HANDLE_STMT));
			}
		}