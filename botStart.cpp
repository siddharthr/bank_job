# include <stdio.h>
# include <conio.h>
# include<iostream>
# include <fstream>
# include "botMove_1.cpp"
# include "botMove_2.cpp"
# include "botMove_3.cpp"
# include<windows.h>
using namespace std;

#define MAXNUM 500

int numtrips[MAXNUM][4];
int min(int a, int b, int c)
{
if(a<b)
	{
	if(a<c)
		return a;
	return c;
	}
else
	{
	if(b<c)
		return b;
	return c;
	}	
}




void pause()
	{
	Sleep(1000);
	}




void fillTableAndMove(int target)
{
int i, j;
i=j=0;
numtrips[1][0]=numtrips[5][0]=numtrips[10][0]=1;
numtrips[1][3]=1;
numtrips[5][2]=1;
numtrips[10][1]=1;
for(i=2;i<5;i++)
	{
	numtrips[i][0]=i;
	numtrips[i][3]=i;
	}
for(i=6;i<10;i++)
	{
	numtrips[i][0]=1+(i-5);
	numtrips[i][3]=(i-5);
	numtrips[i][2]=1;
	}
	
for(i=11;i<=target;i++)
	{
	numtrips[i][0]=1+min(numtrips[i-1][0], numtrips[i-5][0], numtrips[i-10][0]);
	if(numtrips[i][0]-1 == numtrips[i-1][0])
		{
		numtrips[i][3]=numtrips[i-1][3]+1;
		numtrips[i][2]=numtrips[i-1][2];
		numtrips[i][1]=numtrips[i-1][1];
		}
	else if(numtrips[i][0]-1 == numtrips[i-5][0])
		{
		numtrips[i][3]=numtrips[i-5][3];
		numtrips[i][2]=numtrips[i-5][2]+1;
		numtrips[i][1]=numtrips[i-5][1];		
		}
	else if(numtrips[i][0]-1 == numtrips[i-10][0])
		{
		numtrips[i][3]=numtrips[i-10][3];
		numtrips[i][2]=numtrips[i-10][2];
		numtrips[i][1]=numtrips[i-10][1]+1;
		}
	}
	

printf("\n Total: %d \t100s: %d\t\t50s:%d\t\t10s:%d", numtrips[target][0], numtrips[target][1], numtrips[target][2], numtrips[target][3]);
	

/* Siddharth - your work starts here!
r-red	1000
c-cyan / green?  50
y-yellow
s-start
d-deposition pt.

just for convenience im assuming that the bot moves to d at the start..
venum na i can change!

pause() - waiting on the color
makeMove(src, dest) - actually moving, avoiding the color zones..
		if you can explain a little bit, i can help here too!

*/

// if 2 denominations are even.. finish them off first..

if(numtrips[target][1]%2==0 && numtrips[target][2]%2==0)
	{
	while(numtrips[target][1] && numtrips[target][2])
		{
		makeMove('d', 'r');
		pause();
		makeMove('r', 'g');
		pause();
		makeMove('g', 'd');
		pause();
		numtrips[target][1]--;
		numtrips[target][2]--;
		}
	}

if(numtrips[target][1]%2==0 && numtrips[target][3]%2==0)
	{
	while(numtrips[target][1] && numtrips[target][3])
		{
		makeMove('d', 'r');
		pause();
		makeMove('r', 'y');
		pause();
		makeMove('y', 'd');
		pause();
		numtrips[target][1]--;
		numtrips[target][3]--;
		}
	}
	
if(numtrips[target][2]%2==0 && numtrips[target][3]%2==0)
	{
	while(numtrips[target][2] && numtrips[target][3])
		{
		makeMove('d', 'g');
		pause();
		makeMove('g', 'y');
		pause();
		makeMove('y', 'd');
		pause();
		numtrips[target][2]--;
		numtrips[target][3]--;
		}
	}	

// No 2 denominations are even.. 1 even / 2 odd , or all odd

if(numtrips[target][1]%2==0)
	{
	while(numtrips[target][1] && numtrips[target][2])
		{
		makeMove('d', 'r');
		pause();
		makeMove('r', 'g');
		pause();
		makeMove('g', 'd');
		pause();
		numtrips[target][1]--;
		numtrips[target][2]--;
		}
	while(numtrips[target][1] && numtrips[target][3])
		{
		makeMove('d', 'r');
		pause();
		makeMove('r', 'y');
		pause();
		makeMove('y', 'd');
		pause();
		numtrips[target][1]--;
		numtrips[target][3]--;
		}
	}
	
if(numtrips[target][2]%2==0)
	{
	while(numtrips[target][1] && numtrips[target][2])
		{
		makeMove('d', 'r');
		pause();
		makeMove('r', 'g');
		pause();
		makeMove('g', 'd');
		pause();
		numtrips[target][1]--;
		numtrips[target][2]--;
		}
	while(numtrips[target][2] && numtrips[target][3])
		{
		makeMove('d', 'g');
		pause();
		makeMove('g', 'y');
		pause();
		makeMove('y', 'd');
		pause();
		numtrips[target][2]--;
		numtrips[target][3]--;
		}
	}

if(numtrips[target][3]%2==0)
	{
	while(numtrips[target][1] && numtrips[target][3])
		{
		makeMove('d', 'r');
		pause();
		makeMove('r', 'y');
		pause();
		makeMove('y', 'd');
		pause();
		numtrips[target][1]--;
		numtrips[target][3]--;
		}
	while(numtrips[target][2] && numtrips[target][3])
		{
		makeMove('d', 'g');
		pause();
		makeMove('g', 'y');
		pause();
		makeMove('y', 'd');
		pause();
		numtrips[target][2]--;
		numtrips[target][3]--;
		}
	}


// no evens left.. maybe odds left..

while(numtrips[target][1] && numtrips[target][2])
	{
	makeMove('d', 'r');
	pause();
	makeMove('r', 'g');
	pause();
	makeMove('g', 'd');
	pause();
	numtrips[target][1]--;
	numtrips[target][2]--;
	}
while(numtrips[target][1] && numtrips[target][3])
	{
	makeMove('d', 'r');
	pause();
	makeMove('r', 'y');
	pause();
	makeMove('y', 'd');
	pause();
	numtrips[target][1]--;
	numtrips[target][3]--;
	}
while(numtrips[target][2] && numtrips[target][3])
	{
	makeMove('d', 'g');
	pause();
	makeMove('g', 'y');
	pause();
	makeMove('y', 'd');
	pause();
	numtrips[target][2]--;
	numtrips[target][3]--;
	}	
while(numtrips[target][1])
	{
	makeMove('d', 'r');
	pause();
	makeMove('r', 'd');
	pause();
	numtrips[target][1]--;
	}
while(numtrips[target][2])
	{
	makeMove('d', 'g');
	pause();
	makeMove('g', 'd');
	pause();
	numtrips[target][2]--;
	}
while(numtrips[target][3])
	{
	makeMove('d', 'y');
	pause();
	makeMove('y', 'd');
	pause();
	numtrips[target][3]--;
	}

}



int readNum()
{
	int i;
    char *inname = "Bankjob.txt";
    ifstream infile(inname);

    if (!infile) 
	{
        cout << "There was a problem opening file "
             << inname
             << " for reading."
             << endl;
        return 0;
    }
    cout << "Opened " << inname << " for reading." << endl;
    while (infile >> i) 
        {
		cout << "Value from file is " << i << endl;
		return i;
		}
	return 0;
}

int main()
{
int target, i, j;

for(i=0;i<MAXNUM;i++)
	{
	for(j=0;j<4;j++)
		{
		numtrips[i][j]=0;
		}
	}

/*
while(1)
	{
	scanf("%d", &target);
	target/=10;
	fillTableAndMove(target);
	}
	*/
	
target = readNum();
cout<<"\nTarget: "<<target;
setCenters();
Sleep(1000);
fillTableAndMove(target/10);

getch();

}


