int testClass(const String& className)
{
  Array<CIMObjectPath> refs;

  // =======================================================================
  // enumerateInstanceNames
  // =======================================================================

  cout << "+++++ enumerateInstanceNames(" << className << ") ";
  try
  {
    refs = c.enumerateInstanceNames(NAMESPACE,className);
  }
  catch (Exception& e)
  {
    cout << endl;
    errorExit(e);
  }

  cout << refs.size() << " instances" << endl;
  // if zero instances, not an error, but can't proceed
  if (refs.size() == 0)
  {
    cout << "+++++ test completed early" << endl;
    return 0;
  }

  // =======================================================================
  // getInstance
  // =======================================================================

  // -------------------- First do normal getInstance() --------------------

  // pick the middle instance of the bunch
  int i = (refs.size()-1) >> 1;  // This is a shift right, not streamio!
  CIMObjectPath ref = refs[i];
  CIMInstance inst;
  cout << "+++++ getInstance #" << i << endl;
  try
  {
    inst = c.getInstance(NAMESPACE,ref);
  }
  catch (Exception& e)
  {
    errorExit(e);
  }

  // ATTN-MG-20020501: Can add some property value checks here

  // ------------------ do getInstance() with bad key ----------------------
  
  Array<CIMKeyBinding> kb = ref.getKeyBindings();
  // mess up first key name
  kb[0].setName("foobar");
  ref.setKeyBindings(kb);
  
  int status = 0;

  cout << "+++++ getInstance with bad key" << endl;
  try
  {
    inst = c.getInstance(NAMESPACE,ref);
  }
  catch (CIMException& e)
  {
    if (e.getCode() == CIM_ERR_INVALID_PARAMETER) status = 1;
  }
  catch (Exception& e)
  {
    // any other exception is a failure; leave status alone
  }
  if (status == 0)
  {
    cout << "+++++ Error: bad instance name not rejected" << endl;
    return 1;
  }

  // =======================================================================
  // createInstance
  // =======================================================================

  CIMObjectPath ref2;
  cout << "+++++ createInstance" << endl;
  status = 0;
  try
  {
    ref2 = c.createInstance(NAMESPACE,inst);
  }
  catch (CIMException& e)
  {
    if (e.getCode() == CIM_ERR_NOT_SUPPORTED) status = 1;
  }
  catch (Exception& e)
  {
    // any other Exception is a problem; leave status alone
  }
  if (status == 0)
  {
    cout << "+++++ Error: createInstance didn't throw exception" << endl;
    return 1;
  }

  // =======================================================================
  // deleteInstance
  // =======================================================================

  cout << "+++++ deleteInstance" << endl;
  status = 0;
  try
  {
    c.deleteInstance(NAMESPACE,ref);
  }
  catch (CIMException& e)
  {
    if (e.getCode() == CIM_ERR_NOT_SUPPORTED) status = 1;
  }
  catch (Exception& e)
  {
    // any other Exception is a problem; leave status alone
  }
  if (status == 0)
  {
    cout << "+++++ Error: deleteInstance didn't throw exception" << endl;
    return 1;
  }

  // =======================================================================
  // enumerateInstances
  // =======================================================================

  cout << "+++++ enumerateInstances(" << className << ")" << endl;
  
  Array<CIMInstance> ia;
  try
  {
    ia = c.enumerateInstances(NAMESPACE,className);
  }
  catch (Exception& e)
  {
    errorExit(e);
  }

  // There should be several instances
  if (ia.size() == 0)
  {
    cout << "+++++ Error: enumerateInstances on " << className << " returned too few instances" << endl;
    cout << "+++++ Test failed" << endl;
    return 1;
  }

  // =======================================================================
  // modifyInstance
  // =======================================================================

  // We do modifyInstance after enumerateInstances, because
  // modifyInstance requires a CIMInstance argument, which
  // is conveniently what was returned by enumerateInstances

  CIMInstance ni = ia[(ia.size()-1) >> 1]; // pick the middle one

  cout << "+++++ modifyInstance" << endl;
  status = 0;
  try
  {
    c.modifyInstance(NAMESPACE,ni);
  }
  catch (CIMException& e)
  {
    if (e.getCode() == CIM_ERR_NOT_SUPPORTED) status = 1;
  }
  catch (Exception& e)
  {
    // any other Exception is a problem; leave status alone
  }
  if (status == 0)
  {
    cout << "+++++ Error: modifyInstance didn't throw exception" << endl;
    return 1;
  }

  // =======================================================================
  // Tests completed
  // =======================================================================

  return 0;
}