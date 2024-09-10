/* ----------------------------- MNI Header -----------------------------------
@NAME       : calculate_smoothness_ind
@INPUT      : fwhm_info - pointer to data for calculating smoothness
                             in GLM model fit
              lambda_buffer - pointer to residuals and info about smoothness
@OUTPUT     : fwhm_gaussian->fwhm, smoothness, int_smoothness
@RETURNS    : nothing
@DESCRIPTION: Calculates the sample covariance matrix at a given voxel
@CREATED    : Apr. 20, 1997, J. Taylor
@MODIFIED   : 
---------------------------------------------------------------------------- */
void calculate_smoothness_ind(Fwhm_Info *fwhm_info, Lambda *lambda_buffer)
{
   int ibuff, i, j;
   double *data;
   double avg, avg_sq;

   avg_sq = 0.0;

   for(i=0; i<lambda_buffer->num_dim; i++) {
      for(j=0; j<=i; j++) {
         fwhm_info->lambda->values[i][j] = 0.0;
      }
   }

   for(ibuff=0; ibuff<lambda_buffer->num_buffers; ibuff++) {

      data = fwhm_info->data[ibuff];

      if(lambda_buffer->num_dim == 2) {
         fwhm_info->deriv[0] = 0.5* ((data[lambda_buffer->index[3]] +
                                 data[lambda_buffer->index[2]]) -
                                (data[lambda_buffer->index[1]] +
                                 data[lambda_buffer->index[0]]));

         fwhm_info->deriv[1] = 0.5 * ((data[lambda_buffer->index[3]] +
                                 data[lambda_buffer->index[1]]) -
                                (data[lambda_buffer->index[2]] +
                                 data[lambda_buffer->index[0]]));
      }
      else if(lambda_buffer->num_dim == 3) {

         fwhm_info->deriv[0] = 0.25 * ((data[lambda_buffer->index[7]] +
                                 data[lambda_buffer->index[6]] +
                                 data[lambda_buffer->index[5]] + 
                                 data[lambda_buffer->index[4]]) -
                                (data[lambda_buffer->index[3]] +
                                 data[lambda_buffer->index[2]] + 
                                 data[lambda_buffer->index[1]] +
                                 data[lambda_buffer->index[0]]));

         fwhm_info->deriv[1] = 0.25 * ((data[lambda_buffer->index[7]] +
                                 data[lambda_buffer->index[6]] +
                                 data[lambda_buffer->index[3]] + 
                                 data[lambda_buffer->index[2]]) -
                                (data[lambda_buffer->index[5]] +
                                 data[lambda_buffer->index[4]] + 
                                 data[lambda_buffer->index[1]] +
                                 data[lambda_buffer->index[0]]));
      
         fwhm_info->deriv[2] = 0.25 * ((data[lambda_buffer->index[7]] +
                                 data[lambda_buffer->index[5]] +
                                 data[lambda_buffer->index[3]] + 
                                 data[lambda_buffer->index[1]]) -
                                (data[lambda_buffer->index[6]] +
                                 data[lambda_buffer->index[4]] + 
                                 data[lambda_buffer->index[2]] +
                                 data[lambda_buffer->index[0]]));
      }
      else if (lambda_buffer->num_dim == 4) {
         fwhm_info->deriv[0] = 0.125 * ((data[lambda_buffer->index[15]] +
                                 data[lambda_buffer->index[14]] +
                                 data[lambda_buffer->index[13]] + 
                                 data[lambda_buffer->index[12]] +
                                 data[lambda_buffer->index[11]] +
                                 data[lambda_buffer->index[10]] + 
                                 data[lambda_buffer->index[9]] +
                                 data[lambda_buffer->index[8]]) -
                                (data[lambda_buffer->index[7]] +
                                 data[lambda_buffer->index[6]] +
                                 data[lambda_buffer->index[5]] + 
                                 data[lambda_buffer->index[4]] +
                                 data[lambda_buffer->index[3]] +
                                 data[lambda_buffer->index[2]] + 
                                 data[lambda_buffer->index[1]] +
                                 data[lambda_buffer->index[0]]));

         fwhm_info->deriv[1] = 0.125 * ((data[lambda_buffer->index[15]] +
                                 data[lambda_buffer->index[14]] +
                                 data[lambda_buffer->index[13]] + 
                                 data[lambda_buffer->index[12]] +
                                 data[lambda_buffer->index[7]] +
                                 data[lambda_buffer->index[6]] + 
                                 data[lambda_buffer->index[5]] +
                                 data[lambda_buffer->index[4]]) -
                                (data[lambda_buffer->index[11]] +
                                 data[lambda_buffer->index[10]] +
                                 data[lambda_buffer->index[9]] + 
                                 data[lambda_buffer->index[8]] +
                                 data[lambda_buffer->index[3]] +
                                 data[lambda_buffer->index[2]] + 
                                 data[lambda_buffer->index[1]] +
                                 data[lambda_buffer->index[0]]));

         fwhm_info->deriv[2] = 0.125 * ((data[lambda_buffer->index[15]] +
                                 data[lambda_buffer->index[14]] +
                                 data[lambda_buffer->index[11]] + 
                                 data[lambda_buffer->index[10]] +
                                 data[lambda_buffer->index[7]] +
                                 data[lambda_buffer->index[6]] + 
                                 data[lambda_buffer->index[3]] +
                                 data[lambda_buffer->index[2]]) -
                                (data[lambda_buffer->index[13]] +
                                 data[lambda_buffer->index[12]] +
                                 data[lambda_buffer->index[9]] + 
                                 data[lambda_buffer->index[8]] +
                                 data[lambda_buffer->index[5]] +
                                 data[lambda_buffer->index[4]] + 
                                 data[lambda_buffer->index[1]] +
                                 data[lambda_buffer->index[0]]));

         fwhm_info->deriv[3] = 0.125 * ((data[lambda_buffer->index[15]] +
                                 data[lambda_buffer->index[13]] +
                                 data[lambda_buffer->index[11]] + 
                                 data[lambda_buffer->index[9]] +
                                 data[lambda_buffer->index[7]] +
                                 data[lambda_buffer->index[5]] + 
                                 data[lambda_buffer->index[3]] +
                                 data[lambda_buffer->index[1]]) -
                                (data[lambda_buffer->index[14]] +
                                 data[lambda_buffer->index[12]] +
                                 data[lambda_buffer->index[10]] + 
                                 data[lambda_buffer->index[8]] +
                                 data[lambda_buffer->index[6]] +
                                 data[lambda_buffer->index[4]] + 
                                 data[lambda_buffer->index[2]] +
                                 data[lambda_buffer->index[0]]));

      }

      if (fwhm_info->is_gaussian == FALSE) {
         avg = 0.0;
         for(i=0; i<lambda_buffer->num_check; i++) {
            avg += data[lambda_buffer->index[i]];
         }
         avg /= lambda_buffer->num_check;            
      
         avg_sq += avg * avg;
      }

      for(i=0; i<lambda_buffer->num_dim; i++) {
         for(j=0; j<=i; j++) {

            fwhm_info->lambda->values[i][j] +=\
               fwhm_info->deriv[i] * fwhm_info->deriv[j];

            if (fwhm_info->lambda_pool != NULL) {
               fwhm_info->lambda_pool->values[i][j] +=\
                  fwhm_info->deriv[i] * fwhm_info->deriv[j];
            }
         }
      }

   }

   if (fwhm_info->is_gaussian == FALSE) {
      for(i=0; i<lambda_buffer->num_dim; i++) {
         for(j=0; j<=i; j++) {
            fwhm_info->lambda->values[i][j] /= avg_sq;
         }
      }
   }

   for(i=0; i<lambda_buffer->num_dim; i++) {
      for(j=lambda_buffer->num_dim-1; j>i; j--) {
         fwhm_info->lambda->values[i][j] = fwhm_info->lambda->values[j][i];
      }
   }

   fwhm_info->smoothness = sqrt(determinant(fwhm_info->lambda));

   if(fwhm_info->smoothness > 0.0)
      fwhm_info->int_lambda += fwhm_info->smoothness;

   fwhm_info->smoothness *= fwhm_info->constant;

   if(fwhm_info->smoothness > 0.0) {
      fwhm_info->fwhm = pow(fwhm_info->smoothness, 1.0/lambda_buffer->num_dim);
   }
   else
      fwhm_info->fwhm = INVALID_DATA;

   if(fwhm_info->fwhm != INVALID_DATA) {
      fwhm_info->fwhm = (lambda_buffer->constant / fwhm_info->fwhm);
   }
   else
      fwhm_info->fwhm = INVALID_DATA;

   if (fwhm_info->fwhm != INVALID_DATA)
      fwhm_info->num_calc++;

   return;
}