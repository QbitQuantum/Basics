TEST(GraphicsPathTest, svg) {
	GraphicsPath<int> path;
	path.moveto(0,0);
	path.lineto(10,10);
	path.cubicto(20,20,30,30,40,40);
	path.closepath();
	EXPECT_FALSE(path.empty());
	EXPECT_EQ(path.size(), 4);
	ostringstream oss;
	path.writeSVG(oss, false);
	EXPECT_EQ(oss.str(), "M0 0L10 10C20 20 30 30 40 40Z");
	path.clear();
	EXPECT_TRUE(path.empty());
}