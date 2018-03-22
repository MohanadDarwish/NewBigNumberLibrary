#pragma once

#include <iostream>
using namespace std;

enum CONVERT_TYPES { 
		TYPE_BINARY  ,
		TYPE_DECIMAL ,
		TYPE_HEX 
};

class ConversionInterface
{
public:
	ConversionInterface();
	~ConversionInterface();

	//pure virtual interface converting from string to internal
	virtual void ConvertToInternal(const char* _str, int str_num_length, int*& _result_buf, int& result_buf_length, CONVERT_TYPES _type) = 0;
	
	//pure virtual interface converting from internal to string
	virtual void ConvertToString(int* _num, int& _num_length, char* _result_buf, int& _buf_Length, CONVERT_TYPES _type) = 0;
};

