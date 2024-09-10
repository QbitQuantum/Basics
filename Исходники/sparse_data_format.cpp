// Parse a line in sparse data format and convert it to SparseVector.
// Return pointer to first unread chararcter, i.e. a successful
// parse ends at '\0' or at '#'.
const char *sdf_parse_line (const char *line, SparseVector &features)
{
  const char *pos = line;
  char *end;

  // target value
  float value = strtof (pos, &end);
  if (pos == end)
  {
    FATAL << "Can't read target value" << std::endl;
    return pos; 
  }
  features.set_target (value);
  pos = end;

  // TODO: optional query id

  // eat white space
  while (isspace (*pos)) ++pos;  

  // features
  int last_id = 0;
  while ((*pos) && (*pos != '#')) // until end of line or comment char
  {
    // read feature id
    unsigned long convert_buffer = strtoul (pos, &end, 10);
    if (pos == end)
    {
      FATAL << "Can't read feature id" << std::endl;
      return pos;
    }
    pos = end;
    id_t id (convert_buffer); // TODO: check for overflow

    // check increasing order
    if (last_id >= id)
    {
      FATAL << "Feature ids must be in increasing order, but " <<
        last_id << " >= " << id << std::endl;
      return pos;
    }
    last_id = id;

    // read separator
    if (*pos != ':')
    {
      FATAL << "Colon ':' expected" << std::endl;
      return pos; 
    }
    ++pos;

    // read feature value
    float value = strtof (pos, &end);
    if (pos == end)
    {
      FATAL << "Can't read feature value" << std::endl;
      return pos;    
    }
    pos = end;

    // append to vector
    features.push_back (std::make_pair (id, value));

    // eat white space
    while (isspace (*pos)) ++pos;  
  }  

  return pos; 
}