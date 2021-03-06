#include "stdafx.h"
#include "BigNumber.h"

BigNumber::BigNumber()
{
	cout << __FUNCTION__ << endl;
	internal_data = NULL;
	internal_data_length = 0;
	
	internal_byte_data = NULL;
	internal_byte_data_length = 0;
}

BigNumber::BigNumber(const char * _str , int& _str_length ,CONVERT_TYPES _type)
{
	cout << __FUNCTION__ << endl;
	//convert into internal number array of binary representation
	ConvertToInternalNumberArray(_str , _str_length, internal_data, internal_data_length , _type);

	//convert into internal byte array of binary representation
	ConvertToInternalByteArray(_str, _str_length, internal_byte_data, internal_byte_data_length, _type);
}

BigNumber::~BigNumber()
{
	cout << __FUNCTION__ << endl;
	if (internal_data)
	{
		delete[] internal_data;
		internal_data = NULL;
	}
	if (internal_byte_data)
	{
		delete[] internal_byte_data;
		internal_byte_data = NULL;
	}
}

void BigNumber::Print_Internal_data(void)
{
	cout << __FUNCTION__ << endl;
	cout <<"internal_data_size:= " << internal_data_length << endl;
	for (int i = 0; i < internal_data_length; i++)
	{
		printf("%d", this->internal_data[i]);
	}
	cout << endl;
	cout << "============================" << endl;
}
void BigNumber::Print_Internal_byte_data(void)
{
	cout << __FUNCTION__ << endl;
	cout << "internal_byte_data_size:= " << internal_byte_data_length << endl;
	for (int i = 0; i < internal_byte_data_length; i++)
	{
		printf("%x\n", this->internal_byte_data[i]);

	}
	cout << endl;
	cout << "============================" << endl;
}
void BigNumber::ConvertToInternalNumberArray(const char* _str, int & _str_length, int* & _result_buf, int& _buf_Length, CONVERT_TYPES _type)
{
	cout << __FUNCTION__ << endl;
	ConversionInterface *conv_inter_ptr = new ConvertStringToNumberArray();
	conv_inter_ptr->ConvertToInternal(_str, _str_length, _result_buf, _buf_Length, _type);
	delete conv_inter_ptr;
}

void BigNumber::ConvertToInternalByteArray(const char* _str, int & _str_length, int* & _result_buf, int& _buf_Length, CONVERT_TYPES _type)
{
	cout << __FUNCTION__ << endl;
	ConversionInterface *conv_inter_ptr = new ConvertStringToByteArray();
	conv_inter_ptr->ConvertToInternal(_str, _str_length, _result_buf, _buf_Length, _type);
	delete conv_inter_ptr;
}

void BigNumber::ConvertToStringFromNumberArray(char* _result_buf, int & _result_buf_Length, CONVERT_TYPES _type)
{
	cout << __FUNCTION__ << endl;
	ConversionInterface *conv_ptr = new ConvertStringToNumberArray();

	conv_ptr->ConvertToString( internal_data , internal_data_length, _result_buf, _result_buf_Length, _type);
}

void BigNumber::ConvertToStringFromByteArray(char* _result_buf, int & _result_buf_Length, CONVERT_TYPES _type)
{
	cout << __FUNCTION__ << endl;
	ConversionInterface *conv_ptr = new ConvertStringToByteArray();

	conv_ptr->ConvertToString(internal_byte_data, internal_byte_data_length, _result_buf, _result_buf_Length, _type);
}
BigNumber BigNumber::operator+(const BigNumber & _right_operand)
{
	BigNumber* result = new BigNumber();
	unsigned int result_int_element_number = 0;
	unsigned long long temp_result = 0;
	unsigned int carry = 0;
	int result_size = 0;
	(this->internal_byte_data_length > _right_operand.internal_byte_data_length) ? (result_size = this->internal_byte_data_length + 1) : (result_size = _right_operand.internal_byte_data_length);
	result->internal_byte_data = new int[result_size]();
	result->internal_byte_data_length = result_size;
	
	for (int int_number = 0; int_number <result_size; int_number++)
	{
		temp_result = this->internal_byte_data[int_number] + _right_operand.internal_byte_data[int_number];
		temp_result += carry;

		result->internal_byte_data[result_int_element_number] = (unsigned int)temp_result;
		carry = ((temp_result)>>31) & 1;
		result->internal_byte_data[result_int_element_number + 1] = carry;
		result_int_element_number++;
		temp_result = 0;
	}

	return *result;
}