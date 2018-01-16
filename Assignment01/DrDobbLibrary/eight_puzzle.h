#ifndef EIGHT_PUZZLE_INCLUDED
#define EIGHT_PUZZLE_INCLUDED

#include <set>
#include <utility>
#include <vector>

#include "hash_table.h"

enum op_t {EP_OP_UP, EP_OP_DOWN, EP_OP_RIGHT, EP_OP_LEFT};

typedef std::vector<unsigned int> row_t;
typedef row_t::size_type          col_idx_t;

typedef std::vector<row_t>  matrix_t;
typedef matrix_t::size_type row_idx_t;

class state_t
{
   public:
      state_t() {}
      state_t(const matrix_t &initial_state);

      unsigned int get_tile_at_location(row_idx_t r, col_idx_t c) const
      {
         return state[r][c];
      }

      void move(op_t op);

      row_idx_t get_blank_row() const {return blank_row;}
      col_idx_t get_blank_col() const {return blank_column;}

      unsigned int size() const
      {
         return static_cast<unsigned int>(state.size());
      }

      bool operator==(const state_t &rhs) const {return (state == rhs.state);}
      bool operator<(const state_t &rhs) const {return (state < rhs.state);}

   private:
      matrix_t  state;

      row_idx_t blank_row;
      col_idx_t blank_column;
};

class op_gen_t
{
   public:
      std::set<op_t> gen_ops(const state_t &state);
};

class op_apply_t
{
   public:
      std::pair<state_t, double> apply_op(
                                            const state_t &state,
                                            const op_t    &op
                                         );
};

class goal_test_t
{
   public:
      bool is_goal(const state_t &state);
};

class hasher_t
{
   public:
      unsigned int hash(const state_t &state);
};

class ep_check_states_t
{
   public:
      void clear_states() {ht.clear();}
      bool seen_before(const state_t &state);

   private:
      dct::hash_table_t<state_t, 10000, hasher_t> ht;
};

// This template implements the heuristics supplied for the problem domain.
// A specialization must be selected:
//
// 1: Manhattan Distance
// 2: Number of tiles in the wrong location

template<int N>
class heuristic_t
{
   public:
      double apply_heuristic(const state_t &state);
};

inline const state_t &get_goal_state();

inline const std::vector<std::pair<row_idx_t, col_idx_t> >
             &get_goal_tile_locations();

#endif
