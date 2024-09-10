//----------------------------------------------------------------------------
PX2::Transform SceneBuilder::GetLocalTransform (INode *node, TimeValue time)
{
	// 计算节点的本地变换。Max节点的变换方法提供的节点的世界变换，所以我们
	// 必须做一些操纵去获得节点的本地变换。

	Matrix3 maxLocal = node->GetObjTMAfterWSM(time) *
		Inverse(node->GetParentNode()->GetObjTMAfterWSM(time));

	// 分解变换
	AffineParts affParts;
	decomp_affine(maxLocal, &affParts);

	// Position
	bool isTranslationZero = 
		fabsf(affParts.t.x) < MIN_DIFFERENCE &&
		fabsf(affParts.t.y) < MIN_DIFFERENCE &&
		fabsf(affParts.t.z) < MIN_DIFFERENCE;

	// Rotation
	float qSign = (affParts.q.w >= 0.0f ? 1.0f : -1.0f);
	bool isRotationIndentity = 
		fabsf(qSign*affParts.q.w - 1.0f) < MIN_DIFFERENCE &&
		fabsf(affParts.q.x) < MIN_DIFFERENCE &&
		fabsf(affParts.q.y) < MIN_DIFFERENCE &&
		fabsf(affParts.q.z) < MIN_DIFFERENCE;

	// Reflect
	bool hasReflection = (affParts.f < 0.0f);

	// Uniform scale
	bool isScaleUniform = (fabsf(affParts.k.x - affParts.k.y)<MIN_DIFFERENCE &&
		fabsf(affParts.k.y - affParts.k.z)<MIN_DIFFERENCE);

	// Unity scale
	bool isScaleUnity = isScaleUniform &&
		fabsf(affParts.k.x - 1.0f) < MIN_DIFFERENCE;

	// Scale orientation is identity?
	float uSign = (affParts.u.w >= 0.0f ? 1.0f : -1.0f);
	bool isOrientIndentity = isScaleUniform || (
		fabsf(uSign*affParts.u.w - 1.0f) < MIN_DIFFERENCE &&
		fabsf(affParts.u.x) < MIN_DIFFERENCE &&
		fabsf(affParts.u.y) < MIN_DIFFERENCE &&
		fabsf(affParts.u.z) < MIN_DIFFERENCE);

	// 计算Phoenix2等价变换
	PX2::Transform local;

	if (!isTranslationZero)
	{
		local.SetTranslate(PX2::APoint(affParts.t.x, affParts.t.y,
			affParts.t.z));
	}

	if (hasReflection)
	{
		affParts.k *= -1.0f;
	}
	
	if (isScaleUniform)
	{
		// 矩阵的形式为R*(s*I)，s是统一缩放矩阵。
		if (!isRotationIndentity)
		{
			PX2::HMatrix rot;
			PX2::HQuaternion(affParts.q.w, -affParts.q.x, -affParts.q.y,
				-affParts.q.z).ToRotationMatrix(rot);
			local.SetRotate(rot);
		}

		if (!isScaleUnity)
		{
			local.SetUniformScale(affParts.k.x);
		}
	}
	else if (isOrientIndentity)
	{
		if (!isRotationIndentity)
		{
			PX2::HMatrix rot;
			PX2::HQuaternion(affParts.q.w, -affParts.q.x, -affParts.q.y,
				-affParts.q.z).ToRotationMatrix(rot);
			local.SetRotate(rot);
		}

		local.SetScale(PX2::APoint(affParts.k.x, affParts.k.y, affParts.k.z));
	}
	else
	{
		PX2::Matrix3f mat(
			maxLocal.GetAddr()[0][0],
			maxLocal.GetAddr()[1][0],
			maxLocal.GetAddr()[2][0],
			maxLocal.GetAddr()[0][1],
			maxLocal.GetAddr()[1][1],
			maxLocal.GetAddr()[2][1],
			maxLocal.GetAddr()[0][2],
			maxLocal.GetAddr()[1][2],
			maxLocal.GetAddr()[2][2]);

		local.SetMatrix(PX2::HMatrix(mat));
	}

	return local;
}