int main(int argc, char **argv)
{
  double timeA, timeB;
  Sphere *spheres;
  Vec3 p,c,e;
  int n;
  
  timeA = omp_get_wtime();
  n = argc>1 ? atoi(argv[1]) : N; if(n<N)n=100;
  spheres = malloc(n*sizeof(*spheres));
  // position, radius, surface color, reflectivity, transparency, emission color
  Vec3_new(&p, 0, -10004, -20);
  Vec3_new1(&c, 0.2);
  Sphere_new0(&spheres[0], &p, 10000, &c, 0, 0.0);
  Vec3_new(&p, 0, 0, -20);
  Vec3_new(&c, 1.00, 0.32, 0.36);
  Sphere_new0(&spheres[1], &p, 4, &c, 1, 0.5);
  Vec3_new(&p, 5, -1, -15);
  Vec3_new(&c, 0.90, 0.76, 0.46);
  Sphere_new0(&spheres[2], &p, 2, &c, 1, 0.0);
  Vec3_new(&p, 5, 0, -25);
  Vec3_new(&c, 0.65, 0.77, 0.97);
  Sphere_new0(&spheres[3], &p, 3, &c, 1, 0.0);
  Vec3_new(&p, -5.5, 0, -15);
  Vec3_new(&c, 0.90, 0.90, 0.90);
  Sphere_new0(&spheres[4], &p, 3, &c, 1, 0.0);
  // light
  Vec3_new(&p, 0, 20, -30);
  Vec3_new0(&c);
  Vec3_new1(&e, 3);
  Sphere_new(&spheres[5], &p, 3, &c, 0, 0, &e);
  if(n>N){ int i,j,k; Real r,d; Vec3 v;
    srand48(13);
    for(i=N;i<n;i++){
      k=0;
      do{
        Vec3_new(&p, 12*drand48()-6,9*drand48()-4,-35*drand48()-15);
        r = 0.1 + drand48();
        for(j=0;j<i && r>=0.1;j++){
          Vec3_subs(&v,&spheres[j].center,&p);
          d=Vec3_length(&v)-spheres[j].radius;
          if(d<r)r=d;
        }
      }while(r<0.1 && ++k<1000);
      if(r>=0.1){
        Vec3_new(&c, rand()%4/3.0,rand()%4/3.0,rand()%4/3.0);
        Sphere_new0(&spheres[i], &p, r, &c,
          drand48()<0.8?0:1, drand48()<0.8?0:0.8);
      }else printf("#");
    }
  }
  if(argc>2){spheres[1].radius=0.4; spheres[1].radius2=0.16;}

  printf("Calculando...\n"); fflush(stdout);
  
  render(n, spheres);
  timeB = omp_get_wtime();
  double timeC = timeB - timeA;
  printf("Se ha calculado en %f segundos\n",timeC);
  free(spheres);

  return 0;
}