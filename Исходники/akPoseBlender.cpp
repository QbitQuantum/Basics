void akPoseBlender::blendJoint(BlendMode bmode, RotMode rmode, akScalar weight, const akTransformState& a, const akTransformState& b, akTransformState& out)
{
	switch(bmode)
	{
	case PB_BM_LERP:
		out.loc =  lerp(weight, a.loc, b.loc);
		
		if(rmode==PB_RM_SLERP)
			out.rot = slerp(weight, a.rot, b.rot);
		else
			out.rot = lerp(weight, a.rot, b.rot);
			
		out.scale = lerp(weight, a.scale, b.scale);
		break;
		
	case PB_BM_ADD:
		out.loc =  a.loc + b.loc * weight;
		
		if(rmode==PB_RM_SLERP)
			out.rot = slerp(weight, a.rot, a.rot*b.rot);
		else
			out.rot = lerp(weight, a.rot, a.rot*b.rot);
		
		out.scale = lerp(weight, a.scale, mulPerElem(a.scale, b.scale) );

//		{
//		akTransformState sum;
//		akMathUtils::extractTransform(a.toMatrix()*b.toMatrix(), sum.loc, sum.rot, sum.scale);
//		out.loc =  lerp(weight, a.loc, sum.loc);
		
//		if(rmode==PB_RM_SLERP)
//			out.rot = slerp(weight, a.rot, sum.rot);
//		else
//			out.rot = lerp(weight, a.rot, sum.rot);
			
//		out.scale = lerp(weight, a.scale, sum.scale);
//		}

		break;
		
	//TODO test this.
	case PB_BM_SUB:
		out.loc = a.loc - b.loc * weight;
		
		akQuat invrot = conj(b.rot);
		
		if(rmode==PB_RM_SLERP)
			out.rot = slerp(weight, a.rot, a.rot*invrot);
		else
			out.rot = lerp(weight, a.rot, a.rot*invrot);
		
		// Needs a check for dision by 0 (not likely to happen).
		out.scale = lerp(weight, a.scale, divPerElem(a.scale, b.scale) );
		break;
	}
}