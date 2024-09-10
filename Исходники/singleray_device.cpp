  void SingleRayDevice::rtSetArray(Device::RTHandle handle_i, const char* property, const char* type, Device::RTData data_i, size_t size, size_t stride, size_t ofs)
  {

    RT_COMMAND_HEADER;
    Ref<ConstHandle<Data> > data    = castHandle<ConstHandle<Data> >(data_i,"data");
    _RTHandle* handle = (_RTHandle*)handle_i;
    if (!property) throw std::runtime_error("invalid property");
    if (!handle  ) return;
    if      (!strcasecmp(type,"bool1" )) handle->set(property,Variant(data->getInstance(),Variant::BOOL1 ,size,stride == size_t(-1) ? 1*sizeof(bool ) : stride, ofs));
    else if (!strcasecmp(type,"bool2" )) handle->set(property,Variant(data->getInstance(),Variant::BOOL2 ,size,stride == size_t(-1) ? 2*sizeof(bool ) : stride, ofs));
    else if (!strcasecmp(type,"bool3" )) handle->set(property,Variant(data->getInstance(),Variant::BOOL3 ,size,stride == size_t(-1) ? 3*sizeof(bool ) : stride, ofs));
    else if (!strcasecmp(type,"bool4" )) handle->set(property,Variant(data->getInstance(),Variant::BOOL4 ,size,stride == size_t(-1) ? 4*sizeof(bool ) : stride, ofs)); 
    else if (!strcasecmp(type,"int1"  )) handle->set(property,Variant(data->getInstance(),Variant::INT1  ,size,stride == size_t(-1) ? 1*sizeof(int  ) : stride, ofs));
    else if (!strcasecmp(type,"int2"  )) handle->set(property,Variant(data->getInstance(),Variant::INT2  ,size,stride == size_t(-1) ? 2*sizeof(int  ) : stride, ofs));
    else if (!strcasecmp(type,"int3"  )) handle->set(property,Variant(data->getInstance(),Variant::INT3  ,size,stride == size_t(-1) ? 3*sizeof(int  ) : stride, ofs));
    else if (!strcasecmp(type,"int4"  )) handle->set(property,Variant(data->getInstance(),Variant::INT4  ,size,stride == size_t(-1) ? 4*sizeof(int  ) : stride, ofs));
    else if (!strcasecmp(type,"float1")) handle->set(property,Variant(data->getInstance(),Variant::FLOAT1,size,stride == size_t(-1) ? 1*sizeof(float) : stride, ofs));
    else if (!strcasecmp(type,"float2")) handle->set(property,Variant(data->getInstance(),Variant::FLOAT2,size,stride == size_t(-1) ? 2*sizeof(float) : stride, ofs));
    else if (!strcasecmp(type,"float3")) handle->set(property,Variant(data->getInstance(),Variant::FLOAT3,size,stride == size_t(-1) ? 3*sizeof(float) : stride, ofs)); 
    else if (!strcasecmp(type,"float4")) handle->set(property,Variant(data->getInstance(),Variant::FLOAT4,size,stride == size_t(-1) ? 4*sizeof(float) : stride, ofs));
    else throw std::runtime_error("unknown array type: "+std::string(type));
  }