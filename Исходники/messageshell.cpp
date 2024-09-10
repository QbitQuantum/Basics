void MessageShell::handleSpell(const uint8_t* data, size_t, uint8_t dir)
{
  const memSpellStruct* mem = (const memSpellStruct*)data;
  QString tempStr;

  bool client = (dir == DIR_Client);

  tempStr = "";
  
  switch (mem->param1)
  {
  case 0:
    {
      if (!client)
	tempStr = "You have finished scribing '";
      break;
    }
    
  case 1:
    {
      if (!client)
	tempStr = "You have finished memorizing '";
      break;
    }
    
  case 2:
    {
      if (!client)
	tempStr = "You forget '";
      break;
    }
    
  case 3:
    {
      if (!client)
	tempStr = "You finish casting '";
      break;
    }
    
  default:
    {
      tempStr.sprintf( "Unknown Spell Event ( %s ) - '",
		       client  ?
		     "Client --> Server"   :
		       "Server --> Client"
		       );
      break;
    }
  }
  
  
  if (!tempStr.isEmpty())
  {
    QString spellName;
    const Spell* spell = m_spells->spell(mem->spellId);
    
    if (spell)
      spellName = spell->name();
    else
      spellName = spell_name(mem->spellId);

    if (mem->param1 != 3)
      tempStr.sprintf("%s%s', slot %d.", 
		      tempStr.ascii(), 
		      (const char*)spellName, 
		      mem->slotId);
    else 
    {
      tempStr.sprintf("%s%s'.", 
		      tempStr.ascii(), 
		      (const char*)spellName);
    }

    m_messages->addMessage(MT_Spell, tempStr);
  }
}