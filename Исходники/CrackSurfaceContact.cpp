/*	Calculate change in momentum when there is contact. Return true or false if an adjustment was calculated
	If BC at the node, the delta momemtum should be zero in fixed direction
	Only called if both verified are verified and have 1 or more particles
	This method should ignore material that are ignoring cracks
*/
bool CrackSurfaceContact::GetDeltaMomentum(NodalPoint *np,Vector *delPa,CrackVelocityField *cva,CrackVelocityField *cvb,
											Vector *normin,int number,bool postUpdate,double deltime,int *inContact)
{
	// first determine if there is contact
	*inContact=IN_CONTACT;
	
	// velocities above and below
	bool hasParticles;
	double massa,massb;
	Vector pka=cva->GetCMatMomentum(hasParticles,&massa);
	Vector pkb=cvb->GetCMatMomentum(hasParticles,&massb);
	double mnode=1./(massa+massb);
	
	// screen low masses
	double aratio=massa*mnode;
	if(aratio<1.e-6 || aratio>0.999999) return false;
	//if(aratio<1.e-3 || aratio>0.999) return FALSE;
	
	// find Delta p_a (see notes)
	CopyScaleVector(delPa,&pkb,massa*mnode);
	AddScaledVector(delPa,&pka,-massb*mnode);
	
	// get normalized normal vector and find Delta p_a . n (actual (vb-va).n = dotn*(ma+mb)/(ma*mb))
	Vector norm;
	CopyScaleVector(&norm,normin,1./sqrt(DotVectors2D(normin,normin)));
	double dotn=DotVectors2D(delPa,&norm);
	
	// With the first check, any movement apart will be taken as noncontact
	// Also, frictional contact assume dvel<0.
	if(dotn>=0.)
		*inContact=SEPARATED;
	else
	{	// if approaching, check displacements
        // (Note: to use only velocity, skip the following displacement check)
		Vector dispa=cva->GetCMDisplacement(np,true);
		dispa.x/=massa;
		dispa.y/=massa;
		Vector dispb=cvb->GetCMDisplacement(np,true);
		dispb.x/=massb;
		dispb.y/=massb;
		
		// normal cod
		double dnorm=(dispb.x-dispa.x)*norm.x + (dispb.y-dispa.y)*norm.y
                        - mpmgrid.GetNormalCODAdjust(&norm,NULL,0);
		if(postUpdate)
		{	double dvel=(massa+massb)*dotn/(massa*massb);
			dnorm+=dvel*deltime;
		}
		
		// if current displacement positive then no contact
		if(dnorm >= 0.) *inContact=SEPARATED;
	}
	
	// if separated, then no contact unless possibly needed for an imperfect interface
	if(crackContactLaw[number]->ContactIsDone(*inContact==IN_CONTACT)) return false;
	
	// Now need to change momentum. For imperfect interface, change only for perfect directions
	double mredDE;
	if(crackContactLaw[number]->IsFrictionalContact())
	{	bool getHeating = postUpdate && ConductionTask::crackContactHeating;
		double mred = (massa*massb)/(massa+massb);
		double contactArea = 1.;
		if(crackContactLaw[number]->FrictionLawNeedsContactArea())
		{	// Angled path correction (2D only)
			double dist = mpmgrid.GetPerpendicularDistance(&norm, NULL, 0.);
			
			// Area correction method (new): sqrt(2*vmin/vtot)*vtot/dist = sqrt(2*vmin*vtot)/dist
			double vola = cva->GetVolumeNonrigid(true),volb = cvb->GetVolumeNonrigid(true),voltot=vola+volb;
			contactArea = sqrt(2.0*fmin(vola,volb)*voltot)/dist;
			if(fmobj->IsAxisymmetric()) contactArea *= np->x;
		}
		if(!crackContactLaw[number]->GetFrictionalDeltaMomentum(delPa,&norm,dotn,&mredDE,mred,
										getHeating,contactArea,*inContact==IN_CONTACT,deltime,NULL))
		{	return false;
		}
		if(mredDE>0.)
		{	double qrate = mredDE/mred;
			NodalPoint::frictionWork += qrate;
		
			// As heat source need nJ/sec or multiply by 1/timestep
			// Note that this is after transport rates are calculated (by true in last parameter)
			conduction->AddFluxCondition(np,fabs(qrate/deltime),true);
		}
	}
	else
	{
		// Contact handled here only perfect interface (Dt or Dn < 0)
		// Imperfect interfaces are handled as forces later
		if(crackContactLaw[number]->IsPerfectTangentialInterface())
		{	if(!crackContactLaw[number]->IsPerfectNormalInterface(*inContact==IN_CONTACT))
			{	// prefect in tangential, but imperfect in normal direction
				// make stick in tangential direction only
				AddScaledVector(delPa,&norm,-dotn);
			}
			// else perfect in both so return with the stick conditions already in delPa
		}
		else if(crackContactLaw[number]->IsPerfectNormalInterface(*inContact==IN_CONTACT))
		{	// perfect in normal direction, but imperfect in tangential direction
			// make stick in normal direction only
			CopyScaleVector(delPa,&norm,dotn);
		}
		else
		{	// no change in momentum, just imperfect interface forces later and nothing changed here
			return false;
		}
		
	}
	
	return true;
}