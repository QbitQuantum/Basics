 void bind_value(T val, int index)
 {
   value_t *v = new value_t;
   v->data = new char[sizeof(T)];
   *static_cast<T*>(v->data) = val;
   host_data_.push_back(v);
   
   int ctype = mssql_statement::type2int(type_traits<T>::data_type());
   int type = mssql_statement::type2sql(type_traits<T>::data_type());
   SQLRETURN ret = SQLBindParameter(stmt_, index, SQL_PARAM_INPUT, ctype, type, 0, 0, v->data, 0, &v->len);
   throw_error(ret, SQL_HANDLE_STMT, stmt_, "mssql", "couldn't bind parameter");
 }