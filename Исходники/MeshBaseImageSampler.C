void
MeshBaseImageSampler::setupImageSampler(MeshBase & mesh)
{
  // Don't warn that mesh or _is_pars are unused when VTK is not enabled.
  libmesh_ignore(mesh);
  libmesh_ignore(_is_pars);

#ifdef LIBMESH_HAVE_VTK
  // Get access to the Mesh object
  BoundingBox bbox = MeshTools::create_bounding_box(mesh);

  // Set the dimensions from the Mesh if not set by the User
  if (_is_pars.isParamValid("dimensions"))
    _physical_dims = _is_pars.get<Point>("dimensions");

  else
  {
    _physical_dims(0) = bbox.max()(0) - bbox.min()(0);
#if LIBMESH_DIM > 1
    _physical_dims(1) = bbox.max()(1) - bbox.min()(1);
#endif
#if LIBMESH_DIM > 2
    _physical_dims(2) = bbox.max()(2) - bbox.min()(2);
#endif
  }

  // Set the origin from the Mesh if not set in the input file
  if (_is_pars.isParamValid("origin"))
    _origin = _is_pars.get<Point>("origin");
  else
  {
    _origin(0) = bbox.min()(0);
#if LIBMESH_DIM > 1
    _origin(1) = bbox.min()(1);
#endif
#if LIBMESH_DIM > 2
    _origin(2) = bbox.min()(2);
#endif
  }

  // An array of filenames, to be filled in
  std::vector<std::string> filenames;

  // The file suffix, to be determined
  std::string file_suffix;

  // Try to parse our own file range parameters.  If that fails, then
  // see if the associated Mesh is an ImageMesh and use its.  If that
  // also fails, then we have to throw an error...
  //
  // The parseFileRange method sets parameters, thus a writable reference to the InputParameters
  // object must be obtained from the warehouse. Generally, this should be avoided, but
  // this is a special case.
  if (_status != 0)
  {
    // TO DO : enable this. It was taken from ImageSampler.C, but cn't be implemented
    // the same way.
    // We don't have parameters, so see if we can get them from ImageMesh
    /*ImageMeshgenerator * image_mesh_gen = dynamic_cast<ImageMesh *>(&mesh);
    if (!image_mesh)
      mooseError("No file range parameters were provided and the Mesh is not an ImageMesh.");

    // Get the ImageMesh's parameters.  This should work, otherwise
    // errors would already have been thrown...
    filenames = image_mesh->filenames();
    file_suffix = image_mesh->fileSuffix();*/
  }
  else
  {
    // Use our own parameters (using 'this' b/c of conflicts with filenames the local variable)
    filenames = this->filenames();
    file_suffix = fileSuffix();
  }

  // Storage for the file names
  _files = vtkSmartPointer<vtkStringArray>::New();

  for (const auto & filename : filenames)
    _files->InsertNextValue(filename);

  // Error if no files where located
  if (_files->GetNumberOfValues() == 0)
    mooseError("No image file(s) located");

  // Read the image stack.  Hurray for VTK not using polymorphism in a
  // smart way... we actually have to explicitly create the type of
  // reader based on the file extension, using an if-statement...
  if (file_suffix == "png")
    _image = vtkSmartPointer<vtkPNGReader>::New();
  else if (file_suffix == "tiff" || file_suffix == "tif")
    _image = vtkSmartPointer<vtkTIFFReader>::New();
  else
    mooseError("Un-supported file type '", file_suffix, "'");

  // Now that _image is set up, actually read the images
  // Indicate that data read has started
  _is_console << "Reading image(s)..." << std::endl;

  // Extract the data
  _image->SetFileNames(_files);
  _image->Update();
  _data = _image->GetOutput();
  _algorithm = _image->GetOutputPort();

  // Set the image dimensions and voxel size member variable
  int * dims = _data->GetDimensions();
  for (unsigned int i = 0; i < 3; ++i)
  {
    _dims.push_back(dims[i]);
    _voxel.push_back(_physical_dims(i) / _dims[i]);
  }

  // Set the dimensions of the image and bounding box
  _data->SetSpacing(_voxel[0], _voxel[1], _voxel[2]);
  _data->SetOrigin(_origin(0), _origin(1), _origin(2));
  _bounding_box.min() = _origin;
  _bounding_box.max() = _origin + _physical_dims;

  // Indicate data read is completed
  _is_console << "          ...image read finished" << std::endl;

  // Set the component parameter
  // If the parameter is not set then vtkMagnitude() will applied
  if (_is_pars.isParamValid("component"))
  {
    unsigned int n = _data->GetNumberOfScalarComponents();
    _component = _is_pars.get<unsigned int>("component");
    if (_component >= n)
      mooseError("'component' parameter must be empty or have a value of 0 to ", n - 1);
  }
  else
    _component = 0;

  // Apply filters, the toggling on and off of each filter is handled internally
  vtkMagnitude();
  vtkShiftAndScale();
  vtkThreshold();
  vtkFlip();
#endif
}