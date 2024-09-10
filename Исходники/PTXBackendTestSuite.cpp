bool runRalfFunction(std::string name, scalarFnType fun, CUmodule* hModule, CUdeviceptr d_data,
		     DataStruct *h_data,DataStruct* h_data_reference, unsigned int memSize)
{
  const unsigned inputNr = 10;
  const float scalarInputs[4][inputNr] = {{ 0.f, 3.f, 2.f, 8.f, 10.2f, -1.f, 0.f, 1000.23f, 0.02f, -0.02f },
					   { 1.f, 2.f, 4.f, 6.f, -14.13f, -13.f, 0.f, 0.02f, 420.001f, -420.001f },
					   { 2.f, 1.f, 6.f, 4.f, 999.f, -5.f, 0.f, 420.001f, 0.01f, 0.01f },
					   { 3.f, 0.f, 8.f, 2.f, 0.f, -420.001f, 0.f, 0.01f, 1000.23f, 0.01f }};


  std::cout << "====================== " << name << "===============================\n";
  for (unsigned i=0; i<inputNr; ++i) {
    for (unsigned j=0; j<inputNr; ++j) 
    for (unsigned k=0; k<4; ++k) 
    {
      setZero(h_data,h_data_reference);
      h_data->fa[0] = h_data_reference->fa[0] = scalarInputs[k][i];
      h_data->fa[1] = h_data_reference->fa[1] = scalarInputs[k][j];

      //run device function
      loadAndRunTestFunction(hModule, name, d_data, h_data, memSize);   
      fun(h_data_reference);

      if(!compareData(h_data, h_data_reference))                      //compare Data
      {
	std::cout << "\n Error in Ralf: fa0=" << scalarInputs[k][i]  
                  << ", fa1=" << scalarInputs[k][j] << " (" << name << ")\n";
	return false;
      }
    }
  }
  std::cout << " => Test passed!!!\n";
  return true;
}