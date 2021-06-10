//
//  main.cpp
//  DS_hw3_Stack_and_queue
//

#include <string.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include "solve.cpp"
#include "solve.h"

using namespace std;

bool check(ifstream &, vector<vector<int> > &);

int main(int argc, const char *argv[]) {
  string readfile = argv[1];

  string checkfile = readfile;

  cout << "DS HW3 Sum with file: " << readfile << endl;
  solve find_solutions;

  ifstream fin, fcheck;
  fin.open(readfile.c_str(), ios::in);
  int name_pos = checkfile.find(".in");
  if (name_pos != -1) checkfile.replace(name_pos + 1, name_pos + 3, "check");
  fcheck.open(checkfile.c_str(), ios::in);

  if (!fin) {
    cout << readfile << " file could not be opened." << endl;
    exit(-1);
  }
  if (!fcheck) {
    cout << checkfile << " file could not be opened." << endl;
    exit(-1);
  }

  int i;
  int target, negative_limit, candidates_num;
  int case_num = 0, correct_num = 0;
  vector<int> candidates;
  vector<vector<int> > sol;

  clock_t start_time, end_time, solve_time = 0;
  start_time = clock();

  while (!fin.eof()) {
    fin >> target >> negative_limit >> candidates_num;
    for (int j = 0; j < candidates_num; j++) {
      fin >> i;
      candidates.push_back(i);
    }

    if (candidates.empty()) break;

    clock_t s = clock();
    find_solutions.calculate(target, negative_limit, candidates_num, candidates,
                             sol);
    solve_time += clock() - s;

    if (check(fcheck, sol))
      correct_num++;
    else
      cout << "Wrong case: target=" << target << " limit=" << negative_limit
           << " number of candidates=" << candidates_num << endl;

    sol.clear();
    candidates.clear();
    candidates_num = 0;
    case_num++;
  }

  fin.close();

  end_time = clock();
  cout << "Total pass : " << 100.0 * correct_num / (case_num)
       << " percentages of cases" << endl;
  cout << "solve time: " << double(solve_time) / CLOCKS_PER_SEC << " secs"
       << endl
       << "Exc time: " << double(end_time - start_time) / CLOCKS_PER_SEC
       << " secs" << endl;

  return 0;
}

bool check(ifstream &fcheck, vector<vector<int> > &sol) {
  vector<int> temp;
  vector<vector<int> > ans;
  bool check;
  int candiates_count[2001];
  int answer_num, literal_num = 0, i;
  string s;
  for (int j = 0; j < 2001; j++) candiates_count[j] = 0;

  fcheck >> s >> s >> s >> s >> answer_num;
  if (!sol.size() && !answer_num) return 1;
  if (sol.size() != answer_num) return 0;  // wrong solution

  for (int j = 0; j < answer_num; j++) {
    fcheck >> literal_num;
    for (int k = 0; k < literal_num; k++) {
      fcheck >> i;
      candiates_count[i + 1000]++;
    }
  }

  for (int j = 0; j < sol.size(); j++) {
    for (int k = 0; k < sol[j].size(); k++) {
      candiates_count[sol[j][k] + 1000]--;
      if (candiates_count[sol[j][k] + 1000] < 0) return 0;  // wrong solution
    }
  }

  for (int j = 0; j < 2001; j++)
    if (candiates_count[j] != 0) return 0;  // wrong solution

  return 1;
}
