#ifndef HASH_TABLE_INCLUDED
#define HASH_TABLE_INCLUDED

#include <list>
#include <vector>

namespace dct
{
   // HASH_FUNC is a policy class which must have the following public method:
   // unsigned int hash(const ELEMENT_TYPE &element);
   //
   // This method must return an integer hash value for element.

   template <typename ELEMENT_TYPE, unsigned int BUCKETS, typename HASH_FUNC>
   class hash_table_t: private HASH_FUNC
   {
      public:
         hash_table_t(): buckets(BUCKETS) {}

         void clear();
         void delete_element(const ELEMENT_TYPE &element);
         bool element_exists(const ELEMENT_TYPE &element);
         void insert_element(const ELEMENT_TYPE &element);

      private:
         typedef std::list<ELEMENT_TYPE> bucket_t;
         typedef std::vector<bucket_t>   buckets_t;

         buckets_t buckets;
   };
}

#include "hash_table.inl"

#endif
