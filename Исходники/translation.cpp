   template <class P> static
   void Apply( GenericImage<P>& image, const Translation& translation )
   {
      if ( translation.Delta() == 0.0 )
         return;

      int width = image.Width();
      int height = image.Height();
      if ( width == 0 || height == 0 )
         return;

      image.EnsureUnique();

      typename P::sample* f = nullptr;
      typename P::sample** f0 = nullptr;

      int n = image.NumberOfChannels();
      typename GenericImage<P>::color_space cs0 = image.ColorSpace();

      StatusMonitor status = image.Status();

      int numberOfThreads = translation.IsParallelProcessingEnabled() ?
               Min( translation.MaxProcessors(), pcl::Thread::NumberOfThreads( height, 1 ) ) : 1;
      int rowsPerThread = height/numberOfThreads;

      try
      {
         size_type N = size_type( width )*size_type( height );
         if ( status.IsInitializationEnabled() )
            status.Initialize( String().Format( "Translate dx=%.3lf, dy=%.3lf, ",
                        translation.Delta().x, translation.Delta().y ) + translation.Interpolation().Description(),
                        size_type( n )*N );

         f0 = image.ReleaseData();

         for ( int c = 0; c < n; ++c )
         {
            ThreadData<P> data( translation.Delta(), width, height, status, N );

            data.f = f = image.Allocator().AllocatePixels( size_type( width )*size_type( height ) );
            data.fillValue = (c < translation.FillValues().Length()) ? P::ToSample( translation.FillValues()[c] ) : P::MinSampleValue();

            ReferenceArray<Thread<P> > threads;
            for ( int i = 0, j = 1; i < numberOfThreads; ++i, ++j )
               threads.Add( new Thread<P>( data,
                                           translation.Interpolation().NewInterpolator<P>( f0[c], width, height ),
                                           i*rowsPerThread,
                                           (j < numberOfThreads) ? j*rowsPerThread : height ) );

            AbstractImage::RunThreads( threads, data );

            threads.Destroy();

            image.Allocator().Deallocate( f0[c] );
            f0[c] = f;
            f = nullptr;

            status = data.status;
         }

         image.ImportData( f0, width, height, n, cs0 ).Status() = status;
      }
      catch ( ... )
      {
         if ( f != nullptr )
            image.Allocator().Deallocate( f );
         if ( f0 != nullptr )
         {
            for ( int c = 0; c < n; ++c )
               if ( f0[c] != nullptr )
                  image.Allocator().Deallocate( f0[c] );
            image.Allocator().Deallocate( f0 );
         }
         image.FreeData();
         throw;
      }
   }