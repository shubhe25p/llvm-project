//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <algorithm>

// template<InputIterator Iter1, ForwardIterator Iter2>
//   requires HasEqualTo<Iter1::value_type, Iter2::value_type>
//   constexpr Iter1  // constexpr after C++17
//   find_first_of(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2);

#include <algorithm>
#include <cassert>
#include <iterator>

#include "test_macros.h"
#include "test_iterators.h"

#if TEST_STD_VER > 17
TEST_CONSTEXPR bool test_constexpr() {
    int ia[] = {1, 2, 3};
    int ib[] = {7, 8, 9};
    int ic[] = {0, 1, 2, 3, 4, 5, 0, 1, 2, 3};
    typedef forward_iterator<int*>       FI;
    typedef bidirectional_iterator<int*> BI;
    typedef random_access_iterator<int*> RI;

    return    (std::find_first_of(FI(std::begin(ic)), FI(std::end(ic)), FI(std::begin(ia)), FI(std::end(ia))) == FI(ic+1))
           && (std::find_first_of(FI(std::begin(ic)), FI(std::end(ic)), FI(std::begin(ib)), FI(std::end(ib))) == FI(std::end(ic)))
           && (std::find_first_of(BI(std::begin(ic)), BI(std::end(ic)), BI(std::begin(ia)), BI(std::end(ia))) == BI(ic+1))
           && (std::find_first_of(BI(std::begin(ic)), BI(std::end(ic)), BI(std::begin(ib)), BI(std::end(ib))) == BI(std::end(ic)))
           && (std::find_first_of(RI(std::begin(ic)), RI(std::end(ic)), RI(std::begin(ia)), RI(std::end(ia))) == RI(ic+1))
           && (std::find_first_of(RI(std::begin(ic)), RI(std::end(ic)), RI(std::begin(ib)), RI(std::end(ib))) == RI(std::end(ic)))
           ;
    }
#endif

template <class Iter1, class Iter2>
void test_all_cases() {
    int ia[] = {0, 1, 2, 3, 0, 1, 2, 3};
    const unsigned sa = sizeof(ia) / sizeof(ia[0]);
    int ib[] = {1, 3, 5, 7};
    const unsigned sb = sizeof(ib) / sizeof(ib[0]);
    int ic[] = {7};
    int ie[] = {0};

    // Case 1: match found in the middle
    assert(std::find_first_of(Iter1(ia), Iter1(ia + sa),
                              Iter2(ib), Iter2(ib + sb)) ==
                              Iter1(ia + 1));

    // Case 2: no match (search value not in first range)
    assert(std::find_first_of(Iter1(ia), Iter1(ia + sa),
                              Iter2(ic), Iter2(ic + 1)) ==
                              Iter1(ia + sa));

    // Case 3: empty second range
    assert(std::find_first_of(Iter1(ia), Iter1(ia + sa),
                              Iter2(ic), Iter2(ic)) ==
                              Iter1(ia + sa));

    // Case 4: empty first range
    assert(std::find_first_of(Iter1(ia), Iter1(ia),
                              Iter2(ic), Iter2(ic + 1)) ==
                              Iter1(ia));

    // Case 5: non-empty first range, empty second range
    assert(std::find_first_of(Iter1(ib), Iter1(ib + sb),
                              Iter2(ic), Iter2(ic)) ==
                              Iter1(ib + sb));

    // Case 6: both ranges empty
    assert(std::find_first_of(Iter1(ie), Iter1(ie),
                              Iter2(ie), Iter2(ie)) ==
                              Iter1(ie));

    // Case 7: empty first range, empty second range (different arrays)
    assert(std::find_first_of(Iter1(ie), Iter1(ie),
                              Iter2(ic), Iter2(ic)) ==
                              Iter1(ie));

    // Case 8: match at the beginning of subrange
    assert(std::find_first_of(Iter1(ia + 3), Iter1(ia + sa),
                              Iter2(ib), Iter2(ib + sb)) ==
                              Iter1(ia + 3));
}

int main(int, char**)
{
    // Iter1: cpp17_input_iterator, Iter2: forward_iterator
    test_all_cases<cpp17_input_iterator<const int*>, forward_iterator<const int*>>();
    // Iter1: cpp17_input_iterator, Iter2: bidirectional_iterator
    test_all_cases<cpp17_input_iterator<const int*>, bidirectional_iterator<const int*>>();
    // Iter1: cpp17_input_iterator, Iter2: random_access_iterator
    test_all_cases<cpp17_input_iterator<const int*>, random_access_iterator<const int*>>();

    // Iter1: forward_iterator, Iter2: forward_iterator
    test_all_cases<forward_iterator<const int*>, forward_iterator<const int*>>();
    // Iter1: forward_iterator, Iter2: bidirectional_iterator
    test_all_cases<forward_iterator<const int*>, bidirectional_iterator<const int*>>();
    // Iter1: forward_iterator, Iter2: random_access_iterator
    test_all_cases<forward_iterator<const int*>, random_access_iterator<const int*>>();

    // Iter1: bidirectional_iterator, Iter2: forward_iterator
    test_all_cases<bidirectional_iterator<const int*>, forward_iterator<const int*>>();
    // Iter1: bidirectional_iterator, Iter2: bidirectional_iterator
    test_all_cases<bidirectional_iterator<const int*>, bidirectional_iterator<const int*>>();
    // Iter1: bidirectional_iterator, Iter2: random_access_iterator
    test_all_cases<bidirectional_iterator<const int*>, random_access_iterator<const int*>>();

    // Iter1: random_access_iterator, Iter2: forward_iterator
    test_all_cases<random_access_iterator<const int*>, forward_iterator<const int*>>();
    // Iter1: random_access_iterator, Iter2: bidirectional_iterator
    test_all_cases<random_access_iterator<const int*>, bidirectional_iterator<const int*>>();
    // Iter1: random_access_iterator, Iter2: random_access_iterator
    test_all_cases<random_access_iterator<const int*>, random_access_iterator<const int*>>();

    // Iter1 and Iter2 as plain pointers
    test_all_cases<const int*, const int*>();

    // Mixed: plain pointer with wrapped iterators
    test_all_cases<const int*, forward_iterator<const int*>>();
    test_all_cases<const int*, bidirectional_iterator<const int*>>();
    test_all_cases<const int*, random_access_iterator<const int*>>();
    test_all_cases<forward_iterator<const int*>, const int*>();
    test_all_cases<bidirectional_iterator<const int*>, const int*>();
    test_all_cases<random_access_iterator<const int*>, const int*>();

#if TEST_STD_VER > 17
    static_assert(test_constexpr());
#endif

  return 0;
}
