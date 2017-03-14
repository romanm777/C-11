#pragma once

struct MyTime
{
	__int64 m_time;
	clock_t m_clock;
};

__int64 get_time( );

MyTime get_time_ex( );
