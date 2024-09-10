void CubeFace::GetFaceCoordinates(unsigned char nFace, const VK::ivec3 &v, int &x, int &y)
{
	// The vector passed in may not be in the specified face.
	// If not, the coordinates within nFace closest to v are returned.
	// (This helps find the shortest distance from a point to a node in the quad-tree)
	switch(nFace) {
		case RightFace:
			if(v.x < 0) { // If v is in the left, force the coordinates to the nearest corner of this face.
				x = v.z > 0 ? -MaxCoord : MaxCoord;
				y = v.y > 0 ? -MaxCoord : MaxCoord;
			} else {
				x = v.x <= VK::Math::Abs(v.z) ? (v.z > 0 ? -MaxCoord : MaxCoord) : muldiv(-v.z, MaxCoord, v.x);
				y = v.x <= VK::Math::Abs(v.y) ? (v.y > 0 ? -MaxCoord : MaxCoord) : muldiv(-v.y, MaxCoord, v.x);
			}
			break;
		case LeftFace:
			if(v.x > 0) { // If v is in the right, force the coordinates to the nearest corner of this face.
				x = v.z > 0 ? MaxCoord : -MaxCoord;
				y = v.y > 0 ? -MaxCoord : MaxCoord;
			} else {
				x = -v.x <= VK::Math::Abs(v.z) ? (v.z > 0 ? MaxCoord : -MaxCoord) : muldiv(v.z, MaxCoord, -v.x);
				y = -v.x <= VK::Math::Abs(v.y) ? (v.y > 0 ? -MaxCoord : MaxCoord) : muldiv(-v.y, MaxCoord, -v.x);
			}
			break;
		case TopFace:
			if(v.y < 0) { // If v is in the bottom, force the coordinates to the nearest corner of this face.
				x = v.x > 0 ? MaxCoord : -MaxCoord;
				y = v.z > 0 ? MaxCoord : -MaxCoord;
			} else {
				x = v.y <= VK::Math::Abs(v.x) ? (v.x > 0 ? MaxCoord : -MaxCoord) : muldiv(v.x, MaxCoord, v.y);
				y = v.y <= VK::Math::Abs(v.z) ? (v.z > 0 ? MaxCoord : -MaxCoord) : muldiv(v.z, MaxCoord, v.y);
			}
			break;
		case BottomFace:
			if(v.y > 0) { // If v is in the top, force the coordinates to the nearest corner of this face.
				x = v.x > 0 ? MaxCoord : -MaxCoord;
				y = v.z > 0 ? -MaxCoord : MaxCoord;
			} else {
				x = -v.y <= VK::Math::Abs(v.x) ? (v.x > 0 ? MaxCoord : -MaxCoord) : muldiv(v.x, MaxCoord, -v.y);
				y = -v.y <= VK::Math::Abs(v.z) ? (v.z > 0 ? -MaxCoord : MaxCoord) : muldiv(-v.z, MaxCoord, -v.y);
			}
			break;
		case FrontFace:
			if(v.z < 0) { // If v is in the back, force the coordinates to the nearest corner of this face.
				x = v.x > 0 ? MaxCoord : -MaxCoord;
				y = v.y > 0 ? -MaxCoord : MaxCoord;
			} else {
				x = v.z <= VK::Math::Abs(v.x) ? (v.x > 0 ? MaxCoord : -MaxCoord) : muldiv(v.x, MaxCoord, v.z);
				y = v.z <= VK::Math::Abs(v.y) ? (v.y > 0 ? -MaxCoord : MaxCoord) : muldiv(-v.y, MaxCoord, v.z);
			}
			break;
		case BackFace:
			if(v.z > 0) { // If v is in the front, force the coordinates to the nearest corner of this face.
				x = v.x > 0 ? -MaxCoord : MaxCoord;
				y = v.y > 0 ? -MaxCoord : MaxCoord;
			} else {
				x = -v.z <= VK::Math::Abs(v.x) ? (v.x > 0 ? -MaxCoord : MaxCoord) : muldiv(-v.x, MaxCoord, -v.z);
				y = -v.z <= VK::Math::Abs(v.y) ? (v.y > 0 ? -MaxCoord : MaxCoord) : muldiv(-v.y, MaxCoord, -v.z);
			}
			break;
	}

	x = (x + MaxCoord) >> 1;
	y = (y + MaxCoord) >> 1;
}