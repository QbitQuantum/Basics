int main() {

   /* Host/device data structures */
   cl_device_id device;
   cl_context context;
   cl_command_queue queue;
   cl_program program;
   cl_kernel kernel_init, kernel_stage_0, kernel_stage_n, kernel_merge,
         kernel_merge_last;
   cl_int i, err, check, direction;

   /* Data and buffers */
   float data[NUM_FLOATS];
   cl_mem data_buffer;
   cl_uint stage, high_stage, num_stages;
   size_t local_size, global_size;

   /* Initialize data */
   srand(time(NULL));
   for(i=0; i<NUM_FLOATS; i++) {
      data[i] = rand();
   }

   /* Create a device and context */
   device = create_device();
   context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
   if(err < 0) {
      perror("Couldn't create a context");
      exit(1);   
   }

   /* Build the program */
   program = build_program(context, device, PROGRAM_FILE);

   /* Create kernels */
   kernel_init = clCreateKernel(program, BSORT_INIT, &err);
   if(err < 0) {
      perror("Couldn't create the initial kernel");
      exit(1);   
   };
   kernel_stage_0 = clCreateKernel(program, BSORT_STAGE_0, &err);
   if(err < 0) {
      perror("Couldn't create the stage_0 kernel");
      exit(1);   
   };
   kernel_stage_n = clCreateKernel(program, BSORT_STAGE_N, &err);
   if(err < 0) {
      perror("Couldn't create the stage_n kernel");
      exit(1);   
   };
   kernel_merge = clCreateKernel(program, BSORT_MERGE, &err);
   if(err < 0) {
      perror("Couldn't create the merge kernel");
      exit(1);   
   };
   kernel_merge_last = clCreateKernel(program, BSORT_MERGE_LAST, &err);
   if(err < 0) {
      perror("Couldn't create the merge_last kernel");
      exit(1);   
   };

   /* Determine maximum work-group size */
   err = clGetKernelWorkGroupInfo(kernel_init, device, CL_KERNEL_WORK_GROUP_SIZE,
      sizeof(local_size), &local_size, NULL);
   if(err < 0) {
      perror("Couldn't find the maximum work-group size");
      exit(1);   
   };
   local_size = (int)pow(2, trunc(log2(local_size))); 


   /* Create buffer */
   data_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE |
         CL_MEM_COPY_HOST_PTR, sizeof(data), data, &err);
   if(err < 0) {
      perror("Couldn't create a buffer");
      exit(1);   
   };

   /* Create kernel argument */
   err = clSetKernelArg(kernel_init, 0, sizeof(cl_mem), &data_buffer);
   err |= clSetKernelArg(kernel_stage_0, 0, sizeof(cl_mem), &data_buffer);
   err |= clSetKernelArg(kernel_stage_n, 0, sizeof(cl_mem), &data_buffer);
   err |= clSetKernelArg(kernel_merge, 0, sizeof(cl_mem), &data_buffer);
   err |= clSetKernelArg(kernel_merge_last, 0, sizeof(cl_mem), &data_buffer);
   if(err < 0) {
      printf("Couldn't set a kernel argument");
      exit(1);
   };

   /* Create kernel argument */
   err = clSetKernelArg(kernel_init, 1, 8*local_size*sizeof(float), NULL);
   err |= clSetKernelArg(kernel_stage_0, 1, 8*local_size*sizeof(float), NULL);
   err |= clSetKernelArg(kernel_stage_n, 1, 8*local_size*sizeof(float), NULL);
   err |= clSetKernelArg(kernel_merge, 1, 8*local_size*sizeof(float), NULL);
   err |= clSetKernelArg(kernel_merge_last, 1, 8*local_size*sizeof(float), NULL);
   if(err < 0) {
      printf("Couldn't set a kernel argument");
      exit(1);
   };

   /* Create a command queue */
   queue = clCreateCommandQueue(context, device, 0, &err);
   if(err < 0) {
      perror("Couldn't create a command queue");
      exit(1);   
   };

   /* Enqueue initial sorting kernel */
   global_size = NUM_FLOATS/8;
   if(global_size < local_size) {
      local_size = global_size;
   }
   err = clEnqueueNDRangeKernel(queue, kernel_init, 1, NULL, &global_size, 
         &local_size, 0, NULL, NULL); 
   if(err < 0) {
      perror("Couldn't enqueue the kernel");
      exit(1);   
   }

   /* Execute further stages */
   num_stages = global_size/local_size;
   for(high_stage = 2; high_stage < num_stages; high_stage <<= 1) {

      err = clSetKernelArg(kernel_stage_0, 2, sizeof(int), &high_stage);      
      err |= clSetKernelArg(kernel_stage_n, 3, sizeof(int), &high_stage);
      if(err < 0) {
         printf("Couldn't set a kernel argument");
         exit(1);
      };

      for(stage = high_stage; stage > 1; stage >>= 1) {

         err = clSetKernelArg(kernel_stage_n, 2, sizeof(int), &stage);
         if(err < 0) {
            printf("Couldn't set a kernel argument");
            exit(1);
         };

         err = clEnqueueNDRangeKernel(queue, kernel_stage_n, 1, NULL, 
               &global_size, &local_size, 0, NULL, NULL); 
         if(err < 0) {
            perror("Couldn't enqueue the kernel");
            exit(1);   
         }
      }

      err = clEnqueueNDRangeKernel(queue, kernel_stage_0, 1, NULL, 
            &global_size, &local_size, 0, NULL, NULL); 
      if(err < 0) {
         perror("Couldn't enqueue the kernel");
         exit(1);   
      }
   }

   /* Set the sort direction */
   direction = DIRECTION;
   err = clSetKernelArg(kernel_merge, 3, sizeof(int), &direction);
   err |= clSetKernelArg(kernel_merge_last, 2, sizeof(int), &direction);
   if(err < 0) {
      printf("Couldn't set a kernel argument");
      exit(1);
   };

   /* Perform the bitonic merge */
   for(stage = num_stages; stage > 1; stage >>= 1) {

      err = clSetKernelArg(kernel_merge, 2, sizeof(int), &stage);
      if(err < 0) {
         printf("Couldn't set a kernel argument");
         exit(1);
      };

      err = clEnqueueNDRangeKernel(queue, kernel_merge, 1, NULL, 
            &global_size, &local_size, 0, NULL, NULL); 
      if(err < 0) {
         perror("Couldn't enqueue the kernel");
         exit(1);   
      }
   }
   err = clEnqueueNDRangeKernel(queue, kernel_merge_last, 1, NULL, 
         &global_size, &local_size, 0, NULL, NULL); 
   if(err < 0) {
      perror("Couldn't enqueue the kernel");
      exit(1);   
   }

   /* Read the result */
   err = clEnqueueReadBuffer(queue, data_buffer, CL_TRUE, 0, 
      sizeof(data), &data, 0, NULL, NULL);
   if(err < 0) {
      perror("Couldn't read the buffer");
      exit(1);   
   }

   check = 1;

   /* Check ascending sort */
   if(direction == 0) {
      for(i=1; i<NUM_FLOATS; i++) {
         if(data[i] < data[i-1]) {
            check = 0;
            break;
         }
      }
   }
   /* Check descending sort */
   if(direction == -1) {
      for(i=1; i<NUM_FLOATS; i++) {
         if(data[i] > data[i-1]) {
            check = 0;
            break;
         }
      }
   }

   /* Display check result */
   printf("Local size: %zu\n", local_size);
   printf("Global size: %zu\n", global_size);
   if(check)
      printf("Bitonic sort succeeded.\n");
   else
      printf("Bitonic sort failed.\n");

   /* Deallocate resources */
   clReleaseMemObject(data_buffer);
   clReleaseKernel(kernel_init);
   clReleaseKernel(kernel_stage_0);
   clReleaseKernel(kernel_stage_n);
   clReleaseKernel(kernel_merge);
   clReleaseKernel(kernel_merge_last);
   clReleaseCommandQueue(queue);
   clReleaseProgram(program);
   clReleaseContext(context);
   return 0;
}