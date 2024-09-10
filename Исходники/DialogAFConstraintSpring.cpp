/*
================
DialogAFConstraintSpring::LoadConstraint
================
*/
void DialogAFConstraintSpring::LoadConstraint(idDeclAF_Constraint *c)
{
	int i;

	constraint = c;

	// load first anchor from the current idDeclAF_Constraint
	SetSafeComboBoxSelection(&m_comboAnchorJoint, constraint->anchor.joint1.c_str(), -1);
	m_anchor_x = constraint->anchor.ToVec3().x;
	m_anchor_y = constraint->anchor.ToVec3().y;
	m_anchor_z = constraint->anchor.ToVec3().z;

	if (constraint->anchor.type == idAFVector::VEC_JOINT) {
		i = IDC_RADIO_ANCHOR_JOINT;
	} else {
		i = IDC_RADIO_ANCHOR_COORDINATES;
	}

	CheckRadioButton(IDC_RADIO_ANCHOR_JOINT, IDC_RADIO_ANCHOR_COORDINATES, i);

	// load second anchor from the current idDeclAF_Constraint
	SetSafeComboBoxSelection(&m_comboAnchor2Joint, constraint->anchor2.joint1.c_str(), -1);
	m_anchor2_x = constraint->anchor2.ToVec3().x;
	m_anchor2_y = constraint->anchor2.ToVec3().y;
	m_anchor2_z = constraint->anchor2.ToVec3().z;

	if (constraint->anchor2.type == idAFVector::VEC_JOINT) {
		i = IDC_RADIO_ANCHOR2_JOINT;
	} else {
		i = IDC_RADIO_ANCHOR2_COORDINATES;
	}

	CheckRadioButton(IDC_RADIO_ANCHOR2_JOINT, IDC_RADIO_ANCHOR2_COORDINATES, i);

	// spring settings
	m_stretch = constraint->stretch;
	m_compress = constraint->compress;
	m_damping = constraint->damping;
	m_restLength = constraint->restLength;

	// spring limits
	if (constraint->minLength > 0.0f) {
		i = IDC_RADIO_SPRING_MIN_LENGTH;
	} else {
		i = IDC_RADIO_SPRING_NO_MIN_LENGTH;
	}

	CheckRadioButton(IDC_RADIO_SPRING_NO_MIN_LENGTH, IDC_RADIO_SPRING_MIN_LENGTH, i);
	m_minLength = constraint->minLength;

	if (constraint->maxLength > 0.0f) {
		i = IDC_RADIO_SPRING_MAX_LENGTH;
	} else {
		i = IDC_RADIO_SPRING_NO_MAX_LENGTH;
	}

	CheckRadioButton(IDC_RADIO_SPRING_NO_MAX_LENGTH, IDC_RADIO_SPRING_MAX_LENGTH, i);
	m_maxLength = constraint->maxLength;

	// update displayed values
	UpdateData(FALSE);
}