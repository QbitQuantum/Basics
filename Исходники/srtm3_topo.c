NV_INT32 main (NV_INT32 argc, NV_CHAR *argv[])
{
  NV_INT32       i, j, k, m, shift_lat, shift_lon, n, hit_land, hit_water,
                 pos, swap = 1, prev_value, first, ndx, total_bits, block;
  uLong          total_bytes;
  uLongf         out_bytes;
  FILE           *fp, *block_fp, *ofp;
  NV_INT16       row[1200][1201], delta[1200 * 1200], bias, start_val = 0, last_val = 0, diff, min_diff, max_diff, num_bits, null_val;
  NV_CHAR        string[512], ofile[512], dir[512], lathem, lonhem, header_block[HEADER_SIZE], block_file[512];
  NV_CHAR        dir_name[6][40] = {"Africa", "Australia", "Eurasia", "Islands", "North_America", "South_America"};
  NV_INT64       lpos;
  NV_U_BYTE      water[4], head[8], *in_buf, *out_buf, map[MAP_BYTES], byte, block_map[64800];
  time_t         t;
  struct tm      *cur_tm;


  printf ("\n\n%s\n\n", VERSION);


  if (argc < 2)
    {
      fprintf (stderr, "Usage: %s SRTM3_HGT_DIRECTORY_NAME\n\n", argv[0]);
      exit (-1);
    }


  /*  Open and read the block map file.  */

  if (getenv ("SRTM_DATA") == NULL)
    {
      fprintf (stderr, "\n\nYou must set the SRTM_DATA environment variable to point to the location of srtm3 directory\n\n");
      exit (-1);
    }

  strcpy (dir, getenv ("SRTM_DATA"));


  /*  Check the hgt directory name.  */

  block = 0;
  for (i = 0 ; i < 6 ; i++)
    {
      if (!strcmp (dir_name[i], argv[1]))
        {
          block = i + 1;
          break;
        }
    }

  if (!block)
    {
      fprintf (stderr, "SRTM3_HGT_DIRECTORY_NAME %s is incorrect.  Only the following are valid:\n\n", argv[1]);
      for (i = 0 ; i < 6 ; i++) fprintf (stderr, "\t%s\n", dir_name[i]);
      fprintf (stderr, "\n\n");
      exit (-1);
    }


  /*  Open and read the block map file.  */

  sprintf (block_file, "%s%1csrtm3%1csrtm3_block_map.dat", dir, SEPARATOR, SEPARATOR);

  if ((block_fp = fopen (block_file, "rb+")) == NULL)
    {
      if ((block_fp = fopen (block_file, "wb+")) == NULL)
        {
          perror (block_file);
          exit (-1);
        }


      /*  This must be the first time so initialize it.  */

      byte = 0;
      for (i = 0 ; i < 180 ; i++)
        {
          for (j = 0 ; j < 360 ; j++)
            {
              fwrite (&byte, 1, 1, block_fp);
            }
        }
    }

  fseek (block_fp, 0, SEEK_SET);
  fread (block_map, sizeof (block_map), 1, block_fp);


  /*  Are we on a big endian machine?  */

  if (big_endian ()) swap = 0;;


  /*  Set the water flag for the map area.  */

  srtm_bit_pack (water, 0, 32, 0);


  /*  Open the output file.  */

  sprintf (ofile, "%s%1csrtm3%1c%s.cte", dir, SEPARATOR, SEPARATOR, argv[1]);

  if ((ofp = fopen64 (ofile, "wb")) == NULL)
    {
      perror (ofile);
      exit (-1);
    }


  /*  Write the (minimalist) ASCII header.  */


  memset (header_block, 0, HEADER_SIZE);

  t = time (&t);
  cur_tm = gmtime (&t);

  sprintf (header_block, "[HEADER SIZE] = %d\n", HEADER_SIZE);
  sprintf (&header_block[strlen (header_block)], "[VERSION] = %s\n", VERSION);
  sprintf (&header_block[strlen (header_block)], "[ZLIB VERSION] = %s\n", zlibVersion ());
  sprintf (&header_block[strlen (header_block)], "[CREATION DATE] = %s", asctime (cur_tm));
  sprintf (&header_block[strlen (header_block)], "[END OF HEADER]\n");


  fwrite (header_block, HEADER_SIZE, 1, ofp);


  /*  Set the default for all map addresses to 2 (undefined).  Also, write the blank map area out to the
      file to save the space.  */

  for (i = 0 ; i < 180 ; i++)
    {
      for (j = 0 ; j < 360 ; j++)
        {
          srtm_double_bit_pack (map, (i * 360 + j) * 36, 36, 2);
        }
    }
  fseeko64 (ofp, (NV_INT64) HEADER_SIZE, SEEK_SET);
  fwrite (map, MAP_BYTES, 1, ofp);


  /*  Loop through -90 to 90 lat.  */

  for (i = -90 ; i < 90 ; i++)
    {
      lathem = 'N';
      if (i < 0) lathem = 'S';


      /*  Shift into the 0 to 180 world.  */

      shift_lat = i + 90;


      /*  Loop through the entire range of longitudes.  */

      for (j = -180 ; j < 180 ; j++)
        {
          lonhem = 'E';
          if (j < 0) lonhem = 'W';


          /*  Shift into the 0 to 360 world.  */

          shift_lon = j + 180;


          /*  Look for the file.  */

          sprintf (string, "%s%1c%1c%02d%1c%03d.hgt", argv[1], SEPARATOR, lathem, abs (i), lonhem, abs (j));


          /*  If we can open the file, read and process it.  */

          if ((fp = fopen (string, "rb")) != NULL)
            {
              prev_value = -1;
              pos = 0;


              /*  Note that we're only going to 1200 not 1201 because we don't need the redundant data.  */

              for (k = 0 ; k < 1200 ; k++)
                {
                  /*  Read one row (all 1201).  */

                  fread (row[k], 1201 * sizeof (NV_INT16), 1, fp);

                  for (m = 0 ; m < 1200 ; m++)
                    {
                      /*  If we're on a little endian system we need to swap the bytes.  */

                      if (swap)
                        {
#ifdef __GNUC__
                          swab (&row[k][m], &row[k][m], 2);
#else
                          _swab ((NV_CHAR *) &row[k][m], (NV_CHAR *) &row[k][m], 2);
#endif
                        }
                    }
                }


              first = 1;
              ndx = 0;
              min_diff = 32767;
              max_diff = -32768;
              hit_land = 0;
              hit_water = 0;


              /*  Loop through the cell.  */

              for (k = 0 ; k < 1200 ; k++)
                {

                  /*  Snake dance test.  */

                  if (!(k % 2))
                    {
                      /*  West to east.  */

                      for (m = 0 ; m < 1200 ; m++)
                        {
                          if (row[k][m] != -32768)
                            {
                              /*  Set the "hit" flags.  */

                              if (row[k][m])
                                {
                                  hit_land = 1;
                                }
                              else
                                {
                                  hit_water = 1;
                                }


                              /*  First time through set the last_val to start_val.  */

                              if (first)
                                {
                                  start_val = row[k][m];
                                  last_val = start_val;
                                  first = 0;
                                }
                              diff = row[k][m] - last_val;
                              if (diff > max_diff) max_diff = diff;
                              if (diff < min_diff) min_diff = diff;
                              last_val = row[k][m];
                              delta[ndx++] = diff;
                            }
                          else
                            {
                              /*  From what I've seen, -32768 means land but no defined elevation.  */

                              hit_land = 1;
                              delta[ndx++] = -32768;
                            }
                        }
                    }
                  else
                    {

                      /*  East to west.  */

                      for (m = 1199 ; m >= 0 ; m--)
                        {
                          if (row[k][m] != -32768)
                            {
                              /*  Set the "hit" flags.  */

                              if (row[k][m])
                                {
                                  hit_land = 1;
                                }
                              else
                                {
                                  hit_water = 1;
                                }


                              /*  First time through set the last_val to start_val.  */

                              if (first)
                                {
                                  start_val = row[k][m];
                                  last_val = start_val;
                                  first = 0;
                                }
                              diff = row[k][m] - last_val;
                              if (diff > max_diff) max_diff = diff;
                              if (diff < min_diff) min_diff = diff;
                              last_val = row[k][m];
                              delta[ndx++] = diff;
                            }
                          else
                            {
                              /*  From what I've seen, -32768 means land but no defined elevation.  */

                              hit_land = 1;
                              delta[ndx++] = -32768;
                            }
                        }
                    }
                }


              /*  All water cell.  */

              if (!hit_land && hit_water)
                {
                  srtm_double_bit_pack (map, (shift_lat * 360 + shift_lon) * 36, 36, 0);
                }


              /*  Land and water or all land cell.  */

              else
                {
                  /*  The bias is the negative of the minimum difference.  We bias so we don't have to play with
                      sign extension in the bit unpacking.  */

                  bias = -min_diff;


                  /*  Add two to the max difference to allow room for the null value.  */

                  max_diff += (bias + 2);


                  /*  Compute the number of bits needed to store a delta.  */

                  num_bits = NINT (log10 ((NV_FLOAT64) max_diff) / LOG2 + 0.5L);
                  null_val = NINT (pow (2.0L, (NV_FLOAT64) num_bits)) - 1;


                  /*  Compute the total bytes needed to store the block.  */

                  total_bits = 16 + 16 + 4 + 1200 * 1200 * num_bits;
                  total_bytes = total_bits / 8;
                  if (total_bits % 8) total_bytes++;


                  /*  Allocate the uncompressed memory block.  */

                  in_buf = (NV_U_BYTE *) calloc (total_bytes, 1);
                  if (in_buf == NULL)
                    {
                      perror ("Allocating in_buf");
                      exit (-1);
                    }


                  /*  Allocate the compressed memory block.  */

                  out_bytes = total_bytes + NINT ((NV_FLOAT32) total_bytes * 0.10) + 12;
                  out_buf = (NV_U_BYTE *) calloc (out_bytes, 1);
                  if (out_buf == NULL)
                    {
                      perror ("Allocating out_buf");
                      exit (-1);
                    }


                  /*  Pack the internal header.  */

                  pos = 0;
                  srtm_bit_pack (in_buf, pos, 16, start_val); pos += 16;
                  srtm_bit_pack (in_buf, pos, 16, bias); pos += 16;
                  srtm_bit_pack (in_buf, pos, 4, num_bits); pos += 4;


                  /*  Pack the deltas.  */

                  for (k = 0 ; k < 1200 * 1200 ; k++)
                    {
                      if (delta[k] == -32768)
                        {
                          delta[k] = null_val;
                        }
                      else
                        {
                          delta[k] += bias;
                        }
                      srtm_bit_pack (in_buf, pos, num_bits, delta[k]); pos += num_bits;
                    }


                  /*  Compress at maximum level.  */

                  n = compress2 (out_buf, &out_bytes, in_buf, total_bytes, 9);
                  if (n)
                    {
                      fprintf (stderr, "Error %d compressing record\n", n);
                      exit (-1);
                    }
                  free (in_buf);


                  /*  Pack the header.  */

                  pos = 0;
                  srtm_bit_pack (head, pos, 3, 1); pos += 3;
                  srtm_bit_pack (head, pos, 30, out_bytes); pos += 30;
                  srtm_bit_pack (head, pos, 31, total_bytes);


                  /*  Get the address where we're going to write the compressed block.  */

                  fseek (ofp, 0LL, SEEK_END);
                  lpos = ftell (ofp);


                  /*  Write the header to the file.  */

                  fwrite (head, 8, 1, ofp);


                  /*  Write the buffer to the file.  */

                  fwrite (out_buf, out_bytes, 1, ofp);
                  free (out_buf);


                  /*  Save the address of the block to the map.  */

                  srtm_double_bit_pack (map, (shift_lat * 360 + shift_lon) * 36, 36, lpos);
                }

              fclose (fp);


              /*  Set the block map value to the block number (1-6 for Africa, Australia, Eurasia, Islands, 
                  North_America, or South_America respectively).  */

              block_map[shift_lat * 360 + shift_lon] = block;


              fprintf (stderr, "block: %s   lon: %03d   lat: %03d       \r", argv[1], j, i);
              fflush (stderr);
            }
        }
    }


  /*  Write the map.  */

  fseek (ofp, (NV_INT64) HEADER_SIZE, SEEK_SET);
  fwrite (map, MAP_BYTES, 1, ofp);


  fclose (ofp);


  /*  Write the block map.  */

  fseek (block_fp, 0, SEEK_SET);
  fwrite (block_map, sizeof (block_map), 1, block_fp);

  fclose (block_fp);


  fprintf (stderr, "%s processing complete             \n\n", argv[1]);
  fflush (stderr);


  return (0);
}