int CModel::Draw (CObject *objP, float *fLight)
{
	CSubModel		*pso;
	int				r = 1, i;
	CFloatVector	vo;

vo.SetZero ();
transformation.Begin (objP->info.position.vPos, objP->info.position.mOrient);
if (!gameStates.ogl.bUseTransform)
	mView.Assign (transformation.m_info.view [0]);
vPos.Assign (transformation.m_info.pos);
if (IsMultiGame && netGame.BrightPlayers)
	*fLight = 1.0f;
OglActiveTexture (GL_TEXTURE0, 0);
glEnable (GL_TEXTURE_2D);
for (i = 0, pso = m_subModels.Buffer (); i < m_nSubModels; i++, pso++)
	if (pso->m_nParent == -1) {
		if (!pso->Render (objP, this, vo, i, fLight)) {
			r = 0;
			break;
			}
		}
transformation.End ();
glDisable (GL_TEXTURE_2D);
return r;
}