#include <algorithm>
#include <limits>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>

namespace dct
{
   class null_heuristic_t
   {
      public:
         template <typename STATE_T>
         double apply_heuristic(const STATE_T &) {return 0.0;}
   };


   template <typename STATE_T, typename OP_T>
   struct node_t
   {
      node_t(
               const STATE_T &state_p,
               unsigned int  depth_p,
               double        g_cost_p,
               double        h_cost_p,
               const node_t  *parent_p = NULL,
               const OP_T    &op_p     = OP_T()
            ):
            state(state_p),
            depth(depth_p),
            g_cost(g_cost_p),
            h_cost(h_cost_p),
            parent(parent_p),
            op(op_p)
      {
      }

      node_t(): parent(NULL) {}

      STATE_T      state;
      unsigned int depth;
      double       g_cost;
      double       h_cost;
      const node_t *parent;        // Equals NULL for root node
      OP_T         op;             // Meaningful only if parent != NULL
   };

   class null_repeated_state_checking_policy_t
   {
   };

   template <typename STATE_T, typename OP_T>
   class result_comp_t
   {
      public:
         bool operator()(
                           const search_result_template_t<STATE_T, OP_T> &lhs,
                           const search_result_template_t<STATE_T, OP_T> &rhs
                        ) const
         {
            return lhs.goal_state_reached < rhs.goal_state_reached;
         }
   };

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <
               typename STATE_T,
               typename OP_T,
               typename OP_GEN_T,
               typename OP_APPLY_T,
               typename GOAL_TEST_T,
               typename REPEATED_STATE_CHECKER_T,
               typename HEURISTIC_T
            >
   typename search_engine_t<
                              STATE_T,
                              OP_T,
                              OP_GEN_T,
                              OP_APPLY_T,
                              GOAL_TEST_T,
                              REPEATED_STATE_CHECKER_T,
                              HEURISTIC_T
                           >::search_result_t // Return type
   search_engine_t<
                     STATE_T,
                     OP_T,
                     OP_GEN_T,
                     OP_APPLY_T,
                     GOAL_TEST_T,
                     REPEATED_STATE_CHECKER_T,
                     HEURISTIC_T
                  >::a_star(const STATE_T &initial_state, bool return_all)
   {
      typedef std::priority_queue<
                                    const node_t<STATE_T, OP_T> *,
                                    std::vector<const node_t<STATE_T, OP_T> *>,
                                    node_sort_by_g_plus_h_t
                                 > node_queue_t;

      return general_search<node_queue_t>(
                                       initial_state,
                                       std::numeric_limits<unsigned int>::max(),
                                       return_all
                                         );
   } // search_engine_t::a_star

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <
               typename STATE_T,
               typename OP_T,
               typename OP_GEN_T,
               typename OP_APPLY_T,
               typename GOAL_TEST_T,
               typename REPEATED_STATE_CHECKER_T,
               typename HEURISTIC_T
            >
   typename search_engine_t<
                              STATE_T,
                              OP_T,
                              OP_GEN_T,
                              OP_APPLY_T,
                              GOAL_TEST_T,
                              REPEATED_STATE_CHECKER_T,
                              HEURISTIC_T
                           >::search_result_t // Return type
   search_engine_t<
                     STATE_T,
                     OP_T,
                     OP_GEN_T,
                     OP_APPLY_T,
                     GOAL_TEST_T,
                     REPEATED_STATE_CHECKER_T,
                     HEURISTIC_T
                  >::breadth_first(
                                     const STATE_T &initial_state,
                                     bool          return_all
                                  )
   {
      return general_search<std::queue<const node_t<STATE_T, OP_T> *> >(
                                       initial_state,
                                       std::numeric_limits<unsigned int>::max(),
                                       return_all
                                                                       );
   } // search_engine_t::breadth_first

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <
               typename STATE_T,
               typename OP_T,
               typename OP_GEN_T,
               typename OP_APPLY_T,
               typename GOAL_TEST_T,
               typename REPEATED_STATE_CHECKER_T,
               typename HEURISTIC_T
            >
   typename search_engine_t<
                              STATE_T,
                              OP_T,
                              OP_GEN_T,
                              OP_APPLY_T,
                              GOAL_TEST_T,
                              REPEATED_STATE_CHECKER_T,
                              HEURISTIC_T
                           >::search_result_t // Return type
   search_engine_t<
                     STATE_T,
                     OP_T,
                     OP_GEN_T,
                     OP_APPLY_T,
                     GOAL_TEST_T,
                     REPEATED_STATE_CHECKER_T,
                     HEURISTIC_T
                  >::depth_first(const STATE_T &initial_state, bool return_all)
   {
      return depth_limited(
                             initial_state,
                             std::numeric_limits<unsigned int>::max(),
                             return_all
                          );
   } // search_engine_t::depth_first

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <
               typename STATE_T,
               typename OP_T,
               typename OP_GEN_T,
               typename OP_APPLY_T,
               typename GOAL_TEST_T,
               typename REPEATED_STATE_CHECKER_T,
               typename HEURISTIC_T
            >
   typename search_engine_t<
                              STATE_T,
                              OP_T,
                              OP_GEN_T,
                              OP_APPLY_T,
                              GOAL_TEST_T,
                              REPEATED_STATE_CHECKER_T,
                              HEURISTIC_T
                           >::search_result_t // Return type
   search_engine_t<
                     STATE_T,
                     OP_T,
                     OP_GEN_T,
                     OP_APPLY_T,
                     GOAL_TEST_T,
                     REPEATED_STATE_CHECKER_T,
                     HEURISTIC_T
                  >::depth_limited(
                                     const STATE_T &initial_state,
                                     unsigned int  depth_limit,
                                     bool          return_all
                                  )
   {
      return general_search<std::stack<const node_t<STATE_T, OP_T> *> >(
                                                                  initial_state,
                                                                  depth_limit,
                                                                  return_all
                                                                       );
   } // search_engine_t::depth_limited

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <
               typename STATE_T,
               typename OP_T,
               typename OP_GEN_T,
               typename OP_APPLY_T,
               typename GOAL_TEST_T,
               typename REPEATED_STATE_CHECKER_T,
               typename HEURISTIC_T
            >
   typename search_engine_t<
                              STATE_T,
                              OP_T,
                              OP_GEN_T,
                              OP_APPLY_T,
                              GOAL_TEST_T,
                              REPEATED_STATE_CHECKER_T,
                              HEURISTIC_T
                           >::search_result_t // Return type
   search_engine_t<
                     STATE_T,
                     OP_T,
                     OP_GEN_T,
                     OP_APPLY_T,
                     GOAL_TEST_T,
                     REPEATED_STATE_CHECKER_T,
                     HEURISTIC_T
                  >::greedy(const STATE_T &initial_state, bool return_all)
   {
      typedef std::priority_queue<
                                    const node_t<STATE_T, OP_T> *,
                                    std::vector<const node_t<STATE_T, OP_T> *>,
                                    node_sort_by_h_t
                                 > node_queue_t;

      return general_search<node_queue_t>(
                                       initial_state,
                                       std::numeric_limits<unsigned int>::max(),
                                       return_all
                                         );
   } // search_engine_t::greedy

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <
               typename STATE_T,
               typename OP_T,
               typename OP_GEN_T,
               typename OP_APPLY_T,
               typename GOAL_TEST_T,
               typename REPEATED_STATE_CHECKER_T,
               typename HEURISTIC_T
            >
   typename search_engine_t<
                              STATE_T,
                              OP_T,
                              OP_GEN_T,
                              OP_APPLY_T,
                              GOAL_TEST_T,
                              REPEATED_STATE_CHECKER_T,
                              HEURISTIC_T
                           >::search_result_t // Return type
   search_engine_t<
                     STATE_T,
                     OP_T,
                     OP_GEN_T,
                     OP_APPLY_T,
                     GOAL_TEST_T,
                     REPEATED_STATE_CHECKER_T,
                     HEURISTIC_T
                  >::iterative_deepening(
                                           const STATE_T &initial_state,
                                           unsigned int  depth_limit
                                        )
   {
      unsigned int    old_nodes_created(0);
      search_result_t rval;

      for (unsigned int i = 1; i <= depth_limit; ++i)
      {
         // Using iterative deepening to search for all goal states does not
         // make sense.  Therefore, it is not an option; we will always just
         // look for the first goal state that we can reach.
         rval = depth_limited(initial_state, i, false);
         old_nodes_created += nodes_created;

         if (rval.size() != 0)
         {
            // Erase all but the first result obtained at this depth.
            rval.erase(++rval.begin(), rval.end());

            nodes_created = old_nodes_created;

            return rval;
         }
      }

      return rval;
   } // search_engine_t::iterative_deepening

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <
               typename STATE_T,
               typename OP_T,
               typename OP_GEN_T,
               typename OP_APPLY_T,
               typename GOAL_TEST_T,
               typename REPEATED_STATE_CHECKER_T,
               typename HEURISTIC_T
            >
   typename search_engine_t<
                              STATE_T,
                              OP_T,
                              OP_GEN_T,
                              OP_APPLY_T,
                              GOAL_TEST_T,
                              REPEATED_STATE_CHECKER_T,
                              HEURISTIC_T
                           >::search_result_t // Return type
   search_engine_t<
                     STATE_T,
                     OP_T,
                     OP_GEN_T,
                     OP_APPLY_T,
                     GOAL_TEST_T,
                     REPEATED_STATE_CHECKER_T,
                     HEURISTIC_T
                  >::uniform_cost(const STATE_T &initial_state, bool return_all)
   {
      typedef std::priority_queue<
                                    const node_t<STATE_T, OP_T> *,
                                    std::vector<const node_t<STATE_T, OP_T> *>,
                                    node_sort_by_g_t
                                 > node_queue_t;

      return general_search<node_queue_t>(
                                       initial_state,
                                       std::numeric_limits<unsigned int>::max(),
                                       return_all
                                         );
   } // search_engine_t::uniform_cost

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <
               typename STATE_T,
               typename OP_T,
               typename OP_GEN_T,
               typename OP_APPLY_T,
               typename GOAL_TEST_T,
               typename REPEATED_STATE_CHECKER_T,
               typename HEURISTIC_T
            >
   template <typename DATA_STRUCT>
   typename search_engine_t<
                              STATE_T,
                              OP_T,
                              OP_GEN_T,
                              OP_APPLY_T,
                              GOAL_TEST_T,
                              REPEATED_STATE_CHECKER_T,
                              HEURISTIC_T
                           >::search_result_t // Return type
   search_engine_t<
                     STATE_T,
                     OP_T,
                     OP_GEN_T,
                     OP_APPLY_T,
                     GOAL_TEST_T,
                     REPEATED_STATE_CHECKER_T,
                     HEURISTIC_T
                  >::general_search(
                                      const STATE_T &initial_state,
                                      unsigned int  depth_limit,
                                      bool          return_all
                                   )
   {
      std::list<node_t<STATE_T, OP_T> >                    all_nodes;

      std::set<
                 const node_t<STATE_T, OP_T> *,
                 node_sort_by_state_t
              >                                            all_nodes_sorted;

      const node_t<STATE_T, OP_T>                          *current_node;
      const node_t<STATE_T, OP_T>                          *current_node_temp;
      double                                               g_cost;
      double                                               h_cost;
      node_t<STATE_T, OP_T>                                new_node;
      typename std::list<node_t<STATE_T, OP_T> >::iterator new_node_iter;
      STATE_T                                              new_state;
      DATA_STRUCT                                          nodes_to_expand;
      typename search_result_t::value_type                 one_solution;
      std::pair<STATE_T, double>                           op_result;
      std::set<OP_T>                                       ops;
      search_result_t                                      rval;

      REPEATED_STATE_CHECKER_T::clear_states();
      nodes_created = 0;

      // Create a node from the initial state and store it.
      h_cost = HEURISTIC_T::apply_heuristic(initial_state);
      new_node = node_t<STATE_T, OP_T>(initial_state, 0, 0.0, h_cost);

      // We will call the repeated state checker here for consistency.  Since it
      // is called in the main loop for every generated node, it should be
      // called here for the initial node.  For the repeated state checkers we
      // implement, it won't make a difference.  However, for a user-supplied
      // repeated state checker, it could make a difference, so we must call it.
      REPEATED_STATE_CHECKER_T::seen_before(new_node, all_nodes_sorted);

      new_node_iter = all_nodes.insert(all_nodes.end(), new_node);
      nodes_to_expand.push(&(*new_node_iter));
      all_nodes_sorted.insert(&(*new_node_iter));

      ++nodes_created;

      // Search the state space...

      while (!nodes_to_expand.empty())
      {
         current_node = get_next_to_expand(nodes_to_expand);
         nodes_to_expand.pop();

         // If we have reached the goal state, store it and the operators that
         // led to it.
         if (GOAL_TEST_T::is_goal(current_node->state))
         {
            current_node_temp = current_node;

            one_solution.goal_state_reached = current_node_temp->state;
            one_solution.cost               = current_node_temp->g_cost;
            one_solution.operators.clear();

            while (current_node_temp->parent != NULL)
            {
               one_solution.operators.push_back(current_node_temp->op);
               current_node_temp = current_node_temp->parent;
            }

            std::reverse(
                           one_solution.operators.begin(),
                           one_solution.operators.end()
                        );

            rval.insert(one_solution);

            if (!return_all)
               break;
         }

         // If the next level won't be beyond the depth limit, expand the
         // current node.
         if (current_node->depth < depth_limit)
         {
            ops = OP_GEN_T::gen_ops(current_node->state);

            for (
                   typename std::set<OP_T>::iterator op_iter = ops.begin();
                   op_iter != ops.end();
                   ++op_iter
                )
            {
               op_result = OP_APPLY_T::apply_op(current_node->state, *op_iter);
               new_state = op_result.first;
               g_cost    = op_result.second;

               h_cost = HEURISTIC_T::apply_heuristic(new_state);

               new_node = node_t<STATE_T, OP_T>(
                                                  new_state,
                                                  current_node->depth + 1,
                                                  current_node->g_cost + g_cost,
                                                  h_cost,
                                                  current_node,
                                                  *op_iter
                                               );

               if (
                     REPEATED_STATE_CHECKER_T::seen_before(
                                                             new_node,
                                                             all_nodes_sorted
                                                          )
                  )
               {
                  continue;
               }

               new_node_iter = all_nodes.insert(all_nodes.end(), new_node);
               nodes_to_expand.push(&(*new_node_iter));
               all_nodes_sorted.insert(&(*new_node_iter));
               ++nodes_created;
            }
         }
      }

      return rval;
   } // search_engine_t::general_search

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <
               typename STATE_T,
               typename OP_T,
               typename OP_GEN_T,
               typename OP_APPLY_T,
               typename GOAL_TEST_T,
               typename REPEATED_STATE_CHECKER_T,
               typename HEURISTIC_T
            >
   template <typename DATA_STRUCT>
   const node_t<STATE_T, OP_T> *
   search_engine_t<
                     STATE_T,
                     OP_T,
                     OP_GEN_T,
                     OP_APPLY_T,
                     GOAL_TEST_T,
                     REPEATED_STATE_CHECKER_T,
                     HEURISTIC_T
                  >::get_next_to_expand(
                                          const DATA_STRUCT &nodes_to_expand
                                       ) const
   {
      return nodes_to_expand.top();
   } // search_engine_t::get_next_to_expand

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <
               typename STATE_T,
               typename OP_T,
               typename OP_GEN_T,
               typename OP_APPLY_T,
               typename GOAL_TEST_T,
               typename REPEATED_STATE_CHECKER_T,
               typename HEURISTIC_T
            >
   const node_t<STATE_T, OP_T> *
   search_engine_t<
                     STATE_T,
                     OP_T,
                     OP_GEN_T,
                     OP_APPLY_T,
                     GOAL_TEST_T,
                     REPEATED_STATE_CHECKER_T,
                     HEURISTIC_T
                  >::get_next_to_expand(
                const std::queue<const node_t<STATE_T, OP_T> *> &nodes_to_expand
                                       ) const
   {
      return nodes_to_expand.front();
   } // search_engine_t::get_next_to_expand

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <>
   class repeated_state_checker_t<0, null_repeated_state_checking_policy_t>
   {
      public:
         void clear_states() {}

         template <typename T1, typename T2>
         bool seen_before(
                            const T1                       &node,
                            const std::set<const T1 *, T2> &all_nodes_sorted
                         )
         {
            // Suppress compiler warnings about unused parameters
            static_cast<void>(node);
            static_cast<void>(all_nodes_sorted);

            return false;
         } // repeated_state_checker_t<0>::seen_before
   };

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <>
   class repeated_state_checker_t<1, null_repeated_state_checking_policy_t>
   {
      public:
         void clear_states() {}

         template <typename T1, typename T2>
         bool seen_before(
                            const T1                       &node,
                            const std::set<const T1 *, T2> &all_nodes_sorted
                         )
         {
            // Suppress compiler warnings about unused parameters
            static_cast<void>(all_nodes_sorted);

            if (node.parent != NULL)
            {
                if (node.state == node.parent->state)
                   return true;

                if (
                      (node.parent->parent) != NULL &&
                      (node.state == node.parent->parent->state)
                   )
                {
                   return true;
                }
            }

            return false;
         } // repeated_state_checker_t<1>::seen_before
   };

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <>
   class repeated_state_checker_t<2, null_repeated_state_checking_policy_t>
   {
      public:
         void clear_states() {}

         template <typename T1, typename T2>
         bool seen_before(
                            const T1                       &node,
                            const std::set<const T1 *, T2> &all_nodes_sorted
                         )
         {
            const T1 *ptr(&node);

            // Suppress compiler warnings about unused parameters
            static_cast<void>(all_nodes_sorted);

            while (ptr->parent != NULL)
            {
               if (node.state == ptr->parent->state)
                  return true;

               ptr = ptr->parent;
            }

            return false;
         } // repeated_state_checker_t<2>::seen_before
   };

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <>
   class repeated_state_checker_t<3, null_repeated_state_checking_policy_t>
   {
      public:
         void clear_states() {}

         template <typename T1, typename T2>
         bool seen_before(
                            const T1                       &node,
                            const std::set<const T1 *, T2> &all_nodes_sorted
                         )
         {
            if (all_nodes_sorted.find(&node) != all_nodes_sorted.end())
               return true;
            else
               return false;
         } // repeated_state_checker_t<3>::seen_before
   };

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <typename USER_SUPPLIED_CHECKER_T>
   class repeated_state_checker_t<4, USER_SUPPLIED_CHECKER_T>:
         private USER_SUPPLIED_CHECKER_T
   {
      public:
         void clear_states()
         {
            USER_SUPPLIED_CHECKER_T::clear_states();
         } // repeated_state_checker_t<5>::clear_states

         template <typename T1, typename T2>
         bool seen_before(
                            const T1                       &node,
                            const std::set<const T1 *, T2> &all_nodes_sorted
                         )
         {
            // Suppress compiler warnings about unused parameters
            static_cast<void>(all_nodes_sorted);

            return USER_SUPPLIED_CHECKER_T::seen_before(node.state);
         } // repeated_state_checker_t<4>::seen_before
   };
}
