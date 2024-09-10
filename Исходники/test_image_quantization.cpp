void testOctreeWithImage(const RGBAImage& image) {
	std::set<RGBAPixel> colors;
	int r = 0, g = 0, b = 0, count = 0;

	Octree octree;

	// insert all pixels into an octree
	for (int x = 0; x < image.getWidth(); x++) {
		for (int y = 0; y < image.getHeight(); y++) {
			RGBAPixel color = image.getPixel(x, y);
			colors.insert(color);
			r += rgba_red(color);
			g += rgba_green(color);
			b += rgba_blue(color);
			count++;

			Octree::findOrCreateNode(&octree, color)->setColor(color);
		}
	}

	// make sure that all colors are inserted correctly
	BOOST_CHECK(octree.isRoot() && !octree.isLeaf());
	BOOST_CHECK(!octree.hasColor());

	// reduce all colors up to the root of the tree
	// the color should be the overall average color
	traverseReduceOctree(&octree);
	BOOST_CHECK(octree.hasColor());

	RGBAPixel average1 = octree.getColor();
	RGBAPixel average2 = rgba(r / count, g / count, b / count, 255);
	BOOST_CHECK_EQUAL(average1, average2);

	BOOST_TEST_MESSAGE("Overall colors: " << colors.size());
	BOOST_TEST_MESSAGE("Pixels per color: " << (double) (image.getWidth() * image.getHeight()) / colors.size());
	BOOST_TEST_MESSAGE("Average color: " << (int) rgba_red(average1) << ","
			<< (int) rgba_green(average1) << "," << (int) rgba_blue(average1));
}