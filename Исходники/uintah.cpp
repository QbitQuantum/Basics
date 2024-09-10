    void readFloatAttributes(Model *model, const std::string &attrName, size_t numParticles, 
                             const std::string &fn, size_t begin, size_t end)
    {
      FILE *file = fopen(fn.c_str(),"rb");
      if (!file) {
        throw std::runtime_error("could not open data file "+fn);
      }
      assert(file);

      fseek(file,begin,SEEK_SET);
      size_t len = end-begin;

      if (len != numParticles*sizeof(float)) {
        PING;
        PRINT(len);
        PRINT(numParticles);
        PRINT(len/numParticles);
      }
      // PRINT(len);
      
      for (int i=0;i<numParticles;i++) {
        float attrib;
        int rc = fread(&attrib,sizeof(attrib),1,file);
        if (rc != 1) {
          fclose(file);
          throw std::runtime_error("read partial data "+fn);
        }
#if 1
        if (big_endian) {
          attrib = htonf(attrib);
        }
#endif

        model->addAttribute(attrName,attrib);
      }
      
      std::stringstream attrs;
      for (std::map<std::string,std::vector<float> *>::const_iterator it=model->attribute.begin();
           it != model->attribute.end();it++) {
        attrs << "," << it->first;
      }
        

      std::cout << "\r#osp:uintah: " << numParticles << " pt.s (tot:" << float((numDumpedParticles+model->atom.size())/1e6) << "M" << attrs.str() << ")";

      fclose(file);
    }