//-----------------------------------------------------------------------------------
void CAR::GraphsNewVals(double dt)		 // CAR
{	
	size_t gsi = pApp->graphs.size();
	bool tireEdit = false;

	//  RANGE  gui sld ..
	//const Dbl fMAX = 9000.0, max_y = 80.0, max_x = 1.0;
	//const Dbl fMAX = 7000.0, max_y = 180.0, max_x = 12.0, pow_x = 1.0;
	//const Dbl fMAX = 7000.0, max_y = 5080.0, max_x = 502.0, pow_x = 5.5;
	Dbl fMAX = pSet->te_yf, max_y = pSet->te_xfy, max_x = pSet->te_xfx, pow_x = pSet->te_xf_pow;
	if (pApp->scn->sc->asphalt)  max_y *= 0.5;

	switch (pApp->pSet->graphs_type)
	{
	case Gh_BulletHit:  /// bullet hit  force,normvel, sndnum,scrap,screech
		if (gsi >= 6)
		{
			const CARDYNAMICS& cd = dynamics;
			pApp->graphs[0]->AddVal(std::min(1.f, cd.fHitForce * 2.f));
			pApp->graphs[1]->AddVal(std::min(1.f, cd.fHitForce2));
			pApp->graphs[2]->AddVal(std::min(1.f, cd.fHitForce3));
			pApp->graphs[3]->AddVal(std::min(1.f, cd.fCarScrap));
			pApp->graphs[4]->AddVal(std::min(1.f, cd.fCarScreech));
			pApp->graphs[5]->AddVal(cd.fHitDmgA);
		}
		break;

	case Gh_CarAccelG:  /// car accel x,y,z
		if (gsi >= 3)
		{
			MATHVECTOR<Dbl,3> v = dynamics.body.GetForce();
			(-dynamics.Orientation()).RotateVector(v);
			float m = dynamics.body.GetMass();
			//LogO("mass: "+fToStr(m,1,5)+"  x: "+fToStr(v[0]/m,2,4)+"  y: "+fToStr(v[1]/m,2,4)+"  z: "+fToStr(v[2]/m,2,4));

			for (int i=0; i < 3; ++i)
				pApp->graphs[i]->AddVal( std::max(0.f, std::min(1.f, float(
					v[i]/m *0.63f /9.81f/3.f + (i==2 ? 0.f : 0.5f) ) )));
		}	break;

	case Gh_CamBounce:  /// cam bounce x,y,z
		if (gsi >= 3)
		{
			const MATHVECTOR<Dbl,3> v = dynamics.cam_body.GetPosition();
			for (int i=0; i < 3; ++i)
				pApp->graphs[i]->AddVal( std::max(0.f, std::min(1.f, 
					(float)v[i] * 3.f + 0.5f)));
		}	break;
		
	case Gh_TireSlips:  /// tire slide,slip
		if (gsi >= 8)
		for (int i=0; i < 4; ++i)
		{
			pApp->graphs[i]->AddVal(negPow(dynamics.wheel[i].slips.slideratio, 0.2) * 0.12f +0.5f);
			//pApp->graphs[i]->AddVal(dynamics.wheel[i].slips.slide * 0.1f +0.5f);
			pApp->graphs[i+4]->AddVal(dynamics.wheel[i].slips.slipratio * 0.1f +0.5f);
		}	break;
		
	case Gh_Suspension:  /// suspension
		if (gsi >= 8)
		for (int i=0; i < 4; ++i)
		{
			const CARSUSPENSION& susp = dynamics.GetSuspension((WHEEL_POSITION)i);
			pApp->graphs[i+4]->AddVal( dynamics.hover ?
				susp.GetVelocity() * 0.2f +0.5f : negPow(susp.GetVelocity(), 0.5) * 0.2f +0.5f);
			pApp->graphs[i]->AddVal(susp.GetDisplacementPercent());
		}	break;

		
	case Gh_TorqueCurve:  /// torque curves, gears
	//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
	{	static int ii = 0;  ++ii;  // skip upd cntr
		if (ii >= 1/*! 10*/ && gsi >= 6*2)
		{	ii = 0;
			const CARDYNAMICS& d = dynamics;
			const Dbl fin = d.diff_center.GetFinalDrive();
			const Dbl r = 1.0 / (2 * PI_d * d.wheel[0].GetRadius());

			String s0="  ratio\n", s1="rpmLow\n", s2="velMax\n";  // text legend
			for (int i=0; i < 6; ++i)
			{
				int g = i+1;
				bool bValid = i < d.transmission.GetForwardGears();
				bool bCur = (g == GetGear()) && d.clutch.IsLocked();

				const Dbl gr = bValid ? d.transmission.GetGearRatio(g) : 0.01, grfin = gr * fin;

				Dbl engRpm = d.engine.GetRPM();
				Dbl downRpm = i>0 ? d.DownshiftRPM(g) : d.engine.GetStartRPM();

				Dbl rmax = d.engine.GetRpmMax(),
				    rmin = d.engine.GetStartRPM(), rng = rmax-rmin;
				Dbl rpmOld = 0;

				//  graph  ------
				for (int x = 0; x < 512; ++x)
				{
					// 100 kmh = 28 car.m/s = 15 wh.rps = 102 eng.rps = 6100 eng.rpm
					//       / 3.6     /1.95 (2*PI*r)   *6.87 ratio = (3.9 * 1.76) 3rd gear
					Dbl xx = x/511.0;  // 0..1
					Dbl vel = xx * 250.0 / 3.6;  // 250 kmh max, in m/s
					Dbl whrps = vel * r;  // wheel revs per sec
					Dbl rpm = whrps * grfin * 60.0;  // engine rpm

					Dbl tq = gr * d.engine.GetTorqueCurve(1.0, rpm);
					if (rpm > rmax)  tq = 0.0;  if (rpm < rmin)  tq = 0.0;  // lines down ||

					Dbl v = tq / 2400.0;  // 2400 max
					if (bCur && engRpm > rpmOld && engRpm <= rpm)  // cur rpm mark ^
						v = 1.0;

					pApp->graphs[i]->AddVal(v);  // torque
					if (i>0)
					{	v = rpm < downRpm  //downRpm > rpmOld && downRpm <= rpm
							? 0.0 : std::max(0.0, std::min(1.0, (rpm-rmin)/rng ));  // rpm range
						pApp->graphs[i+6]->AddVal(v);  }
					rpmOld = rpm;
				}
				pApp->graphs[i]->SetUpdate();
				if (i>0)
				pApp->graphs[i+6]->SetUpdate();

				//  text  ------
				if (bValid)
				{
					Dbl velMax = 3.6 * d.engine.GetRpmMax() / (grfin * 60.0) / r;
					if (!bValid)  velMax = 0;
					
					s0 += toStr(g)+": "+fToStr(gr,3,5)+"\n";
					s1 += fToStr(downRpm,0,4)+"\n";
					s2 += fToStr(velMax,0,3)+"\n";
				}
			}
			s0 += "  final\n    "+fToStr(fin,3,5);
			pApp->graphs[0]->UpdTitle(s0);  pApp->graphs[1]->UpdTitle(s1);  pApp->graphs[2]->UpdTitle(s2);
	}	}	break;

		
	case Gh_Engine:  /// engine torque, power
	{	static int ii = 0;  ++ii;  // skip upd cntr
		if (ii >= 10 && gsi >= 2)
		{	ii = 0;
			const CARENGINE& eng = dynamics.engine;
			float maxTrq = 0.f, maxPwr = 0.f;
			int rpmMaxTq = 0, rpmMaxPwr = 0;
			float rmin = eng.GetStartRPM(), rmax = eng.GetRpmMax(), rng = rmax - rmin;

			for (int x = 0; x < 512; ++x)
			{
				float r = x/512.f * rng + rmin;
				float tq = eng.GetTorqueCurve(1.0, r);
				float pwr = tq * 2.0 * PI_d * r / 60.0 * 0.001 * 1.341;  //kW  // 1kW = 1.341 bhp
				if (tq > maxTrq)  {  maxTrq = tq;  rpmMaxTq = r;  }
				if (pwr > maxPwr)  {  maxPwr = pwr;  rpmMaxPwr = r;  }

				pApp->graphs[0]->AddVal( tq / 600.0 );
				pApp->graphs[1]->AddVal( pwr / 600.0 );
			}
			pApp->graphs[0]->SetUpdate();
			pApp->graphs[1]->SetUpdate();
			//pApp->graphs[0]->UpdTitle(ss);
	}	}	break;

	
	case Gh_Clutch:  /// clutch,rpm,gears
		if (gsi >= 4)
		{
			const CARENGINE& eng = dynamics.engine;
			const CARCLUTCH& clu = dynamics.clutch;
			pApp->graphs[0]->AddVal(eng.GetRPM() / 7500.0);
			#if 0
				MATHVECTOR<Dbl,3> vel = dynamics.GetVelocity(), vx(1,0,0);
				dynamics.Orientation().RotateVector(vx);
				Dbl d = vel.dot(vx),
					velCar = vel.Magnitude() * (d >= 0.0 ? 1 : -1), velWh = dynamics.GetSpeedMPS();
				//pApp->graphs[1]->AddVal(velCar * 0.02f));
				//pApp->graphs[2]->AddVal(velWh * 0.02f);
				if (velWh < 1.1f && velWh > -1.1f)
					d = 1.f;
				else
					d = fabs(velCar >= velWh ? velCar/velWh : velWh/velCar);
				pApp->graphs[2]->AddVal(/*std::min(1.f, std::max(1.f,*/ d * 0.5f);
			#else
			pApp->graphs[1]->AddVal(clu.GetClutch() * 0.3f + 0.15f);
			pApp->graphs[2]->AddVal(clu.IsLocked() ? 0.15f : 0.f);
			#endif
			pApp->graphs[3]->AddVal(GetGear() / 6.f);
		}	break;


	case Gh_Diffs:  /// differentials
		if (gsi >= 6)
		for (int i=0; i < 3*2; ++i)
		{
			CARDIFFERENTIAL* diff;
			switch (i%3)
			{
			case 0: diff = &dynamics.diff_front;  break;
			case 1: diff = &dynamics.diff_rear;  break;
			case 2: diff = &dynamics.diff_center;  break;
			}
			Dbl d;
			if (i/3==0) {
				d = diff->GetSide1Speed() - diff->GetSide2Speed();
				d = negPow(d, 0.4)*0.07 + 0.5;  }  // blue
			else {
				d = diff->GetSide1Torque() - diff->GetSide2Torque();
				d = d*0.0004 + 0.5;  }  // orange
			pApp->graphs[i]->AddVal(d);
		}	break;
		

	case Gh_TireEdit:  /// tire pacejka
	//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
	{	static int ii = 0;  ++ii;  // skip upd cntr
		const int im = pApp->iUpdTireGr > 0 ? 2 : 8;  // faster when editing val
		if (ii >= im && gsi >= TireNG*2)
		{	ii = 0;  pApp->iUpdTireGr = 0;

			const CARTIRE* tire = dynamics.GetTire(FRONT_LEFT);
			Dbl* ft = new Dbl[TireLenG];

			Dbl fmin, fmax, frng, maxF;
			const bool common = 1;  // common range for all
			const bool cust = 1;

			///  Fy lateral --
			for (int i=0; i < TireNG; ++i)
			{
				bool comi = common || i == 0;
				if (comi)
				{	fmin = FLT_MAX;  fmax = FLT_MIN;  frng = 0.0;  }
				
				for (int x=0; x < TireLenG; ++x)
				{	Dbl x0 = Dbl(x) / TireLenG;	 //Dbl yy = max_y * 2.0 * (x-LEN*0.5) / LEN;
					Dbl yy = max_y * pow(x0, pow_x);
					Dbl n = (TireNG-1-i+1) * 0.65;
					Dbl fy = !pApp->iTireLoad ? tire->Pacejka_Fy(yy, n, 0, 1.0, maxF)  // normF
											: tire->Pacejka_Fy(yy, 3, n-2, 1.0, maxF); // camber
					ft[x] = fy;

					if (comi)  // get min, max
					{	if (fy < fmin)  fmin = fy;
						if (fy > fmax)  fmax = fy;  }
				}
				if (comi)  // get range
					frng = 1.0 / (fmax - fmin);
				if (cust)
				{	fmax = fMAX;  fmin = 0.0;  frng = 1.0 / (fmax - fmin);  }
				
				for (int x = 0; x < TireLenG; ++x)
					pApp->graphs[i]->AddVal( (ft[x] - fmin) * frng );
				pApp->graphs[i]->SetUpdate();

				if (i==0)
					pApp->graphs[i]->UpdTitle("Fy Lateral--\n"
						"max y "+fToStr((float)fmax,0,1)+"  x "+fToStr(max_y,0,1)+"\n");
			}

			///  Fx long |
			for (int i=0; i < TireNG; ++i)
			{
				bool comi = common || i == 0;
				if (comi)
				{	fmin = FLT_MAX;  fmax = FLT_MIN;  frng = 0.0;  }
				
				for (int x=0; x < TireLenG; ++x)
				{	Dbl x0 = Dbl(x) / TireLenG;
					Dbl xx = max_x * pow(x0, pow_x);
					Dbl n = (TireNG-1-i+1) * 0.65;
					Dbl fx = pApp->iEdTire != 2 ? tire->Pacejka_Fx(xx, n, 1.0, maxF)  // normF
							 : (!pApp->iTireLoad ? tire->Pacejka_Mz(xx, 0, n, 0.0, 1.0, maxF)    // align- norm
												 : tire->Pacejka_Mz(0, xx, n, 0.0, 1.0, maxF));  // align- camber
					ft[x] = fx;

					if (comi)  // get min, max
					{	if (fx < fmin)  fmin = fx;
						if (fx > fmax)  fmax = fx;  }
				}
				if (comi)  // get range
					frng = 1.0 / (fmax - fmin);
				if (cust)
				{	fmax = fMAX;  fmin = 0.0;  frng = 1.0 / (fmax - fmin);  }
				
				for (int x = 0; x < TireLenG; ++x)
					pApp->graphs[i+TireNG]->AddVal( (ft[x] - fmin) * frng );
				pApp->graphs[i+TireNG]->SetUpdate();

				if (i==0)
					pApp->graphs[i+TireNG]->UpdTitle("Fx Longit |\n"
						"max y "+fToStr((float)fmax,0,1)+"  x "+fToStr(max_x,0,1)+"\n");
			}
			delete[]ft;
		}
	}	tireEdit = true;
	break;
	
	case Gh_Tires4Edit:  /// all tires pacejka vis, edit
	//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
	{	static int ii = 0;  ++ii;  // skip upd cntr
		const int im = 1;  //pApp->iUpdTireGr > 0 ? 2 : 8;  // faster when editing val
		if (ii >= im && gsi >= TireNG*2)
		{	ii = 0;  pApp->iUpdTireGr = 0;

			Dbl* ft = new Dbl[TireLenG];

			Dbl fmin, fmax, frng, maxF;
			const bool common = 1;  // common range for all
			const bool cust = 1;

			///  Fy lateral --  ........
			for (int i=0; i < TireNG; ++i)
			{
				WHEEL_POSITION wp = (WHEEL_POSITION)i;
				const CARTIRE* tire = dynamics.GetTire(wp);
				const CARWHEEL& wh = dynamics.GetWheel(wp);
				const CARWHEEL::SlideSlip& t = wh.slips;

				bool comi = common || i == 0;
				if (comi)
				{	fmin = FLT_MAX;  fmax = FLT_MIN;  frng = 0.0;  }
				
				Dbl yyo=0;
				for (int x=0; x < TireLenG; ++x)
				{	Dbl x0 = Dbl(x) / TireLenG;
					Dbl yy = max_y * pow(x0, pow_x);
					Dbl fy = fabs(t.fy_ar * tire->Pacejka_Fy(yy, t.Fz, t.gamma, t.frict, maxF));

					if (t.fy_rar > yyo && t.fy_rar <= yy)
						fy = 0.0;  // cur mark |
					yyo = yy;

					ft[x] = fy;
					if (comi)  // get min, max
					{	if (fy < fmin)  fmin = fy;
						if (fy > fmax)  fmax = fy;  }
				}
				if (comi)  // get range
					frng = 1.0 / (fmax - fmin);
				if (cust)
				{	fmax = fMAX;  fmin = 0.0;  frng = 1.0 / (fmax - fmin);  }
				
				for (int x = 0; x < TireLenG; ++x)
					pApp->graphs[i]->AddVal( (ft[x] - fmin) * frng );
				pApp->graphs[i]->SetUpdate();

				if (i==0)
					pApp->graphs[i]->UpdTitle("Fy Lateral --   "
						/*"max y "+fToStr((float)fmax,0,1)+"  x "+fToStr(max_y,0,1)+"\n"/**/);
			}

			///  Fx long |  ........
			for (int i=0; i < TireNG; ++i)
			{
				WHEEL_POSITION wp = (WHEEL_POSITION)i;
				const CARTIRE* tire = dynamics.GetTire(wp);
				const CARWHEEL& wh = dynamics.GetWheel(wp);
				const CARWHEEL::SlideSlip& t = wh.slips;

				bool comi = common || i == 0;
				if (comi)
				{	fmin = FLT_MAX;  fmax = FLT_MIN;  frng = 0.0;  }
				
				Dbl xxo=0;
				for (int x=0; x < TireLenG; ++x)
				{	Dbl x0 = Dbl(x) / TireLenG;
					Dbl xx = max_x * pow(x0, pow_x);
					Dbl fx = fabs(t.fx_sr * tire->Pacejka_Fx(xx, t.Fz, t.frict, maxF));

					if (t.fx_rsr > xxo && t.fx_rsr <= xx)
						fx = 0.0;  // cur mark |
					xxo = xx;

					ft[x] = fx;
					if (comi)  // get min, max
					{	if (fx < fmin)  fmin = fx;
						if (fx > fmax)  fmax = fx;  }
				}
				if (comi)  // get range
					frng = 1.0 / (fmax - fmin);
				if (cust)
				{	fmax = fMAX;  fmin = 0.0;  frng = 1.0 / (fmax - fmin);  }
				
				for (int x = 0; x < TireLenG; ++x)
					pApp->graphs[i+TireNG]->AddVal( (ft[x] - fmin) * frng );
				pApp->graphs[i+TireNG]->SetUpdate();

				if (i==0)
					pApp->graphs[i+TireNG]->UpdTitle("Fx Longit |   "
						/*"max y "+fToStr((float)fmax,0,1)+"  x "+fToStr(max_x,0,1)+"\n"/**/);
			}
			delete[]ft;
		}
	}	tireEdit = true;
	break;
	}

	if (tireEdit)
	{	const CGui* g = pApp->gui;
		const CARTIRE* tire = dynamics.GetTire(FRONT_LEFT);
		String ss,sd;
		if (pApp->iEdTire == 0)
		{
			ss += "#A0F0FF--Lateral--\n";  sd += g->sCommon;
			for (int i=0; i < tire->lateral.size(); ++i)
			{
				float f = tire->lateral[i];
				char p = f > 100 ? 0 : (f > 10 ? 1 : (f > 1 ? 2 : 3));
				bool cur = (i == pApp->iCurLat);

				ss += cur ? "#A0EEFF" : "#E0FFFF";
				ss += g->csLateral[i][0] +" "+ fToStr(f, p,5);
				ss += cur ? "  <\n" : "\n";
				sd += g->csLateral[i][1] +"\n";
			}

			ss += "\n#C0F0F0alpha hat\n";
			int z = (int)tire->alpha_hat.size()-1;
			ss += "  "+fToStr( tire->alpha_hat[0], 3,5) + "\n";
			ss += "  "+fToStr( tire->alpha_hat[z/2], 3,5) + "\n";
			ss += "  "+fToStr( tire->alpha_hat[z], 3,5) + "\n";
		}
		else if (pApp->iEdTire == 1)
		{
			ss += "#FFFF70| Longit |\n";  sd += g->sCommon;
			for (int i=0; i < tire->longitudinal.size(); ++i)
			{
				float f = tire->longitudinal[i];
				char p = f > 100 ? 0 : (f > 10 ? 1 : (f > 1 ? 2 : 3));
				bool cur = (i == pApp->iCurLong);

				ss += cur ? "#FFE090" : "#FFFFD0";
				ss += g->csLongit[i][0] +" "+ fToStr(f, p,5);
				ss += cur ? "  <\n" : "\n";
				sd += g->csLongit[i][1] +"\n";
			}

			ss += "\n#F0F0C0sigma hat\n";
			int z = (int)tire->sigma_hat.size()-1;
			ss += "  "+fToStr( tire->sigma_hat[0], 3,5) + "\n";
			ss += "  "+fToStr( tire->sigma_hat[z/2], 3,5) + "\n";
			ss += "  "+fToStr( tire->sigma_hat[z], 3,5) + "\n";
		}
		
		pApp->graphs[gsi-2]->UpdTitle(ss);
		pApp->graphs[gsi-1]->UpdTitle(sd);
	}
}