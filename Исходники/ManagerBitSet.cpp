    dp::math::Box3f ManagerBitSet::calculateBoundingBox( const GroupSharedPtr& group ) const
    {
#if defined(SSE)
      if ( useSSE )
      {
        GroupBitSetSharedPtr groupImpl = std::static_pointer_cast<GroupBitSet>(group);

        __m128 minValue = _mm_set1_ps( std::numeric_limits<float>::signaling_NaN() );
        __m128 maxValue = _mm_set1_ps( std::numeric_limits<float>::signaling_NaN() );

        char const* basePtr = reinterpret_cast<char const*>(groupImpl->getMatrices());
        for ( size_t index = 0;index < groupImpl->getObjectCount(); ++index )
        {
          ObjectBitSetSharedPtr objectImpl = std::static_pointer_cast<ObjectBitSet>(groupImpl->getObject( index ));
          dp::math::sse::Mat44f const& modelView = *reinterpret_cast<dp::math::sse::Mat44f const*>(basePtr + objectImpl->getTransformIndex() * groupImpl->getMatricesStride());
          dp::math::Vec4f const& extent = objectImpl->getExtent();

          dp::math::sse::Vec4f vectors[8];
          vectors[0] = *reinterpret_cast<dp::math::sse::Vec4f const*>(&objectImpl->getLowerLeft()) * modelView;

          dp::math::sse::Vec4f x( extent[0] * modelView[0] );
          dp::math::sse::Vec4f y( extent[1] * modelView[1] );
          dp::math::sse::Vec4f z( extent[2] * modelView[2] );

          vectors[1] = vectors[0] + x;
          vectors[2] = vectors[0] + y;
          vectors[3] = vectors[1] + y;
          vectors[4] = vectors[0] + z;
          vectors[5] = vectors[1] + z;
          vectors[6] = vectors[2] + z;
          vectors[7] = vectors[3] + z;

          for ( unsigned int i = 0;i < 8; ++i )
          {
            minValue = _mm_min_ps( minValue, vectors[i].sse() );
            maxValue = _mm_max_ps( maxValue, vectors[i].sse() );
          }
        }

        dp::math::Vec3f minVec, maxVec;
        _MM_EXTRACT_FLOAT( minVec[0], minValue, 0);
        _MM_EXTRACT_FLOAT( minVec[1], minValue, 1);
        _MM_EXTRACT_FLOAT( minVec[2], minValue, 2);

        _MM_EXTRACT_FLOAT( maxVec[0], maxValue, 0);
        _MM_EXTRACT_FLOAT( maxVec[1], maxValue, 1);
        _MM_EXTRACT_FLOAT( maxVec[2], maxValue, 2);

        return dp::math::Box3f( minVec, maxVec );
      }
      else
#elif defined(NEON)
        if ( useNEON )
        {
          GroupBitSetSharedPtr groupImpl = std::static_pointer_cast<GroupBitSet>(group);

          float32x4_t minValue = vdupq_n_f32( std::numeric_limits<float>::max() );
          float32x4_t maxValue = vdupq_n_f32( -std::numeric_limits<float>::max() );

          char const* basePtr = reinterpret_cast<char const*>(groupImpl->getMatrices());
          for ( size_t index = 0;index < groupImpl->getObjectCount(); ++index )
          {
            const ObjectBitSetSharedPtr objectImpl = std::static_pointer_cast<ObjectBitSet>(groupImpl->getObject( index ));
            dp::math::neon::Mat44f const& modelView = *reinterpret_cast<dp::math::neon::Mat44f const*>(basePtr + objectImpl->getTransformIndex() * groupImpl->getMatricesStride());
            dp::math::Vec4f const& extent = objectImpl->getExtent();

            dp::math::neon::Vec4f vectors[8];
            vectors[0] = *reinterpret_cast<dp::math::neon::Vec4f const*>(&objectImpl->getLowerLeft()) * modelView;

            dp::math::neon::Vec4f x( extent[0] * modelView[0] );
            dp::math::neon::Vec4f y( extent[1] * modelView[1] );
            dp::math::neon::Vec4f z( extent[2] * modelView[2] );

            vectors[1] = vectors[0] + x;
            vectors[2] = vectors[0] + y;
            vectors[3] = vectors[1] + y;
            vectors[4] = vectors[0] + z;
            vectors[5] = vectors[1] + z;
            vectors[6] = vectors[2] + z;
            vectors[7] = vectors[3] + z;

            for ( unsigned int i = 0;i < 8; ++i )
            {
              minValue = vminq_f32( minValue, vectors[i].neon() );
              maxValue = vmaxq_f32( maxValue, vectors[i].neon() );
            }

          }

          dp::math::Vec3f minVec, maxVec;

          vst1q_lane_f32( &minVec[0], minValue, 0);
          vst1q_lane_f32( &minVec[1], minValue, 1);
          vst1q_lane_f32( &minVec[2], minValue, 2);

          vst1q_lane_f32( &maxVec[0], maxValue, 0);
          vst1q_lane_f32( &maxVec[1], maxValue, 1);
          vst1q_lane_f32( &maxVec[2], maxValue, 2);

          return dp::math::Box3f( minVec, maxVec );
        }
        else

#endif
      // CPU fallback
      {
        GroupBitSetSharedPtr groupImpl = std::static_pointer_cast<GroupBitSet>(group);

        dp::math::Box4f boundingBox;

        char const* basePtr = reinterpret_cast<char const*>(groupImpl->getMatrices());
        for ( size_t index = 0;index < groupImpl->getObjectCount(); ++index )
        {
          const ObjectBitSetSharedPtr objectImpl = std::static_pointer_cast<ObjectBitSet>(groupImpl->getObject( index ));
          dp::math::Mat44f const& modelView = reinterpret_cast<dp::math::Mat44f const&>(*(basePtr + objectImpl->getTransformIndex() * groupImpl->getMatricesStride()));
          dp::math::Vec4f const& extent = objectImpl->getExtent();

          dp::math::Vec4f vectors[8];
          vectors[0] = (objectImpl->getLowerLeft() * modelView);

          dp::math::Vec4f x( extent[0] * modelView.getPtr()[0], extent[0] * modelView.getPtr()[1], extent[0] * modelView.getPtr()[2], extent[0] * modelView.getPtr()[3] );
          dp::math::Vec4f y( extent[1] * modelView.getPtr()[4], extent[1] * modelView.getPtr()[5], extent[1] * modelView.getPtr()[6], extent[1] * modelView.getPtr()[7] );
          dp::math::Vec4f z( extent[2] * modelView.getPtr()[8], extent[2] * modelView.getPtr()[9], extent[2] * modelView.getPtr()[10], extent[2] * modelView.getPtr()[11] );

          vectors[1] = vectors[0] + x;
          vectors[2] = vectors[0] + y;
          vectors[3] = vectors[1] + y;
          vectors[4] = vectors[0] + z;
          vectors[5] = vectors[1] + z;
          vectors[6] = vectors[2] + z;
          vectors[7] = vectors[3] + z;

          for ( unsigned int i = 0;i < 8; ++i )
          {
            boundingBox.update( vectors[i] );
          }
        }

        dp::math::Vec4f lower = boundingBox.getLower();
        dp::math::Vec4f upper = boundingBox.getUpper();

        return dp::math::Box3f( dp::math::Vec3f( lower[0], lower[1], lower[2]), dp::math::Vec3f( upper[0], upper[1], upper[2]));
      }
    }