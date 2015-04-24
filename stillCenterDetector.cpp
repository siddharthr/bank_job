#include<highgui.h>
#include<cv.h>
#include <cv.hpp>
#include<iostream>
# include<math.h>
using namespace cv;
using namespace std;



Point centerDetect(Mat imgoriginal, char targetcolor)
{
// b, g, r
int ythresh[3]={90, 130, 120};   // correct
int bthresh[3]={95, 80, 80}; 	// correct

int rthresh[3]={50, 50, 120};
int gthresh[3]={100, 100, 30};
int pthresh[3]={100, 50, 120};  //correct
int kthresh[3]={50, 50, 50}; //black

Point answer;

if(!imgoriginal.data)
	{
	cout<<"\nERR: CenterDetector.cpp - no data in original img! ";
	}

Mat matcopy = imgoriginal.clone();
//IplImage* src=cvLoadImage(name,1); // Loading the image
IplImage * src = new IplImage();
*src = matcopy;


CvScalar s,c, temp; // create two scalar variables
// cout<<"\n ColourDetect - Searching for: "<<targetcolor;

for(int i=0;i<(src->height)-30;i++)//In the 2D array of the img..count till the vertical pixel reaches the height of src
	{
	for(int j=0;j<(src->width);j++)//In the 2D array of the img..count till orizontal pixel reaches the width of src
		{
		s=cvGet2D(src,i,j); //Get the RGB values of src's i,j into a scalar s
		
		
	
		if(targetcolor=='y')
			{ 
			if((s.val[2] > ythresh[2]) && (s.val[1] > ythresh[1]) && (s.val[0] < ythresh[0])) 
				{ 
		//		if(cvGet2D(src, i+15, j).val[2] > ythresh[2] && cvGet2D(src, i+15, j).val[1] > ythresh[1] && cvGet2D(src, i+15, j).val[0] < ythresh[0])
					if(cvGet2D(src, i+40, j).val[2] > ythresh[2] && cvGet2D(src, i+40, j).val[1] > ythresh[1] && cvGet2D(src, i+40, j).val[0] < ythresh[0])
						{
						cout<<"\nYellow - Center i(y-axis): "<<i+28<<"\tj(x-axis): "<<j;
						return Point(j, i+28);
						}
				}
			}
			
		else if(targetcolor=='b')
			{ 
			if((s.val[2] < bthresh[2]) && (s.val[1] < bthresh[1]) && (s.val[0] > bthresh[0])) // r[2], g[1], b[0]
				{ 
				if(cvGet2D(src, i+16, j).val[2] < bthresh[2] && cvGet2D(src, i+16, j).val[1] < bthresh[1] && cvGet2D(src, i+16, j).val[0] > bthresh[0])
		//			if(cvGet2D(src, i+30, j).val[2] > bthresh[2] && cvGet2D(src, i+30, j).val[1] > bthresh[1] && cvGet2D(src, i+30, j).val[0] < bthresh[0])
						{
						cout<<"\nBlue Center: ( "<<j+1<<", "<<i+11<<" )";
						return Point(j+1, i+11);
						}
				}
			}
			
		else if(targetcolor=='p')
			{ 
			if((s.val[2] > pthresh[2]) && (s.val[1] < pthresh[1]) && (s.val[0] > pthresh[0])) 
				{ 
				if(cvGet2D(src, i+16, j).val[2] > pthresh[2] && cvGet2D(src, i+16, j).val[1] < pthresh[1] && cvGet2D(src, i+16, j).val[0] > pthresh[0])
		//			if(cvGet2D(src, i+4, j+2).val[2] > pthresh[2] && cvGet2D(src, i+4, j+2).val[1] < pthresh[1] && cvGet2D(src, i+4, j+2).val[0] > pthresh[0])
						{
						cout<<"\nPink Center : ( "<<j<<", "<<i+9<<" )";
						return Point(j, i+9);
						}
				}
			}
			
		else if(targetcolor=='r')
			{ 
			if((s.val[2] > rthresh[2]) && (s.val[1] < rthresh[1]) && (s.val[0] < rthresh[0])) 
				{ 
				if(cvGet2D(src, i+15, j).val[2] > rthresh[2] && cvGet2D(src, i+15, j).val[1] < rthresh[1] && cvGet2D(src, i+15, j).val[0] < rthresh[0])
					if(cvGet2D(src, i+35, j).val[2] > rthresh[2] && cvGet2D(src, i+35, j).val[1] < rthresh[1] && cvGet2D(src, i+35, j).val[0] < rthresh[0])
						{
						cout<<"\nRed - Center i(y-axis): "<<i+15<<"\tj(x-axis): "<<j;
						return Point(j+5, i+27);
						}
				}
			}		
			
		else if(targetcolor=='g')
			{ 
			if((s.val[2] < gthresh[2]) && (s.val[1] > gthresh[1]) && (s.val[0] < gthresh[0])) 
				{ 
				if(cvGet2D(src, i+15, j).val[2] < gthresh[2] && cvGet2D(src, i+15, j).val[1] > gthresh[1] && cvGet2D(src, i+15, j).val[0] < gthresh[0])
		//			if(cvGet2D(src, i+40, j).val[2] < gthresh[2] && cvGet2D(src, i+40, j).val[1] > gthresh[1] && cvGet2D(src, i+40, j).val[0] < gthresh[0])
						{
						cout<<"\nGreen - Center i(y-axis): "<<i+27<<"\tj(x-axis): "<<j;
						return Point(j, i+27);
						}
				}
			}	

		else if(targetcolor=='k')
			{ 
			if((s.val[2] < kthresh[2]) && (s.val[1] < kthresh[1]) && (s.val[0] < kthresh[0])) 
				{ 
				if(cvGet2D(src, i+15, j+15).val[2] < kthresh[2] && cvGet2D(src, i+15, j+15).val[1] < kthresh[1] && cvGet2D(src, i+15, j+15).val[0] < kthresh[0])
					if(cvGet2D(src, i+30, j).val[2] < kthresh[2] && cvGet2D(src, i+30, j).val[1] < kthresh[1] && cvGet2D(src, i+30, j).val[0] < kthresh[0])
						{
						cout<<"\nBlack - Center i(y-axis): "<<i+30<<"\tj(x-axis): "<<j;
						return Point(j, i+30);
						}
				}
			}
			
		else  // default - all white
			{
			c.val[2]=255; 
			c.val[1]=255;
			c.val[0]=255;
			cout<<"\nAnother color!"; 
			return Point(0,0);
			}					

		}
	}


cout<<"\nCenterDetect - Failure ..1 : "<<targetcolor;

for(int i=0;i<(src->height);i++)//top to bottom
	{
	for(int j=0;j<(src->width);j++)//left to right
		{
		s=cvGet2D(src,i,j); //Get the RGB values of src's i,j into a scalar s
		
		if(targetcolor=='b')
			{ 
			if((s.val[2] < bthresh[2]) && (s.val[1] < bthresh[1]) && (s.val[0] > bthresh[0])) // r[2], g[1], b[0]
				{ 
		//		if(cvGet2D(src, i+15, j).val[2] < bthresh[2] && cvGet2D(src, i+15, j).val[1] < bthresh[1] && cvGet2D(src, i+15, j).val[0] > bthresh[0])
		//			if(cvGet2D(src, i+30, j).val[2] > bthresh[2] && cvGet2D(src, i+30, j).val[1] > bthresh[1] && cvGet2D(src, i+30, j).val[0] < bthresh[0])
						{
						cout<<"\nPink Center : ( "<<j+4<<", "<<i+6<<" ) (2).";
						return Point(j+4, i+6);
						}
				}
			}	
			
		else if(targetcolor=='p')
			{ 
			if((s.val[2] > pthresh[2]) && (s.val[1] < pthresh[1]) && (s.val[0] > pthresh[0])) 
				{ 
		//		if(cvGet2D(src, i+15, j).val[2] > pthresh[2] && cvGet2D(src, i+15, j).val[1] < pthresh[1] && cvGet2D(src, i+15, j).val[0] > pthresh[0])
		//			if(cvGet2D(src, i+30, j).val[2] > pthresh[2] && cvGet2D(src, i+30, j).val[1] < pthresh[1] && cvGet2D(src, i+30, j).val[0] > pthresh[0])
						{
						cout<<"\nPink Center : ( "<<j+5<<", "<<i+6<<" )  (2).";
						return Point(j+5, i+6);
						}
				}
			}	
	
	
		else if(targetcolor=='y')
			{ 
			if((s.val[2] > ythresh[2]) && (s.val[1] > ythresh[1]) && (s.val[0] < ythresh[0])) 
				{ 
		//		if(cvGet2D(src, i+15, j).val[2] > ythresh[2] && cvGet2D(src, i+15, j).val[1] > ythresh[1] && cvGet2D(src, i+15, j).val[0] < ythresh[0])
		//			if(cvGet2D(src, i+40, j).val[2] > ythresh[2] && cvGet2D(src, i+40, j).val[1] > ythresh[1] && cvGet2D(src, i+40, j).val[0] < ythresh[0])
						{
						cout<<"\nYellow - Center i(y-axis): "<<i+28<<"\tj(x-axis): "<<j;
						return Point(j, i+15);
						}
				}
			}
			

			
		else if(targetcolor=='r')
			{ 
			if((s.val[2] > rthresh[2]) && (s.val[1] < rthresh[1]) && (s.val[0] < rthresh[0])) 
				{ 
	//			if(cvGet2D(src, i+15, j).val[2] > rthresh[2] && cvGet2D(src, i+15, j).val[1] < rthresh[1] && cvGet2D(src, i+15, j).val[0] < rthresh[0])
	//				if(cvGet2D(src, i+40, j).val[2] > rthresh[2] && cvGet2D(src, i+40, j).val[1] < rthresh[1] && cvGet2D(src, i+40, j).val[0] < rthresh[0])
						{
						cout<<"\nRed - Center i(y-axis): "<<i+28<<"\tj(x-axis): "<<j;
						return Point(j, i+15);
						}
				}
			}		
			
		else if(targetcolor=='g')
			{ 
			if((s.val[2] < gthresh[2]) && (s.val[1] > gthresh[1]) && (s.val[0] < gthresh[0])) 
				{ 
		//		if(cvGet2D(src, i+15, j).val[2] < gthresh[2] && cvGet2D(src, i+15, j).val[1] > gthresh[1] && cvGet2D(src, i+15, j).val[0] < gthresh[0])
		//			if(cvGet2D(src, i+40, j).val[2] < gthresh[2] && cvGet2D(src, i+40, j).val[1] > gthresh[1] && cvGet2D(src, i+40, j).val[0] < gthresh[0])
						{
						cout<<"\nGreen - Center i(y-axis): "<<i+28<<"\tj(x-axis): "<<j;
						return Point(j, i+15);
						}
				}
			}	

		else if(targetcolor=='k')
			{ 
			if((s.val[2] < kthresh[2]) && (s.val[1] < kthresh[1]) && (s.val[0] < kthresh[0])) 
				{ 
		//		if(cvGet2D(src, i+15, j+15).val[2] < kthresh[2] && cvGet2D(src, i+15, j+15).val[1] < kthresh[1] && cvGet2D(src, i+15, j+15).val[0] < kthresh[0])
		//			if(cvGet2D(src, i+40, j).val[2] < kthresh[2] && cvGet2D(src, i+40, j).val[1] < kthresh[1] && cvGet2D(src, i+40, j).val[0] < kthresh[0])
						{
						cout<<"\nBlack - Center i(y-axis): "<<i+40<<"\tj(x-axis): "<<j;
						return Point(j, i+40);
						}
				}
			}
			
		else  // default - all white
			{
			c.val[2]=255; 
			c.val[1]=255;
			c.val[0]=255;
			cout<<"\nother color!"; 
			return Point(0,0);
			}					

		}
	}
	
cout<<"\n Center Detect - Dbl Fail...";

 
/*
cvNamedWindow( "Input", CV_WINDOW_AUTOSIZE ); //Create a window “Input”
cvShowImage( "Input", src ); //Display src in a window named “Input”
cvNamedWindow( "Output", CV_WINDOW_AUTOSIZE ); //Create a window “Output”
cvShowImage( "Output", copy ); //Display copy in a window named “Output”
*/
//cvReleaseImage( &src );
//cout<<"\nCD.cpp - released";

return Point(0,0);
}


int main()
{
// Mat img = colourDetect("realarena.jpg", 'b');

Mat img=imread("realarena.jpg", 1);
//Mat img=imread("sidarena4.jpg", 1);


if(!img.data)
		{
		cout<<"\nNo data..";
		Sleep(5000);
			return -1;
		}
	
	
cout<<"\nhas data..";


Point p = centerDetect(img, 'y');

circle( img, p, 1, Scalar(0,0,255), 3, 8, 0 );
namedWindow( "circles", 1 );
imshow( "circles", img );

// Sleep(5000);

cvWaitKey(); //Wait till the user presses a key or cvWaitKey(10) will wait for 10ms
}
/*
circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
namedWindow( "circles", 1 );
imshow( "circles", img );

*/


