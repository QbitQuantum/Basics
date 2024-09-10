/* Need to write out global imagery */
static void write_global_imagery()
{
   int i,size,pixel,decimal,negative;
   int strlen=3;
   char *lambda;
   char atot_image_filename[100];
   char aph_image_filename[100];
   char ady_image_filename[100];
   char bb_image_filename[100];
   char tc_image_filename[100];
   char aph_ratio_image_filename[100];
   
   float *atot_lambda, *aph_lambda, *ady_lambda, *bb_lambda;

   gzFile *atot_file, *aph_file, *ady_file, *bb_file, *tc_file, *aph_ratio_file;

   size = width*height*sizeof(float); 

   for(i=0;i<NB;i++){
      atot_lambda = malloc(width*height*sizeof(float));
      aph_lambda = malloc(width*height*sizeof(float));
      ady_lambda = malloc(width*height*sizeof(float));
      bb_lambda = malloc(width*height*sizeof(float));
      lambda = ecvt(fwave[i],strlen,&decimal,&negative);
      /* IOP image filename based on wavelength and yymm */
      printf("Creating IOP outputs at %s nm ...\n", lambda);
      sprintf(atot_image_filename,"%s/atot_%s_%04d.flw.gz",OUTDIR,lambda,yymm);
      sprintf(aph_image_filename,"%s/aph_%s_%04d.flw.gz",OUTDIR,lambda,yymm);
      sprintf(ady_image_filename,"%s/ady_%s_%04d.flw.gz",OUTDIR,lambda,yymm);
      sprintf(bb_image_filename,"%s/bb_%s_%04d.flw.gz",OUTDIR,lambda,yymm);
      /* printf("%s\n",atot_image_filename);
      printf("%s\n",aph_image_filename);
      printf("%s\n",ady_image_filename);
      printf("%s\n",bb_image_filename);  */
      if ((atot_file = gzopen(atot_image_filename, "wb")) == NULL) {
         fprintf(stderr, "Could not open %s\n", atot_image_filename);
         exit(1);
      }
      if ((aph_file = gzopen(aph_image_filename, "wb")) == NULL) {
         fprintf(stderr, "Could not open %s\n", aph_image_filename);
         exit(1);
      } 
      if ((ady_file = gzopen(ady_image_filename, "wb")) == NULL) {
         fprintf(stderr, "Could not open %s\n", ady_image_filename);
         exit(1);
      }
      if ((bb_file = gzopen(bb_image_filename, "wb")) == NULL) {
         fprintf(stderr, "Could not open %s\n", bb_image_filename);
         exit(1);
      }  
      /* retrieve the individual bands from the BIP created in 
      main function */   
      for(pixel=0;pixel<width*height;pixel++){
         atot_lambda[pixel] = atot[(pixel*NB)+i];
         aph_lambda[pixel] = aph[(pixel*NB)+i];
         ady_lambda[pixel] = adg[(pixel*NB)+i];
         bb_lambda[pixel] = bb[(pixel*NB)+i];
      }
      
      /* now write out to file */
      gzwrite(atot_file, atot_lambda, size);
      gzwrite(aph_file, aph_lambda, size); 
      gzwrite(ady_file, ady_lambda, size);
      gzwrite(bb_file, bb_lambda, size); 
      
      /* close the files */ 
      gzclose(atot_file);
      gzclose(aph_file); 
      gzclose(ady_file);
      gzclose(bb_file); 
      
      /* free up the temporary array memory */
      free(atot_lambda);
      free(aph_lambda); 
      free(ady_lambda);
      free(bb_lambda); 
   }

   /* write out the global total-chlorophyll product and absorption ratio */
   sprintf(tc_image_filename,"%s/tc_%04d.flw.gz",OUTDIR,yymm);   
   sprintf(aph_ratio_image_filename,"%s/aph_ratio_%04d.flw.gz",OUTDIR,yymm);
   if ((tc_file = gzopen(tc_image_filename, "wb")) == NULL) {
      fprintf(stderr, "Could not open %s\n", tc_image_filename);
      exit(1);
   }
   if ((aph_ratio_file = gzopen(aph_ratio_image_filename, "wb")) == NULL) {
      fprintf(stderr, "Could not open %s\n", aph_ratio_image_filename);
      exit(1);
   }
   
   /* now write out to file */
   gzwrite(tc_file,TC,size);
   gzwrite(aph_ratio_file,aph_ratio,size);
   
   /* close the files */
   gzclose(tc_file);
   gzclose(aph_ratio_file);

   /* free up the BIP memory created in the main routine */
   free(atot);
   free(aph);
   free(adg);
   free(bb);
   free(TC);
   free(aph_ratio);
}