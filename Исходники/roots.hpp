T newton_raphson_iterate(F f, T guess, T min, T max, int digits, boost::uintmax_t& max_iter)
{
   BOOST_MATH_STD_USING

   T f0(0), f1, last_f0(0);
   T result = guess;

   T factor = static_cast<T>(ldexp(1.0, 1 - digits));
   T delta = 1;
   T delta1 = tools::max_value<T>();
   T delta2 = tools::max_value<T>();

   boost::uintmax_t count(max_iter);

   do{
      last_f0 = f0;
      delta2 = delta1;
      delta1 = delta;
      boost::math::tie(f0, f1) = f(result);
      if(0 == f0)
         break;
      if(f1 == 0)
      {
         // Oops zero derivative!!!
#ifdef BOOST_MATH_INSTRUMENT
         std::cout << "Newton iteration, zero derivative found" << std::endl;
#endif
         detail::handle_zero_derivative(f, last_f0, f0, delta, result, guess, min, max);
      }
      else
      {
         delta = f0 / f1;
      }
#ifdef BOOST_MATH_INSTRUMENT
      std::cout << "Newton iteration, delta = " << delta << std::endl;
#endif
      if(fabs(delta * 2) > fabs(delta2))
      {
         // last two steps haven't converged, try bisection:
         delta = (delta > 0) ? (result - min) / 2 : (result - max) / 2;
      }
      guess = result;
      result -= delta;
      if(result <= min)
      {
         delta = 0.5F * (guess - min);
         result = guess - delta;
         if((result == min) || (result == max))
            break;
      }
      else if(result >= max)
      {
         delta = 0.5F * (guess - max);
         result = guess - delta;
         if((result == min) || (result == max))
            break;
      }
      // update brackets:
      if(delta > 0)
         max = guess;
      else
         min = guess;
   }while(--count && (fabs(result * factor) < fabs(delta)));

   max_iter -= count;

#ifdef BOOST_MATH_INSTRUMENT
   std::cout << "Newton Raphson iteration, final count = " << max_iter << std::endl;

   static boost::uintmax_t max_count = 0;
   if(max_iter > max_count)
   {
      max_count = max_iter;
      std::cout << "Maximum iterations: " << max_iter << std::endl;
   }
#endif

   return result;
}