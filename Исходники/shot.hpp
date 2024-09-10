//////////////////////////////////////////////////////////////////////////////////////////////
// Quadrilinear interpolation; used when color and shape descriptions are NOT activated simultaneously
template <typename PointInT, typename PointNT, typename PointOutT> void
pcl::SHOTEstimationBase<PointInT, PointNT, PointOutT>::interpolateSingleChannel (
    const pcl::PointCloud<PointInT> &cloud,
    const std::vector<int> &indices,
    const std::vector<float> &dists,
    const Eigen::Vector4f &central_point,
    const std::vector<Eigen::Vector4f, Eigen::aligned_allocator<Eigen::Vector4f> > &rf,
    std::vector<double> &binDistance,
    const int nr_bins,
    Eigen::VectorXf &shot)
{
  if (rf.size () != 3)
  {
    PCL_ERROR ("[pcl::%s::interpolateSingleChannel] RF size different than 9! Aborting...\n");
    return;
  }

  for (size_t i_idx = 0; i_idx < indices.size (); ++i_idx)
  {
    Eigen::Vector4f delta = cloud.points[indices[i_idx]].getVector4fMap () - central_point;

    // Compute the Euclidean norm
    double distance_sqr = dists[i_idx]; //delta.squaredNorm ();

    if (areEquals (distance_sqr, 0.0))
      continue;

    double xInFeatRef = delta.dot (rf[0]); //(x * feat[i].rf[0] + y * feat[i].rf[1] + z * feat[i].rf[2]);
    double yInFeatRef = delta.dot (rf[1]); //(x * feat[i].rf[3] + y * feat[i].rf[4] + z * feat[i].rf[5]);
    double zInFeatRef = delta.dot (rf[2]); //(x * feat[i].rf[6] + y * feat[i].rf[7] + z * feat[i].rf[8]);

    // To avoid numerical problems afterwards
    if (fabs (yInFeatRef) < 1E-30)
      yInFeatRef  = 0;
    if (fabs (xInFeatRef) < 1E-30)
      xInFeatRef  = 0;
    if (fabs (zInFeatRef) < 1E-30)
      zInFeatRef  = 0;


    unsigned char bit4 = ((yInFeatRef > 0) || ((yInFeatRef == 0.0) && (xInFeatRef < 0))) ? 1 : 0;
    unsigned char bit3 = ((xInFeatRef > 0) || ((xInFeatRef == 0.0) && (yInFeatRef > 0))) ? !bit4 : bit4;

    assert (bit3 == 0 || bit3 == 1);

    int desc_index = (bit4<<3) + (bit3<<2);

    desc_index = desc_index << 1;

    if ((xInFeatRef * yInFeatRef > 0) || (xInFeatRef == 0.0))
      desc_index += (fabs (xInFeatRef) >= fabs (yInFeatRef)) ? 0 : 4;
    else
      desc_index += (fabs (xInFeatRef) > fabs (yInFeatRef)) ? 4 : 0;

    desc_index += zInFeatRef > 0 ? 1 : 0;

    // 2 RADII
    desc_index += (distance_sqr > sqradius4_) ? 2 : 0;

    int step_index = static_cast<int>(floor (binDistance[i_idx] +0.5));
    int volume_index = desc_index * (nr_bins+1);

    //Interpolation on the cosine (adjacent bins in the histogram)
    binDistance[i_idx] -= step_index;
    double intWeight = (1- fabs (binDistance[i_idx]));

    if (binDistance[i_idx] > 0)
      shot[volume_index + ((step_index+1) % nr_bins)] += binDistance[i_idx];
    else
      shot[volume_index + ((step_index - 1 + nr_bins) % nr_bins)] += - binDistance[i_idx];

    //Interpolation on the distance (adjacent husks)
    double distance = sqrt (dists[i_idx]); //sqrt(distance_sqr);

    if (distance > radius1_2_)   //external sphere
    {
      double radiusDistance = (distance - radius3_4_) / radius1_2_;

      if (distance > radius3_4_) //most external sector, votes only for itself
        intWeight += 1 - radiusDistance;  //peso=1-d
      else  //3/4 of radius, votes also for the internal sphere
      {
        intWeight += 1 + radiusDistance;
        shot[(desc_index - 2) * (nr_bins+1) + step_index] -= radiusDistance;
      }
    }
    else    //internal sphere
    {
      double radiusDistance = (distance - radius1_4_) / radius1_2_;

      if (distance < radius1_4_) //most internal sector, votes only for itself
        intWeight += 1 + radiusDistance;  //weight=1-d
      else  //3/4 of radius, votes also for the external sphere
      {
        intWeight += 1 - radiusDistance;
        shot[(desc_index + 2) * (nr_bins+1) + step_index] += radiusDistance;
      }
    }

    //Interpolation on the inclination (adjacent vertical volumes)
    double inclinationCos = zInFeatRef / distance;
    if (inclinationCos < - 1.0)
      inclinationCos = - 1.0;
    if (inclinationCos > 1.0)
      inclinationCos = 1.0;

    double inclination = acos (inclinationCos);

    assert (inclination >= 0.0 && inclination <= PST_RAD_180);

    if (inclination > PST_RAD_90 || (fabs (inclination - PST_RAD_90) < 1e-30 && zInFeatRef <= 0))
    {
      double inclinationDistance = (inclination - PST_RAD_135) / PST_RAD_90;
      if (inclination > PST_RAD_135)
        intWeight += 1 - inclinationDistance;
      else
      {
        intWeight += 1 + inclinationDistance;
        assert ((desc_index + 1) * (nr_bins+1) + step_index >= 0 && (desc_index + 1) * (nr_bins+1) + step_index < descLength_);
        shot[(desc_index + 1) * (nr_bins+1) + step_index] -= inclinationDistance;
      }
    }
    else
    {
      double inclinationDistance = (inclination - PST_RAD_45) / PST_RAD_90;
      if (inclination < PST_RAD_45)
        intWeight += 1 + inclinationDistance;
      else
      {
        intWeight += 1 - inclinationDistance;
        assert ((desc_index - 1) * (nr_bins+1) + step_index >= 0 && (desc_index - 1) * (nr_bins+1) + step_index < descLength_);
        shot[(desc_index - 1) * (nr_bins+1) + step_index] += inclinationDistance;
      }
    }

    if (yInFeatRef != 0.0 || xInFeatRef != 0.0)
    {
      //Interpolation on the azimuth (adjacent horizontal volumes)
      double azimuth = atan2 (yInFeatRef, xInFeatRef);

      int sel = desc_index >> 2;
      double angularSectorSpan = PST_RAD_45;
      double angularSectorStart = - PST_RAD_PI_7_8;

      double azimuthDistance = (azimuth - (angularSectorStart + angularSectorSpan*sel)) / angularSectorSpan;

      assert ((azimuthDistance < 0.5 || areEquals (azimuthDistance, 0.5)) && (azimuthDistance > - 0.5 || areEquals (azimuthDistance, - 0.5)));

      azimuthDistance = (std::max)(- 0.5, std::min (azimuthDistance, 0.5));

      if (azimuthDistance > 0)
      {
        intWeight += 1 - azimuthDistance;
        int interp_index = (desc_index + 4) % maxAngularSectors_;
        assert (interp_index * (nr_bins+1) + step_index >= 0 && interp_index * (nr_bins+1) + step_index < descLength_);
        shot[interp_index * (nr_bins+1) + step_index] += azimuthDistance;
      }
      else
      {
        int interp_index = (desc_index - 4 + maxAngularSectors_) % maxAngularSectors_;
        assert (interp_index * (nr_bins+1) + step_index >= 0 && interp_index * (nr_bins+1) + step_index < descLength_);
        intWeight += 1 + azimuthDistance;
        shot[interp_index * (nr_bins+1) + step_index] -= azimuthDistance;
      }

    }

    assert (volume_index + step_index >= 0 &&  volume_index + step_index < descLength_);
    shot[volume_index + step_index] += intWeight;
  }