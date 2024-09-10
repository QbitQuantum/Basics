int main(int argc, char** argv)
{
	IplImage* img = NULL;
	IplImage* dst = NULL;
	IplImage* dst2 = NULL;
	IplImage* dst3 = NULL;
	IplImage* dst4 = NULL;
	IplImage* dst5 = NULL;

	char* cha = "./temp/";//le dossier de base
	DIR* rep = NULL;
	struct dirent* fichierLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */
	struct dirent* repLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */
	char* ch;
	rep = opendir(cha);
	if (rep == NULL)
	{
		exit(1);
	}
	while((repLu = readdir(rep)) != NULL )
	{
		while (strcmp(repLu->d_name, ".") == 0 || strcmp(repLu->d_name, "..") == 0)
		{
			repLu = readdir(rep);
			printf("%s\n",repLu->d_name);
		}
		DIR* rep2 = NULL;
		ch = concat(cha,repLu->d_name);
		rep2 = opendir(ch);
		char* c = ch;
		c = concat(ch,"/");
		while ((fichierLu = readdir(rep2)) != NULL )
		{
			if (strcmp(fichierLu->d_name, ".") != 0 && strcmp(fichierLu->d_name, "..") != 0)
			{
				printf("Le fichier lu s'appelle %s\n", fichierLu->d_name);

				ch = concat(c,fichierLu->d_name);
				img = cvLoadImage( ch , CV_LOAD_IMAGE_COLOR);
				if (img == NULL)
				{
					printf("Oups j'ai eu un problème.\n");
					return -1;
				}

				IplImage *hsv;
				hsv = cvCloneImage(img);
				cvCvtColor(img, hsv, CV_BGR2HSV);
				IplImage *hsv2;
				hsv2 = cvCloneImage(img);
				cvCvtColor(img, hsv2, CV_BGR2HSV);
				IplImage *hsv3;
				hsv3 = cvCloneImage(img);
				cvCvtColor(img, hsv3, CV_BGR2HSV);

				IplImage *maskrouge;
				maskrouge = cvCreateImage(cvGetSize(img), img->depth, 1);
				IplImage *maskbleu;
				maskbleu = cvCreateImage(cvGetSize(img), img->depth, 1);
				IplImage *maskblanc;
				maskblanc = cvCreateImage(cvGetSize(img), img->depth, 1);

				int h1=0, s1=200, v1= 80;
				int h2=106, s2=138;
				int h3=350, s3=83;
				cvInRangeS(hsv, cvScalar(h1 -tolerance, s1 - tolerance, v1 - tolerance, 0.0), cvScalar(h1 + tolerance, s1 + tolerance, v1 + tolerance, 0.0), maskrouge);
				cvInRangeS(hsv2, cvScalar(h2 -tolerance, s2 - tolerance, 0, 0.0), cvScalar(h2 + tolerance, s2 + tolerance, 255, 0.0), maskbleu);
				cvInRangeS(hsv3, cvScalar(h3 -tolerance, s3 - tolerance, 0, 0.0), cvScalar(h3 + tolerance, s3 + tolerance, 255, 0.0), maskblanc);

				//IplConvKernel *kernel;
				//kernel = cvCreateStructuringElementEx(5, 5, 2, 2, CV_SHAPE_ELLIPSE, NULL);

				//cvDilate(maskrouge, maskrouge, kernel, 1);
				//cvDilate(maskbleu, maskbleu, kernel, 1);
				//cvDilate(maskblanc, maskblanc, kernel, 1);cvDilate(maskrouge, maskrouge, kernel, 1);
				//cvDilate(maskbleu, maskbleu, kernel, 1);
				//cvDilate(maskblanc, maskblanc, kernel, 1);
				//cvErode(maskrouge, maskrouge, kernel, 1);

				// affichage

				dst = cvCreateImage(cvSize( img->width / 6, img->height / 6 ), img->depth,img->nChannels );
				dst2 = cvCreateImage(cvSize( maskrouge->width / 6, maskrouge->height / 6 ), maskrouge->depth,maskrouge->nChannels );
				dst3 = cvCreateImage(cvSize( maskbleu->width / 6, maskbleu->height / 6 ), maskbleu->depth,maskbleu->nChannels );
				dst4 = cvCreateImage(cvSize( maskblanc->width / 6, maskblanc->height / 6 ), maskblanc->depth,maskblanc->nChannels );
				//dst5 = cvCreateImage(cvSize( hsv->width / 2, hsv->height / 2 ), hsv->depth, hsv->nChannels );

				cvResize(img, dst, CV_INTER_AREA );
				cvResize(maskrouge, dst2, CV_INTER_AREA );
				cvResize(maskbleu, dst3, CV_INTER_AREA );
				cvResize(maskblanc, dst4, CV_INTER_AREA );
				//cvResize(hsv, dst5, CV_INTER_AREA );

				cvShowImage("test1",dst);
				cvShowImage("test2",dst2);
				cvShowImage("test3",dst3);
				cvShowImage("test4",dst4);
				//cvShowImage("test5",dst5);
				cvMoveWindow("test1" ,0,0);
				cvMoveWindow("test2" ,dst->width,dst->height+60);
				cvMoveWindow("test3" ,dst->width,0);
				cvMoveWindow("test4" ,0,dst->height+60);
				//cvMoveWindow("test5" , 0, 0);

				cvWaitKey(0);

				cvReleaseImage(&maskrouge);
				cvReleaseImage(&maskbleu);
				cvReleaseImage(&maskblanc);
				cvReleaseImage(&hsv);
				cvReleaseImage(&hsv2);
				cvReleaseImage(&hsv3);
				cvReleaseImage(&img);
				cvReleaseImage(&dst);
				cvReleaseImage(&dst2);
				cvReleaseImage(&dst3);
				cvReleaseImage(&dst4);
				cvReleaseImage(&dst5);
				cvDestroyWindow("test1");
				cvDestroyWindow("test2");
				cvDestroyWindow("test3");
				cvDestroyWindow("test4");
				//cvDestroyWindow("test5");
			}
		}
	}


	if (closedir(rep) == -1)
		exit(-1);

	return 0;
}