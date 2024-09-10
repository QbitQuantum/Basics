static Variant HHVM_FUNCTION(dbase_create, const String& filename, const Variant& fields) {
  if (!fields.isArray()) {
    raise_warning("Expected array as second parameter");
    return false;
  }

  //if (php_check_open_basedir(Z_STRVAL_PP(filename) TSRMLS_CC)) {
  //  RETURN_FALSE;
  //}

  int fd;
  if ((fd = open(filename.c_str(), O_BINARY|O_RDWR|O_CREAT, 0644)) < 0) {
    raise_warning("Unable to create database (%d): %s", errno, strerror(errno));
    return false;
  }

  Array arr_fields = fields.toArray();
  ssize_t num_fields = arr_fields.size();
  if (num_fields <= 0) {
    raise_warning("Unable to create database without fields");
    close(fd);
    return false;
  }

  // have to use regular malloc() because this gets free()'d by
  // code in the dbase library.
  dbhead_t* dbh = (dbhead_t*)malloc(sizeof(dbhead_t));
  dbfield_t* dbf = (dbfield_t*)malloc(sizeof(dbfield_t) * num_fields);
  if ((dbh == nullptr) || (dbf == nullptr)) {
    raise_warning("Unable to allocate memory for header info");
    if (dbh != nullptr) {
      free(dbh);
    }
    if (dbf != nullptr) {
      free(dbf);
    }
    close(fd);
    return false;
  }

  // This will ensure close(fd) and free_dbf_head(dbh) on "return false".
  DBaseConnection dbc(dbh);

  // initialize the header structure
  dbh->db_fields = dbf;
  dbh->db_fd = fd;
  dbh->db_dbt = DBH_TYPE_NORMAL;
  strcpy(dbh->db_date, "19930818");
  dbh->db_records = 0;
  dbh->db_nfields = num_fields;
  dbh->db_hlen = sizeof(struct dbf_dhead) + 1 + num_fields * sizeof(struct dbf_dfield);

  int rlen = 1;
  // make sure that the db_format entries for all fields are set to NULL to ensure we
  // don't seg fault if there's and error and we need to call free_dbf_head() before all
  // fields have been defined.
  dbfield_t* cur_f = dbf;
  for (size_t i = 0; i < num_fields; i++, cur_f++) {
    cur_f->db_format = nullptr;
  }

  cur_f = dbf;
  int i = 0;
  for (ArrayIter arr_it(arr_fields); arr_it; ++arr_it, cur_f++, i++) {
    Array& field = arr_it.second().toArrRef();
    ArrayIter field_it(field);

    // field name
    if (!field_it) {
      raise_warning("expected field name as first element of list in field %d", i);
      return false;
    }
    const String& field_name = field_it.second().toCStrRef();
    if ((field_name.size() > 10) || (field_name.size() == 0)) {
      raise_warning("invalid field name '%s' (must be non-empty and less than or equal to 10 characters)", field_name.c_str());
      return false;
    }
    strncpy(cur_f->db_fname, field_name.c_str(), field_name.size()+1);

    // field type
    ++field_it;
    if (!field_it) {
      raise_warning("expected field type as second element of list in field %d", i);
      return false;
    }
    cur_f->db_type = toupper(field_it.second().toCStrRef().c_str()[0]);

    cur_f->db_fdc = 0;

    // verify the field length
    switch (cur_f->db_type) {
    case 'L':
      cur_f->db_flen = 1;
      break;
    case 'M':
      cur_f->db_flen = 10;
      dbh->db_dbt = DBH_TYPE_MEMO;
      // should create the memo file here, probably
      break;
    case 'D':
      cur_f->db_flen = 8;
      break;
    case 'F':
      cur_f->db_flen = 20;
      break;
    case 'N':
    case 'C':
      // field length
      ++field_it;
      if (!field_it) {
        raise_warning("expected field length as third element of list in field %d", i);
        return false;
      }
      cur_f->db_flen = field_it.second().toInt32();

      if (cur_f->db_type == 'N') {
        ++field_it;
        if (!field_it) {
          raise_warning("expected field precision as fourth element of list in field %d", i);
          return false;
        }
      }
      break;
    default:
      raise_warning("unknown field type '%c'", cur_f->db_type);
      return false;
    }
    cur_f->db_foffset = rlen;
    rlen += cur_f->db_flen;

    cur_f->db_format = get_dbf_f_fmt(cur_f);
  }

  dbh->db_rlen = rlen;
  put_dbf_info(dbh);

  // We need a copy of dbc here, because return will destroy original.
  open_dbases->insert(std::make_pair(dbh->db_fd, std::shared_ptr<DBaseConnection>(new DBaseConnection(dbc))));
  return Variant(dbh->db_fd);
}