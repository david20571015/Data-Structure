//
// main.cpp
// ds_hw1_warm_up
//

#include "PrimeChecker.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

PRIMECHECKER checker;

int main(int argc, char **argv)
{
	//input file
	ifstream fin;
	fin.open("example", ios::in);
	if (!fin)
	{
		cout << "Where is the pattern file given by TA ?????" << endl;
		exit(-1);
	} //input file

	clock_t t_start, t_end;
	t_start = clock();

	int num, total_num = 0, correct_num = 0;
	unsigned long a, b, check;
	while (fin >> a >> b >> check)
	{
		total_num++;
		if (check == checker.PrimeChecker(a, b))
		{
			correct_num++;
		}
	}
	fin.close();

	t_end = clock();
	cout << "Total use  " << double(t_end - t_start) / CLOCKS_PER_SEC << " secs" << endl;
	cout << "Total pass " << double(correct_num * 100) / total_num << " percentages of cases" << endl;
	return 0;
}
