CString CMyDialogEx::calculateResult(){

	setAurithmetic(0);
	CString result, additionalNumber;
	double first, second, n_result;
	if (this->m_edit == ""){
		result = "0";
	}
	else{
		int i = 0;
		if (m_edit[0] == '-'){
			i = 1;
		}
		while (i < m_edit.GetLength()){
			if (m_edit[i] == '+' || m_edit[i] == '/' || m_edit[i] == '-' || m_edit[i] == '*'){
				result = m_edit.Mid(0, i);
				break;
			}
			i++;
		}
		if (i == m_edit.GetLength()){
			result = m_edit;
		}
		else if (i != m_edit.GetLength() - 1){
			additionalNumber = m_edit.Mid(i + 1, m_edit.GetLength() - i - 1);
			first = _wtof(result);
			second = _wtof(additionalNumber);
			if (m_edit[i] == '+'){
				n_result = first + second;
			}
			else if (m_edit[i] == '-'){
				n_result = first - second;
			}
			else if (m_edit[i] == '*'){
				n_result = first * second;
			}
			else{
				n_result = first / second;
			}
			result.Format(_T("%lf"),n_result);
		}
	}
	return(result);
}