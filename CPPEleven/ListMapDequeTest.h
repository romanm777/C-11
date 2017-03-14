#pragma once
#include "SimpleRV.h"

void compare_perf( );

void stack_test( );

void map_multimap_test( );

void list_test( );

void vector_test( );

using SimpleVec = std::vector<SimpleRV>;
using SimpleList = std::list<SimpleRV>;
using SimpleDeque = std::deque<SimpleRV>;

using IntVec = std::vector<int>;
using IntList = std::list<int>;
using IntDeque = std::deque<int>;
