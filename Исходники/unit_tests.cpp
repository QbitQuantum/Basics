#include "easypng.h"
#include "proxy.h"
#include "quadtree.h"

using namespace std;
using namespace util;

#if MP_PART(1)

// test constructor, decompress
UNIT_TEST(test_outHalf, 5, 2, 1000)
{
	PNG imgIn("in.png");

	Quadtree halfTree(imgIn, 128);
	PNG imgOut = halfTree.decompress();

	PNG imgSoln("soln_outHalf.png");
	ASSERT(imgOut == imgSoln);
	PASS;
}

#endif

#if MP_PART(2)

UNIT_TEST(test_pruneSize, 0, 1, 1000)
{
	PNG imgIn("in.png");
	Quadtree fullTree;
	fullTree.buildTree(imgIn, 256);