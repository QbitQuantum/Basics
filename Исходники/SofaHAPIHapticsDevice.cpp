		void SofaHAPIHapticsDevice::draw(const sofa::core::visual::VisualParams* vparams)
		{
			if (!device.get()) return;
			if(drawDevice.getValue())
			{
				// TODO
				HAPI::HAPIHapticsDevice::DeviceValues dv = device->getDeviceValues();
				/// COMPUTATION OF THE virtualTool 6D POSITION IN THE World COORDINATES
				Vec3d pos = conv(dv.position);
				Vec3d force = conv(dv.force);
				Quat quat = conv(dv.orientation);
				quat.normalize();
				Transform baseDevice_H_endDevice(pos*data.scale, quat);
				Transform world_H_virtualTool = data.world_H_baseDevice * baseDevice_H_endDevice * data.endDevice_H_virtualTool;
				Vec3d wpos = world_H_virtualTool.getOrigin();

				vparams->drawTool()->setLightingEnabled(true); //Enable lightning
				if (drawHandleSize.getValue() == 0.0f)
				{
					std::vector<Vec3d> points;
					points.push_back(wpos);
					vparams->drawTool()->drawSpheres(points, 1.0f, sofa::defaulttype::Vec<4,float>(0,0,1,1));
				}
				else
				{
					Vec3d wposH = wpos + data.world_H_baseDevice.projectVector( baseDevice_H_endDevice.projectVector(Vec3d(0.0,0.0,drawHandleSize.getValue())));
					vparams->drawTool()->drawArrow(wposH, wpos, drawHandleSize.getValue()*0.05f, sofa::defaulttype::Vec<4,float>(0,0,1,1));
				}
				if (force.norm() > 0 && drawForceScale.getValue() != 0.0f)
				{
					//std::cout << "F = " << force << std::endl;
					Vec3d fscaled = force*(drawForceScale.getValue()*data.scale);
					Transform baseDevice_H_endDeviceF(pos*data.scale+fscaled, quat);
					Transform world_H_virtualToolF = data.world_H_baseDevice * baseDevice_H_endDeviceF * data.endDevice_H_virtualTool;
					Vec3d wposF = world_H_virtualToolF.getOrigin();
					vparams->drawTool()->drawArrow(wpos, wposF, 0.1f, sofa::defaulttype::Vec<4,float>(1,0,0,1));
				}

				vparams->drawTool()->setLightingEnabled(false); //Disable lightning
			}
		}