/*---------------------------------------------------------------------------*/
static void
ct_callback(void *ptr)
{
  uint32_t wind_speed;
  int16_t wind_dir;
  int16_t wind_dir_delta;

  /* Disable to make the calculations in an interrupt-safe context */
  GPIO_DISABLE_INTERRUPT(ANEMOMETER_SENSOR_PORT_BASE,
                         ANEMOMETER_SENSOR_PIN_MASK);
  wind_speed = weather_sensors.anemometer.ticks;
  wind_speed *= WEATHER_METER_ANEMOMETER_SPEED_1S;
  weather_sensors.anemometer.value = (uint16_t)wind_speed;
  anemometer.ticks_avg++;
  anemometer.value_avg += weather_sensors.anemometer.value;
  anemometer.value_buf_xm += weather_sensors.anemometer.value;

  /* Take maximum value */
  if(weather_sensors.anemometer.value > anemometer.value_max) {
    anemometer.value_max = weather_sensors.anemometer.value;
  }

  /* Mitsuta method to get the wind direction average */
  wind_dir = weather_meter_get_wind_dir();
  wind_dir_delta = wind_dir - wind_vane.value_prev;

  if(wind_dir_delta < -1800) {
    wind_vane.value_prev += wind_dir_delta + 3600;
  } else if(wind_dir_delta > 1800) {
    wind_vane.value_prev += wind_dir_delta - 3600;
  } else {
    wind_vane.value_prev += wind_dir_delta;
  }

  wind_vane.value_buf_xm += wind_vane.value_prev;

  /* Calculate the 2 minute average */
  if(!(anemometer.ticks_avg % WEATHER_METER_AVG_PERIOD)) {
    PRINTF("\nWeather: calculate the %u averages ***\n", WEATHER_METER_AVG_PERIOD);

    if(anemometer.value_buf_xm) {
      anemometer.value_avg_xm = anemometer.value_buf_xm / WEATHER_METER_AVG_PERIOD;
      anemometer.value_buf_xm = 0;
    } else {
      anemometer.value_avg_xm = 0;
    }

    if(wind_vane.value_buf_xm >= 0) {
      wind_vane.value_buf_xm = wind_vane.value_buf_xm / WEATHER_METER_AVG_PERIOD;
      wind_vane.value_avg_xm = wind_vane.value_buf_xm;
    } else {
      wind_vane.value_buf_xm = ABS(wind_vane.value_buf_xm) / WEATHER_METER_AVG_PERIOD;
      wind_vane.value_avg_xm = wind_vane.value_buf_xm;
      wind_vane.value_avg_xm = ~wind_vane.value_avg_xm + 1;
    }

    if(wind_vane.value_avg_xm >= 3600) {
      wind_vane.value_avg_xm -= 3600;
    } else if(wind_vane.value_avg_xm < 0) {
      wind_vane.value_avg_xm += 3600;
    }

    wind_vane.value_buf_xm = 0;
    wind_vane.value_prev = wind_dir;
  }

  /* Check for roll-over */
  if(!anemometer.ticks_avg) {
    anemometer.value_avg = 0;
  }

  weather_sensors.anemometer.ticks = 0;

  /* Enable the interrupt again */
  GPIO_ENABLE_INTERRUPT(ANEMOMETER_SENSOR_PORT_BASE,
                        ANEMOMETER_SENSOR_PIN_MASK);

  ctimer_set(&ct, CLOCK_SECOND, ct_callback, NULL);
}