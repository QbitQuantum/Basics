bool CHotKeysToCmdRouter::UnregisterCommand(UINT i_command_id)
{
 bool result = true;
 bool is_command_exist = false;
 if (NULL==mp_OriginalWnd)
 {
  _ASSERTE(0);
  return false;
 }

 //ID-шек c кодом i_command_id в базе данных может быть больше одной, поэтому нам нужен цикл
 HotKeyMap::iterator it;
 while((it = _FindCommandID(i_command_id)) != m_hot_key_map.end()) 
 {
  is_command_exist = true;
  //нашли ID-шку в базе данных. Надо снять с регистрации горячую клавишу
  if (!UnregisterHotKey(mp_OriginalWnd->m_hWnd, (*it).first))
   result = false;
  if (GlobalDeleteAtom((*it).first) != 0)
   result = false;

  //удаляем из базы данных
  m_hot_key_map.erase(it);  
 }

 //если были ошибки или команды нет в базе данных, то возвращаем false.
 return result && is_command_exist;
}