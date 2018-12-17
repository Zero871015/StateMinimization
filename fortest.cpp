#include <iostream>
#include <time.h>
#include <string>
using namespace std;

int main()
{
	string state[] = { "a","b","c","d","e" };
	string str[] = { "00","01","10","11"};
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << str[j] << " " << state[i] << " " << state[rand() % 5] <<" "<< rand() % 2 << rand() % 2 << endl;
		}
	}
	system("PAUSE");
	return 0;
}