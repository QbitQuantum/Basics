/*!
\brief Do periodical checks for weather change
\author Xanatar
*/
void check_region_weatherchange ()
{
	int r,sn=0, rn=0, dr=0, sm, i;

	outInfo("performing weather change...");

	//! \todo revisit this part
	for (i=0;i<256;i++)
	{
		region_st &regionRef = region[i];
		if ((regionRef.keepchance==0)&&(regionRef.drychance==0)) continue;
		r = rand()%100;
		if ((r<=regionRef.keepchance)||(regionRef.keepchance==100)) continue;
		//we're here, let's change the weeeeather
		dr = (regionRef.wtype==0) ? 0 : regionRef.drychance;
		rn = (regionRef.wtype==1) ? 0 : regionRef.rainchance;
		sn = (regionRef.wtype==2) ? 0 : regionRef.snowchance;
		if (!regionRef.ignoreseason)
		{
			//! \todo actually the calendar system for weather variation during the year wasn't a bad idea, but it should NOT involve 3 float multiplications + 3 float to int and 3 int to float conversions for each region every weathercheck
			dr = static_cast<int>(static_cast<float>(dr) * Calendar::g_fCurDryMod);
			rn = static_cast<int>(static_cast<float>(rn) * Calendar::g_fCurRainMod);
			sn = static_cast<int>(static_cast<float>(sn) * Calendar::g_fCurSnowMod);
		}
		sm = dr+rn+sn;
		r = rand()%sm;
		if (r < dr) regionRef.wtype = 0;
		else if (r < (rn+dr)) regionRef.wtype = 1;
		else regionRef.wtype = 2;
	}


	// Chronodt 17/8/04 - begun additional weathercode
		//! \todo sobstitute temporary region subnames with the true ones when regions redone
		//! \todo a for cycle with all the regions (cregion is the region currently esamined)

	//for (whatever will cycle all region, with cregion as index or iterator)
	{
		Climates climate = region[cregion].climate;
		if (climate == clNone) continue;	//no weather change for a dungeon
		WeatherType current = region[cregion].weatherCurrent;
		sint16_t oldintensity = region[cregion].weatherIntensity;
		sint16_t newintensity = oldintensity;

		//Getting the 4 adiacent regions. getXXXXregion should return invalid if such region does not exist
		uint16_t nregion = getNorthRegion(cregion);
		uint16_t eregion = getEastRegion(cregion);
		uint16_t sregion = getSouthRegion(cregion);
		uint16_t wregion = getWestRegion(cregion);

		// modifying the intensity by surrounding squares (obiously the old status)
		newintensity += getIntensityModifier(cregion, nregion);
		newintensity += getIntensityModifier(cregion, eregion);
		newintensity += getIntensityModifier(cregion, sregion);
		newintensity += getIntensityModifier(cregion, wregion);

		// adding intensity by random raincheck (based on region configuration)
		//! \todo modify these with new region parameters
		uint8_t dry  = region[cregion].drychance;
		uint8_t rain = region[cregion].rainchance;
		uint8_t snow = region[cregion].snowchance;
		uint8_t r = rand()%100;
		if (r < dry) newintensity -= (dry - r) * 5;
		r = rand()%100;
		if (r < rain) newintensity += (rain - r) * 5;

		if (newintensity > 140) newintensity = 140;
		if (newintensity < 0) newintensity = 0;

		bool snow = false;
		string message = "";

		//! \todo insert a maxlight to limit light in bad beather (but nightvision should counter this)

		switch (current)	//select message type to send clients based on previous weather in region. Also checking if weather change is too sudden, and if so lessen the impact :D
		{
		case wtSun:		// intensity 0 - 20
			if (newintensity > 40)
			{
				newintensity = 40;	//If it was so clear, we need at least a few clouds in the sky before it can rain (or snow)
				message = "You see some clouds closing in";
			}
			break;
		case wtCloud:		// intensity 21 - 40
			if (newintensity > 90)		// to have more than a light rain we need heavier clouds first
			{
				newintensity = 70;
				message = "Cloud covering thickens visibly. You hear rumbling in the distance";
			}
			else if (newintensity <= 20) message = "The sky clears off and the sun shines again";
			else if (newintensity > 70)
			{	//snow check
				r = rand()%100;
				if (r < snow) snow = true;
			}
			break;
		case wtStormCloud:	// intensity 41 - 70
			//from this weather type, we can reach every other, since from here it can start raining with any intensity. Or it can snow or even clear up
			if (newintensity <= 40 && newintensity > 20) message = "The sky begins to clear off";
			else if (newintensity <= 20) message = "Strong winds clear away the thick clouds, until the sun shines again";
			else if (newintensity > 70)
			{	//snow check
				r = rand()%100;
				if (r < snow) snow = true;
			}
			break;
		case wtLightRain:	// intensity 71 - 90
			if (newintensity < 71)
			{
				if (newintensity > 20) message = "The rain is stopping";
				else message = "The rain is stopping and the sky clears up";
			}
			else message = "The rain gets stronger";
			r = rand()%100;
			if (climate == clArtic && r < (snow/4)) snow = true;	//If artic climate and raining, check if rain becomes snow (at 1/4 of normal snow chance)
			break;
		case wtMediumRain:	// intensity 91 - 110
			if (newintensity <71)
			{
				if (newintensity > 40) message = "The rain is stopping";
				else
				{
					newintensity = 41;
					message = "The rain is stopping and the sky begins to clear up";
				}
			}
			else message = "The rain gets stronger";
			r = rand()%100;
			if (climate == clArtic && r < (snow/4)) snow = true;	//If artic climate and raining, check if rain becomes snow (at 1/4 of normal snow chance)
			break;
		case wtHeavyRain:	// intensity 111 - 140
			if (newintensity <111)
			{
				if (newintensity > 70) message = "The rain begins to slow down";
				else
				{
					newintensity = 71;
					message = "The rain has stopped falling, but the sky is still covered up";
				}
			}
			else message = "The rain gets stronger";
			r = rand()%100;
			if (climate == clArtic && r < (snow/4)) snow = true;	//If artic climate and raining, check if rain becomes snow (at 1/4 of normal snow chance)
			break;
		case wtLightSnow:	// intensity 71 - 90
			if (newintensity < 71)
			{
				if (newintensity > 20) message = "The snow is stopping";
				else message = "The snow is stopping and the sky clears up";
			}
			else message = "The snow gets stronger";
			r = rand()%100;
			if (climate != clNormal || r > ((100 - snow)/4)) snow = true;	//If normal climate and snowing, check if snow becomes rain (at 1/4 of normal snow_to_rain chance, the complementary of snow chance)
			break;
		case wtMediumSnow:	// intensity 91 - 110
			if (newintensity <71)
			{
				if (newintensity > 40) message = "The snow is stopping";
				else
				{
					newintensity = 41;
					message = "The snow is stopping and the sky begins to clear up";
				}
			}
			else message = "The snow gets stronger";
			r = rand()%100;
			if (climate != clNormal || r > ((100 - snow)/4)) snow = true;	//If normal climate and snowing, check if snow becomes rain (at 1/4 of normal snow_to_rain chance, the complementary of snow chance)
			break;
		case wtHeavySnow:	// intensity 111 - 140
		snow = true;
		if (newintensity <111)
		{
		if (newintensity > 70) message = "The snow begins to slow down";
		else
			{
				newintensity = 71;
				message = "The snow has stopped falling, but the sky is still covered up";
			}
		}
		else message = "The snow gets stronger";
			r = rand()%100;
			if (climate != clNormal || r > ((100 - snow)/4)) snow = true;	//If normal climate and snowing, check if snow becomes rain (at 1/4 of normal snow_to_rain chance, the complementary of snow chance)
			break;
		}


		if (newintensity <= 20) region[cregion].weatherNew = wtSun;
		else if (newintensity <= 40) region[cregion].weatherNew = wtCloud;
		else if (newintensity <= 70) region[cregion].weatherNew = wtStormCloud;
		else if (newintensity <= 90 && !snow) region[cregion].weatherNew = wtLightRain;
		else if (newintensity <= 110 && !snow) region[cregion].weatherNew = wtMediumRain;
		else if (!snow) region[cregion].weatherNew = wtHeavyRain;
		else if (newintensity <= 90 && snow) region[cregion].weatherNew = wtLightSnow;
		else if (newintensity <= 110 && snow) region[cregion].weatherNew = wtMediumSnow;
		else region[cregion].weatherNew = wtHeavySnow;

		region[cregion].weatherIntensityNew = newintensity;

		uint8_t weather = 0;
		is (snow) weather = 0x02;		//snow effect
		if (newintensity <=70) weather = 0xff;	//No weather

		uint8_t intensity = (newintensity > 70) ? newintensity - 70 : newintensity;
		uint8_t intensity2 = intensity;
		bool mixedweather = false;

		if ( ((current == wtLightRain || current == wtMediumRain || current == wtHeavyRain) && snow) ||	   	// Rain has just become snow or...
		     ((current == wtLightSnow || current == wtMediumSnow || current == wtHeavySnow) && !snow))		// Snow has just become rain
		{
			intensity = rand() % intensity; 	// randomize % of snow ...
			intensity2 -= intensity;		// ...and the remaining intensity goes to rain
			weather = 0x2;  	// snow
			weather2 = 0x0; 	// rain
			mixedweather = true;
		}
		//! \todo the limit of light level by weather (it is best to modify existing code in timers.cpp)

		nPackets::Sent::Weather pk( weather, intensity);
		nPackets::Sent::Weather pk2( weather2, intensity2);


		NxwSocketWrapper sw;
		sw.fillOnline( pos );		//!< \todo change with something like fillOnlineInRegion
		for( sw.rewind(); !sw.isEmpty(); sw++ )
		{
			pClient j =sw.getSocket();
			if( j )
			{
				j->sendPacket(&pk);
				if (mixedweather) j->sendPacket(&pk2);
				j->sysmessage(message);
			}
		}

	}
	// End region for cycle. Now we must build another one to update the weatherIntensity and weatherCurrent of all regions
	// if you ask why, think of what would happen if you changed them as you process them, since each region takes a little info
	// from each adiacent region.... :)  (yes, this is a system with a memory :D)

	//! \todo an online iteration of all online chars in region
	//for (whatever will cycle all regions)
	{
		region[cregion].weatherCurrent = region[cregion].weatherNew;
		region[cregion].weatherIntensity = region[cregion].weatherIntensityNew;
	}

	outPlain("[ OK ]\n");

}