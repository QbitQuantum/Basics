		void							TMCtrl::update(REAL dt)
		{
			if(!_node.valid())
				return;

			Z_ASSERT( find(_node.get_unsafe()->getCtrlSet().getArray().begin(), _node.get_unsafe()->getCtrlSet().getArray().end(), this) != _node.get_unsafe()->getCtrlSet().getArray().end());

			_anim_ctrl.advance(dt);

			LOD::TRANSITION transition = LOD::isForceTransition() ? LOD::getForcedTransition() : _anim_ctrl.getTransition();
			LOD::INTERPOLATION interpolation = LOD::isForceInterpolation() ? LOD::getForcedInterpolation() : getInterpolation();

			if(interpolation == LOD::INTERPOLATION_LINEAR)
			{
				switch(transition)
				{
				case LOD::TRANSITION_NONE:
					{
						AnimCtrl::Clip& stage = _anim_ctrl.current_stage();
						if(getPosAnimData())
							_node.get_unsafe()->setPos(_pos_eval.sample(stage.getTime()));
						if(getRotAnimData())
							_node.get_unsafe()->setRot(_rot_eval.sample(stage.getTime()));
						if(getScaleAnimData())
							_node.get_unsafe()->setScale(_scale_eval.sample(stage.getTime()));
					}
					break;
				case LOD::TRANSITION_BLEND_CAPTURED:
					{
						AnimCtrl::Clip& stage = _anim_ctrl.current_stage();
						if(getPosAnimData())
							_node.get_unsafe()->setPos(_pos_eval.sample(stage.getTime()).lerp(_pos_captured, 1 - stage.getWeight()));
						if(getRotAnimData())
							_node.get_unsafe()->setRot(_rot_eval.sample(stage.getTime()).slerp(_rot_captured, 1 - stage.getWeight()));
						if(getScaleAnimData())
							_node.get_unsafe()->setScale(_scale_eval.sample(stage.getTime()).lerp(_scale_captured, 1 - stage.getWeight()));
					}
					break;
				case LOD::TRANSITION_MULTISTAGE_BLEND:
					{
						Vec3 pos;
						Quat rot;
						Vec3 scale;
						bool enable_pos = !!getPosAnimData();
						bool enable_rot = !!getRotAnimData();
						bool enable_scale = !!getScaleAnimData();
						if(true)
						{
							size_t c = _anim_ctrl.getStageCount();
							AnimCtrl::Clip* stages = _anim_ctrl.getStages();
							for(size_t i = 0; i < c; ++i)
							{
								const AnimCtrl::Clip& stage = stages[i];
								if(i == 0)
								{
									if(enable_pos)
										pos = _pos_eval.sample(stage.getTime());
									if(enable_rot)
										rot = _rot_eval.sample(stage.getTime());
									if(enable_scale)
										scale = _scale_eval.sample(stage.getTime());
									continue;
								}
								if(enable_pos)
									pos = pos.lerp(_pos_eval.sample(stage.getTime()), stage.getWeight());
								if(enable_rot)
									rot = rot.slerp(_rot_eval.sample(stage.getTime()), stage.getWeight());
								if(enable_scale)
									scale = scale.lerp(_scale_eval.sample(stage.getTime()), stage.getWeight());
							}
							if(enable_pos)
								_node.get_unsafe()->setPos(pos);
							if(enable_rot)
								_node.get_unsafe()->setRot(rot);
							if(enable_scale)
								_node.get_unsafe()->setScale(scale);
						}
					}
					break;
				}
			}
			else
			{
				switch(transition)
				{
				case LOD::TRANSITION_NONE:
					{
						AnimCtrl::Clip& stage = _anim_ctrl.current_stage();
						if(getPosAnimData())
							_node.get_unsafe()->setPos(_pos_eval.eval_step(stage.getTime()));
						if(getRotAnimData())
							_node.get_unsafe()->setRot(_rot_eval.eval_step(stage.getTime()));
						if(getScaleAnimData())
							_node.get_unsafe()->setScale(_scale_eval.eval_step(stage.getTime()));
					}
					break;
				case LOD::TRANSITION_BLEND_CAPTURED:
					{
						AnimCtrl::Clip& stage = _anim_ctrl.current_stage();
						if(getPosAnimData())
							_node.get_unsafe()->setPos(_pos_eval.eval_step(stage.getTime()).lerp(_pos_captured, 1 - stage.getWeight()));
						if(getRotAnimData())
							_node.get_unsafe()->setRot(_rot_eval.eval_step(stage.getTime()).slerp(_rot_captured, 1 - stage.getWeight()));
						if(getScaleAnimData())
							_node.get_unsafe()->setScale(_scale_eval.eval_step(stage.getTime()).lerp(_scale_captured, 1 - stage.getWeight()));
					}
					break;
				case LOD::TRANSITION_MULTISTAGE_BLEND:
					{
						Vec3 pos;
						Quat rot;
						Vec3 scale;
						bool enable_pos = !!getPosAnimData();
						bool enable_rot = !!getRotAnimData();
						bool enable_scale = !!getScaleAnimData();
						if(true)
						{
							size_t c = _anim_ctrl.getStageCount();
							AnimCtrl::Clip* stages = _anim_ctrl.getStages();
							for(size_t i = 0; i < c; ++i)
							{
								const AnimCtrl::Clip& stage = stages[i];
								if(i == 0)
								{
									if(enable_pos)
										pos = _pos_eval.eval_step(stage.getTime());
									if(enable_rot)
										rot = _rot_eval.eval_step(stage.getTime());
									if(enable_scale)
										scale = _scale_eval.eval_step(stage.getTime());
									continue;
								}
								if(enable_pos)
									pos = pos.lerp(_pos_eval.eval_step(stage.getTime()), stage.getWeight());
								if(enable_rot)
									rot = rot.slerp(_rot_eval.eval_step(stage.getTime()), stage.getWeight());
								if(enable_scale)
									scale = scale.lerp(_scale_eval.eval_step(stage.getTime()), stage.getWeight());
							}
							if(enable_pos)
								_node.get_unsafe()->setPos(pos);
							if(enable_rot)
								_node.get_unsafe()->setRot(rot);
							if(enable_scale)
								_node.get_unsafe()->setScale(scale);
						}
					}
					break;
				}
			}
		}