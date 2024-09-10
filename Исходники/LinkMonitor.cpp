/*virtual*/ int LinkMonitor::onNewATResponseLine(ATCommandsInterface* pInst, const char* line)
{
  DBG("Line is %s", line);
  int v;
  if( sscanf(line, "+CREG: %*d,%d", &v) >= 1 ) //Reg state is valid
  {
    DBG("+CREG %d", v);
    switch( v )
    {
      case 0:
        m_registrationState = REGISTRATION_STATE_UNKNOWN;
        break;
      case 1:
        m_registrationState = REGISTRATION_STATE_HOME_NETWORK;
        break;
      case 2:
        m_registrationState = REGISTRATION_STATE_REGISTERING;
        break;
      case 3:
        m_registrationState = REGISTRATION_STATE_DENIED;  
        break;
      case 4:
        m_registrationState = REGISTRATION_STATE_NO_SIGNAL;  
        break;        
      case 5:
        m_registrationState = REGISTRATION_STATE_ROAMING;  
        break;
      default:
        m_registrationState = REGISTRATION_STATE_UNKNOWN;  
        break;
    }
  }
  else if( sscanf(line, "+COPS: %*d,%*d,\"%*[^\"]\",%d", &v) >= 1 )
  {
    DBG("+COPS %d", v);
    switch( v )
    {
      case 0:
        m_bearer = BEARER_GSM;
        break;
      case 2:
        m_bearer = BEARER_UMTS;
        break;
      case 3:
        m_bearer = BEARER_EDGE;
        break;
      case 4: //HSDPA
      case 5: //HSUPA
      case 6: //HSDPA + HSUPA
        m_bearer = BEARER_HSPA;
        break;
      case 7:
        m_bearer = BEARER_LTE;
        break;  
      case 1: //GSM Compact
      default:
        m_bearer = BEARER_UNKNOWN;
        break;
    }
  }
  else if( sscanf(line, "+CSQ: %d,%*d", &v) >= 1 )
  {
    DBG("+CSQ %d", v);
    if(v == 99) //Unknown
    {
      m_rssi = 0; //Unknown
    }
    else
    {
      m_rssi = -113 + 2*v;
    }
  }
  return OK;
}