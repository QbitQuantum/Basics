void wxCustomHeightListCtrl::OnMouseEvent(wxMouseEvent& event)
{
	bool changed = false;
	if (event.ButtonDown() && m_allow_selection) {
		wxPoint pos = event.GetPosition();
		int x, y;
		CalcUnscrolledPosition(pos.x, pos.y, &x, &y);
		if (y < 0 || y > static_cast<int>(m_lineHeight * m_rows.size())) {
			m_focusedLine = npos;
			m_selectedLines.clear();
			changed = true;
		}
		else {
			size_t line = static_cast<size_t>(y / m_lineHeight);

			if (event.ShiftDown()) {
				if (m_focusedLine == npos) {
					changed |= m_selectedLines.insert(line).second;
				}
				else if (line < m_focusedLine) {
					for (size_t i = line; i <= m_focusedLine; ++i) {
						changed |= m_selectedLines.insert(i).second;
					}
				}
				else {
					for (size_t i = line; i >= m_focusedLine && i != npos; --i) {
						changed |= m_selectedLines.insert(i).second;
					}
				}
			}
			else if (event.ControlDown()) {
				if (m_selectedLines.find(line) == m_selectedLines.end()) {
					m_selectedLines.insert(line);
				}
				else {
					m_selectedLines.erase(line);
				}
				changed = true;
			}
			else {
				m_selectedLines.clear();
				m_selectedLines.insert(line);
				changed = true;
			}

			m_focusedLine = line;
		}
		Refresh();
	}

	event.Skip();

	if (changed) {
		wxCommandEvent evt(wxEVT_COMMAND_LISTBOX_SELECTED, GetId());
		ProcessEvent(evt);
	}
}