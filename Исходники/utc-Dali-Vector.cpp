int UtcDaliVectorDoubleRemove(void)
{
  tet_infoline("Testing Dali::Vector<double>::Remove");

  Vector< double > vector;
  DALI_TEST_EQUALS( ZERO, vector.Count(), TEST_LOCATION );

  vector.PushBack( 11.1 );
  vector.PushBack( 22.2 );
  vector.PushBack( 33.3 );
  vector.PushBack( 44.4 );
  DALI_TEST_EQUALS( static_cast<Dali::VectorBase::SizeType>(4), vector.Count(), TEST_LOCATION );
  DALI_TEST_EQUALS( vector[ 0 ], 11.1, TEST_LOCATION );
  DALI_TEST_EQUALS( vector[ 1 ], 22.2, TEST_LOCATION );
  DALI_TEST_EQUALS( vector[ 2 ], 33.3, TEST_LOCATION );
  DALI_TEST_EQUALS( vector[ 3 ], 44.4, TEST_LOCATION );

  Vector< double >::Iterator res = std::find( vector.Begin(), vector.End(), 22.2 );
  DALI_TEST_EQUALS( 22.2, *res, TEST_LOCATION );
  vector.Remove( res );
  res = std::find( vector.Begin(), vector.End(), 22.2 );
  DALI_TEST_EQUALS( vector.End(), res, TEST_LOCATION );
  DALI_TEST_EQUALS( static_cast<Dali::VectorBase::SizeType>(3), vector.Count(), TEST_LOCATION );
  DALI_TEST_EQUALS( vector[ 0 ], 11.1, TEST_LOCATION );
  DALI_TEST_EQUALS( vector[ 1 ], 44.4, TEST_LOCATION );
  DALI_TEST_EQUALS( vector[ 2 ], 33.3, TEST_LOCATION );

  vector.Remove( vector.End() - 1 );
  DALI_TEST_EQUALS( static_cast<Dali::VectorBase::SizeType>(2), vector.Count(), TEST_LOCATION );
  DALI_TEST_EQUALS( vector[ 0 ], 11.1, TEST_LOCATION );
  DALI_TEST_EQUALS( vector[ 1 ], 44.4, TEST_LOCATION );

  vector.Remove( vector.Begin() );
  DALI_TEST_EQUALS( static_cast<Dali::VectorBase::SizeType>(1), vector.Count(), TEST_LOCATION );
  DALI_TEST_EQUALS( vector[ 0 ], 44.4, TEST_LOCATION );

  try
  {
    // illegal erase, one past the end
    vector.Remove( vector.Begin() + 1 );
    tet_result(TET_FAIL);
  }
  catch( Dali::DaliException& e )
  {
    DALI_TEST_PRINT_ASSERT( e );
    DALI_TEST_ASSERT( e, "(iterator < End()) && (iterator >= Begin())", TEST_LOCATION );
  }
  catch( ... )
  {
    tet_printf("Assertion test failed - wrong Exception\n" );
    tet_result(TET_FAIL);
  }
  DALI_TEST_EQUALS( static_cast<Dali::VectorBase::SizeType>(1), vector.Count(), TEST_LOCATION );
  DALI_TEST_EQUALS( vector[ 0 ], 44.4, TEST_LOCATION );

  vector.Remove( vector.Begin() );
  DALI_TEST_EQUALS( ZERO, vector.Count(), TEST_LOCATION );

  try
  {
    // illegal erase, one before the beginning
    vector.Remove( vector.Begin() - 1 );
    tet_result(TET_FAIL);
  }
  catch( Dali::DaliException& e )
  {
    DALI_TEST_PRINT_ASSERT( e );
    DALI_TEST_ASSERT( e, "(iterator < End()) && (iterator >= Begin())", TEST_LOCATION );
  }
  catch( ... )
  {
    tet_printf("Assertion test failed - wrong Exception\n" );
    tet_result(TET_FAIL);
  }

  END_TEST;
}