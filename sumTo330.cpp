// your includes here
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


int sumTo330(vector<int> nums) {
int size =  nums.size();
vector <int> vectSum;
int count = 0;

	for (int i = 0; i < size -2; i++)
	{
		for (int j = 1; j < size -1; j++)
		{
			for (int k = j+1; k < size; k++)
			{
				vectSum.push_back(nums[i] + nums[j] + nums[k]);
				
				if (vectSum[count] == 300)
				{
					cout<<"hit 300"<<endl;
					return 300;
				}
				
				count = count +1;



			}

		}
	}

	int newsize = vectSum.size();
	int closestVal1;
	int closestVal2;
	int value = 0;
	for (int i = 0; i < newsize; i++)
	{
		closestVal1 = abs(300 - vectSum[i]);
		closestVal2 = abs(300 - vectSum[i+1]);
		if (closestVal1 < closestVal2)
		{
			value = vectSum[i];
		}
		else 
		{
			value = vectSum[i+1];
		}
	}
	cout<<"value is "<<value<<endl;
return value;
}


int main()
{

vector <int> test{1,2,3,4,5,6,7,8,100,33};
sumTo330(test);
return 0;
}