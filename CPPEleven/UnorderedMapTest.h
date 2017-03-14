#pragma once
#include "SimpleRV.h"


using SimpleUnorderMap = std::unordered_map<std::string, SimpleRV>;
using StrSRvPair = std::pair<std::string, SimpleRV>;

using StrMap = std::map< std::string, std::string >;
using StrUnorderMap = std::unordered_map< std::string, std::string >;

void unordered_map_test( );

void unordered_hasher_test( );

void map_unord_map_compare( );

StrMap fill_map( std::vector<int>& indices );

StrUnorderMap fill_unord_map( std::vector<int>& indices );

StrUnorderMap fill_unord_map_cap( std::vector<int>& indices );

void hasher_test( );