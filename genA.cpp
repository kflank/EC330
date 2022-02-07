#include <iostream>


using namespace std;


unsigned long genA(int n) 
{

	int Avals[n]; 
	Avals[0] = 1;
	Avals[1] = 1;
	int val = 0;


		for (int i = 2; i < n; i++) //starting the loop at 2 b/c [0],[1] are given
		{

			for (int j = 0; j < i; j++)
			{

				val = val + Avals[j]*Avals[i-j-1];
					if (i-j-1 == 0)
					{
						Avals[i] = val;
						val = 0;
					}

			}


		}
	return Avals[n-1];
		//cout<<Avals[n-1]<<endl;
	}





//no main here


