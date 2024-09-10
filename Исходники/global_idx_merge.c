int main(int argc, char **argv)
{
  double start_time, end_time;
  start_time = get_time();
  int ret = 0;
  init_mpi(argc, argv);
  parse_args(argc, argv);

  rank_0_print("Merge Program\n");

#if 0
  comm = MPI_COMM_WORLD;
#endif

  ret = IDX_file_open(output_file_name);
  if (ret != 0)  terminate_with_error_msg("PIDX_file_create");

  maxh = strlen(bitSequence);

  fprintf(stderr, "Partition size :: and count %d %d %d :: %d %d %d\n", idx_count[0], idx_count[1], idx_count[2], idx_size[0], idx_size[1], idx_size[2]);
  fprintf(stderr, "bitstring %s maxh = %d\n", bitSequence, maxh);

  // shared_block_level is the level upto which the idx blocks are shared
  int shared_block_level = (int)log2(idx_count[0] * idx_count[1] * idx_count[2]) + bits_per_block + 1;
  if (shared_block_level >= maxh)
    shared_block_level = maxh;

  int shared_block_count = pow(2, shared_block_level - 1) / samples_per_block;
  fprintf(stderr, "Shared block level = %d Shared block count = %d\n", shared_block_level, shared_block_count);

  int level = 0;
  int ts = 0;

  // Iteration through all the timesteps
  for (ts = start_time_step; ts <= end_time_step; ts++)
  {
    // Iteration through all the shared blocks
    //for (level = 0; level < shared_block_level; level = level + 1)
    {
      int hz_index = (int)pow(2, level - 1);
      int file_no = hz_index / (blocks_per_file * samples_per_block);
      int file_count;
      char existing_file_name[PIDX_FILE_PATH_LENGTH];
      char new_file_name[PIDX_FILE_PATH_LENGTH];
      int ic = 0;
      if (level <= bits_per_block + log2(blocks_per_file) + 1)
        file_count = 1;
      else
        file_count = (int)pow(2, level - (bits_per_block + log2(blocks_per_file) + 1));

      // file_no is the index of the file that needs to be opened to read from all the partitions
      // they contain the shared blocks
      fprintf(stderr, "Opening file %d\n", file_no);

#if 1
      // iterate throuh all the files that contains the shared blocks
      // most likely this will be only the first file of all the partitions
      // so fc = 1
      int fc = 0;
      for (fc = file_no; fc < file_no + file_count; fc++)
      {
        // malloc for the header for the outpur blocks, i.e. the merged blocks
        uint32_t* write_binheader;
        int write_binheader_count;
        write_binheader_count = 10 + 10 * blocks_per_file * variable_count;
        int write_binheader_length = write_binheader_count * sizeof (*write_binheader);
        write_binheader = malloc(write_binheader_length);
        memset(write_binheader, 0, write_binheader_length);

        //iterate through all the variables/fields
        int var = 0;
        off_t var_offset = 0;
        for (var = 0; var < 1; var++)
        {
          unsigned char *write_data_buffer = malloc(samples_per_block * shared_block_count * bpv[var]/8);
          memset(write_data_buffer, 0, samples_per_block * shared_block_count * bpv[var]/8);
          //fprintf(stderr, "Write bufer size = %d [%d x %d x %d]\n", samples_per_block * shared_block_count * bpv[var]/8, (int)pow(2, bits_per_block), shared_block_count, bpv[var]/8);

          // shared block data
          // doube pointer (number o fpartitions x number of shared blocks)
          unsigned char **read_data_buffer = malloc(idx_count[0] * idx_count[1] * idx_count[2] * sizeof(*read_data_buffer));
          memset(read_data_buffer, 0, idx_count[0] * idx_count[1] * idx_count[2] * sizeof(*read_data_buffer));

          // shared block header info

          uint32_t** read_binheader = malloc(idx_count[0] * idx_count[1] * idx_count[2] * sizeof(*read_binheader));
          memset(read_binheader, 0, idx_count[0] * idx_count[1] * idx_count[2] * sizeof(*read_binheader));

          file_initialize_time_step(ts, output_file_name, output_file_template);
          generate_file_name(blocks_per_file, output_file_template, fc, new_file_name, PATH_MAX);
          //fprintf(stderr, "Merged blocks to be written in %s\n", new_file_name);

          // iterate through all the parttions
          for (ic = 0; ic < idx_count[0] * idx_count[1] * idx_count[2]; ic++)
          {
            char file_name_skeleton[PIDX_FILE_PATH_LENGTH];
            strncpy(file_name_skeleton, output_file_name, strlen(output_file_name) - 4);
            file_name_skeleton[strlen(output_file_name) - 4] = '\0';

            if (idx_count[0] != 1 || idx_count[1] != 1 || idx_count[2] != 1)
              sprintf(partition_file_name, "%s_%d.idx", file_name_skeleton, ic);
            else
              strcpy(partition_file_name, output_file_name);

            file_initialize_time_step(ts, partition_file_name, partition_file_template);
            generate_file_name(blocks_per_file, partition_file_template, fc, existing_file_name, PATH_MAX);

            int read_binheader_count;
            read_binheader_count = 10 + 10 * blocks_per_file * variable_count;
            read_binheader[ic] = (uint32_t*) malloc(sizeof (*read_binheader[ic])*(read_binheader_count));
            memset(read_binheader[ic], 0, sizeof (*(read_binheader[ic]))*(read_binheader_count));

            fprintf(stderr, "[%d] Partition File name %s\n", ic, existing_file_name);
            // file exists
            if ( access( partition_file_name, F_OK ) != -1 )
            {
              // contins data from the shared blocks
              read_data_buffer[ic] = malloc(samples_per_block * shared_block_count * bpv[var]/8);
              memset(read_data_buffer[ic], 0, samples_per_block * shared_block_count * bpv[var]/8);

              int fd;
              fd = open(existing_file_name, O_RDONLY | O_BINARY);
              if (fd < 0)
              {
                fprintf(stderr, "[File : %s] [Line : %d] open\n", __FILE__, __LINE__);
                continue;
                return 0;
              }

              // reads the header infor from binary file of the partitions
              ret = read(fd, read_binheader[ic], (sizeof (*(read_binheader[ic])) * read_binheader_count));
              if (ret < 0)
              {
                fprintf(stderr, "[File : %s] [Line : %d] read\n", __FILE__, __LINE__);
                return 0;
              }
              //assert(ret == (sizeof (*(read_binheader[ic])) * read_binheader_count));

              // copy the header from the partition file to the merged output file
              // do it only for first partition (this gets all info other than block offset nd count)
              if (ic == 0)
                memcpy(write_binheader, read_binheader[ic], 10 * sizeof (*write_binheader));

              int bpf = 0;
              size_t data_size = 0;
              off_t data_offset = 0;
              for (bpf = 0; bpf < shared_block_count; bpf++)
              {
                data_offset = ntohl(read_binheader[ic][(bpf + var * blocks_per_file)*10 + 12]);
                data_size = ntohl(read_binheader[ic][(bpf + var * blocks_per_file)*10 + 14]);
                fprintf(stderr, "[%s] [Partition %d Block %d Variable %d] --> Offset %d Count %d\n", partition_file_name, ic, bpf, var, (int)data_offset, (int)data_size);

                if (data_offset != 0 && data_size != 0)
                {
                  pread(fd, read_data_buffer[ic] + (bpf * samples_per_block * (bpv[var] / 8)), data_size, data_offset);

                  write_binheader[((bpf + var * blocks_per_file)*10 + 12)] = htonl(write_binheader_length + (bpf * data_size) + var * shared_block_count);
                  write_binheader[((bpf + var * blocks_per_file)*10 + 14)] = htonl(data_size);

                  // Merge happening while the shared block is being read
                  // Hardcoded stupid merge
                  // checks if value is not zero then copies to the write block
                  int m = 0;
                  for (m = 0; m < data_size / (bpv[var] / 8) ; m++)
                  {
                    double temp;
                    memcpy(&temp, read_data_buffer[ic] + (bpf * samples_per_block + m) * sizeof(double), sizeof(double));
                    if (temp != 0)
                      memcpy(write_data_buffer + ((bpf * samples_per_block) + m) * sizeof(double), &temp, sizeof(double));
                  }
                }
              }

              close(fd);
            }
            else
              continue;
          }

          //Merge after all the reads
          for (ic = 0; ic < idx_count[0] * idx_count[1] * idx_count[2]; ic++)
          {
            //input is read_data_buffer**
            //output is write_data_buffer*
          }

          if ( access( new_file_name, F_OK ) != -1 )
          {
            // file exists
            int fd;
            fd = open(new_file_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
            {
            }
            close(fd);
          }
          else
          {
            // file doesn't exist
            /*
            int r;
            for (r = 0; r < (shared_block_count * samples_per_block * bpv[var]/8) / sizeof(double); r++)
            {
              double dval;
              memcpy(&dval, write_data_buffer + r * sizeof(double), sizeof(double));
              fprintf(stderr, "value at %d = %f\n", r, dval);
            }
            */

            int fd;
            fd = open(new_file_name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
            pwrite(fd, write_binheader, sizeof (*write_binheader)*(write_binheader_count), 0);
            pwrite(fd, write_data_buffer, shared_block_count * samples_per_block * bpv[var]/8, sizeof (*write_binheader)*(write_binheader_count));
            close(fd);
          }
        }
      }
      #endif
    }
  }


  shutdown_mpi();

  end_time = get_time();
  fprintf(stderr, "Total time taken = %f %f\n", end_time, start_time);

  return 0;
}