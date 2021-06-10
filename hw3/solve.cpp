//
//  set.cpp
//  DS_hw3_Stack_and_queue
//

#include "solve.h"

#include <algorithm>

void FindCombSum(int target, const int &candidates_num, int &start,
                 const vector<int> &candidates, vector<int> &sol,
                 vector<vector<int> > &solutions) {
  if (target == 0) {
    solutions.push_back(sol);
    return;
  }
  for (int i = start; i < candidates_num && candidates[i] <= target; i++) {
    sol.push_back(candidates[i]);
    FindCombSum(target - candidates[i], candidates_num, i, candidates, sol,
                solutions);
    sol.pop_back();
  }
}

void solve::calculate(int target, int limit, int candidates_num,
                      vector<int> candidates, vector<vector<int> > &solutions) {
  int num_of_positives, num_of_negatives = 0;
  for (int i = 0; candidates[i] < 0; i++) num_of_negatives++;
  num_of_positives = candidates_num - num_of_negatives;

  int start = 0;

  vector<int> posi_candidates(candidates.begin() + num_of_negatives,
                              candidates.end());

  if (limit >= 0) {
    vector<int> sol;
    FindCombSum(target, num_of_positives, start, posi_candidates, sol,
                solutions);
  }
  if (limit >= 1) {
    for (int i = 0; i < num_of_negatives; i++) {
      vector<int> sol;
      sol.push_back(candidates[i]);
      FindCombSum(target - candidates[i], num_of_positives, start,
                  posi_candidates, sol, solutions);
    }
  }
  if (limit >= 2) {
    for (int i = 0; i < num_of_negatives; i++)
      for (int j = i; j < num_of_negatives; j++) {
        vector<int> sol;
        sol.push_back(candidates[i]);
        sol.push_back(candidates[j]);
        FindCombSum(target - candidates[i] - candidates[j], num_of_positives,
                    start, posi_candidates, sol, solutions);
      }
  }
}
