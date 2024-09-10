      static source_type nearbyint ( argument_type s )
      {
#if !defined(BOOST_NO_STDC_NAMESPACE)
          using std::floor;
#endif
          return Double( floor(s.v) );
      }