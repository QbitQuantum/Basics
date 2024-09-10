void InterpolateRotation(Quat startRot, Quat endRot, AngAxis startSpin, float endSpin,
						 PreciseTimeValue startT, PreciseTimeValue endT, PreciseTimeValue curT,
						 float easyIn, bool targetConstant, Quat& resRot, AngAxis& resSpin)
{
	float timeDif = float(endT - startT);
	AngAxis totalSpin = startSpin;
	totalSpin.angle *= timeDif;
	Quat rot0 = startRot + Quat(totalSpin);
	AngAxis difSpin;
	difSpin.angle = QangAxis(rot0, endRot, difSpin.axis);
	AngAxis reverseSpin = difSpin;
	reverseSpin.angle = endSpin;
	AngAxis totalDifSpin = difSpin;
	totalDifSpin.angle = -endSpin*timeDif;
	Quat rot1 = endRot + Quat(totalDifSpin);
	AngAxis partialSpin = startSpin;
	partialSpin.angle *= float(curT - startT);
	Quat rot00 = startRot + Quat(partialSpin);
	AngAxis partialRevSpin = reverseSpin;
	partialRevSpin.angle *= float(curT - endT);
	Quat rot11 = endRot + Quat(partialRevSpin);
	if (!targetConstant)
		rot11.MakeClosest(rot00);
	float timeRatio = float(endT - curT)/timeDif;
	float adjRatio = timeRatio*(timeRatio*easyIn + 1.0f - easyIn);
	resRot = Slerp(rot11, rot00, adjRatio);

	curT.tick -= 1;
	partialSpin = startSpin;
	partialSpin.angle *= float(curT - startT);
	Quat rot20 = startRot + Quat(partialSpin);
	partialRevSpin = reverseSpin;
	partialRevSpin.angle *= float(curT - endT);
	Quat rot21 = endRot + Quat(partialRevSpin);
	if (!targetConstant)
		rot21.MakeClosest(rot20);
	timeRatio = float(endT - curT)/timeDif;
	float adjRatio2 = timeRatio*(timeRatio*easyIn + 1.0f - easyIn);
	Quat prevRot = Slerp(rot21, rot20, adjRatio2);
	resSpin.angle = QangAxis(prevRot, resRot, resSpin.axis);
	if (!targetConstant)
		resSpin.angle = timeRatio*startSpin.angle + (1.0f-timeRatio)*endSpin;
}