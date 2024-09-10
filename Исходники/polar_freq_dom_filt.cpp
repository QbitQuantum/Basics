void PolarFreqDomainFilter::Initialize(void)
{
   int i;
   int samp_num, bin_num;
   char line_buf[100];
   char *item;
   double tmp_nsexp, frac_part, int_part;
   double min_data_freq, max_data_freq;
   double left_freq, right_freq;
   double bin_freq, left_val, right_val, slope, base;
   std::complex<float> *time_resp;
   //PointDataFile input_file;
   std::complex<float> exponent;
   std::complex<float> pseudo_complex;
   ofstream *resp_file;

   tmp_nsexp = log10(double(Fft_Size))/log10(2.0);
   frac_part = modf(tmp_nsexp, &int_part);

   double delta_f = 1.0/(Fft_Size*Dt_For_Fft);

   //------------------------------------------------------------
   //  initialize derived parameters

   Ns_Exp = int_part;

   Full_Buffer = new std::complex<float>[Fft_Size];
   for(i=0; i<Fft_Size; i++)
   {
      Full_Buffer[i] = std::complex<float>(0.0,0.0);
   }

   time_resp = new std::complex<float>[Fft_Size];
   for(i=0; i<Fft_Size; i++)
   {
      time_resp[i] = std::complex<float>(0.0,0.0);
   }
   FftDitNipo( time_resp, Fft_Size);

   Mag_Resp = new float[Fft_Size];
   Phase_Resp = new float[Fft_Size];

   //-----------------------------------------------------
   //  Read in the raw response data

   Magnitude_Data_File = new ifstream(Magnitude_Data_Fname, ios::in);
   *Magnitude_Data_File >> Num_Mag_Samps;
   Magnitude_Data_File->getline(line_buf,100);
   Raw_Magnitude_Resp = new float[Num_Mag_Samps];
   Freqs_For_Magnitude = new float[Num_Mag_Samps];
   for(samp_num=0;samp_num<Num_Mag_Samps; samp_num++)
   {
      Magnitude_Data_File->getline(line_buf,100);
      item = strtok(line_buf,",\n\t");
      Freqs_For_Magnitude[samp_num] = atof(item);
      item = strtok(NULL,",\n\t");
      Raw_Magnitude_Resp[samp_num] = atof(item);
   }
   Magnitude_Data_File->close();

   resp_file = new ofstream("mag_resp.txt\0", ios::out);

   min_data_freq = Mag_Freq_Scaling_Factor * Freqs_For_Magnitude[0];
   max_data_freq = Mag_Freq_Scaling_Factor * Freqs_For_Magnitude[Num_Mag_Samps-1];

   samp_num=-1;
   right_freq = Mag_Freq_Scaling_Factor * Freqs_For_Magnitude[0];
   right_val = pow(10.0,(Raw_Magnitude_Resp[0]/20.0));
   left_freq = -delta_f*Fft_Size/2;
   slope = right_val/(right_freq-left_freq);
   base = -left_freq*slope;

   for(bin_num=-Fft_Size/2;bin_num<0;bin_num++)
   {
      bin_freq = bin_num * delta_f;


      if(bin_freq < min_data_freq)
      //
      // put straight-line skirt on negative frequency portion
      // not covered by input data
      {
         Mag_Resp[Fft_Size+bin_num] = bin_freq * slope + base;
      }
      else
      //
      //  do negative-frequency portion that is covered by input data
      {
         if(bin_freq >= right_freq) 
         {
            samp_num++;
            left_freq = right_freq;
            right_freq = Mag_Freq_Scaling_Factor * Freqs_For_Magnitude[samp_num+1];
            left_val = pow(10.0, Raw_Magnitude_Resp[samp_num]/20.0);
            right_val = pow(10.0, Raw_Magnitude_Resp[samp_num+1]/20.0);
            slope = (right_val - left_val)/(right_freq - left_freq);
            base = left_val - left_freq*slope;
         }
         Mag_Resp[Fft_Size+bin_num] = bin_freq * slope + base;
      }
      *resp_file << bin_num << ", " << Mag_Resp[Fft_Size+bin_num] << endl;
   }

   //
   //  do the positive frequency portion which is covered by input data
   bin_freq = 0;
   bin_num = 0;
   while(bin_freq<max_data_freq && bin_num<Fft_Size/2)
   {
      bin_freq = bin_num * delta_f;
      if(bin_freq >= right_freq)
      {
         samp_num++;
         left_freq = right_freq;
         right_freq = Mag_Freq_Scaling_Factor * Freqs_For_Magnitude[samp_num+1];
         left_val = pow(10.0, Raw_Magnitude_Resp[samp_num]/20.0);
         right_val = pow(10.0, Raw_Magnitude_Resp[samp_num+1]/20.0);
         slope = (right_val - left_val)/(right_freq - left_freq);
         base = left_val - left_freq*slope;
      }
      Mag_Resp[bin_num] = bin_freq * slope + base;
      *resp_file << bin_num << ", " << Mag_Resp[bin_num] << endl;
      bin_num++;
   }
   //
   // put straight-line skirt on positive frequency portion not coverd by input data
   left_freq = Mag_Freq_Scaling_Factor * Freqs_For_Magnitude[Num_Mag_Samps-1];
   left_val = pow(10.0,(Raw_Magnitude_Resp[Num_Mag_Samps-1]/20.0));
   right_freq = delta_f*(Fft_Size-2)/2;
   slope = -left_val/(right_freq-left_freq);
   base = left_val-left_freq*slope;
   while(bin_num<Fft_Size/2)
   {
      bin_freq = bin_num * delta_f;
      Mag_Resp[bin_num] = bin_freq * slope + base;
      *resp_file << bin_num << ", " << Mag_Resp[bin_num] << endl;
      bin_num++;
   }
   resp_file->close();

   Phase_Data_File = new ifstream(Phase_Data_Fname, ios::in);
   *Phase_Data_File >> Num_Phase_Samps;
   Phase_Data_File->getline(line_buf,100);

   Raw_Phase_Resp = new float[Num_Phase_Samps];
   Freqs_For_Phase = new float[Num_Phase_Samps];

   for(samp_num=0;samp_num<Num_Phase_Samps; samp_num++)
   {
      Phase_Data_File->getline(line_buf,100);
      item = strtok(line_buf,",\n\t");
      Freqs_For_Phase[samp_num] = atof(item);
      item = strtok(NULL,",\n\t");
      Raw_Phase_Resp[samp_num] = atof(item);
   }
   Phase_Data_File->close();

   resp_file = new ofstream("Phase_resp.txt\0", ios::out);

   min_data_freq = Mag_Freq_Scaling_Factor * Freqs_For_Phase[0];
   max_data_freq = Mag_Freq_Scaling_Factor * Freqs_For_Phase[Num_Phase_Samps-1];

   samp_num=-1;
   right_freq = Phase_Freq_Scaling_Factor * Freqs_For_Phase[0];
   right_val = Raw_Phase_Resp[0];
   left_freq = -delta_f*Fft_Size/2;
   slope = right_val/(right_freq-left_freq);
   base = -left_freq*slope;

   for(bin_num=-Fft_Size/2;bin_num<0;bin_num++)
   {
      bin_freq = bin_num * delta_f;
      if(bin_freq < min_data_freq)
      //
      // put straight-line skirt on negative frequency portion
      // not covered by input data
      {
         //Phase_Resp[Fft_Size+bin_num] = bin_freq * slope + base;
         Phase_Resp[Fft_Size+bin_num] = Raw_Phase_Resp[0];
      }
      else
      //
      //  do negative-frequency portion that is covered by input data
      {
         if(bin_freq >= right_freq) 
         {
            samp_num++;
            left_freq = right_freq;
            right_freq = Phase_Freq_Scaling_Factor * Freqs_For_Phase[samp_num+1];
            left_val = Raw_Phase_Resp[samp_num];
            right_val = Raw_Phase_Resp[samp_num+1];
            slope = (right_val - left_val)/(right_freq - left_freq);
            base = left_val - left_freq*slope;
         }
         Phase_Resp[Fft_Size+bin_num] = bin_freq * slope + base;
      }
      *resp_file << bin_num << ", " << Phase_Resp[Fft_Size+bin_num] << endl;
   }

   //
   //  do the positive frequency portion which is covered by input data
   bin_freq = 0;
   bin_num = 0;
   while(bin_freq<max_data_freq && bin_num<Fft_Size/2)
   {
      bin_freq = bin_num * delta_f;
      if(bin_freq >= right_freq)
      {
         samp_num++;
         left_freq = right_freq;
         right_freq = Phase_Freq_Scaling_Factor * Freqs_For_Phase[samp_num+1];
         left_val = Raw_Phase_Resp[samp_num];
         right_val = Raw_Phase_Resp[samp_num+1];
         slope = (right_val - left_val)/(right_freq - left_freq);
         base = left_val - left_freq*slope;
      }
      Phase_Resp[bin_num] = bin_freq * slope + base;
      *resp_file << bin_num << ", " << Phase_Resp[bin_num] << endl;
      bin_num++;
   }
   //
   // put straight-line skirt on positive frequency portion not coverd by input data
   left_freq = Phase_Freq_Scaling_Factor * Freqs_For_Phase[Num_Phase_Samps-1];
   left_val = Raw_Phase_Resp[Num_Phase_Samps-1];
   right_freq = delta_f*(Fft_Size-2)/2;
   slope = -left_val/(right_freq-left_freq);
   base = left_val-left_freq*slope;
   while(bin_num<Fft_Size/2)
   {
      bin_freq = bin_num * delta_f;
      //Phase_Resp[bin_num] = bin_freq * slope + base;
      Phase_Resp[bin_num] = Raw_Phase_Resp[Num_Phase_Samps-1];
      *resp_file << bin_num << ", " << Phase_Resp[bin_num] << endl;
      bin_num++;
   }
   resp_file->close();
   //-----------------------------------------------------

}