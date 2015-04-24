#include<highgui.h>
#include<cv.h>
# include "Serial.cpp"
# include "CenterDetector.cpp"
#include<math.h>
#include<iostream>
# include<windows.h>
using namespace cv;

using namespace std;


Point redcenter, greencenter, yellowcenter, depocenter;
Point pinkcenter, bluecenter;
int angle;

// 00:22 am
//  2 + avoidance..


// YOU NEED TO SET THESE VALUES.. set from setDegrees.cpp
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
else
	n=32;
	
	
for(int i=0;i<n;i++)
	{
	if(sign==1)
		{serialWriteByte(4);Sleep(75);}		// sharp right
	else
		{serialWriteByte(5);Sleep(75);}
	}	

}

void move(Point dest)
{

VideoCapture cap(0); // open the default camera . -1 all cams? 1-webcam?
if(!cap.isOpened())  // check if we succeeded
    {
	cout<<"\nERROR-move: Camera Could not be found/ opened!";
	return;
	}
Sleep(2000);
int straight = 0;

while(1)
	{
	try
	{
	Mat frame;
	
	cap.grab();
	cap.retrieve(frame);
	
//	Mat matcopy = frame.clone();
//	imshow("matcopy", matcopy);	
//  need to rotate?
	
	
//	Point pinkcenter, bluecenter;
	
	/*
	pinkcenter = centerDetect(frame, 'p');
	while(pinkcenter.x == 0 && pinkcenter.y ==0)
	    pinkcenter = centerDetect(frame, 'p');               

     bluecenter = centerDetect(frame, 'b');	
	 while(bluecenter.x == 0 && bluecenter.y ==0)
	    bluecenter = centerDetect(frame, 'b');
     */
     
 	// Start -  pink/blue code
 	
	pinkcenter = centerDetect(frame, 'p');
	for(int i=0;(pinkcenter.x == 0 && pinkcenter.y ==0)&&(i<10);i++)
		pinkcenter = centerDetect(frame, 'p');		
		
	
		
	bluecenter = centerDetect(frame, 'b');
	for(int i=0;(bluecenter.x == 0 && bluecenter.y ==0)&&(i<10);i++)
	    bluecenter = centerDetect(frame, 'b');
	
	if((pinkcenter.x ==0 && pinkcenter.y == 0) && (bluecenter.x ==0 && bluecenter.y == 0))
		{
        turnlargedegrees(180);
        serialWriteByte(8);
        Sleep(150);
        serialWriteByte(1);Sleep(75);
        continue;
		}
	else if((pinkcenter.x ==0 && pinkcenter.y == 0) && bluecenter.x!=0)
		{
		turnlargedegrees(180);
        serialWriteByte(8);
        Sleep(150);
        serialWriteByte(1);Sleep(75);
        continue;
		}
	else if((bluecenter.x ==0 && bluecenter.y == 0) && pinkcenter.x!=0)
		{
        serialWriteByte(8);
        Sleep(150);
        serialWriteByte(1);Sleep(75);
        continue;
		}
    
	//End - pink blue code
	
	//Remaining Distance
	
	int stopaxisx, stopaxisy;
	stopaxisx = dest.x - (pinkcenter.x+bluecenter.x)/2;
	stopaxisy = dest.y - (pinkcenter.y+bluecenter.y)/2;
	
	if(abs(stopaxisx) < 40 && abs(stopaxisy) < 40)
		{
		serialWriteByte(7); //stop
		cout<<"\nReached!! ";
		cout<<"\nStopaxis x: "<<stopaxisx<<" y: "<<stopaxisy;
		cout<<"\tDest: "<<dest.x<<" "<<dest.y;
	//	Sleep(5000);
		break;
		}
	else if(abs(dest.x - pinkcenter.x) < 15 && abs(dest.y - pinkcenter.y) < 15)
		{
        serialWriteByte(7); //stop
		cout<<"\nReached!! ";
		cout<<"\nStopaxis x: "<<stopaxisx<<" y: "<<stopaxisy;
		cout<<"\tDest: "<<dest.x<<" "<<dest.y;
	//	Sleep(5000);
		break;
		}
	else if(abs(dest.x - bluecenter.x) < 15 && abs(dest.y - bluecenter.y) < 15)
		{
        serialWriteByte(7); //stop
		cout<<"\nReached!! ";
		cout<<"\nStopaxis x: "<<stopaxisx<<" y: "<<stopaxisy;
		cout<<"\tDest: "<<dest.x<<" "<<dest.y;
	//	Sleep(5000);
		break;
		}


	// Angle
	
    double botangle, destangle, botrad, destrad;
	
	int axisx, axisy;
	axisx = pinkcenter.x - bluecenter.x;
	axisy = pinkcenter.y - bluecenter.y;

	if(axisx!=0)
		{
        botrad=atan(axisy/axisx);
        botangle = botrad*180/(double)(3.14);	
        }
	else           
		{ 
		botangle=((axisy>0)?90:-90);              
		}

	
	int axisx1, axisy1;
	axisx1 = dest.x - pinkcenter.x;
	axisy1 = dest.y - pinkcenter.y;
	
	if(axisx1!=0)
		{
        destrad=atan(axisy1/axisx1);
        destangle=destrad*180/(double)(3.14);
        }
 	else   
	 	{ 
		destangle =((axisy1>0)?90:-90);
		}
 	
 	
 	angle = (int)(destangle - botangle);
 	
 	if( (pinkcenter.x < bluecenter.x && dest.x > bluecenter.x) || (pinkcenter.x > bluecenter.x && dest.x < bluecenter.x) )
		angle = angle-180; //?
		
	if(abs(angle) > 180)
		angle = (360 - abs(angle))*(angle/abs(angle))*(-1); // correct
	

    cout<<"\nAngle: "<<angle;

	/* OLD STRAIGHT CODE>> REVERT IF PROBS	
	if(abs(angle) < 23 )
		{
		serialWriteByte(1);
		cout<<"\nMOVE - Continuing straight";
		serialWriteByte(1);
		straight= 1;
		Sleep(150);
	//	continue;
		}
	*/
	
	if(abs(angle) > 40)
		{
		turnlargedegrees(angle);
		continue;
		}
		

	if(abs(angle) < 30 )
		{
		if(abs(stopaxisx) > 50 && abs(stopaxisy) > 50 )
			{
			serialWriteByte(8);
			cout<<"\n\t\t\t\tMOVE - LONG STRAIGHT";
			Sleep(150);
			straight=1;
			}
		else
			{
			serialWriteByte(1);
			cout<<"\n\t\t\t\tMOVE - shortstraight";
	
			straight= 1;              // or 1?
			}
	//	Sleep(150);
	//	continue;
		}
	
	if(angle > 0)
		{
		if(straight == 0 || (stopaxisx<50 || stopaxisy<50))
			{
			serialWriteByte(4);

			cout<<"\n\t\t\t\tMOVE - 4 Sharp Right"; // sharp R
			Sleep(150); //200 - works
			}
		else
			{
			serialWriteByte(2);

			cout<<"\n\t\t\t\tMOVE - 2 Arc Right"; //arc left
			Sleep(150); // 200 - works
			}
		}
	else if(angle <0)
		{
		if(straight == 0 || (stopaxisx<50 || stopaxisy<50))
			{
			serialWriteByte(5);

			cout<<"\n\t\t\t\tMOVE - 5 Sharp Left";
			Sleep(150);   //200 works
			}
		else
			{
			serialWriteByte(3);//Sleep(50);

			cout<<"\n\t\t\t\tMOVE - 3  Arc Left";
     		Sleep(150);   //200 works
			}
		}
    }
	catch(int e) 
		{
		cout<<"\nEXCEPTION in move()... "<<e; Sleep(5000); continue;
		}
	//Sleep(500);
	straight = 0;
	}
	cout<<"\nREACHED A POINT"; 
		
}


void setCenters()
	{
	VideoCapture cap(0); // device id (maybe 1) for usb cam
	if(!cap.isOpened())  // check if we succeeded
	    {
		cout<<"\nERROR:move.cpp - Camera Could not be found/ opened!";
		Sleep(5000);
		return ;		
		}
		
	Sleep(3000); // 3 secs for cam
	Mat frame;
	cap.grab();
	cap.retrieve(frame);
	
	pinkcenter = centerDetect(frame, 'p');	
	bluecenter = centerDetect(frame, 'b');
	redcenter = centerDetect(frame, 'r');	
	greencenter = centerDetect(frame, 'g');
	yellowcenter = centerDetect(frame, 'y');
	depocenter = centerDetect(frame, 'b');
	
	cout<<"\n Found Centers.. Check not Zero!";
	
	cap.release();		
	}


void turn180degrees()
{
for(int i=0;i<30;i++)
	{
	serialWriteByte(4);Sleep(75);		// sharp right
	}	

}

void makeMove(char src, char dest)
{
		 
	cout<<"\n\n\t\tmaking Move : ("<<src<<" to "<<dest<<")";
	
	Point srcp, destp, p;
	
	if(src=='r')
		srcp = redcenter;
	else if(src=='g')
		srcp = greencenter;
	else if(src== 'y')
		srcp = yellowcenter;
	else if(src=='d')
		srcp = depocenter;
	
	if(dest=='r')
		destp = redcenter;
	else if(dest=='g')
		destp = greencenter;
	else if(dest== 'y')
		destp = yellowcenter;
	else if(dest=='d')
		destp = depocenter;	
		
// no avoidance.. direct code..
	if(src!='d' && dest!='d')
		move(destp);
	else
		{
		if(abs(destp.x-srcp.x) < abs(destp.y-srcp.y))
			p = Point(destp.x ,srcp.y);
		else
			p = Point(srcp.x, destp.y);
		move(p);
		move(destp);
		}


	
// Else Move to some p, from there to destp
	

	
	

	
	serialWriteByte(6);  //beep
	cout<<"\nMOVE - 6 Beep"; 
	Sleep(2000);
	
	return ;
}
