void RBEvaluation::write_out_vectors(System& sys,
                                     std::vector<NumericVector<Number>*>& vectors,
                                     const std::string& directory_name,
                                     const std::string& data_name,
                                     const bool write_binary_vectors)
{
  START_LOG("write_out_vectors()", "RBEvaluation");
  //libMesh::out << "Writing out the basis functions..." << std::endl;

  if(this->processor_id() == 0)
  {
    // Make a directory to store all the data files
    mkdir(directory_name.c_str(), 0777);
  }

  // Make sure processors are synced up before we begin
  this->comm().barrier();

  std::ostringstream file_name;
  const std::string basis_function_suffix = (write_binary_vectors ? ".xdr" : ".dat");

  file_name << directory_name << "/" << data_name << "_header" << basis_function_suffix;
  Xdr header_data(file_name.str(),
                  write_binary_vectors ? ENCODE : WRITE);
  sys.write_header(header_data, get_io_version_string(), /*write_additional_data=*/false);

  // Following EquationSystemsIO::write, we use a temporary numbering (node major)
  // before writing out the data
  MeshTools::Private::globally_renumber_nodes_and_elements(sys.get_mesh());

  // // Use System::write_serialized_data to write out the basis functions
  // // by copying them into this->solution one at a time.
  // for(unsigned int i=0; i<vectors.size(); i++)
  // {
  //   // No need to copy, just swap
  //   // *solution = *vectors[i];
  //   vectors[i]->swap(*sys.solution);
  //   file_name.str(""); // reset the string
  //   file_name << directory_name << "/bf" << i << basis_function_suffix;
  //   Xdr bf_data(file_name.str(),
  //               write_binary_vectors ? ENCODE : WRITE);
  //   // set the current version
  //   bf_data.set_version(LIBMESH_VERSION_ID(LIBMESH_MAJOR_VERSION,
  // 					   LIBMESH_MINOR_VERSION,
  // 					   LIBMESH_MICRO_VERSION));

  //   sys.write_serialized_data(bf_data, false);

  //   // Synchronize before moving on
  //   this->comm().barrier();
  //   // Swap back
  //   vectors[i]->swap(*sys.solution);
  // }

  file_name.str("");
  file_name << directory_name << "/" << data_name << "_data" << basis_function_suffix;

  Xdr bf_data(file_name.str(),
	      write_binary_vectors ? ENCODE : WRITE);

  // Write all vectors at once.
  {
    // Note the API wants pointers to constant vectors, hence this...
    std::vector<const NumericVector<Number>*> bf_out(vectors.begin(),
						     vectors.end());
    // for(unsigned int i=0; i<vectors.size(); i++)
    //   bf_out.push_back(vectors[i]);
    sys.write_serialized_vectors (bf_data, bf_out);
  }


  // set the current version
  bf_data.set_version(LIBMESH_VERSION_ID(LIBMESH_MAJOR_VERSION,
					 LIBMESH_MINOR_VERSION,
					 LIBMESH_MICRO_VERSION));


  // Undo the temporary renumbering
  sys.get_mesh().fix_broken_node_and_element_numbering();

  STOP_LOG("write_out_vectors()", "RBEvaluation");
}