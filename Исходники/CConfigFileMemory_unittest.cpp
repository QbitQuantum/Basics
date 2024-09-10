TEST(CConfigFileMemory, parseVariables)
{
#ifdef _MSC_VER
	_putenv_s("ENV_VAR_MULTIPLIER", "2");
#else
	::setenv("ENV_VAR_MULTIPLIER", "2", 1);
#endif

	const std::string sampleCfgTxt2 =
		"@define MAXSPEED 10\n"
		"@define  MAXOMEGA  -30  \n"
		"[test]\n"
		"var1=5\n"
		"var2=${MAXSPEED}\n"
		"var3=${MAXOMEGA}\n"
		"var4=$eval{5*MAXSPEED+MAXOMEGA}\n"
		"var5 = $eval{ MAXSPEED - MAXOMEGA } \n"
		"var6=$env{ENV_VAR_MULTIPLIER}\n"
		"varstr1=MAXSPEED\n";
	;
	mrpt::config::CConfigFileMemory cfg;
	cfg.setContent(sampleCfgTxt2);

	EXPECT_EQ(cfg.read_int("test", "var1", 0), 5);
	EXPECT_EQ(cfg.read_int("test", "var2", 0), 10);
	EXPECT_EQ(cfg.read_int("test", "var3", 0), -30);
	EXPECT_NEAR(cfg.read_double("test", "var4", .0), 20.0, 1e-6);
	EXPECT_NEAR(cfg.read_double("test", "var5", .0), 40.0, 1e-6);
	EXPECT_NEAR(cfg.read_double("test", "var6", .0), 2.0, 1e-6);
	EXPECT_EQ(cfg.read_string("test", "varstr1", ""), std::string("MAXSPEED"));
}