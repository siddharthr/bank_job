#include<highgui.h>
#include<cv.h>
# include "Serial.cpp"
# include "CenterDetector.cpp"
#include<math.h>
#include<iostream>
# include<windows.h>

// set correct corresponding values of n
void turnlargedegrees(int theta)
{
int n=0;
int sign=(theta/abs(theta));
theta = abs(theta);
if(theta > 30 && theta <=70) // turn 45
	n = 8;
else if(theta > 70 && theta <=115) // turn 90
	n=16;
else if(theta > 115 && theta <=155) // turn 135
	n=24;	
else	// turn 180
	n=32;
	
	
for(int i=0;i<n;i++)
	{
	if(sign==1)
		{serialWriteByte(4);Sleep(75);}		// sharp right
	else
		{serialWriteByte(5);Sleep(75);}
	}	

}


int main()
{
cout<<"Enter theta: ";	
int theta;
cin>>theta;
turnlargedegrees(theta);

}
