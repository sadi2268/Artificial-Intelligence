#include <iostream>
#include <vector>

#include "eight_puzzle.h"
#include "search.h"

using namespace dct;
using namespace std;

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
int main()
{
   typedef search_engine_t<
                             state_t,
                             op_t,
                             op_gen_t,
                             op_apply_t,
                             goal_test_t,
                             // repeated_state_checker_t<3>,
                             repeated_state_checker_t<4, ep_check_states_t>,
                             heuristic_t<1>
                          > se_t;

   matrix_t initial_config(3, row_t(3));

#if 1
   initial_config[0][0] = 8;
   initial_config[0][1] = 7;
   initial_config[0][2] = 6;
   initial_config[1][0] = 5;
   initial_config[1][1] = 0;
   initial_config[1][2] = 4;
   initial_config[2][0] = 3;
   initial_config[2][1] = 2;
   initial_config[2][2] = 1;
#else
   initial_config[0][0] = 3;
   initial_config[0][1] = 0;
   initial_config[0][2] = 8;
   initial_config[1][0] = 2;
   initial_config[1][1] = 5;
   initial_config[1][2] = 7;
   initial_config[2][0] = 1;
   initial_config[2][1] = 4;
   initial_config[2][2] = 6;
#endif

   state_t initial_state(initial_config);

   const state_t &goal_state(get_goal_state());

   if (initial_state.size() != goal_state.size())
   {
      cout << "The initial and goal states must be the same size!" << endl;
      exit(0);
   }

   se_t                              se;
   se_t::search_result_t             solutions;
   se_t::search_result_t::value_type one_solution;

   // solutions = se.depth_limited(initial_state, 30);
   // solutions = se.depth_first(initial_state);
   // solutions = se.iterative_deepening(initial_state, 30);
   // solutions = se.breadth_first(initial_state);
   // solutions = se.uniform_cost(initial_state);
   // solutions = se.greedy(initial_state);
   solutions = se.a_star(initial_state);

   cout << endl;

   if (solutions.size() != 0)
   {
      one_solution = *(solutions.begin());

      cout << "The first of "
           << static_cast<unsigned int>(solutions.size())
           << " solution(s) is: "
           << endl
           << endl
           << static_cast<unsigned int>(one_solution.operators.size())
           << " move(s)"
           << endl
           << "Cost: "
           << one_solution.cost
           << endl
           << endl;

      for (
             vector<op_t>::size_type i = 0;
             i != one_solution.operators.size();
             ++i
          )
      {
         if (one_solution.operators[i] == EP_OP_UP)
            cout << "UP" << endl;
         else if (one_solution.operators[i] == EP_OP_DOWN)
            cout << "DOWN" << endl;
         else if (one_solution.operators[i] == EP_OP_RIGHT)
            cout << "RIGHT" << endl;
         else if (one_solution.operators[i] == EP_OP_LEFT)
            cout << "LEFT" << endl;
      }

      cout << endl;
   }
   else
   {
      cout << "No solution exists!" << endl << endl;
   }

   cout << se.get_nodes_created() << " nodes were created." << endl << endl;
} // main
