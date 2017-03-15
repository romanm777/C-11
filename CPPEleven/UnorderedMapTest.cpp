#include "stdafx.h"
#include "UnorderedMapTest.h"
#include "GetTime.h"
#include "Windows.h"

const int Count = 100000;

using IntVec = std::vector<int>;

void unordered_map_test( )
{
	std::cout << std::endl << "=================== Unordered_map test =========================" << std::endl;

	const int count = 508;//100;
	SimpleUnorderMap my_map;

	// bucket count
	size_t bucket_count = my_map.bucket_count( );
	std::cout << "bucket_count( ): " << bucket_count << std::endl;

	// reserve
	std::cout << "reserve()" << std::endl;
	my_map.reserve( count + 2 );

	for ( int i = 0; i < count; ++i ) {
		StrSRvPair pair = StrSRvPair( "key " + std::to_string( i ), SimpleRV( "item " + std::to_string( i ) ) );
		my_map.insert( pair );
	}

	// at()
	std::cout << "at( )" << std::endl;
	try
	{
		const SimpleRV& val = my_map.at( "key 3" );
		std::cout << *val.m_names.begin( ) << std::endl;
	}
	catch ( std::out_of_range& exc )
	{
		std::cout << exc.what( ) << std::endl;
	}

	// bucket()
	std::cout << "bucket( )" << std::endl;
	std::vector< size_t > buckets;
	for ( int i = 0; i < count / 10; ++i )
	{
		std::string key( "key " + std::to_string( i ) );
		size_t bucket = my_map.bucket( key );
		std::cout << "\"" << key << "\" is in bucket " << bucket << std::endl;

		buckets.push_back( bucket );
	}

	// bucket_cout
	bucket_count = my_map.bucket_count( );
	std::cout << "bucket_count( ): " << bucket_count << std::endl;

	//	unordered_map::bucket_size
	for (size_t bucket : buckets )
	{
		std::cout << "bucket_size( ) of bucket " << bucket << ": " << my_map.bucket_size( bucket ) << std::endl;
	}

	//	unordered_map::count
	std::cout << "count( ) of key 34: " << my_map.count( "key 34" ) << std::endl;

	//	unordered_map::emplace
	my_map.emplace( StrSRvPair( "key 27", SimpleRV( "emplace item" ) ) );
	std::cout << "emplace( ): \"key 27\", SimpleRV( \"emplace item\" " << std::endl;
	std::cout << "item with a key \"key 27\" is " << "\"" << *(my_map.at( "key 27" ).m_names.begin( )) << "\"" << std::endl;

	my_map.emplace( StrSRvPair( "key 27e", SimpleRV( "emplace item extend" ) ) );
	std::cout << "emplace( ): \"key 27e\", SimpleRV( \"emplace item extend\" " << std::endl;
	std::cout << "item with a key \"key 27\" is " << "\"" << *(my_map.at( "key 27e" ).m_names.begin( )) << "\"" << std::endl;

	//	unordered_map::emplace_hint
	const std::string key( "key 17 emplace_hint" );
	my_map.emplace_hint( my_map.end( ), key, SimpleRV( "item 17 emplace_hint" ) );
	std::cout << "item with a key \"" << key << "\" is \"" << *(my_map.at( key ).m_names.begin( )) << "\"" << std::endl;

	//	unordered_map::equal_range
	std::pair< SimpleUnorderMap::iterator, SimpleUnorderMap::iterator > range = my_map.equal_range( "key 20" );

	//	unordered_map::hash_function
	SimpleUnorderMap::hasher fn = my_map.hash_function( );
	std::cout << "this " << fn( "this" ) << std::endl;
	std::cout << "bla-bla " << fn( "bla-bla" ) << std::endl;

	//	unordered_map::load_factor
	//	unordered_map::max_bucket_count
	//	unordered_map::max_load_factor
	//	unordered_map::max_size
	std::cout << "size = " << my_map.size( ) << std::endl;
	std::cout << "max_size = " << static_cast< int >(my_map.max_size( )) << std::endl;
	std::cout << "bucket_count = " << my_map.bucket_count( ) << std::endl;
	std::cout << "max_bucket_count = " << my_map.max_bucket_count( ) << std::endl;
	std::cout << "load_factor = " << my_map.load_factor( ) << std::endl;
	std::cout << "max_load_factor = " << my_map.max_load_factor( ) << std::endl;

	//	unordered_map::operator=
	//	unordered_map::operator[]
	//	unordered_map::rehash
	//	unordered_map::reserve
	//	unordered_map::size
	//	unordered_map::swap
}

void unordered_hasher_test( )
{

}

void access_items( StrUnorderMap& umap, const IntVec& indices )
{
	const size_t size = indices.size( );
	for( int i = 0; i < size; i += 3 )
	{
		std::string& str = umap.at( "first key " + std::to_string( indices[i] ) );
	}
}

void access_items( StrMap& map, const IntVec& indices )
{
	const size_t size = indices.size( );
	for( int i = 0; i < size; i += 3 )
	{
		std::string& str = map.at( "first key " + std::to_string( indices[i] ) );
	}
}

void map_unord_map_compare( )
{
	Sleep( 2000 );

	std::cout << std::endl << "=================== Map vs unordered_map test =========================" << std::endl;

	/** filling the first*/
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::vector<int> indices;
	for ( int i = 0; i < Count / 2; ++i )
	{
		indices.push_back( i );
		indices.push_back( Count - 1 - i );
	}

	/** Unordered_map */
	size_t size = indices.size( );

	MyTime start = get_time_ex( );
	StrUnorderMap u_map = fill_unord_map( indices );
	MyTime end = get_time_ex( );
	std::cout << "Unorder map fill time: " << end.m_clock - start.m_clock << std::endl;

	/** Unordered_map with capacity */

	start = get_time_ex( );
	StrUnorderMap u_map_cap = fill_unord_map_cap( indices );
	end = get_time_ex( );
	std::cout << "Unorder map (capacity) fill time: " << end.m_clock - start.m_clock << std::endl;

	/** Map */
	start = get_time_ex( );
	StrMap map = fill_map( indices );
	end = get_time_ex( );
	std::cout << "Map fill time: " << end.m_clock - start.m_clock << std::endl;

	//
	//
	//
	/** *****************************/
	start = get_time_ex( );
	access_items( map, indices );
	end = get_time_ex( );
	std::cout << "Map access time: " << end.m_clock - start.m_clock << std::endl;

	start = get_time_ex( );
	access_items( u_map, indices );
	end = get_time_ex( );
	std::cout << "Unord_map access time: " << end.m_clock - start.m_clock << std::endl;

	start = get_time_ex( );
	access_items( u_map_cap, indices );
	end = get_time_ex( );
	std::cout << "Unord_map (cap) access time: " << end.m_clock - start.m_clock << std::endl;

	/******************************************************/
	//std::unordered_map<int, std::string, KeyHasher>	map_hasher;


}



/** Service functios */

StrMap fill_map( std::vector<int>& indices )
{
	StrMap map;

	const size_t size = indices.size( );
	for ( int i = 0; i < size; ++i )
	{
		map.insert( std::make_pair( "first key " + std::to_string( indices[i] ), "item " + std::to_string( indices[i] ) ) );
	}

	return map;
}

StrUnorderMap fill_unord_map( std::vector<int>& indices )
{
	StrUnorderMap u_map;

	const size_t size = indices.size( );
	for ( int i = 0; i < size; ++i )
	{
		u_map.insert( std::make_pair( "first key " + std::to_string( indices[i] ), "item " + std::to_string( indices[i] ) ) );
	}

	return u_map;
}

StrUnorderMap fill_unord_map_cap( std::vector<int>& indices )
{
	StrUnorderMap u_map_cap;
	size_t buckets = u_map_cap.bucket_count( );
	u_map_cap.reserve( Count + 100 );
	size_t new_bucket = u_map_cap.bucket_count( );

	const size_t size = indices.size( );
	for ( int i = 0; i < size; ++i )
	{
		u_map_cap.insert( std::make_pair( "first key " + std::to_string( indices[i] ), "item " + std::to_string( indices[i] ) ) );
	}

	return u_map_cap;
}

/****************************************************************/


struct KeyHasher
{
	std::size_t operator()( const std::string& key ) const
	{
		size_t hash = std::hash< std::string >( )( key );
		/*return ((hash<string>( )(k.first)
			^ (hash<string>( )(k.second) << 1)) >> 1)
			^ (hash<int>( )(k.third) << 1);*/

		return hash; // +(rand( ) << 2) + rand( );
	}
};

using HashUnordMap = std::unordered_map<std::string, std::string, KeyHasher>;
using UnordMap = std::unordered_map<std::string, std::string>;
using SizeTVec = std::vector< size_t >;
using SizeTSet = std::set< size_t >;

template <typename T>
void create_umap( std::unordered_map<std::string, std::string, T>& umap, const IntVec& indices );

template <typename T>
void show_buckets_count( std::unordered_map<std::string, std::string, T>& umap );

template <typename T>
void access_items( std::unordered_map<std::string, std::string, T>& umap );

void create_umap_with_hasher( HashUnordMap& umap, const IntVec& indices )
{
	create_umap( umap, indices );
}

void create_umap_simple( UnordMap& umap, const IntVec& indices )
{
	create_umap(umap, indices );
}

void show_buckets_hasher( HashUnordMap& umap )
{
	show_buckets_count(umap);
}

void show_buckets_simple( UnordMap& umap )
{
	show_buckets_count(umap);
}

IntVec CreateIndices( const int size )
{
	IntVec indices;
	for( int i = 0; i < size / 2; ++i )
	{
		indices.push_back( i );
		indices.push_back( Count - 1 - i );
	}

	return indices;
}

const int Size = 1000;

void hasher_test( )
{
	Sleep( 2000 );

	IntVec indices = CreateIndices( Size );

	// map with my hasher
	HashUnordMap u_map_hasher;// = { { "John", "first" }, { "Mary", "another" } };
	create_umap_with_hasher( u_map_hasher, indices );
	
	show_buckets_hasher( u_map_hasher );

	// map without my hasher
	UnordMap u_map;// = { { "John", "first" }, { "Mary", "another" } };
	create_umap_simple( u_map, indices );

	show_buckets_simple( u_map );
}

template <typename T>
void create_umap( std::unordered_map<std::string, std::string, T>& umap, const IntVec& indices )
{
	std::cout << "Bucket number before fill: " << umap.bucket_count( ) << std::endl;

	const size_t ind_size = indices.size( );

	for ( int i = 0; i < ind_size; ++i )
	{
		umap.emplace( std::unordered_map<std::string, std::string, T>::value_type( "Leon" + std::to_string( indices[i] ), "worker" + std::to_string( indices[i] ) ) );
	}

	std::cout << "Bucket number after fill: " << umap.bucket_count( ) << std::endl;
}

template <typename T>
void show_buckets_count( std::unordered_map<std::string, std::string, T>& umap )
{
	const size_t size = umap.size( );
	SizeTVec buckets;

	for ( int i = 0; i < size; ++i )
	{
		buckets.push_back( umap.bucket( "Leon" + std::to_string( i ) ) );
	}

	SizeTSet not_unique_buckets;

	std::sort( buckets.begin( ), buckets.end( ) );
	SizeTVec::iterator it = std::unique( buckets.begin( ), buckets.end( ), [&not_unique_buckets]( const size_t& first, const size_t& second ) {
		bool is_equal = first == second;

		if ( is_equal )
		{
			not_unique_buckets.emplace( first );
		}

		return is_equal;
	} );

	int i = 0;
	for ( SizeTSet::iterator it = not_unique_buckets.begin( ); it != not_unique_buckets.end( ); ++it, ++i )
	{
		//std::cout << "Bucket #" << *it << " has " << umap.bucket_size( *it ) << " items." << std::endl;
	}

	std::cout << i << " of " << umap.bucket_count( ) << " buckets has more than 1 item. Other buckets has 0 or 1 item" << std::endl;
}

template <typename T>
void access_items( std::unordered_map<std::string, std::string, T>& umap )
{
	;
}