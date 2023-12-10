#include <bits/stdc++.h>
using namespace std;

void file()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

int GCD(int num1, int num2)
{

    if (num2 == 0)
        return num1;
	cout<<setprecision(12)<<num1/num2<<"\t"<<setprecision(12)<<num1<<"\t"<<setprecision(12)<<num2<<"\t"<<setprecision(12)<<num1%num2<<endl;
    return GCD(num2, num1%num2);
}

int main()
{
  
    int num1, num2;
    cout<<"Enter the first number: ";
    cin >> num1;
    cout<<"Enter the second number: ";
    cin >> num2;
	
    int gcd = GCD(num1, num2);
    cout << "GCD is " << gcd << endl;

    return 0;
}