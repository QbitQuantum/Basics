int TissueCell::TakeStep(RealType dt, RealType v0, RealType mob, RealType t_relax, RealType noise, RealType box_size, MTRand& rng, bool eq){
		int rtn = 0;
		// Handle invalid arguments
		if (mob < 0){ throw std::invalid_argument("mob < 0"); }
		if (t_relax < 0){ throw std::invalid_argument("t_relax < 0"); }
		if (noise < 0){ throw std::invalid_argument("noise < 0"); }

		//RealType ffffx = this->Fx;
		//RealType ffffy = this->Fy;
		//RealType xxxxx = this->x;
		//RealType yyyyy = this->y;
		//RealType aaaangle = this->angle;

		RealType dxF = (mob * Fx) * dt;
		RealType dxV = (std::cos(this->angle) * v0) * dt;
		RealType dx = dxF + dxV;
		RealType dyF = (mob * Fy) * dt;
		RealType dyV = (std::sin(this->angle) * v0) * dt;
		RealType dy = dyF + dyV;


		RealType vmag = sqrt(dx * dx + dy * dy); 

		RealType dtheta = 0;
		// arcsin of a cross product of two normalized vecors will give the deflection in theta.
		RealType step_noise = (rng.rand() - .5) * noise;
		if (vmag != 0){
			try{
				dtheta = (dt / t_relax) * std::asin( (std::cos(angle) * dy - std::sin(angle) * dx) / vmag);
				if (isnan(dtheta)){
					throw (std::cos(angle) * dy - std::sin(angle) * dx) / vmag;
				}
			}
			catch(RealType arcarg){
				std::cout << "Caught bad arctan." <<std::endl;
				if (arcarg >= 1 && arcarg <= 1.00001){
					dtheta = (dt / t_relax) * 3.141592865358979 / 2.0;
				}
				else if (arcarg <=-1 && arcarg >=-1.00001){
					dtheta = - (dt / t_relax) * 3.141592865358979 / 2.0;
				}
				else{
					throw std::domain_error("Arctangent argument outside of allowed extended domain from floating point arithmetic");
				}
			}

		}
		this->angle += step_noise;

#ifndef FORCE_WARN_OFF
		if (vmag > 10){
			std::cout << "WARNING: Assuming Req of 1: Single step is on the order of Req; vmag = " << vmag <<". Check your timestep and interaction parameters." << std::endl;
		}
#endif

		this->x += dx;
		this->y += dy;

		// =========================================================================================
		// Apply periodic topology:

		// Map x and y [0, box_size) periodically
		// e.g. box_size = 10.0, sends 10.0 -> 0.0
		// For a non-equilibration step:
		if (!eq){
			if (this->x >= box_size){ this->x -= box_size ;} 		
			if (this->y >= box_size){ this->y -= box_size; } 
			// e.g. box_size = 10.0, then -10.0 -> ceil(1) -> 0 and  -10.1 -> ceil(1.01) -> 9.99
			if (this->x < 0){ this->x += box_size; }  
			if (this->y < 0){ this->y += box_size; }
		}

		// For an equilibration step:
		if (eq){
			RealType beforex = this->x;
			RealType beforey = this->y;
			this->x = fmod(fmod(this->x, box_size) + box_size, box_size);
			this->y = fmod(fmod(this->y, box_size) + box_size, box_size);

			if (beforex != this->x or beforey != this->y){
				rtn = 1;
			}
		}

		RealType twoPi = 2.0 * 3.141592865358979;
		if (!(this->angle + dtheta >= 0)){
			this->angle += twoPi;
		}
		if (!(this->angle + dtheta < twoPi)){
			this->angle -= twoPi;
		}

		this->angle += dtheta;
		// Assertions to match the above definitions
		// Furthermore: Do not allow a particle to step more than a box width.
		//  (angle can rotate artibrarily)
		assert(fmod( 0 + twoPi, twoPi) == 0);
		assert(this->x < box_size);
		assert(this->x >= 0);
		assert(this->y < box_size);
		assert(this->y >= 0);
		if (!(this-> angle < twoPi)){
			std::cout << "Current angle is " << this->angle << " which is apparently larger than or equal to " << twoPi << std::endl;
			assert(this-> angle < twoPi);
		}
		if (!(this-> angle >= 0)){
			std::cout << "Current angle is " << this->angle << " which is apparently smaller than 0." << std::endl;
			assert(this->angle >= 0);
		}

		// Clear the old forces;
		this->Fx = 0;
		this->Fy = 0;
		
		return rtn;
}