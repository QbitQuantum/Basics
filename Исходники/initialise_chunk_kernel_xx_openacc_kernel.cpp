// host stub function
void ops_par_loop_initialise_chunk_kernel_xx(char const *name, ops_block block,
                                             int dim, int *range, ops_arg arg0,
                                             ops_arg arg1) {

  // Timing
  double t1, t2, c1, c2;
  ops_arg args[2] = {arg0, arg1};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 2, range, 0))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(0, "initialise_chunk_kernel_xx");
    OPS_kernels[0].count++;
    ops_timers_core(&c1, &t1);
  }

  // compute localy allocated range for the sub-block

  int start[2];
  int end[2];
#ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
#endif // OPS_MPI

  int arg_idx[2];
  int arg_idx_base[2];
#ifdef OPS_MPI
  if (compute_ranges(args, 2, block, range, start, end, arg_idx) < 0)
    return;
#else // OPS_MPI
  for (int n = 0; n < 2; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
    arg_idx[n] = start[n];
  }
#endif
  for (int n = 0; n < 2; n++) {
    arg_idx_base[n] = arg_idx[n];
  }

  int dat0 = args[0].dat->elem_size;

  // set up initial pointers
  int base0 = args[0].dat->base_offset +
              (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size) *
                  start[0] * args[0].stencil->stride[0];
  base0 = base0 +
          (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size) *
              args[0].dat->size[0] * start[1] * args[0].stencil->stride[1];
#ifdef OPS_GPU
  int *p_a0 = (int *)((char *)args[0].data_d + base0);
#else
  int *p_a0 = (int *)((char *)args[0].data + base0);
#endif

  int *p_a1 = NULL;

  int x_size = MAX(0, end[0] - start[0]);
  int y_size = MAX(0, end[1] - start[1]);

  // initialize global variable with the dimension of dats
  xdim0 = args[0].dat->size[0];
  if (xdim0 != xdim0_initialise_chunk_kernel_xx_h) {
    xdim0_initialise_chunk_kernel_xx = xdim0;
    xdim0_initialise_chunk_kernel_xx_h = xdim0;
  }

// Halo Exchanges

#ifdef OPS_GPU
  ops_H_D_exchanges_device(args, 2);
#else
  ops_H_D_exchanges_host(args, 2);
#endif
  ops_halo_exchanges(args, 2, range);

#ifdef OPS_GPU
  ops_H_D_exchanges_device(args, 2);
#else
  ops_H_D_exchanges_host(args, 2);
#endif
  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[0].mpi_time += t2 - t1;
  }

  initialise_chunk_kernel_xx_c_wrapper(p_a0, p_a1, arg_idx[0], arg_idx[1],
                                       x_size, y_size);

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[0].time += t1 - t2;
  }
#ifdef OPS_GPU
  ops_set_dirtybit_device(args, 2);
#else
  ops_set_dirtybit_host(args, 2);
#endif
  ops_set_halo_dirtybit3(&args[0], range);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[0].mpi_time += t2 - t1;
    OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg0);
  }
}