#pragma once

#include <string>
#include <iostream>
#include <charconv>
#include <limits>
#include <cassert>
using namespace std;

//переводит введенную строку в число(раюотает до того, пока не введется число, которое находится между min и max)
template<typename T>
T InputArithmetic(T min = numeric_limits<T>::min(), T max = numeric_limits<T>::max())
{
	assert(min <= max);
	T val;
	string input_str;
	while(true)
	{
		getline(cin, input_str);
		auto res = from_chars(input_str.c_str(), input_str.c_str() + input_str.size(), val);
		if (res.ec != std::errc() || res.ptr != input_str.c_str() + input_str.size())
		{
			cout << "Попрбуйте еще раз!" << endl;
			continue;
		}
		else if(val <= max && val >= min)
			break;
		else
		{
			cout << "Попрбуйте еще раз!" << endl;
			continue;
		}
	}
	return val;
}
