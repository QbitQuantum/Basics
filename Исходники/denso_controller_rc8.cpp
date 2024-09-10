HRESULT DensoControllerRC8::AddController()
{
  static const std::string CTRL_CONNECT_OPTION[BCAP_CTRL_CONNECT_ARGS] = 
    {"", "CaoProv.DENSO.VRC", "localhost", ""};

  HRESULT hr = E_FAIL;
  int srvs, argc;

  for(srvs = DensoBase::SRV_MIN; srvs <= DensoBase::SRV_MAX; srvs++) {
    std::stringstream ss;
    std::string strTmp;
    VARIANT_Ptr vntRet(new VARIANT());
    VARIANT_Vec vntArgs;

    VariantInit(vntRet.get());

    for(argc = 0; argc < BCAP_CTRL_CONNECT_ARGS; argc++) {
      VARIANT_Ptr vntTmp(new VARIANT());
      VariantInit(vntTmp.get());

      vntTmp->vt = VT_BSTR;

      if(argc == 0) {
        strTmp = "";
        if(m_name != "") {
          ss << ros::this_node::getNamespace() << m_name << srvs;
          strTmp = ss.str();
        }
      } else {
        strTmp = CTRL_CONNECT_OPTION[argc];
      }

      vntTmp->bstrVal = ConvertStringToBSTR(strTmp);

      vntArgs.push_back(*vntTmp.get());
    }

    hr = m_vecService[srvs]->ExecFunction(ID_CONTROLLER_CONNECT, vntArgs, vntRet);
    if(FAILED(hr)) break;

    m_vecHandle.push_back(vntRet->ulVal);
  }

  return hr;
}