#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <bitset>

#include "ConversionInterface.h"

using namespace std;

#define SUCCESS  0
#define CONVERSION_ERROR 1

#define SET_BIT_IN_BYTE(_BYTE, _BIT, _VALUE)   (  (_BYTE) = ( _BYTE & (~( 1 << _BIT )) ) | (_VALUE << _BIT)  )

class ConvertStringToByteArray :
	public ConversionInterface
{
public:
	ConvertStringToByteArray();
	~ConvertStringToByteArray();
	//========================================================//
	void ConvertToInternal(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length, CONVERT_TYPES _type);

	char ToInternalFromHex(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length);
	char ToInternalFromDecimal(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length);
	char ToInternalFromBin(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length);
	//========================================================//
	void ConvertToString(int* _num, int& _num_length, char* _result_buf, int& _result_buf_Length, CONVERT_TYPES _type);

	char ConvertToHex(int* _internal_num, int &_internal_num_length, char* _result_buf, int& _result_buf_Length);
	int ToHex(int*_internal_num, int& _internal_num_length, char* _result_buf, int& _result_buf_Length);
	char ConvertToDecimal(int* _internal_num, int & _internal_num_length, char*& _result_buf, int& _result_buf_Length);
	int ToDecimal(int* _internal_num, int& _internal_num_length, char*& _result_buf, int& _result_buf_Length);
	void update_bcd_digit_value_coressponding_to_its_current_value(vector< vector<char> >& whole_num_bcd_vector);
	void shift_whole_num_bcd_vector_left(vector< vector<char> >& whole_num_bcd_vector);
	size_t Convert_String_to_Decimal_vector(int* _internal_num, int& _internal_num_length, char* _result_buf, int& _result_buf_Length);
	char ConvertToBin(int* _internal_num, int & _internal_num_length, char* _result_buf, int& _result_buf_Length);
	int Divide_Decimal_vector_by_Two(vector<int>& decimal_array/*divisor*/, vector<int>& quotient);
	//========================================================//
	int LongDivsion(vector<int>& int_array, vector<int>& quotient, int divisor);

};