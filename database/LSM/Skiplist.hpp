//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// Thread safety
// -------------
//
// Writes require external synchronization, most likely a mutex.
// Reads require a guarantee that the SkipList will not be destroyed
// while the read is in progress.  Apart from that, reads progress
// without any internal locking or synchronization.
//
// Invariants:
//
// (1) Allocated nodes are never deleted until the SkipList is
// destroyed.  This is trivially guaranteed by the code since we
// never delete any skip list nodes.
//
// (2) The contents of a Node except for the next/prev pointers are
// immutable after the Node has been linked into the SkipList.
// Only Insert() modifies the list, and it is careful to initialize
// a node and use release-stores to publish the nodes in one or
// more lists.
//
// ... prev vs. next pointer ordering ...
//

#ifndef STORAGE_HYDRADB_SKIPLIST_HPP
#define STORAGE_HYDRADB_SKIPLIST_HPP

// Thread safety
// -------------
//
// Writes require external synchronization, most likely a mutex.
// Reads require a guarantee that the SkipList will not be destroyed
// while the read is in progress.  Apart from that, reads progress
// without any internal locking or synchronization.
//
// Invariants:
//
// (1) Allocated nodes are never deleted until the SkipList is
// destroyed.  This is trivially guaranteed by the code since we
// never delete any skip list nodes.
//
// (2) The contents of a Node except for the next/prev pointers are
// immutable after the Node has been linked into the SkipList.
// Only Insert() modifies the list, and it is careful to initialize
// a node and use release-stores to publish the nodes in one or
// more lists.
//
// ... prev vs. next pointer ordering ...

#include <atomic>
#include <cassert>
#include <cstdlib>

namespace hydradb{
    template <typename Key, class Comparator>
    class SkipList{
        private:
            struct Node; //need to define later
        public:
            //Create a skiplist object that uses a comparator for byte comparisons, and allocate memory as needed.
            explicit SkipList(Comparator cmp, Node SUBSTITUTE_HERE); //memory managemnet
            SkipList(const SkipList&) = delete; //remove the ~ operator
            SkipList& operator=(const SkipList&) = delete; //remove the deletion operator 
            // Insert key into the list.
            // REQUIRES: nothing that compares equal to key is currently in the list.
            void Insert(const Key& key);

            // Returns true iff an entry that compares equal to key is in the list.
            bool Contains(const Key& key) const;

            // Return estimated number of entries from `start_ikey` to `end_ikey`.
            uint64_t ApproximateNumEntries(const Slice& start_ikey, const Slice& end_ikey) const;


    };
}
#endif