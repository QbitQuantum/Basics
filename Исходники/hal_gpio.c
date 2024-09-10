/**************************************************************************************************
 * @fn      HalGpioSrdyInit
 *
 *
 * @brief   Initialise SRDY GPIO.
 *
 * @param   gpioCfg - SRDY pin configuration parameters
 *
 * @return  STATUS
 **************************************************************************************************/
int HalGpioSrdyInit(halGpioCfg_t *gpioCfg)
{
	memcpy(srdyGpioCfg.gpio.value,
			gpioCfg->gpio.value,
			strlen(gpioCfg->gpio.value));
	if (__BIG_DEBUG_ACTIVE == TRUE)
	{
		time_printf("[%s] srdyGpioCfg.gpio.value = '%s'\n", __FUNCTION__, srdyGpioCfg.gpio.value);
	}
	memcpy(srdyGpioCfg.gpio.direction,
			gpioCfg->gpio.direction,
			strlen(gpioCfg->gpio.direction));
	if (__BIG_DEBUG_ACTIVE == TRUE)
	{
		time_printf("[%s] srdyGpioCfg.gpio.direction = '%s'\n", __FUNCTION__, srdyGpioCfg.gpio.direction);
	}

	srdyGpioCfg.gpio.active_high_low = gpioCfg->gpio.active_high_low;

	memcpy(srdyGpioCfg.gpio.edge,
			gpioCfg->gpio.edge,
			strlen(gpioCfg->gpio.edge));
	if (__BIG_DEBUG_ACTIVE == TRUE)
	{
		time_printf("[%s] srdyGpioCfg.gpio.edge = '%s'\n", __FUNCTION__, srdyGpioCfg.gpio.edge);
	}

	if ( ( gpioCfg->levelshifter.value) &&
			( gpioCfg->levelshifter.active_high_low) &&
			( gpioCfg->levelshifter.direction))
	{
		memcpy(srdyGpioCfg.levelshifter.value,
				gpioCfg->levelshifter.value,
				strlen(gpioCfg->levelshifter.value));
		if (__BIG_DEBUG_ACTIVE == TRUE)
		{
			time_printf("[%s] srdyGpioCfg.levelshifter.value = '%s'\n", __FUNCTION__, srdyGpioCfg.levelshifter.value);
		}
		memcpy(srdyGpioCfg.levelshifter.direction,
				gpioCfg->levelshifter.direction,
				strlen(gpioCfg->levelshifter.direction));
		srdyGpioCfg.levelshifter.active_high_low = gpioCfg->levelshifter.active_high_low;
		if (__BIG_DEBUG_ACTIVE == TRUE)
		{
			time_printf("[%s] srdyGpioCfg.levelshifter.direction = '%s'\n", __FUNCTION__, srdyGpioCfg.levelshifter.direction);
		}

		//open the GPIO DIR file for the level shifter direction signal
		gpioSrdyFd = open(srdyGpioCfg.levelshifter.direction, O_RDWR);
		if(gpioSrdyFd == 0)
		{
			perror(srdyGpioCfg.levelshifter.direction);
			if (__BIG_DEBUG_ACTIVE == TRUE)
			{
				time_printf("[%s] %s open failed\n", __FUNCTION__, srdyGpioCfg.levelshifter.direction);
			}
			npi_ipc_errno = NPI_LNX_ERROR_HAL_GPIO_SRDY_LVLSHFT_DIR_OPEN;
			return NPI_LNX_FAILURE;
		}

		//Set the direction of the GPIO to output
		if (ERROR == write(gpioSrdyFd, "out", 3))
		{
			perror(srdyGpioCfg.levelshifter.direction);
			if (__BIG_DEBUG_ACTIVE == TRUE)
			{
				time_printf("[%s] can't write in %s \n", __FUNCTION__, srdyGpioCfg.levelshifter.direction);
			}
			npi_ipc_errno = NPI_LNX_ERROR_HAL_GPIO_SRDY_LVLSHFT_DIR_WRITE;
			return NPI_LNX_FAILURE;
		}
		//close the DIR file
		close(gpioSrdyFd);

		//open the GPIO VALUE file for the level shifter direction signal
		gpioSrdyFd = open(srdyGpioCfg.levelshifter.value, O_RDWR);
		if(gpioSrdyFd == 0)
		{
			perror(srdyGpioCfg.levelshifter.value);
			if (__BIG_DEBUG_ACTIVE == TRUE)
			{
				time_printf("[%s] %s open failed\n", __FUNCTION__, srdyGpioCfg.levelshifter.value);
			}
			npi_ipc_errno = NPI_LNX_ERROR_HAL_GPIO_SRDY_LVLSHFT_VAL_OPEN;
			return NPI_LNX_FAILURE;
		}

		//Set the value of the GPIO to 0 (level shifter direction from CC2531 to Host)

		if (ERROR == write(gpioSrdyFd, "0", 1))
		{
			perror(srdyGpioCfg.levelshifter.value);
			if (__BIG_DEBUG_ACTIVE == TRUE)
			{
				time_printf("[%s] can't write in %s\n", __FUNCTION__, srdyGpioCfg.levelshifter.value);
			}
			npi_ipc_errno = NPI_LNX_ERROR_HAL_GPIO_SRDY_LVLSHFT_VAL_WRITE;
			return NPI_LNX_FAILURE;
		}
		//close the DIR file
		close(gpioSrdyFd);
	}
	else
	{
		if (__BIG_DEBUG_ACTIVE == TRUE)
		{
			LOG_ALWAYS("[%s] Wrong Configuration File, one of the  following Key value are missing for SRDY.Level Shifter definition: '\n", __FUNCTION__);
			LOG_ALWAYS("value: \t\t%s\n", srdyGpioCfg.gpio.value);
			LOG_ALWAYS("direction: \t%s\n", srdyGpioCfg.gpio.direction);
			LOG_ALWAYS("active_high_low: %d\n", srdyGpioCfg.gpio.active_high_low);
			LOG_ALWAYS("Level Shifter is optional, please check if you need it or not before continuing...\n");
		}
	}
	//TODO: Lock the shift register GPIO.

	//open the SRDY GPIO DIR file
	gpioSrdyFd = open(srdyGpioCfg.gpio.direction, O_RDWR);
	if(gpioSrdyFd == 0)
	{
		perror(srdyGpioCfg.gpio.direction);
		if (__BIG_DEBUG_ACTIVE == TRUE)
		{
			time_printf("[%s] %s open failed\n", __FUNCTION__, srdyGpioCfg.gpio.direction);
		}
		npi_ipc_errno = NPI_LNX_ERROR_HAL_GPIO_SRDY_GPIO_DIR_OPEN;
		return NPI_LNX_FAILURE;
	}

	//Set SRDY GPIO as input
	if(ERROR == write(gpioSrdyFd, "in", 2))
	{
		perror(srdyGpioCfg.levelshifter.direction);
		if (__BIG_DEBUG_ACTIVE == TRUE)
		{
			time_printf("[%s] can't write in %s\n", __FUNCTION__, srdyGpioCfg.gpio.direction);
		}
		npi_ipc_errno = NPI_LNX_ERROR_HAL_GPIO_SRDY_GPIO_DIR_WRITE;
		return NPI_LNX_FAILURE;
	}
	//close SRDY DIR file
	close(gpioSrdyFd);

	//open the SRDY GPIO Edge file
	gpioSrdyFd = open(srdyGpioCfg.gpio.edge, O_RDWR);
	if(gpioSrdyFd == 0)
	{
		perror(srdyGpioCfg.gpio.edge);
		if (__BIG_DEBUG_ACTIVE == TRUE)
		{
			time_printf("[%s] %s open failed\n", __FUNCTION__, srdyGpioCfg.gpio.edge);
		}
		npi_ipc_errno = NPI_LNX_ERROR_HAL_GPIO_SRDY_GPIO_EDGE_OPEN;
		return NPI_LNX_FAILURE;
	}

	//Set SRDY GPIO edge detection for both rising and falling
	if(ERROR == write(gpioSrdyFd, "both", 4))
	{
		perror(srdyGpioCfg.levelshifter.edge);
		if (__BIG_DEBUG_ACTIVE == TRUE)
		{
			time_printf("[%s] can't write in %s\n", __FUNCTION__, srdyGpioCfg.gpio.edge);
		}
		npi_ipc_errno = NPI_LNX_ERROR_HAL_GPIO_SRDY_GPIO_EDGE_WRITE;
		return NPI_LNX_FAILURE;
	}
	//close SRDY edge file
	close(gpioSrdyFd);

	//open the SRDY GPIO VALUE file so it can be written to using the file handle later
	gpioSrdyFd = open(srdyGpioCfg.gpio.value, O_RDWR| O_NONBLOCK);
	if(gpioSrdyFd == 0)
	{
		perror(srdyGpioCfg.gpio.value);
		if (__BIG_DEBUG_ACTIVE == TRUE)
		{
			time_printf("[%s] %s open failed\n", __FUNCTION__, srdyGpioCfg.gpio.value);
		}
		npi_ipc_errno = NPI_LNX_ERROR_HAL_GPIO_SRDY_GPIO_VAL_OPEN;
		return NPI_LNX_FAILURE;
	}

	return(gpioSrdyFd);
}