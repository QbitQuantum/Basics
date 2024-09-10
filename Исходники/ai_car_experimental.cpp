void AI_Car_Experimental::analyzeOthers(float dt, const std::list <CAR> & checkcars)
{
	//const float speed = std::max(1.0f,car->GetVelocity().Magnitude());
	const float half_carlength = 1.25; //in meters

	//std::cout << speed << ": " << authority << std::endl;

	//const MATHVECTOR <float, 3> steer_right_axis = direction::Right;
	const MATHVECTOR <float, 3> throttle_axis = direction::Forward;

#ifdef VISUALIZE_AI_DEBUG
	//avoidancedraw->ClearLine();
#endif

	for (std::list <CAR>::const_iterator i = checkcars.begin(); i != checkcars.end(); ++i)
	{
		if (&(*i) != car)
		{
			struct AI_Car_Experimental::OTHERCARINFO & info = othercars[&(*i)];

			//find direction of other cars in our frame
			MATHVECTOR <float, 3> relative_position = i->GetCenterOfMassPosition() - car->GetCenterOfMassPosition();
			(-car->GetOrientation()).RotateVector(relative_position);

			//std::cout << relative_position.dot(throttle_axis) << ", " << relative_position.dot(steer_right_axis) << std::endl;

			//only make a move if the other car is within our distance limit
			float fore_position = relative_position.dot(throttle_axis);
			//float speed_diff = i->GetVelocity().dot(throttle_axis) - car->GetVelocity().dot(throttle_axis); //positive if other car is faster

			MATHVECTOR <float, 3> myvel = car->GetVelocity();
			MATHVECTOR <float, 3> othervel = i->GetVelocity();
			(-car->GetOrientation()).RotateVector(myvel);
			(-i->GetOrientation()).RotateVector(othervel);
			float speed_diff = othervel.dot(throttle_axis) - myvel.dot(throttle_axis); //positive if other car is faster

			//std::cout << speed_diff << std::endl;
			//float distancelimit = clamp(distancelimitcoeff*-speed_diff, distancelimitmin, distancelimitmax);
			const float fore_position_offset = -half_carlength;
			if (fore_position > fore_position_offset)// && fore_position < distancelimit) //only pay attention to cars roughly in front of us
			{
				//float horizontal_distance = relative_position.dot(steer_right_axis); //fallback method if not on a patch
				//float orig_horiz = horizontal_distance;

				const BEZIER * othercarpatch = GetCurrentPatch(&(*i));
				const BEZIER * mycarpatch = GetCurrentPatch(car);

				if (othercarpatch && mycarpatch)
				{
					float my_track_placement = GetHorizontalDistanceAlongPatch(*mycarpatch, TransformToPatchspace(car->GetCenterOfMassPosition()));
					float their_track_placement = GetHorizontalDistanceAlongPatch(*othercarpatch, TransformToPatchspace(i->GetCenterOfMassPosition()));

					float speed_diff_denom = clamp(speed_diff, -100, -0.01);
					float eta = (fore_position-fore_position_offset)/-speed_diff_denom;

					info.fore_distance = fore_position;

					if (!info.active)
						info.eta = eta;
					else
						info.eta = RateLimit(info.eta, eta, 10.f*dt, 10000.f*dt);

					float horizontal_distance = their_track_placement - my_track_placement;
					//if (!info.active)
						info.horizontal_distance = horizontal_distance;
					/*else
						info.horizontal_distance = RateLimit(info.horizontal_distance, horizontal_distance, spacingdistance*dt, spacingdistance*dt);*/

					//std::cout << info.horizontal_distance << ", " << info.eta << std::endl;

					info.active = true;
				}
				else
					info.active = false;

				//std::cout << orig_horiz << ", " << horizontal_distance << ",    " << fore_position << ", " << speed_diff << std::endl;

				/*if (!min_horizontal_distance)
					min_horizontal_distance = optional <float> (horizontal_distance);
				else if (std::abs(min_horizontal_distance.get()) > std::abs(horizontal_distance))
					min_horizontal_distance = optional <float> (horizontal_distance);*/
			}
			else
				info.active = false;

/*#ifdef VISUALIZE_AI_DEBUG
			if (info.active)
			{
				avoidancedraw->AddLinePoint(car->GetCenterOfMassPosition());
				MATHVECTOR <float, 3> feeler1(speed*info.eta,0,0);
				car->GetOrientation().RotateVector(feeler1);
				MATHVECTOR <float, 3> feeler2(0,-info.horizontal_distance,0);
				car->GetOrientation().RotateVector(feeler2);
				avoidancedraw->AddLinePoint(car->GetCenterOfMassPosition()+feeler1+feeler2);
				avoidancedraw->AddLinePoint(car->GetCenterOfMassPosition());
			}
#endif*/
		}
	}
}