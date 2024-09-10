    auto match(vfloat2 p, vfloat2 tr_prediction,
	       F A, F B, GD Ag,
	       const int winsize,
	       const float min_ev_th,
	       const int max_interations,
	       const float convergence_delta)
    {
      typedef typename F::value_type V;
      int WS = winsize;
      int ws = winsize;
      int hws = ws/2;

      // Gradient matrix
      Eigen::Matrix2f G = Eigen::Matrix2f::Zero();
      int cpt = 0;
      for(int r = -hws; r <= hws; r++)
	for(int c = -hws; c <= hws; c++)
	  {
	    vfloat2 n = p + vfloat2(r, c);
	    if (A.has(n.cast<int>()))
	      {
		Eigen::Matrix2f m;
		auto g = Ag.linear_interpolate(n);
		float gx = g[0];
		float gy = g[1];
		m <<
		  gx * gx, gx * gy,
		  gx * gy, gy * gy;
		G += m;
		cpt++;
	      }
	  }

      // Check minimum eigenvalue.
      float min_ev = 99999.f;
      auto ev = (G / cpt).eigenvalues();
      for (int i = 0; i < ev.size(); i++)
	if (fabs(ev[i].real()) < min_ev) min_ev = fabs(ev[i].real());

      if (min_ev < min_ev_th)
	return std::pair<vfloat2, float>(vfloat2(-1,-1), FLT_MAX);

      Eigen::Matrix2f G1 = G.inverse();

      // Precompute gs and as.
      vfloat2 prediction_ = p + tr_prediction;
      vfloat2 v = prediction_;
      Eigen::Vector2f nk = Eigen::Vector2f::Ones();

      char gs_buffer[WS * WS * sizeof(vfloat2)];
      vfloat2* gs = (vfloat2*) gs_buffer;
      // was: vfloat2 gs[WS * WS];

      typedef plus_promotion<V> S;
      char as_buffer[WS * WS * sizeof(S)];
      S* as = (S*) as_buffer;
      // was: S as[WS * WS];
      {
	for(int i = 0, r = -hws; r <= hws; r++)
	  {
	    for(int c = -hws; c <= hws; c++)
	      {
		vfloat2 n = p + vfloat2(r, c);
		if (Ag.has(n.cast<int>()))
		  {
		    gs[i] = Ag.linear_interpolate(n).template cast<float>();
		    as[i] = cast<S>(A.linear_interpolate(n));
		  }
		i++;
	      }
	  }
      }
      auto domain = B.domain();// - border(hws + 1);

      // Gradient descent
      for (int k = 0; k <= max_interations && nk.norm() >= convergence_delta; k++)
	{
	  Eigen::Vector2f bk = Eigen::Vector2f::Zero();
	  // Temporal difference.
	  int i = 0;
	  for(int r = -hws; r <= hws; r++)
	    {
	      for(int c = -hws; c <= hws; c++)          
		{
		  vfloat2 n = p + vfloat2(r, c);
		  if (Ag.has(n.cast<int>()))
		    {
		      vfloat2 n2 = v + vfloat2(r, c);
		      auto g = gs[i];
		      float dt = (cast<float>(as[i]) - cast<float>(B.linear_interpolate(n2)));
		      bk += Eigen::Vector2f{g[0] * dt, g[1] * dt};
		    }
		  i++;
		}
	    }

	  nk = G1 * bk;
	  v += vfloat2{nk[0], nk[1]};

	  if (!domain.has(v.cast<int>()))
	    return std::pair<vfloat2, float>(vfloat2(0, 0), FLT_MAX);
	}

      // Compute the SSD.
      float err = 0;
      for(int r = -hws; r <= hws; r++)
	for(int c = -hws; c <= hws; c++)
	  {
	    vfloat2 n2 = v + vfloat2(r, c);
	    int i = (r+hws) * ws + (c+hws);
	    {
	      err += fabs(cast<float>(as[i] - cast<S>(B.linear_interpolate(n2))));
	      cpt++;
	    }
	  }

      return std::pair<vfloat2, float>(v - p, err / (cpt));


    }