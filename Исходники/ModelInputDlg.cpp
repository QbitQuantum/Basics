	void CModelInputDlg::SetModelInput(CModelInput& modelInput, bool bDefault)
	{
		ASSERT(m_titleCtrlArray.GetSize() == m_varCtrlArray.GetSize());
		ASSERT(m_titleCtrlArray.GetSize() == (int)m_variables.size());

		m_modelInput = modelInput;
		m_bDefault = bDefault;

		for (int i = 0, ii = 0; i < m_variables.size(); i++)
		{
			CStatic* pStatic = (CStatic*)m_titleCtrlArray[i];
			pStatic->EnableWindow(!m_bDefault);

			if (ii < modelInput.size())
			{
				switch (m_variables[i].GetType())
				{
				case CModelInputParameterDef::kMVBool:
				{
					CComboBox* pCombo = (CComboBox*)m_varCtrlArray[i];
					pCombo->SetCurSel(modelInput[ii++].GetBool() ? 0 : 1);
					pCombo->EnableWindow(!m_bDefault);
					break;
				}

				case CModelInputParameterDef::kMVInt:
				case CModelInputParameterDef::kMVReal:
				case CModelInputParameterDef::kMVString:
				case CModelInputParameterDef::kMVFile:
				{
					CCFLEdit* pEdit = (CCFLEdit*)m_varCtrlArray[i];
					pEdit->SetString(modelInput[ii++].GetStr());
					pEdit->EnableWindow(!m_bDefault);
					break;
				}

				case CModelInputParameterDef::kMVListByPos:
				{
					CCFLComboBox* pCombo = (CCFLComboBox*)m_varCtrlArray[i];
					pCombo->SelectFromItemData(modelInput[ii++].GetListIndex());
					pCombo->EnableWindow(!m_bDefault);
					break;
				}

				case CModelInputParameterDef::kMVListByString:
				case CModelInputParameterDef::kMVListByCSV:
				{
					CCFLComboBox* pCombo = (CCFLComboBox*)m_varCtrlArray[i];
					pCombo->SelectStringExact(-1, modelInput[ii++].GetStr());
					pCombo->EnableWindow(!m_bDefault);
					break;
				}

				case CModelInputParameterDef::kMVTitle:
				case CModelInputParameterDef::kMVLine:
				case CModelInputParameterDef::kMVStaticText:
				{
					CStatic* pStatic = (CStatic*)m_varCtrlArray[i];
					pStatic->EnableWindow(!m_bDefault);
					break;
				}

				default: ASSERT(false);
				}
			}
		}
	}