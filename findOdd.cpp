#include <iostream>


using namespace std;






char findOdd(char arr[], int arr_size) {
	/* your code here */
	char letter;
	int numArr[26] = {}; // array for ASCII conversion
	for (int i = 0; i < arr_size; i++)
	{
		
		int spot = int(arr[i]);
		//cout<<"spot is "<<spot<<endl;
		numArr[spot-97] = numArr[spot -97] + 1;
	}

	for (int i = 0;  i< 26; i++)
	{
		if (numArr[i] % 2 == 1){


			
			letter = char(i +97);
			//cout<<char(i +97)<<endl;
			return letter;
		}

	}
	//return 0;
}

















//I have a character array I made for testing purposes I am assuming that this will be replaced for testing
/*

int main()
{
int arr_size;
//char arr[3] = {'a','b','b'};
char arr[9] = {'a','c','b','a','b','c','c','c','e'};  
arr_size = sizeof(arr);
findOdd(arr , arr_size);

return 0;
};

*/
