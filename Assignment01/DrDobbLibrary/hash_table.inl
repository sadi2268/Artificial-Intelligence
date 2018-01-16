#include <algorithm>

namespace dct
{
   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <typename ELEMENT_TYPE, unsigned int BUCKETS, typename HASH_FUNC>
   void hash_table_t<
                       ELEMENT_TYPE,
                       BUCKETS,
                       HASH_FUNC
                    >::clear()
   {
      for (typename buckets_t::size_type i = 0; i != buckets.size(); ++i)
         buckets[i].clear();
   } // hash_table_t::clear

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <typename ELEMENT_TYPE, unsigned int BUCKETS, typename HASH_FUNC>
   void hash_table_t<
                       ELEMENT_TYPE,
                       BUCKETS,
                       HASH_FUNC
                    >::delete_element(const ELEMENT_TYPE &element)
   {
      typename buckets_t::size_type
               bucket_idx(HASH_FUNC::hash(element) % BUCKETS);

      bucket_t &bucket(buckets[bucket_idx]);

      bucket.remove(element);
   } // hash_table_t::delete_element

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <typename ELEMENT_TYPE, unsigned int BUCKETS, typename HASH_FUNC>
   bool hash_table_t<
                       ELEMENT_TYPE,
                       BUCKETS,
                       HASH_FUNC
                    >::element_exists(const ELEMENT_TYPE &element)
   {
      typename buckets_t::size_type
               bucket_idx(HASH_FUNC::hash(element) % BUCKETS);

      const bucket_t &bucket(buckets[bucket_idx]);

      return std::find(bucket.begin(), bucket.end(), element) != bucket.end();
   } // hash_table_t::element_exists

   // **************************************************************************
   // **************************************************************************
   // **************************************************************************
   template <typename ELEMENT_TYPE, unsigned int BUCKETS, typename HASH_FUNC>
   void hash_table_t<
                       ELEMENT_TYPE,
                       BUCKETS,
                       HASH_FUNC
                    >::insert_element(const ELEMENT_TYPE &element)
   {
      typename buckets_t::size_type
               bucket_idx(HASH_FUNC::hash(element) % BUCKETS);

      bucket_t &bucket(buckets[bucket_idx]);

      // Consciously allow an element to be inserted multiple times as opposed
      // to, for every insertion, checking if the element already exists.  This
      // will not affect correctness and is simpler.  As far as efficiency,
      // it's a tossup as one can construct usage scenarios where either method
      // is superior to the other.  So, I must concede that this is a somewhat
      // arbitrary decision.
      bucket.push_front(element);
   } // hash_table_t::insert_element
}
