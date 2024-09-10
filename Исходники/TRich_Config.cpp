bool TRich_Config::Create(const char * output_file){
  
  printf("A new configuration will be created and saved to %s\n",output_file);
  
  Config lcfg;
  
  lcfg.setTabWidth(TABWIDTH);
  
  this->AddParam_RUN(&lcfg);
  this->AddParam_FRONTEND(&lcfg);
  this->AddParam_FPGA(&lcfg);
  this->AddParam_MAROC3_com(&lcfg);
  this->AddParam_EXT(&lcfg);

  try{
    lcfg.writeFile(output_file);
    cerr << "New configuration successfully written to: " << output_file<< endl;
    return true;
  }
  catch(const FileIOException &fioex){
    cerr << "I/O error while writing file: " << output_file << endl;
    return false;
  }
}