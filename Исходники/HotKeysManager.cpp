//Производит регистрацию/антиригистрацию всех горячих клавиш указанного роутера.
//i_register - если true, то регистрация, иначе антирегистрация
bool HotKeysManager::RegisterOneRouter(CHotKeysToCmdRouter* ip_router, bool i_register)
{
 bool result = true;
 bool is_command_exist = false;
 if (NULL==ip_router || NULL==ip_router->mp_OriginalWnd)
 {
  ASSERT(0);
  return false;
 }

 CHotKeysToCmdRouter::HotKeyMap::iterator it;
 for(it = ip_router->m_hot_key_map.begin(); it != ip_router->m_hot_key_map.end(); ++it)
 {
  if (!i_register)
  {
   if (UnregisterHotKey(ip_router->mp_OriginalWnd->m_hWnd, (*it).first))
    result = false;
  }
  else
  {
   BOOL status = RegisterHotKey(ip_router->mp_OriginalWnd->m_hWnd, (*it).first, (*it).second.m_fsModifiers, (*it).second.m_vk);
   result = status ? true : false;
  }
 }

 return result;
}