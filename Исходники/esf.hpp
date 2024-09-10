template <typename PointInT, typename PointOutT> void
pcl::ESFEstimation<PointInT, PointOutT>::computeESF (
    PointCloudIn &pc, std::vector<float> &hist)
{
  const int binsize = 64;
  unsigned int sample_size = 20000;
  srand (static_cast<unsigned int> (time (0)));
  int maxindex = static_cast<int> (pc.points.size ());

  int index1, index2, index3;
  std::vector<float> d2v, d1v, d3v, wt_d3;
  std::vector<int> wt_d2;
  d1v.reserve (sample_size);
  d2v.reserve (sample_size * 3);
  d3v.reserve (sample_size);
  wt_d2.reserve (sample_size * 3);
  wt_d3.reserve (sample_size);

  float h_in[binsize] = {0};
  float h_out[binsize] = {0};
  float h_mix[binsize] = {0};
  float h_mix_ratio[binsize] = {0};

  float h_a3_in[binsize] = {0};
  float h_a3_out[binsize] = {0};
  float h_a3_mix[binsize] = {0};
  float h_d1[binsize] = {0};

  float h_d3_in[binsize] = {0};
  float h_d3_out[binsize] = {0};
  float h_d3_mix[binsize] = {0};

  float ratio=0.0;
  float pih = static_cast<float>(M_PI) / 2.0f;
  float a,b,c,s;
  int th1,th2,th3;
  int vxlcnt = 0;
  int pcnt1,pcnt2,pcnt3;
  for (size_t nn_idx = 0; nn_idx < sample_size; ++nn_idx)
  {
    // get a new random point
    index1 = rand()%maxindex;
    index2 = rand()%maxindex;
    index3 = rand()%maxindex;

    if (index1==index2 || index1 == index3 || index2 == index3)
    {
      nn_idx--;
      continue;
    }

    Eigen::Vector4f p1 = pc.points[index1].getVector4fMap ();
    Eigen::Vector4f p2 = pc.points[index2].getVector4fMap ();
    Eigen::Vector4f p3 = pc.points[index3].getVector4fMap ();

    // A3
    Eigen::Vector4f v21 (p2 - p1);
    Eigen::Vector4f v31 (p3 - p1);
    Eigen::Vector4f v23 (p2 - p3);
    a = v21.norm (); b = v31.norm (); c = v23.norm (); s = (a+b+c) * 0.5f;
    if (s * (s-a) * (s-b) * (s-c) <= 0.001f)
      continue;

    v21.normalize ();
    v31.normalize ();
    v23.normalize ();

    //TODO: .dot gives nan's
    th1 = static_cast<int> (pcl_round (acos (fabs (v21.dot (v31))) / pih * (binsize-1)));
    th2 = static_cast<int> (pcl_round (acos (fabs (v23.dot (v31))) / pih * (binsize-1)));
    th3 = static_cast<int> (pcl_round (acos (fabs (v23.dot (v21))) / pih * (binsize-1)));
    if (th1 < 0 || th1 >= binsize)
    {
      nn_idx--;
      continue;
    }
    if (th2 < 0 || th2 >= binsize)
    {
      nn_idx--;
      continue;
    }
    if (th3 < 0 || th3 >= binsize)
    {
      nn_idx--;
      continue;
    }

    //pcl::PointXYZ cog(((rand()%100)-50.0f) / 100.0f,((rand()%100)-50.0f) / 100.0f,((rand()%100)-50.0f) / 100.0f);
    // D1
    //                      d1v.push_back( pcl::euclideanDistance(cog, pc.points[index1]) );

    // D2
    d2v.push_back (pcl::euclideanDistance (pc.points[index1], pc.points[index2]));
    d2v.push_back (pcl::euclideanDistance (pc.points[index1], pc.points[index3]));
    d2v.push_back (pcl::euclideanDistance (pc.points[index2], pc.points[index3]));

    int vxlcnt_sum = 0;
    int p_cnt = 0;
    // IN, OUT, MIXED, Ratio line tracing, index1->index2
    {
      const int xs = p1[0] < 0.0? static_cast<int>(floor(p1[0])+GRIDSIZE_H): static_cast<int>(ceil(p1[0])+GRIDSIZE_H-1);
      const int ys = p1[1] < 0.0? static_cast<int>(floor(p1[1])+GRIDSIZE_H): static_cast<int>(ceil(p1[1])+GRIDSIZE_H-1);
      const int zs = p1[2] < 0.0? static_cast<int>(floor(p1[2])+GRIDSIZE_H): static_cast<int>(ceil(p1[2])+GRIDSIZE_H-1);
      const int xt = p2[0] < 0.0? static_cast<int>(floor(p2[0])+GRIDSIZE_H): static_cast<int>(ceil(p2[0])+GRIDSIZE_H-1);
      const int yt = p2[1] < 0.0? static_cast<int>(floor(p2[1])+GRIDSIZE_H): static_cast<int>(ceil(p2[1])+GRIDSIZE_H-1);
      const int zt = p2[2] < 0.0? static_cast<int>(floor(p2[2])+GRIDSIZE_H): static_cast<int>(ceil(p2[2])+GRIDSIZE_H-1);
      wt_d2.push_back (this->lci (xs, ys, zs, xt, yt, zt, ratio, vxlcnt, pcnt1));
      if (wt_d2.back () == 2)
        h_mix_ratio[static_cast<int> (pcl_round (ratio * (binsize-1)))]++;
      vxlcnt_sum += vxlcnt;
      p_cnt += pcnt1;
    }
    // IN, OUT, MIXED, Ratio line tracing, index1->index3
    {
      const int xs = p1[0] < 0.0? static_cast<int>(floor(p1[0])+GRIDSIZE_H): static_cast<int>(ceil(p1[0])+GRIDSIZE_H-1);
      const int ys = p1[1] < 0.0? static_cast<int>(floor(p1[1])+GRIDSIZE_H): static_cast<int>(ceil(p1[1])+GRIDSIZE_H-1);
      const int zs = p1[2] < 0.0? static_cast<int>(floor(p1[2])+GRIDSIZE_H): static_cast<int>(ceil(p1[2])+GRIDSIZE_H-1);
      const int xt = p3[0] < 0.0? static_cast<int>(floor(p3[0])+GRIDSIZE_H): static_cast<int>(ceil(p3[0])+GRIDSIZE_H-1);
      const int yt = p3[1] < 0.0? static_cast<int>(floor(p3[1])+GRIDSIZE_H): static_cast<int>(ceil(p3[1])+GRIDSIZE_H-1);
      const int zt = p3[2] < 0.0? static_cast<int>(floor(p3[2])+GRIDSIZE_H): static_cast<int>(ceil(p3[2])+GRIDSIZE_H-1);
      wt_d2.push_back (this->lci (xs, ys, zs, xt, yt, zt, ratio, vxlcnt, pcnt2));
      if (wt_d2.back () == 2)
        h_mix_ratio[static_cast<int>(pcl_round (ratio * (binsize-1)))]++;
      vxlcnt_sum += vxlcnt;
      p_cnt += pcnt2;
    }
    // IN, OUT, MIXED, Ratio line tracing, index2->index3
    {
      const int xs = p2[0] < 0.0? static_cast<int>(floor(p2[0])+GRIDSIZE_H): static_cast<int>(ceil(p2[0])+GRIDSIZE_H-1);
      const int ys = p2[1] < 0.0? static_cast<int>(floor(p2[1])+GRIDSIZE_H): static_cast<int>(ceil(p2[1])+GRIDSIZE_H-1);
      const int zs = p2[2] < 0.0? static_cast<int>(floor(p2[2])+GRIDSIZE_H): static_cast<int>(ceil(p2[2])+GRIDSIZE_H-1);
      const int xt = p3[0] < 0.0? static_cast<int>(floor(p3[0])+GRIDSIZE_H): static_cast<int>(ceil(p3[0])+GRIDSIZE_H-1);
      const int yt = p3[1] < 0.0? static_cast<int>(floor(p3[1])+GRIDSIZE_H): static_cast<int>(ceil(p3[1])+GRIDSIZE_H-1);
      const int zt = p3[2] < 0.0? static_cast<int>(floor(p3[2])+GRIDSIZE_H): static_cast<int>(ceil(p3[2])+GRIDSIZE_H-1);
      wt_d2.push_back (this->lci (xs,ys,zs,xt,yt,zt,ratio,vxlcnt,pcnt3));
      if (wt_d2.back () == 2)
        h_mix_ratio[static_cast<int>(pcl_round(ratio * (binsize-1)))]++;
      vxlcnt_sum += vxlcnt;
      p_cnt += pcnt3;
    }

    // D3 ( herons formula )
    d3v.push_back (sqrtf (sqrtf (s * (s-a) * (s-b) * (s-c))));
    if (vxlcnt_sum <= 21)
    {
      wt_d3.push_back (0);
      h_a3_out[th1] += static_cast<float> (pcnt3) / 32.0f;
      h_a3_out[th2] += static_cast<float> (pcnt1) / 32.0f;
      h_a3_out[th3] += static_cast<float> (pcnt2) / 32.0f;
    }
    else
      if (p_cnt - vxlcnt_sum < 4)
      {
        h_a3_in[th1] += static_cast<float> (pcnt3) / 32.0f;
        h_a3_in[th2] += static_cast<float> (pcnt1) / 32.0f;
        h_a3_in[th3] += static_cast<float> (pcnt2) / 32.0f;
        wt_d3.push_back (1);
      }
      else
      {
        h_a3_mix[th1] += static_cast<float> (pcnt3) / 32.0f;
        h_a3_mix[th2] += static_cast<float> (pcnt1) / 32.0f;
        h_a3_mix[th3] += static_cast<float> (pcnt2) / 32.0f;
        wt_d3.push_back (static_cast<float> (vxlcnt_sum) / static_cast<float> (p_cnt));
      }
  }
  // Normalizing, get max
  float maxd1 = 0;
  float maxd2 = 0;
  float maxd3 = 0;

  for (size_t nn_idx = 0; nn_idx < sample_size; ++nn_idx)
  {
    // get max of Dx
    if (d1v[nn_idx] > maxd1)
      maxd1 = d1v[nn_idx];
    if (d2v[nn_idx] > maxd2)
      maxd2 = d2v[nn_idx];
    if (d2v[sample_size + nn_idx] > maxd2)
      maxd2 = d2v[sample_size + nn_idx];
    if (d2v[sample_size*2 +nn_idx] > maxd2)
      maxd2 = d2v[sample_size*2 +nn_idx];
    if (d3v[nn_idx] > maxd3)
      maxd3 = d3v[nn_idx];
  }

  // Normalize and create histogram
  int index;
  for (size_t nn_idx = 0; nn_idx < sample_size; ++nn_idx)
  {
    h_d1[static_cast<int>(pcl_round (d1v[nn_idx] / maxd1 * (binsize-1)))]++ ;

    if (wt_d3[nn_idx] >= 0.999) // IN
    {
      index = static_cast<int>(pcl_round (d3v[nn_idx] / maxd3 * (binsize-1)));
      if (index >= 0 && index < binsize)
        h_d3_in[index]++;
    }
    else
    {
      if (wt_d3[nn_idx] <= 0.001) // OUT
      {
        index = static_cast<int>(pcl_round (d3v[nn_idx] / maxd3 * (binsize-1)));
        if (index >= 0 && index < binsize)
          h_d3_out[index]++ ;
      }
      else
      {
        index = static_cast<int>(pcl_round (d3v[nn_idx] / maxd3 * (binsize-1)));
        if (index >= 0 && index < binsize)
          h_d3_mix[index]++;
      }
    }
  }
  //normalize and create histogram
  for (size_t nn_idx = 0; nn_idx < d2v.size(); ++nn_idx )
  {
    if (wt_d2[nn_idx] == 0)
      h_in[static_cast<int>(pcl_round (d2v[nn_idx] / maxd2 * (binsize-1)))]++ ;
    if (wt_d2[nn_idx] == 1)
      h_out[static_cast<int>(pcl_round (d2v[nn_idx] / maxd2 * (binsize-1)))]++;
    if (wt_d2[nn_idx] == 2)
      h_mix[static_cast<int>(pcl_round (d2v[nn_idx] / maxd2 * (binsize-1)))]++ ;
  }

  //float weights[10] = {1,  1,  1,  1,  1,  1,  1,  1 , 1 ,  1};
  float weights[10] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 1.0f,  1.0f, 2.0f, 2.0f, 2.0f};

  hist.reserve (binsize * 10);
  for (int i = 0; i < binsize; i++)
    hist.push_back (h_a3_in[i] * weights[0]);
  for (int i = 0; i < binsize; i++)
    hist.push_back (h_a3_out[i] * weights[1]);
  for (int i = 0; i < binsize; i++)
    hist.push_back (h_a3_mix[i] * weights[2]);

  for (int i = 0; i < binsize; i++)
    hist.push_back (h_d3_in[i] * weights[3]);
  for (int i = 0; i < binsize; i++)
    hist.push_back (h_d3_out[i] * weights[4]);
  for (int i = 0; i < binsize; i++)
    hist.push_back (h_d3_mix[i] * weights[5]);

  for (int i = 0; i < binsize; i++)
    hist.push_back (h_in[i]*0.5f * weights[6]);
  for (int i = 0; i < binsize; i++)
    hist.push_back (h_out[i] * weights[7]);
  for (int i = 0; i < binsize; i++)
    hist.push_back (h_mix[i] * weights[8]);
  for (int i = 0; i < binsize; i++)
    hist.push_back (h_mix_ratio[i]*0.5f * weights[9]);

  float sm = 0;
  for (size_t i = 0; i < hist.size (); i++)
    sm += hist[i];

  for (size_t i = 0; i < hist.size (); i++)
    hist[i] /= sm;
}