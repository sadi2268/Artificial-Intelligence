#ifndef SEARCH_INCLUDED
#define SEARCH_INCLUDED

#include <queue>
#include <set>
#include <vector>

namespace dct
{
   // A std::set<> of these structs is what is returned to the user after a
   // search is completed.
   template <typename STATE_T, typename OP_T>
   struct search_result_template_t
   {
      STATE_T           goal_state_reached;
      double            cost;
      std::vector<OP_T> operators;
   };

   // This class provides an ordering criteria of result structures for
   // std::set<> to use.  It is not needed directly by the client but appears
   // here for the sake of name visibility below.
   template <typename STATE_T, typename OP_T>
   class result_comp_t;

   // This class template is used internally.  It is declared here to provide
   // visibility to its name down below.
   template <typename STATE_T, typename OP_T>
   struct node_t;

   // This class serves as a null heuristic policy for when a heuristic is not
   // needed (i.e. for all but greedy and A* search).  It is not used directly
   // by the user; it is used as a default template parameter.
   class null_heuristic_t;

   // Interfaces for class template search_engine_t policies:
   //
   // OP_GEN_T: std::set<OP_T> gen_ops(const STATE_T &);
   //
   // OP_APPLY_T: std::pair<STATE_T, double> apply_op(
   //                                                   const STATE_T &,
   //                                                   const OP_T &
   //                                                );
   //      Here, a state and the cost of the operator application are returned.
   //
   // GOAL_TEST_T: bool is_goal(const STATE_T &);
   //
   // REPEATED_STATE_CHECKER_T: Supply one of the canned policies, shown below
   //
   // HEURISTIC_T: double apply_heuristic(const STATE_T &);

   template <
               typename STATE_T,
               typename OP_T,
               typename OP_GEN_T,
               typename OP_APPLY_T,
               typename GOAL_TEST_T,
               typename REPEATED_STATE_CHECKER_T,
               typename HEURISTIC_T = null_heuristic_t
            >
   class search_engine_t: private OP_GEN_T,
                          private OP_APPLY_T,
                          private GOAL_TEST_T,
                          private REPEATED_STATE_CHECKER_T,
                          private HEURISTIC_T
   {
      public:
         typedef std::set<
                            search_result_template_t<STATE_T, OP_T>,
                            result_comp_t<STATE_T, OP_T>
                         > search_result_t;

         search_result_t a_star(
                                  const STATE_T &initial_state,
                                  bool          return_all = false
                               );

         search_result_t breadth_first(
                                         const STATE_T &initial_state,
                                         bool          return_all = false
                                      );

         search_result_t depth_first(
                                       const STATE_T &initial_state,
                                       bool          return_all = false
                                    );

         search_result_t depth_limited(
                                         const STATE_T &initial_state,
                                         unsigned int  depth_limit,
                                         bool          return_all = false
                                      );

         search_result_t greedy(
                                  const STATE_T &initial_state,
                                  bool          return_all = false
                               );

         // Upon success, this method will return exactly one solution - the
         // first one found.  This function may not be requested to find all
         // solutions.
         search_result_t iterative_deepening(
                                               const STATE_T &initial_state,
                                               unsigned int  depth_limit
                                            );

         search_result_t uniform_cost(
                                        const STATE_T &initial_state,
                                        bool          return_all = false
                                     );

         unsigned int get_nodes_created() const
         {
            return nodes_created;
         }

      private:
         class node_sort_by_state_t
         {
            public:
               bool operator()(
                                 const node_t<STATE_T, OP_T> *lhs,
                                 const node_t<STATE_T, OP_T> *rhs
                              ) const
               {
                  return (lhs->state < rhs->state);
               }
         };

         class node_sort_by_g_t
         {
            public:
               bool operator()(
                                 const node_t<STATE_T, OP_T> *lhs,
                                 const node_t<STATE_T, OP_T> *rhs
                              ) const
               {
                  return (lhs->g_cost > rhs->g_cost);
               }
         };

         class node_sort_by_h_t
         {
            public:
               bool operator()(
                                 const node_t<STATE_T, OP_T> *lhs,
                                 const node_t<STATE_T, OP_T> *rhs
                              ) const
               {
                  return (lhs->h_cost > rhs->h_cost);
               }
         };

         class node_sort_by_g_plus_h_t
         {
            public:
               bool operator()(
                                 const node_t<STATE_T, OP_T> *lhs,
                                 const node_t<STATE_T, OP_T> *rhs
                              ) const
               {
                  return (
                            (lhs->g_cost + lhs->h_cost) >
                            (rhs->g_cost + rhs->h_cost)
                         );
               }
         };

         template <typename DATA_STRUCT>
         search_result_t general_search(
                                          const STATE_T &initial_state,
                                          unsigned int  depth_limit,
                                          bool          return_all
                                       );

         template <typename DATA_STRUCT>
         const node_t<STATE_T, OP_T> *get_next_to_expand(
                                              const DATA_STRUCT &nodes_to_expand
                                                        ) const;

         const node_t<STATE_T, OP_T> *get_next_to_expand(
                const std::queue<const node_t<STATE_T, OP_T> *> &nodes_to_expand
                                                        ) const;

         unsigned int nodes_created;
   };

   // This class is used as a default template argument for the class template
   // repeated_state_checker_t shown below.  This allows the user to not
   // supply a policy in the cases where one is not needed.
   class null_repeated_state_checking_policy_t;

   // Policy classes for checking for repeated states are generated by
   // instantiating this class template with an integer.  Policies are as
   // follows:
   //
   // 0: Do not check for repeated states
   // 1: Don't go back to where we came from or loop to ourself
   // 2: Don't return to any ancestors
   // 3: Check all previous states via lookup
   // 4: User-supplied repeated state checker
   //       This must be instantiated with a user policy that has this
   //       interface:
   //          void clear_states(); // Delete all stored states
   //          bool seen_before(const STATE_T &state);
   //       Here, STATE_T is the user-defined type of a state.

   template <
               unsigned int N,
               typename USER_SUPPLIED_CHECKER_T =
                        null_repeated_state_checking_policy_t
            >
   class repeated_state_checker_t: private USER_SUPPLIED_CHECKER_T
   {
      public:
         void clear_states();

         template <typename T1, typename T2>
         bool seen_before(
                            const T1                       &node,
                            const std::set<const T1 *, T2> &all_nodes_sorted
                         );
   };
}

#include "search.inl"

#endif
