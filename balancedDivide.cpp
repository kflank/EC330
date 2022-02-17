#include "balancedDivide.h"
 
struct Assignment;

   using std::vector;


Assignment helper(const vector<int> &birthdays, vector<int> ga, vector<int> gb, int i, int sumA, int sumB);

 

 
Assignment balancedDivide(vector<int> const &birthdays)
{
    return helper(birthdays, {}, {}, 0, 0, 0); // Don't forget to change this
}
 
Assignment helper(const vector<int> &birthdays, vector<int> ga, vector<int> gb, int i, int sumA, int sumB)
{
    if (i == birthdays.size())
    {
        return Assignment(abs(sumA - sumB), ga, gb);
    }
 	
    ga.push_back(birthdays[i]);
   	Assignment assignment_a = helper(birthdays, ga, gb, i + 1, sumA + birthdays[i], sumB);
    ga.pop_back();
 
    gb.push_back(birthdays[i]);
    Assignment assignment_b = helper(birthdays, ga, gb, i + 1, sumA, sumB + birthdays[i]);
    gb.pop_back();
 
    if (assignment_a.diff < assignment_b.diff)
    {
        return assignment_a;
    }
    else
    {
        return assignment_b;
    }
}



/*
int main ()
{



}

*/