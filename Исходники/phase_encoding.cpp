 Eigen::MatrixXd parse_scheme (const Header& header)
 {
   Eigen::MatrixXd PE;
   const auto it = header.keyval().find ("pe_scheme");
   if (it != header.keyval().end()) {
     try {
       PE = parse_matrix (it->second);
     } catch (Exception& e) {
       throw Exception (e, "malformed PE scheme in image \"" + header.name() + "\"");
     }
     if (ssize_t(PE.rows()) != ((header.ndim() > 3) ? header.size(3) : 1))
       throw Exception ("malformed PE scheme in image \"" + header.name() + "\" - number of rows does not equal number of volumes");
   } else {
     // Header entries are cast to lowercase at some point
     const auto it_dir  = header.keyval().find ("PhaseEncodingDirection");
     const auto it_time = header.keyval().find ("TotalReadoutTime");
     if (it_dir != header.keyval().end() && it_time != header.keyval().end()) {
       Eigen::Matrix<default_type, 4, 1> row;
       row.head<3>() = Axes::id2dir (it_dir->second);
       row[3] = to<default_type>(it_time->second);
       PE.resize ((header.ndim() > 3) ? header.size(3) : 1, 4);
       PE.rowwise() = row.transpose();
     }
   }
   return PE;
 }