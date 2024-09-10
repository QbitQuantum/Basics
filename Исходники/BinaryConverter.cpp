void BinaryConverter::LoadAnimations(Serializer::Reader &rd)
{
	//load channels and PRS keys
	const Uint32 numAnims = rd.Int32();
	for (Uint32 i = 0; i < numAnims; i++) {
		const std::string animName = rd.String();
		const double duration = rd.Double();
		Animation *anim = new Animation(animName, duration);
		const Uint32 numChans = rd.Int32();
		for (Uint32 j = 0; j < numChans; j++) {
			const std::string tgtName = rd.String();
			MatrixTransform* tgtNode = dynamic_cast<MatrixTransform*>(m_model->m_root->FindNode(tgtName));
			anim->m_channels.push_back(AnimationChannel(tgtNode));
			auto& chan = anim->m_channels.back();
			for (Uint32 numKeys = rd.Int32(); numKeys > 0; numKeys--) {
				const double ktime = rd.Double();
				const vector3f kpos = rd.Vector3f();
				chan.positionKeys.push_back(PositionKey(ktime, kpos));
			}
			for (Uint32 numKeys = rd.Int32(); numKeys > 0; numKeys--) {
				const double ktime = rd.Double();
				const Quaternionf krot = rd.RdQuaternionf();
				chan.rotationKeys.push_back(RotationKey(ktime, krot));
			}
			for (Uint32 numKeys = rd.Int32(); numKeys > 0; numKeys--) {
				const double ktime = rd.Double();
				const vector3f kscale = rd.Vector3f();
				chan.scaleKeys.push_back(ScaleKey(ktime, kscale));
			}
		}
		m_model->m_animations.push_back(anim);
	}
}