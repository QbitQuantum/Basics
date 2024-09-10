inline void LimitTurnUP()
{
	float Dlimit=max(0.0f,min(1.0f,(ViewLen+moveZ-3000.0f)/4000.0f));
	//TestNum=ViewLen+moveZ;
	float TurnUP=Easy_vector_dot(_mm_set_ps(1.0f,0.0f,1.0f,0.0f),ViewMat[2]);
	if(SceneSelect>-1) Dlimit=0.0f;
	if(TurnUP<0.45f+Dlimit*0.285f)
	{
		//ViewUnit.RotInternal(min(0.0f,PosTurn[1]),1.0f,0.0f,0.0f);
		__m128 ViewUnitMATTMP1[4];
		ViewUnit.GetMatrix(ViewUnitMATTMP1);
		float TurnUPTMP2=Easy_vector_dot(_mm_set_ps(1.0f,0.0f,1.0f,0.0f),ViewUnitMATTMP1[2]);
		if(SceneSelect==-1)
		{
			while(TurnUPTMP2<(0.45f+Dlimit*0.285f))
			{
				ViewUnit.RotInternal(-0.001f,1.0f,0.0f,0.0f);
				ViewUnit.GetMatrix(ViewUnitMATTMP1);
				TurnUPTMP2=Easy_vector_dot(_mm_set_ps(1.0f,0.0f,1.0f,0.0f),ViewUnitMATTMP1[2]);
			}
		}
		return;
	}
	if(TurnUP>0.75f)
	{
		ViewUnit.RotInternal(max(0.0f,PosTurn[1]),1.0f,0.0f,0.0f);
		return;
	}
	ViewUnit.RotInternal(PosTurn[1],1.0f,0.0f,0.0f);
}