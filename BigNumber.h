#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "ConversionInterface.h"
#include "ConvertStringToNumberArray.h"
#include "ConvertStringToByteArray.h"

using namespace std;
class BigNumber
{
public:
	BigNumber();
	//i give it a string of digits and a radix and inside it i invoke the method convert tointernal 
	BigNumber( const char * str , int & str_length , CONVERT_TYPES type );

	//make sure that i destroy any memory allocated
	~BigNumber();

	//convert from internal to string in desired radix
	void ConvertToStringFromNumberArray(char* _result_buf, int & _result_buf_Length, CONVERT_TYPES _type = TYPE_DECIMAL);

	void ConvertToStringFromByteArray(char* _result_buf, int & _result_buf_Length, CONVERT_TYPES _type = TYPE_DECIMAL);
	
	//convert the passed string from the app with the radix of that the number in that string ..
	//..checking if the passed string is viable and within the correct range and digits of that radix
	void ConvertToInternalNumberArray(const char* _str, int & _str_length, int* & _result_buf, int& _buf_Length, CONVERT_TYPES _type);
	
	void ConvertToInternalByteArray(const char* _str, int & _str_length, int* & _result_buf, int& _buf_Length, CONVERT_TYPES _type);

	void Print_Internal_data(void);
	void Print_Internal_byte_data(void);
	BigNumber operator+(const BigNumber & _right_operand);

private:
	//this internal data should holds values of 1s or 0s each 1/0 is in an int
	int* internal_data;
	int internal_data_length=0;
	 
	int* internal_byte_data;
	int internal_byte_data_length = 0;
};

