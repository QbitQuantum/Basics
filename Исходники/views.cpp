#include <iostream>

TEST_CASE("views")
{
    aam::MatrixX shapes(2, 4);
    shapes << 1, 2, 3, 4, 
              5, 6, 7, 8;

    aam::MatrixX shapesSeparated(2, 4);
    shapesSeparated << 1, 2, 5, 6,
                       3, 4, 7, 8;

    REQUIRE(shapesSeparated.block(0, 0, 2, 2).isApprox(aam::toSeparatedView<aam::Scalar>(shapes.row(0))));
    REQUIRE(shapesSeparated.block(0, 2, 2, 2).isApprox(aam::toSeparatedView<aam::Scalar>(shapes.row(1))));

    // Test with affine transforms
    Eigen::Transform<aam::Scalar, 2, Eigen::AffineCompact> t;
    t = Eigen::Translation<aam::Scalar, 2>(0.5, 0.5) * Eigen::Scaling(aam::Scalar(2));
    
    auto x = aam::toSeparatedView<aam::Scalar>(shapes.row(0)).rowwise().homogeneous();
    aam::MatrixX r = x * t.matrix().transpose();
    
    aam::MatrixX shouldBe(2, 2);
    shouldBe << 2.5, 4.5, 6.5, 8.5;

    REQUIRE(r.isApprox(shouldBe));

    aam::MatrixX shouldBeArray(1, 4);
    shouldBeArray << 2.5, 4.5, 6.5, 8.5;
    REQUIRE(aam::toInterleavedView<aam::Scalar>(r).isApprox(shouldBeArray));
}