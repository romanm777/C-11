#include "stdafx.h"
#include "GetTime.h"

__int64 get_time( )
{
	//return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	time_t temp;
	time( &temp );

	return (__int64)temp;
}

MyTime get_time_ex( )
{
	MyTime temp;

	time( &temp.m_time );
	temp.m_clock = clock( );

	return temp;
}