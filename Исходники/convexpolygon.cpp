ConvexPolygon ConvexPolygon::intersect(const ConvexPolygon& poly) const
{
	ConvexPolygon result;

	int a = 0;
	int b = 0;

	int aa = 0;
	int ba = 0;

	enum State {IN_A, IN_B, UNKNOWN};
	State state = UNKNOWN;

	bool firstPoint = true;

	do {
		const int a1 = (a + m_vertices.size() - 1) % m_vertices.size();
		const int b1 = (b + poly.vertices().size() - 1) % poly.vertices().size();

		const cv::Point2f vecA = m_vertices[a] - m_vertices[a1];
		const cv::Point2f vecB = poly.vertices()[b] - poly.vertices()[b1];

		const float cross = signedArea2(cv::Point2f(0, 0), vecA, vecB);
		const float aHB = signedArea2(poly.vertices()[b1], poly.vertices()[b], m_vertices[a]);
		const float bHA = signedArea2(m_vertices[a1], m_vertices[a], poly.vertices()[b]);

		//std::cout << "cross=" << cross << ", aHB=" << aHB << ", bHA=" << bHA << std::endl;

		std::vector<cv::Point2f> intersectionPoints;
		LineSegment::IntersectResult intersectResult = LineSegment(m_vertices[a1], m_vertices[a]).intersect(LineSegment(poly.vertices()[b1], poly.vertices()[b]), intersectionPoints);

		if (intersectResult == LineSegment::INTERESECTING) {
			if (firstPoint && state == UNKNOWN) {
				aa = 0;
				ba = 0;
				firstPoint = false;
			}

			if (aHB > 0) {
				state = IN_A;
			} else if (bHA > 0) {
				state = IN_B;
			}

			assert(intersectionPoints.size() > 0);
			result.addPoint(intersectionPoints[0]);
		}

		if ((intersectResult == LineSegment::COINCIDENT) && (intersectionPoints.size() > 0) && (vecA.dot(vecB) < 0)) {
			result = ConvexPolygon(intersectionPoints);
			return result;
		}

		if ((std::abs(cross) <= std::numeric_limits<float>::epsilon()) && (std::abs(aHB) <= std::numeric_limits<float>::epsilon()) && (std::abs(bHA) <= std::numeric_limits<float>::epsilon())) {
			if (state == IN_A) {
				ba++;
				b = (b + 1) % poly.vertices().size();
			} else {
				aa++;
				a = (a + 1) % m_vertices.size();
			}
		} else if ((std::abs(cross) <= std::numeric_limits<float>::epsilon()) && (aHB < 0) && (bHA < 0)) {
			std::cout << "III" << std::endl;
			result.clear();
			return result;
		} else if (cross >= 0) {
			if (bHA > 0) {
				if (state == IN_A) {
					result.addPoint(m_vertices[a]);
				}
				aa++;
				a = (a + 1) % m_vertices.size();
			} else {
				if (state == IN_B) {
					result.addPoint(poly.vertices()[b]);
				}
				ba++;
				b = (b + 1) % poly.vertices().size();
			}
		} else {
			if (aHB > 0) {
				if (state == IN_B) {
					result.addPoint(poly.vertices()[b]);
				}
				ba++;
				b = (b + 1) % poly.vertices().size();
			} else {
				if (state == IN_A) {
					result.addPoint(m_vertices[a]);
				}
				aa++;
				a = (a + 1) % m_vertices.size();
			}
		}

		//std::cout << "a=" << a << ", b=" << b << ", aa=" << aa << ", ba=" << ba << ", state=" << state << std::endl;
	} while (((aa < (int)m_vertices.size()) || (ba < (int)poly.vertices().size())) && (aa < 2 * (int)m_vertices.size()) && (ba < 2 * (int)poly.vertices().size()));

	return result;
}