	void
	PeterRoosenTracksConverter::run_converter(bool status)
	{
		SQLRETURN sql_return;
		SQLHSTMT hstmt;
		
		sql_return = SQLAllocHandle(SQL_HANDLE_STMT, _connection, &hstmt);
		if (sql_return != SQL_SUCCESS)
		{
			std::cout << "Allocating statement handle failed." << std::endl;
		}
		
		double x1, y1, x2, y2;
		SQLINTEGER x1_ind, y1_ind, x2_ind, y2_ind;
		
		sql_return = SQLBindCol(hstmt, 1, SQL_C_DOUBLE, &x1, sizeof(double), &x1_ind);
		if (sql_return != SQL_SUCCESS)
		{
			std::cout << "Binding to column 1 failed." << std::endl;
		}
		sql_return = SQLBindCol(hstmt, 2, SQL_C_DOUBLE, &y1, sizeof(double), &y1_ind);
		if (sql_return != SQL_SUCCESS)
		{
			std::cout << "Binding to column 2 failed." << std::endl;
		}
		sql_return = SQLBindCol(hstmt, 3, SQL_C_DOUBLE, &x2, sizeof(double), &x2_ind);
		if (sql_return != SQL_SUCCESS)
		{
			std::cout << "Binding to column 3 failed." << std::endl;
		}
		sql_return = SQLBindCol(hstmt, 4, SQL_C_DOUBLE, &y2, sizeof(double), &y2_ind);
		if (sql_return != SQL_SUCCESS)
		{
			std::cout << "Binding to column 4 failed." << std::endl;
		}
		
		std::string stmt_string("SELECT x1, y1, x2, y2 FROM tracks WHERE id < 100000 ORDER BY id ASC;");
		sql_return = SQLExecDirect(hstmt, (SQLCHAR*)(stmt_string.c_str()), SQL_NTS);
		if (sql_return != SQL_SUCCESS)
		{
			std::cout << "Executing SQL statement failed." << std::endl;
		}
		
		// init positions:
		double old_x1 = -1.0;
		double old_x2 = -1.0;
		double old_y1 = -1.0;
		double old_y2 = -1.0;
		
		enum CoordOrder
		{
			COORD_ORDER_1TO2,
			COORD_ORDER_2TO1,
			UNKNOWN
		};
		
		CoordOrder coord_order = UNKNOWN;
		// done.
		
		// init time (to 2000-01-01 00:00:00):
		tm* current_time = new tm;
		current_time->tm_sec = 0;
		current_time->tm_min = 0;
		current_time->tm_hour = 0;
		current_time->tm_mday = 1;
		current_time->tm_mon = 0;
		current_time->tm_year = 100;
		
		time_t count = mktime(current_time);
		// done.
		
		// init and open output file:
		std::ofstream output_file;
		output_file.setf(std::ios::fixed);
		output_file.precision(4);
		
		std::string init_filename(_output_file);
		init_filename.append("0");
		output_file.open(init_filename.c_str());
		
		int file_counter = 1;
		// done.
		
		// init step size:
		const int STEP_SIZE = 10;
		// done.
		
		// loop over result set:
		while ( (sql_return = SQLFetch(hstmt)) != SQL_NO_DATA)
		{
			if ( (status) && (file_counter % 10000 == 0) )
				std::cout << file_counter << std::endl;
			
			if (sql_return == SQL_ERROR)
				std::cout << "Fetching column " << count + 1
					<< " failed." << std::endl;
			
/*			if (output_file.tellp() >= _max_output_file_size)
			{
				output_file.close();
				
				std::stringstream number;
				number << file_counter;
				++file_counter;
				
				std::string filename(_output_file);
				filename.append(number.str());
				output_file.open(filename.c_str());
				
				coord_order = UNKNOWN;
			}*/
			
			if (coord_order == UNKNOWN)
			{
				if ( (old_x2 == x1) && (old_y2 == y1) )
				{
					coord_order = COORD_ORDER_1TO2;
					
					new_file(output_file, file_counter);
					
					write_to_file(output_file, count, x1, y1);
					count += STEP_SIZE;
				} else if ( (old_x1 == x2) && (old_y1 == y2) )
				{
					coord_order = COORD_ORDER_2TO1;
					
					new_file(output_file, file_counter);
					
					write_to_file(output_file, count, x2, y2);
					count += STEP_SIZE;
				} else
				{
					// Coordinates do not belong together. That would result
					// in a 2 point track. Just forget it!
					
					// set coord_order to UNKNOWN. Actually not needed. But
					// you known where to continue immediately.
					coord_order = UNKNOWN;
				}
			}
			
			if (coord_order == COORD_ORDER_1TO2)
			{
				if ( (old_x2 == x1) && (old_y2 == y1) )
				{
					write_to_file(output_file, count, x2, y2);
					count += STEP_SIZE;
				} else if ( (old_x2 == x2) && (old_y2 == y2) )
				{
					// coord_order changed:
					output_file << "\t/* Coordinate order changed. ";
					output_file << "Now it is from 2 to 1. */";
					output_file << std::endl;
					coord_order = COORD_ORDER_2TO1;
					
					write_to_file(output_file, count, x1, y1);
					count += STEP_SIZE;
				} else
				{
					coord_order = UNKNOWN;
				}
			} else // if (coord_order == COORD_ORDER_2TO1)
			{
				if ( (old_x1 == x2) && (old_y1 == y2) )
				{
					write_to_file(output_file, count, x1, y1);
					count += STEP_SIZE;
				} else if ( (old_x1 == x1) && (old_y1 == y1) )
				{
					// coord_order changed:
					output_file << "\t/* Coordinaten order changed. ";
					output_file << "Now it is from 1 to 2. */";
					output_file << std::endl;
					coord_order = COORD_ORDER_1TO2;
					
					write_to_file(output_file, count, x2, y2);
					count += STEP_SIZE;
				} else
				{
					coord_order = UNKNOWN;
				}
			}
			
			old_x1 = x1;
			old_y1 = y1;
			old_x2 = x2;
			old_y2 = y2;
		}
		
		output_file.close();
		
		delete current_time;
	}