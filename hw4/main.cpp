//! @file DS_HW04-BST main function
//! @author Wei-Tse Hung
//! @date 30 Nov 2015
//! @version ver0.0.1
//! @details
//! Email: uintahorn.ee04g@nctu.edu.tw \n
//! Created by Wei-Tse Hung on 11/30/15. \n
//! Copyright (c) 2015 Wei-Tse Hung. All rights reserved.

#include <time.h>

#include <algorithm>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>

#include "OrderMGMT.cpp"

using namespace std;

bool compare(ifstream &, list<unsigned> &, list<unsigned> &);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "usage: ./hw4 TestCase#" << endl;
    return 1; /* errno1: Operation not permitted */
  }

  ifstream testCase(argv[1], ifstream::in);
  ifstream testANS(strcat(argv[1], ".ans"), ifstream::in);
  if (!testCase.is_open() || !testANS.is_open()) {
    cout << "TestCase file or answer doesn't exist!" << endl;
    return 2; /* errno2: No such file or directory */
  }

  list<unsigned> your_list, golden_list;

  enum COMMAND {
    AddOrder,
    DeleteOrders,
    SearchByDate,
    SearchByDateRank,
    CheckCorrectness,
    Halt
  };
  COMMAND cmd(Halt);
  unsigned arg(0), cf_times(0), pass_times(0);
  string s;

  clock_t time_init(clock()), time_end(0);
  timespec t_start, t_end;
  clock_gettime(CLOCK_REALTIME, &t_start);
  // your program start here
  // Functional testing

  OrderMGMT MGMTSystem;  // Calling Constructor

  while (testCase >> s) {
    if (cmd != Halt) {
      arg = atoi(s.c_str());
      testCase >> s;
      switch (cmd) {
        case AddOrder:
          MGMTSystem.addOrder(arg, atoi(s.c_str()));
          break;
        case DeleteOrders:
          MGMTSystem.deleteOrders(arg, atoi(s.c_str()));
          break;
        case SearchByDate:
          your_list = MGMTSystem.searchByDate(arg, atoi(s.c_str()));
          break;
        case SearchByDateRank:
          your_list = MGMTSystem.searchByDateRank(arg, atoi(s.c_str()));
          break;
        case CheckCorrectness:
          if (compare(testANS, golden_list, your_list)) {
            ++pass_times;
          }
          ++cf_times;
          break;
        default:
          cout << "Invalid command!" << endl;
          return 127; /* errno127: Key has expired */
      }
      cmd = Halt;
    } else if (s == "AddOrder") {
      cmd = AddOrder;
    } else if (s == "DeleteOrders") {
      cmd = DeleteOrders;
    } else if (s == "SearchByDate") {
      cmd = SearchByDate;
    } else if (s == "SearchByDateRank") {
      cmd = SearchByDateRank;
    } else if (s == "CheckCorrectness") {
      cmd = CheckCorrectness;
    }
  }
  // your program end here

  clock_gettime(CLOCK_REALTIME, &t_end);
  time_end = clock();
  cout << "total CPU time = "
       << static_cast<double>(time_end - time_init) / CLOCKS_PER_SEC << endl;
  cout << "total time = "
       << static_cast<double>(t_end.tv_nsec - t_start.tv_nsec) / 1e9 << endl;
  cout << "Correctness = " << static_cast<double>(100 * pass_times / cf_times)
       << "%" << endl;
  return 0;
}

bool compare(ifstream &testANS, list<unsigned> &golden_list,
             list<unsigned> &your_list) {
  golden_list.clear();
  string s;
  while (testANS >> s) {
    if (s == ">") {
      while (testANS >> s) {
        if (s == ";")
          break;
        else
          golden_list.push_back(atoi(s.c_str()));
      }
      break;
    }
  }
  return golden_list.size() == your_list.size() &&
         equal(your_list.begin(), your_list.end(), golden_list.begin());
}
