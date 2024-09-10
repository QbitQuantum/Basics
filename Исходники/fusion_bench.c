static void
bench_shmpool( bool debug )
{
     DirectResult  ret;
     void         *mem[256];
     const int     sizes[8] = { 12, 36, 200, 120, 39, 3082, 8, 1040 };

     FusionSHMPoolShared *pool;

     ret = fusion_shm_pool_create( world, "Benchmark Pool", 524288, debug, &pool );
     if (ret) {
          DirectFBError( "fusion_shm_pool_create() failed", ret );
          return;
     }

     BENCH_START();

     BENCH_LOOP() {
          int i;

          for (i=0; i<128; i++)
               mem[i] = SHMALLOC( pool, sizes[i&7] );

          for (i=0; i<64; i++)
               SHFREE( pool, mem[i] );

          for (i=128; i<192; i++)
               mem[i] = SHMALLOC( pool, sizes[i&7] );

          for (i=64; i<128; i++)
               SHFREE( pool, mem[i] );

          for (i=192; i<256; i++)
               mem[i] = SHMALLOC( pool, sizes[i&7] );

          for (i=128; i<256; i++)
               SHFREE( pool, mem[i] );
     }

     BENCH_STOP();

     printf( "shm pool alloc/free %s           -> %8.2f k/sec\n",
             debug ? "(debug)" : "       ", BENCH_RESULT_BY(256) );

     fusion_shm_pool_destroy( world, pool );
}