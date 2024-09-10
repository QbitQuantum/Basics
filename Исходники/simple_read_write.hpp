    void write_1darray_vector_of_string_impl (group_or_file f, std::string const & name, ArrayVectorOfStringType const & V) {
     size_t s=0; for (auto & x : V) s = std::max(s,x.size());
     try {
      if (h5::exists(f, name)) f->unlink( name.c_str());  // put some option here ?
      DataSet ds;
      StrType strdatatype(PredType::C_S1, s);
      const size_t n = V.size();
      std::vector<char> buf(n*s, 0x00);
      size_t i=0; for (auto & x : V) {strcpy( &buf[i*s], x.c_str()); ++i;}

      mini_vector<hsize_t,1> L; L[0]=V.size();
      mini_vector<hsize_t,1> S; S[0]=1;
      auto d_space = dataspace_from_LS<1,false > (L,L,S);

      ds = f->createDataSet( name.c_str(), strdatatype, d_space );
      ds.write( (void *)(&buf[0]),strdatatype, d_space );
     }
     TRIQS_ARRAYS_H5_CATCH_EXCEPTION;
    }