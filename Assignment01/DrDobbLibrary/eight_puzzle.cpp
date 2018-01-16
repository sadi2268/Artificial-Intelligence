#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include "eight_puzzle.h"

using namespace std;

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
state_t::state_t(const matrix_t &initial_state): state(initial_state)
{
   const row_idx_t num_rows(initial_state.size());
   vector<bool>    present(num_rows * num_rows, false);
   unsigned int    tile;

   for (row_idx_t i = 0; i != num_rows; ++i)
   {
      const col_idx_t num_cols(initial_state[i].size());

      if (num_rows != num_cols)
      {
         cout << "The input puzzle must be square!" << endl;
         exit(0);
      }

      for (col_idx_t j = 0; j != num_cols; ++j)
      {
         tile = state[i][j];

         if (tile > (num_rows * num_rows - 1))
         {
            cout << "Tile " << tile << " is not a valid tile!" << endl;
            exit(0);
         }

         if (present[tile])
         {
            cout << "Tile " << tile << " is repeated!" << endl;
            exit(0);
         }
         else
            present[tile] = true;

         if (tile == 0)
         {
            blank_row    = i;
            blank_column = j;
         }
      }
   }

   for (vector<bool>::size_type i = 0; i != present.size(); ++i)
   {
      if (!present[i])
      {
         cout << "Tile "
              << static_cast<unsigned int>(i)
              << " is missing!"
              << endl;

         exit(0);
      }
   }
} // state_t::state_t

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
void state_t::move(op_t op)
{
   if (op == EP_OP_UP)
   {
      swap(
             state[blank_row - 1][blank_column],
             state[blank_row][blank_column]
          );

      blank_row--;
   }
   else if (op == EP_OP_DOWN)
   {
      swap(
             state[blank_row + 1][blank_column],
             state[blank_row][blank_column]
          );

      ++blank_row;
   }
   else if (op == EP_OP_RIGHT)
   {
      swap(
             state[blank_row][blank_column + 1],
             state[blank_row][blank_column]
          );

      ++blank_column;
   }
   else if (op == EP_OP_LEFT)
   {
      swap(
             state[blank_row][blank_column - 1],
             state[blank_row][blank_column]
          );

      blank_column--;
   }
} // state_t::move

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
std::set<op_t> op_gen_t::gen_ops(const state_t &state)
{
   col_idx_t col(state.get_blank_col());
   row_idx_t row(state.get_blank_row());
   set<op_t> rval;

   if (row > 0)
      rval.insert(EP_OP_UP);

   if (row < (state.size() - 1))
      rval.insert(EP_OP_DOWN);

   if (col > 0)
      rval.insert(EP_OP_LEFT);

   if (col < (state.size() - 1))
      rval.insert(EP_OP_RIGHT);

   return rval;
} // op_gen_t::gen_ops

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
std::pair<state_t, double> op_apply_t::apply_op(
                                                  const state_t &state,
                                                  const op_t    &op
                                               )
{
   state_t rval(state);

   rval.move(op);

   return make_pair(rval, 1.0);
} // op_apply_t::apply_op

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
bool goal_test_t::is_goal(const state_t &state)
{
   return (state == get_goal_state());
} // goal_test_t::is_goal

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
bool ep_check_states_t::seen_before(const state_t &state)
{
   if (ht.element_exists(state))
      return true;

   ht.insert_element(state);

   return false;
} // ep_check_states_t::seen_before

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
unsigned int hasher_t::hash(const state_t &state)
{
   unsigned int mult(1);
   unsigned int sum(0);

   for (row_idx_t i = 0; i != state.size(); ++i)
   {
      for (col_idx_t j = 0; j != state.size(); ++j)
      {
         sum += state.get_tile_at_location(i,j) * mult;
         mult *= 10;
      }
   }

   return sum;
} // hasher_t::hash

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
template <>
double heuristic_t<1>::apply_heuristic(const state_t &state)
{
   // This method implements the "Manhattan Distance" heuristic.

   const vector<pair<row_idx_t, col_idx_t> >
         &goal_tile_locations(get_goal_tile_locations());

   unsigned int size(state.size());
   unsigned int sum(0);

   vector<pair<row_idx_t, col_idx_t> > state_tile_locations(size * size);

   for (row_idx_t row = 0; row != size; ++row)
   {
      for (col_idx_t col = 0; col != size; ++col)
      {
         state_tile_locations[state.get_tile_at_location(row, col)] =
            make_pair(row, col);
      }
   }

   // While summing up the Manhattan distances, do not count the blank square.
   for (unsigned int i = 1; i != goal_tile_locations.size(); ++i)
   {
      sum += abs(
         static_cast<int>(
                            goal_tile_locations[i].first -
                            state_tile_locations[i].first
                         )
                );

      sum += abs(
                   static_cast<int>(
                                      goal_tile_locations[i].second -
                                      state_tile_locations[i].second
                                   )
                );
   }

   return static_cast<double>(sum);
} // heuristic_t<1>::apply_heuristic

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
template <>
double heuristic_t<2>::apply_heuristic(const state_t &state)
{
   unsigned int  count(0);
   const state_t &goal(get_goal_state());
   unsigned int  size(state.size());

   for (row_idx_t row = 0; row != size; ++row)
   {
      for (col_idx_t col = 0; col != size; ++col)
      {
         if (
               (
                   state.get_tile_at_location(row, col) !=
                   goal.get_tile_at_location(row, col)
               ) &&
               (state.get_tile_at_location(row, col) != 0)
            )
         {
            ++count;
         }
      }
   }

   return static_cast<double>(count);
} // heuristic_t<2>::apply_heuristic

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
inline const state_t &get_goal_state()
{
   static bool    initialized(false);
   static state_t the_goal;

   if (!initialized)
   {
      matrix_t goal_config(3, row_t(3));

      goal_config[0][0] = 1;
      goal_config[0][1] = 2;
      goal_config[0][2] = 3;
      goal_config[1][0] = 4;
      goal_config[1][1] = 0;
      goal_config[1][2] = 5;
      goal_config[2][0] = 6;
      goal_config[2][1] = 7;
      goal_config[2][2] = 8;

      state_t goal_state(goal_config);

      the_goal = goal_state;

      initialized = true;
   }

   return the_goal;
} // get_goal_state

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
inline const std::vector<std::pair<row_idx_t, col_idx_t> >
             &get_goal_tile_locations()
{
   static vector<pair<row_idx_t, col_idx_t> > goal_tile_locations;
   static bool                                initialized(false);

   if (!initialized)
   {
      const state_t &goal(get_goal_state());
      unsigned int  size(goal.size());

      goal_tile_locations.resize(size * size);

      for (row_idx_t row = 0; row != size; ++row)
      {
         for (col_idx_t col = 0; col != size; ++col)
         {
            goal_tile_locations[goal.get_tile_at_location(row, col)] =
               make_pair(row, col);
         }
      }

      initialized = true;
   }

   return goal_tile_locations;
} // get_goal_tile_locations
