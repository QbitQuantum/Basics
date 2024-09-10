static config_err_t
_decode_value_raw (ipmi_sensors_config_state_data_t *state_data,
                   const char *threshold_input,
                   uint8_t *threshold_raw)
{
  int8_t r_exponent, b_exponent;
  int16_t m, b;
  uint8_t linearization, analog_data_format;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  config_err_t ret;
  double threshold_value;
  char *ptr;

  assert (state_data);
  assert (threshold_input);
  assert (threshold_raw);

  if ((ret = _get_sdr_decoding_data (state_data,
                                     &r_exponent,
                                     &b_exponent,
                                     &m,
                                     &b,
                                     &linearization,
                                     &analog_data_format)) != CONFIG_ERR_SUCCESS)
    {
      rv = ret;
      goto cleanup;
    }

  errno = 0;
  threshold_value = strtod (threshold_input, &ptr);
  if (errno
      || ptr[0] != '\0')
    {
      pstdout_fprintf (state_data->pstate,
		       stderr,
		       "Invalid input: %s\n",
		       threshold_input);
      /* fatal error, should have been validated earlier */
      goto cleanup;
    }

  if (ipmi_sensor_decode_raw_value (r_exponent,
                                    b_exponent,
                                    m,
                                    b,
                                    linearization,
                                    analog_data_format,
                                    threshold_value,
                                    threshold_raw) < 0)
    {
      pstdout_fprintf (state_data->pstate,
		       stderr,
		       "ipmi_sensor_decode_raw_value: %s\n",
		       strerror (errno));
      goto cleanup;
    }

  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  return (rv);
}