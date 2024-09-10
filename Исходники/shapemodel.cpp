/*---------------------------------------------------------------------*//**
	全シェイプを含めたバウンディングボックスを計算する
**//*---------------------------------------------------------------------*/
void ShapeModel::getAllShapesBoundingBox(Vector3F* vBbCenter, f32* rBb)
{
	if(_vShapesBbCenter == 0L)	// 未計算
	{
		Vector3F vBbMinWk;
		Vector3F vBbMaxWk;

		// 全シェイプ分を計算する
		Vector3F vBbMinS;
		Vector3F vBbMaxS;
		_sarrShape[0]->getBoundingBox(&vBbMinWk, &vBbMaxWk);
		for(int i = 1; i < (int)_numShape; i++)
		{
			_sarrShape[i]->getBoundingBox(&vBbMinS, &vBbMaxS);
			if(vBbMinWk._v[0] > vBbMinS._v[0])	{	vBbMinWk._v[0] = vBbMinS._v[0];	}
			if(vBbMinWk._v[1] > vBbMinS._v[1])	{	vBbMinWk._v[1] = vBbMinS._v[1];	}
			if(vBbMinWk._v[2] > vBbMinS._v[2])	{	vBbMinWk._v[2] = vBbMinS._v[2];	}
			if(vBbMaxWk._v[0] < vBbMaxS._v[0])	{	vBbMaxWk._v[0] = vBbMaxS._v[0];	}
			if(vBbMaxWk._v[1] < vBbMaxS._v[1])	{	vBbMaxWk._v[1] = vBbMaxS._v[1];	}
			if(vBbMaxWk._v[2] < vBbMaxS._v[2])	{	vBbMaxWk._v[2] = vBbMaxS._v[2];	}
		}

		// 取得済みとして保存する
		_vShapesBbCenter = new Vector3F((vBbMinWk.x() + vBbMaxWk.x()) * 0.5f, (vBbMinWk.y() + vBbMaxWk.y()) * 0.5f, (vBbMinWk.z() + vBbMaxWk.z()) * 0.5f);
		_rShapesBb = (vBbMaxWk - vBbMinWk).length() * 0.5f;
	}

	if(vBbCenter != 0L)	{	vBbCenter->copy(_vShapesBbCenter);	}
	if(rBb != 0L)		{	*rBb = _rShapesBb;					}
}