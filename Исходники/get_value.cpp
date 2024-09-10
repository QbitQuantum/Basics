bool			bunny_configuration_get_double(const t_bunny_configuration *config,
						       double			*val)
{
  SmallConf		*conf = (SmallConf*)config;
  bool			ret;

  ret = conf->GetDouble(val);
  scream_log_if
    ("%p conf, %p target  -> %s (%f)", "configuration",
     config, val, ret ? "true" : "false", ret ? *val : nan(""));
  return (ret);
}