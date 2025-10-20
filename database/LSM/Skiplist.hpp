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

            class Iterator{
                public:
                    explicit Iterator(const SkipList* list);

                    // Change the underlying skiplist used for this iterator
                    // This enables us not changing the iterator without deallocating
                    // an old one and then allocating a new one
                    void SetList(const SkipList* list);

                    // Returns true if and only the iterator is positioned at a valid node, else false.
                    bool Valid() const;

                    // Returns the key at the current position.
                    // REQUIRES: Valid()
                    const Key& key() const;

                    // Advances to the next position.
                    // REQUIRES: Valid()
                    void Next();

                    // Advances to the previous position.
                    // REQUIRES: Valid()
                    void Prev();

                    // Advance to the first entry with a key >= target
                    void Seek(const Key& target);

                    // Retreat to the last entry with a key <= target
                    void SeekForPrev(const Key& target);

                    // Position at the first entry in list.
                    // Final state of iterator is Valid() iff list is not empty.
                    void SeekToFirst();

                    // Position at the last entry in list.
                    // Final state of iterator is Valid() iff list is not empty.
                    void SeekToLast();

                private:
                    const SkipList* list_;
                    Node* node_;
                    // Intentionally copyable
                };   
                    // Immutable after construction
                    Comparator const compare_;
                    Allocator* const allocator_;  // Allocator used for allocations of nodes
                    
    };
}
#endif