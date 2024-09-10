//-----------------------------------------------------------------------------
// 説明: シャドウのレンダリング(ポリゴンなどの描画関数を呼び出す前に呼ぶ)
// 引数: 
//       lightName [in] 光源の名前
//       lightDif [in] 光源のディフューズ
//       lightSpc [in] 光源のスペキュラ
//       lookAtMat [in] カメラ姿勢への変換行列
// 返り値:
// その他: 
//-----------------------------------------------------------------------------
void GLUTShadow::renderSunnyPlaceBegin(GLenum lightName, const Vector4f* lightAmb, const Vector4f* lightDif, const Vector4f* lightSpc, const Matrix4f* lookAtMat)
{
	/* テクスチャ変換行列を設定する */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	/* テクスチャ座標の [-1,1] の範囲を [0,1] の範囲に収める */
	glTranslatef(0.5f, 0.5f, 0.5f);
	glScalef(0.5f, 0.5f, 0.5f);

	/* テクスチャのモデルビュー変換行列と透視変換行列の積をかける */
	glMultMatrixf(m_modelview);

	/* 現在のモデルビュー変換の逆変換をかけておく */
	Matrix4f mat = (*lookAtMat);
	Matrix4f inv_mat = mat;
	//glGetFloatv(GL_MODELVIEW_MATRIX, mat.data());
	inv_mat = mat.inverse();
	glMultMatrixf( inv_mat.data() );

	/* モデルビュー変換行列に戻す */
	glMatrixMode(GL_MODELVIEW);

	/* テクスチャマッピングとテクスチャ座標の自動生成を有効にする */
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_Q);

	/* アルファテストを有効にして影の部分だけを描画する */
	glEnable(GL_ALPHA_TEST);

	/* 日向の部分がもとの図形に重ねて描かれるように奥行きの比較関数を変更する */
	glDepthFunc(GL_LEQUAL);

	/* 光源の明るさを日向の部分での明るさに設定 */
    glLightfv(lightName, GL_AMBIENT, (*lightAmb).data() );
	glLightfv(lightName, GL_DIFFUSE, (*lightDif).data() );
    glLightfv(lightName, GL_SPECULAR, (*lightSpc).data() );

}