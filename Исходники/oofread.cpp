void CModel::GetBounds (void)
{
	CSubModel*		pso;
	CFloatVector	vo;
	int				i;

vo.SetZero ();
OOF_InitMinMax (&m_vMin, &m_vMax);
for (i = 0, pso = m_subModels.Buffer (); i < m_nSubModels; i++, pso++)
	if (pso->m_nParent == -1)
		GetSubModelBounds (pso, vo);
}