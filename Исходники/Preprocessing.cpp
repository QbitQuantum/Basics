void filter(const Eigen::MatrixXd& x, Eigen::MatrixXd& y, const Eigen::MatrixXd& b, const Eigen::MatrixXd& a)
{
  y.setZero();

  for(int c = 0; c < x.rows(); c++)
  {
    for(int t = 0; t < x.cols(); t++)
    {
      const int maxPQ = std::max(b.rows(), a.rows());
      for(int pq = 0; pq < maxPQ; pq++)
      {
        const double tSource = t - pq;
        if(pq < b.rows())
        {
          if(tSource >= 0)
            y(c, t) += b(pq) * x(c, tSource);
          else
            y(c, t) += b(pq) * x(c, -tSource);
        }
        if(pq > 0 && pq < a.rows())
        {
          if(tSource >= 0)
            y(c, t) += a(pq) * x(c, tSource);
          else
            y(c, t) += a(pq) * x(c, -tSource);
        }
      }
      y(c, t) /= a(0);
    }
  }
}