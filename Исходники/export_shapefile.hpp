 static void add_string_attribute(Osmium::Export::Shapefile* shapefile, int n, v8::Local<v8::Value> value) {
     uint16_t source[(Osmium::Export::Shapefile::max_dbf_field_length+2)*2];
     char dest[(Osmium::Export::Shapefile::max_dbf_field_length+1)*4];
     memset(source, 0, (Osmium::Export::Shapefile::max_dbf_field_length+2)*4);
     memset(dest, 0, (Osmium::Export::Shapefile::max_dbf_field_length+1)*4);
     int32_t dest_length;
     UErrorCode error_code = U_ZERO_ERROR;
     value->ToString()->Write(source, 0, Osmium::Export::Shapefile::max_dbf_field_length+1);
     u_strToUTF8(dest, shapefile->field(n).width(), &dest_length, source, std::min(Osmium::Export::Shapefile::max_dbf_field_length+1, value->ToString()->Length()), &error_code);
     if (error_code == U_BUFFER_OVERFLOW_ERROR) {
         // thats ok, it just means we clip the text at that point
     } else if (U_FAILURE(error_code)) {
         throw std::runtime_error("UTF-16 to UTF-8 conversion failed");
     }
     shapefile->add_attribute(n, dest);
 }