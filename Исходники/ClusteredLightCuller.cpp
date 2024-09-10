__forceinline int ClusteredLightCuller::_sphereOverlapsFroxel(int x, int y, int z, float sphere_radius, const vec3& sphere_center, const FroxelInfo* froxel_infos)
{
   __m128* center_coord = (__m128*)&froxel_infos[_toFlatFroxelIndex(x, y, z)].center_coord;
   __m128 sse_sphere_center = _mm_set_ps(1.0, sphere_center.z, sphere_center.y, sphere_center.x);
   __m128 sse_plane_normal = _normalize(_mm_sub_ps(*center_coord, sse_sphere_center));

   __m128 plane_origin = _mm_add_ps(sse_sphere_center, _mm_mul_ps(_mm_set1_ps(sphere_radius), sse_plane_normal));
   __m128 sse_dot_plane = _mm_dp_ps(plane_origin, sse_plane_normal, 0x70 | 0xF);

   __m128* corner_a = (__m128*)&froxel_infos[_toFlatFroxelIndex(x + 0, y + 0, z + 0)].corner_coord;
   __m128* corner_b = (__m128*)&froxel_infos[_toFlatFroxelIndex(x + 1, y + 0, z + 0)].corner_coord;
   __m128* corner_c = (__m128*)&froxel_infos[_toFlatFroxelIndex(x + 1, y + 1, z + 0)].corner_coord;
   __m128* corner_d = (__m128*)&froxel_infos[_toFlatFroxelIndex(x + 0, y + 1, z + 0)].corner_coord;

   if (_overlap(sse_plane_normal, sse_dot_plane, corner_a, corner_b, corner_c, corner_d))
      return 1;

   corner_a = (__m128*)&froxel_infos[_toFlatFroxelIndex(x + 0, y + 0, z + 1)].corner_coord;
   corner_b = (__m128*)&froxel_infos[_toFlatFroxelIndex(x + 1, y + 0, z + 1)].corner_coord;
   corner_c = (__m128*)& froxel_infos[_toFlatFroxelIndex(x + 1, y + 1, z + 1)].corner_coord;
   corner_d = (__m128*)& froxel_infos[_toFlatFroxelIndex(x + 0, y + 1, z + 1)].corner_coord;

   return (_overlap(sse_plane_normal, sse_dot_plane, corner_a, corner_b, corner_c, corner_d));
}