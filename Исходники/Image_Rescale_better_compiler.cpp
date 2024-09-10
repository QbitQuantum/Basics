/*****************************************************
** 不要修改下面的任何函数和代码！！！
**
**
**  如果需要，你可以阅读这些代码，或调用它们，或copy其中的部分。
** （注意不要让它们过多的局限你的修改思路）
** 
**  但是，请仔细阅读下面函数中的注释.
**  便于你理解 slow_rescale()是如何实现图片放大的
*****************************************************/
unsigned char *slow_rescale(unsigned char *src, int src_x, int src_y, int dest_x, int dest_y)
{
 /*
   图像数据类似于一个矩阵，矩阵的宽和高分别就是图像的宽（x方向长度）和高（y方向长度）
   每个矩阵的元素就是图像中的一个像素点，记录的是这个点的颜色
   但一个颜色需要用3个8位的元素分别记录构成这个颜色的RGB值。

   因此，假设图像的宽为sx，高为sy
   那么存储图像中所有像素的颜色信息需要sx * sy * 3个字节
   
   在本实验中，PPM图像将所有信息按行顺序存放在一维数组中 
   [(0,0) (1,0) (2,0) ... (sx-1,0) (0,1) (1,1) ... (sx-1,1) ... ... ... (sx-1,sy-1)]
   注意：这里的每个（x，y）代表一个像素，而真正存放这个像素的地址空间是连续的3个字节。.

   本文件中提供的 getPixel() 和 setPixel() 可以用来存取图像的像素颜色.
   你也可以写你字节的存取函数或甚至不使用存取函数以达到更快的速度

   ----------------------
   双线性插值放大算法思路：
   
   我们提供分辨率较小（？？？）的实验图片和一个大的目标分辨率（1920x1080）.

   因此需要用插值的方法从小图像的颜色计算出大图像的颜色。

   （1）计算目标图像和源图像的宽高比值.
  
   例如源图像的宽高为 (src_x, src_y)
   目标图像的宽高为   (dst_x, dst_y):
	
   则： 
   step_x=src_x/dst_x;
   step_y=src_y/dst_y;

   例如： 源(10 x 10) 和目标 (25 x 25) 可计算出step_x=step_y=0.4

   （2）源图像中的0.4个像素将要“变”为目标图像中的一个像素！

   也就是说，我们需要进行下列赋值：
   dst(0,0) <- src(0,0)
   dst(0,1) <- src(0,0.4)
   dst(0,2) <- src(0,0.8)
   dst(0,3) <- src(0,1.2)
   .
   .
   .
   dst(1,0) <- src(0.4,0)
   dst(1,1) <- src(0.4,0.4)
   .
   .
   等等
   
    
   但是, src(0.4,0.4) 这样以小数为下标的像素点并不是真实存在的。
   所以， 需要插值。

   （3） 插值的方法就是找到这个小数下标的上下左右共四个最近的整数下标像素点。如下图:
   
   对于 src(0.4,0.4)找到的4个点就是N1-N4:
                          
                                 N1               T1                       N2
                               src(0,0) -----------*----------------------src(1,0)
                                                   |
                                                   |
                                                   |
                                                src(0.4,0.4)
                                                   |
                                                   |
                                                   |
                                                   |
                                                   |
                                                   |
                                                   |
                              src(0,1)-------------*----------------------src(1,1)
                                 N3                T2                       N4

   
   利用N1和N2的颜色，以及根据0.4和“0”“1”之间各自的距离，可以插值计算得到T1的颜色,
   （即0.6*N1 + 0.4*N2 = T1)
   类似的，
   利用N3和N4的颜色，可以插值计算得到T2的颜色,
   利用T1和T2的颜色，可以插值计算得到最终所需要的src(0.4,0.4)的颜色,
   
   （4）注意这里的“颜色”都需要分RGB三个字节分别进行计算。

   而当源或目标分辨率很大的时候，计算次数十分庞大。所以，优化是十分必要的。

   下面是一个十分“不优化”的函数。你可以将之作为“反例”进行参考。
   重要的是只要你理解上面的插值过程，你就可以完成你自己的fast函数了！

 */

 double step_x,step_y;			// Step increase as per instructions above
 unsigned char R1,R2,R3,R4;		// Colours at the four neighbours
 unsigned char G1,G2,G3,G4;
 unsigned char B1,B2,B3,B4;
 double RT1, GT1, BT1;			// Interpolated colours at T1 and T2
 double RT2, GT2, BT2;
 unsigned char R,G,B;			// Final colour at a destination pixel
 unsigned char *dst;			// Destination image - must be allocated here! 
 int x,y;				// Coordinates on destination image
 double fx,fy;				// Corresponding coordinates on source image
 double dx,dy;			// Fractional component of source image coordinates

 dst=(unsigned char *)calloc(dest_x*dest_y*3,sizeof(unsigned char));   // Allocate and clear destination image
 if (!dst) return(NULL);					       // Unable to allocate image

 step_x=(double)(src_x-1)/(double)(dest_x-1);
 step_y=(double)(src_y-1)/(double)(dest_y-1);

 for (x=0;x<dest_x;x++)			// Loop over destination image
  for (y=0;y<dest_y;y++)
  {
   fx=x*step_x;
   fy=y*step_y;
   dx=fx-(int)fx;
   dy=fy-(int)fy;   
   getPixel(src,floor(fx),floor(fy),src_x,&R1,&G1,&B1);	// get N1 colours
   getPixel(src,ceil(fx),floor(fy),src_x,&R2,&G2,&B2);	// get N2 colours
   getPixel(src,floor(fx),ceil(fy),src_x,&R3,&G3,&B3);	// get N3 colours
   getPixel(src,ceil(fx),ceil(fy),src_x,&R4,&G4,&B4);	// get N4 colours
   // Interpolate to get T1 and T2 colours
   RT1=(dx*R2)+(1-dx)*R1;
   GT1=(dx*G2)+(1-dx)*G1;
   BT1=(dx*B2)+(1-dx)*B1;
   RT2=(dx*R4)+(1-dx)*R3;
   GT2=(dx*G4)+(1-dx)*G3;
   BT2=(dx*B4)+(1-dx)*B3;
   // Obtain final colour by interpolating between T1 and T2
   R=(unsigned char)((dy*RT2)+((1-dy)*RT1));
   G=(unsigned char)((dy*GT2)+((1-dy)*GT1));
   B=(unsigned char)((dy*BT2)+((1-dy)*BT1));
   // Store the final colour
   setPixel(dst,x,y,dest_x,R,G,B);
  }
 return(dst);
}