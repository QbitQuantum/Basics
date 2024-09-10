   int CONetCDF4::getGroup(const CNetCDF4Path & path)
   {
      int retvalue = this->ncidp;
      
      CNetCDF4Path::const_iterator
         it  = path.begin(), end = path.end();

      for (;it != end; it++)
      {
         const std::string & groupid = *it;
         CheckError(nc_inq_ncid(retvalue, const_cast<char*>(groupid.c_str()), &retvalue));
      }
      return (retvalue);
   }