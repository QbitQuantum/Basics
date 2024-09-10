    Tensor<1,dim>
    MyExactSolution<dim>::gradient (const Point<dim>   &p,
	const unsigned int) const
    {
      Tensor<1,dim> result;
      for(unsigned int i=0; i<dim; ++i)
      {
	result[i] = alpha*pow(p.distance(singularity), alpha-2.)*p[i];
      }
      return result;
    }