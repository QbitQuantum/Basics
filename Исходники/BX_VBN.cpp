/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_VBN_New                                                                []          
[]                                                                            []
[]____________________________________________________________________________[]
*/
BX_RESULT
BX_VBN_New(BX_VBN_Args& arg)
{
	if (!CheckAdminPassword(arg.AdminPassword))
		return BXE_BadAdminPassword;

// Пустые пароли назначать нельзя:
	if (arg.Password.Size() < 1)
		return BXE_VBN_New_PasswordVoid;

	if (oc_reg.m_Language.Size() == 0)
		return BXE_NoLanguages;

//----------------------------------------------------------------------------[] 
	OC_VBN 		oc_vbn;

// Найти последний порядковый объекта:
	int LastNo = -1;
	oc_vbn.SetIndex_No();
	if (oc_vbn.GoLast())
		LastNo = oc_vbn.m_No;

// Создать объект
	oc_vbn.New();
	SERVER_DEBUG_ASSERT_RETURN(
		oc_vbn.IsValid(),
		"BX_VBN_New(): Error creating object.",
		BX_SYSTEM_ERROR);

// Присвоить порядковый номер
	oc_vbn.m_No			= byte(LastNo + 1);

// Установить пароль:
	oc_vbn.m_Password = arg.Password;

// Зарегистрировать в реестре:
	oc_reg.m_VBN.Add(oc_vbn.GetObjectID());

	arg.objID = oc_vbn.GetObjectID();

//----------------------------------------------------------------------------[] 
// Установить параметры сети:

// Name
	if (arg.Name.Size() > 0)
		oc_vbn.m_Name	= arg.Name;
	else if ( (string(oc_vbn.m_Name)).Size() == 0)
	{
		arg.Name.Format("VBN #%d", (int)oc_vbn.m_No);
		oc_vbn.m_Name	= arg.Name;
	}

// Description
	oc_vbn.m_Description			= arg.Description;

// IsModerated
	oc_vbn.m_IsModerated			= arg.IsModerated;

// DefaultLanguage
	if (OC_Exist(OBJ_CLASS_ID_Language, arg.DefaultLanguage))
		oc_vbn.m_DefaultLanguage	= arg.DefaultLanguage;
	else
		oc_vbn.m_DefaultLanguage	= oc_reg.m_Language[0];

// DefaultTZOffset
	if (labs(arg.DefaultTZOffset) <= SECS_IN_DAY/2) {
		oc_vbn.m_DefaultTZOffset	= arg.DefaultTZOffset;
	}

// ConceptMask
	VALIDATE_ID_ARRAY(OBJ_CLASS_ID_Concept, arg.ConceptMask);
	ExpandWithParentConcepts(arg.ConceptMask);
	_IDsToBits_Set(	arg.ConceptMask, oc_vbn.m_ConceptMask);

//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 

	return BX_OK;
}