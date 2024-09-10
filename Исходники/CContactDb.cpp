EXPORT_C gint32 CContactDb::UpdateEntity(CDbEntity * pEntity)
	{
	int i;
	char sql[256] = {0};
	OpenDatabase();
	
	try 
		{
		m_dbBeluga.execDML("begin transaction;");
		/* update contact entity */
		strcpy(sql, "update contact set "); 
		for (i=1; i<ContactField_EndFlag; i++)
			{
			GString * fieldName = (GString*)g_ptr_array_index(m_pFieldsName, i);
			strcat(sql, fieldName->str);
			strcat(sql, " = ?");
			if (i != ContactField_EndFlag - 1)
				strcat(sql, ", ");
			}
		strcat(sql, "where cid = ?;");
		
		CppSQLite3Statement statement = m_dbBeluga.compileStatement(sql);

		GString * idValue = NULL;
		if (ECode_No_Error == pEntity->GetFieldValue(0, &idValue))
		{
			statement.bind(ContactField_EndFlag, idValue->str);
			g_string_free(idValue, TRUE);
		}
		else
			statement.bindNull(ContactField_EndFlag);

		for (i=1; i<ContactField_EndFlag; i++)
			{
			GString * fieldValue = NULL;
			if (ECode_No_Error == pEntity->GetFieldValue(i, &fieldValue))
				{
				statement.bind(i, fieldValue->str);
				g_string_free(fieldValue, TRUE);
				}
			else
				statement.bindNull(i);
			}
		statement.execDML();
		statement.reset();
		
		/* update contact_ext entity */
		CContact * contact = (CContact*)pEntity;
		GString * fieldValue = NULL;
		contact->GetFieldValue(ContactField_Type, &fieldValue);
		if (ContactType_Phone == atoi(fieldValue->str))
			{
			CPhoneContact * phonecontact = (CPhoneContact*)pEntity;
			GString * fieldId = NULL;
			phonecontact->GetFieldValue(ContactField_Id, &fieldId);
			memset(sql, 0, sizeof(sql));
			sprintf(sql, "delete from contact_ext where cid = %d;", atoi(fieldId->str));
			m_dbBeluga.execDML(sql);
			
			/* insert phones */
			GHashTable * phones = NULL;
			phonecontact->GetAllPhones(&phones);
			g_hash_table_foreach(phones, update_contact_ext_row, phonecontact);
			g_hash_table_destroy(phones);
			
			/* insert emails */
			GHashTable * emails = NULL;
			phonecontact->GetAllEmails(&emails);
			g_hash_table_foreach(emails, update_contact_ext_row, phonecontact);
			g_hash_table_destroy(emails);
			
			/* insert ims */
			GHashTable * ims = NULL;
			phonecontact->GetAllIMs(&ims);
			g_hash_table_foreach(ims, update_contact_ext_row, phonecontact);
			g_hash_table_destroy(ims);
			
			/* insert addresses */
			GPtrArray * addresses = NULL;
			phonecontact->GetAllAddresses(&addresses);
			for (guint32 j=0; j<addresses->len; j++)
				{
				memset(sql, 0, sizeof(sql));
				stAddress * addr = (stAddress*)g_ptr_array_index(addresses, j);
				sprintf(sql, "insert into address values(NULL, %d, '%s', '%s', '%s', '%s', '%s', '%s');", 
									addr->atype, addr->block, addr->street, addr->district,
									addr->city, addr->state, addr->country, addr->postcode);
									
				guint32 nAddrId = m_dbBeluga.execScalar("select max(aid) from address;");
				memset(sql, 0, sizeof(sql));
				sprintf(sql, "insert into contact_ext values(NULL, %d, %d, %d);", 
									atoi(fieldId->str), addr->atype, nAddrId);
				m_dbBeluga.execDML(sql);
				}
			freeAddressArray(addresses);
			g_string_free(fieldId, TRUE);
			}
		g_string_free(fieldValue, TRUE);
		
		m_dbBeluga.execDML("commit transaction;");
		delete pEntity;
		pEntity = NULL;
		CloseDatabase();
		return 0;
		}
	catch(CppSQLite3Exception& e)
		{
		m_dbBeluga.execDML("rollback transaction;");
		delete pEntity;
		pEntity = NULL;
		CloseDatabase();
		return ERROR(ESide_Client, EModule_Db, ECode_Update_Failed);
		}
		
	return 0;
	}