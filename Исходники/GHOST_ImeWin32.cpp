void GHOST_ImeWin32::GetCaret(HIMC imm_context, LPARAM lparam, ImeComposition *composition)
{
	/**
	 * This operation is optional and language-dependent because the caret
	 * style is depended on the language, e.g.:
	 *   * Korean IMEs: the caret is a blinking block,
	 *     (It contains only one hangul character);
	 *   * Chinese IMEs: the caret is a blinking line,
	 *     (i.e. they do not need to retrieve the target selection);
	 *   * Japanese IMEs: the caret is a selection (or underlined) block,
	 *     (which can contain one or more Japanese characters).
	 */
	int target_start = -1;
	int target_end = -1;
	switch (PRIMARYLANGID(input_language_id_)) {
	case LANG_KOREAN:
		if (lparam & CS_NOMOVECARET) {
			target_start = 0;
			target_end = 1;
		}
		break;
	case LANG_CHINESE:
	{
		int clause_size = ImmGetCompositionStringW(imm_context, GCS_COMPCLAUSE, NULL, 0);
		if (clause_size) {
			static std::vector<unsigned long> clauses;
			clause_size = clause_size / sizeof(clauses[0]);
			clauses.resize(clause_size);
			ImmGetCompositionStringW(imm_context, GCS_COMPCLAUSE, &clauses[0],
				sizeof(clauses[0])  *clause_size);
			if (composition->cursor_position == composition->ime_string.size()) {
				target_start = clauses[clause_size - 2];
				target_end = clauses[clause_size - 1];
			}
			else {
				for (int i = 0; i < clause_size - 1; i++) {
					if (clauses[i] == composition->cursor_position) {
						target_start = clauses[i];
						target_end = clauses[i + 1];
						break;
					}
				}
			}
		}
		else {
			if (composition->cursor_position != -1) {
				target_start = composition->cursor_position;
				target_end = composition->ime_string.size();
			}
		}
		break;
	}
	case LANG_JAPANESE:

		/**
		 * For Japanese IMEs, the robustest way to retrieve the caret
		 * is scanning the attribute of the latest composition string and
		 * retrieving the begining and the end of the target clause, i.e.
		 * a clause being converted.
		 */
		if (lparam & GCS_COMPATTR) {
			int attribute_size = ::ImmGetCompositionStringW(imm_context,
				GCS_COMPATTR,
				NULL, 0);
			if (attribute_size > 0) {
				char *attribute_data = new char[attribute_size];
				if (attribute_data) {
					::ImmGetCompositionStringW(imm_context, GCS_COMPATTR,
						attribute_data, attribute_size);
					for (target_start = 0; target_start < attribute_size;
						++target_start) {
						if (IsTargetAttribute(attribute_data[target_start]))
							break;
					}
					for (target_end = target_start; target_end < attribute_size;
						++target_end) {
						if (!IsTargetAttribute(attribute_data[target_end]))
							break;
					}
					if (target_start == attribute_size) {
						/**
						 * This composition clause does not contain any target clauses,
						 * i.e. this clauses is an input clause.
						 * We treat whole this clause as a target clause.
						 */
						target_end = target_start;
						target_start = 0;
					}
					if (target_start != -1 && target_start < attribute_size &&
						attribute_data[target_start] == ATTR_TARGET_NOTCONVERTED)
					{
						composition->cursor_position = target_start;
					}
				}
				delete[] attribute_data;
			}
		}
		break;
	}
	composition->target_start = target_start;
	composition->target_end = target_end;
}