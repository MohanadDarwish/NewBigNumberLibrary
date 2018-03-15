#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

#include "ConversionInterface.h"

using namespace std;

#define SUCCESS  0
#define CONVERSION_ERROR 1

class ConvertStringToNumberArray :
	public ConversionInterface
{
public:
	ConvertStringToNumberArray();
	~ConvertStringToNumberArray();

	void ConvertToString(int* _num, int& _num_length, char* _result_buf, int& _buf_Length, CONVERT_TYPES _type);

	//using the passed type to distinguish what type is the number string passed to convert to the correct value of internal data type
	void ConvertToInternal(const char* _str, int str_num_length ,int*& _result_buf , int& result_buf_length, CONVERT_TYPES _type);
	
private:
	char ToInternalFromHex(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length);
	char ToInternalFromDecimal(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length);
	char ToInternalFromBin(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length);
	
	char ConvertToHex(int* _internal_num , int &_internal_num_length ,  char* _result_buf , int& _result_buf_Length);
	char ConvertToDecimal(int* _internal_num , int & _internal_num_length ,  char*& _result_buf , int& _result_buf_Length);
		int ToDecimal(int* _internal_num, int& _internal_num_length, char*& _result_buf, int& _result_buf_Length);
		void update_bcd_digit_value_coressponding_to_its_current_value(vector< vector<char> >& whole_num_bcd_vector);
		void shift_whole_num_bcd_vector_left(vector< vector<char> >& whole_num_bcd_vector);
		size_t Convert_String_to_Decimal_vector(int* _internal_num, int& _internal_num_length, char* _result_buf, int& _result_buf_Length);
	char ConvertToBin(int* _internal_num , int & _internal_num_length ,  char* _result_buf , int& _result_buf_Length);

	int Divide_Decimal_vector_by_Two(vector<int>& decimal_array, vector<int>& quotient);
	
};

