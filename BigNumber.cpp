#include "stdafx.h"
#include "BigNumber.h"


BigNumber::BigNumber()
{
	cout << __FUNCTION__ << endl;
	internal_data = NULL;
	internal_data_length = 0;
}

BigNumber::BigNumber(const char * _str , int& _str_length ,CONVERT_TYPES _type)
{
	cout << __FUNCTION__ << endl;
	/*internal_data = new int[_str_length];
	internal_data_length = _str_length;*/

	//cout << "str length passed to bignumber constructor is := " << strlen(str) << endl;
	//cout << "internal_data length inside bignumber constructor after allocation is := " << strlen(str) << endl;
	ConvertToInternal(_str , _str_length, internal_data, internal_data_length , _type);
}

BigNumber::~BigNumber()
{
	cout << __FUNCTION__ << endl;
	if (internal_data)
	{
		delete[] internal_data;
		internal_data = NULL;
	}
}

void BigNumber::Print_Internal_data(void)
{
	cout << "##########################" << endl;
	cout << __FUNCTION__ << endl;
	cout <<"internal_data_size:= " << internal_data_length << endl;
	for (int i = 0; i < internal_data_length; i++)
	{
		//cout <<this->internal_data[i];
		printf("%d", this->internal_data[i]);
	}
	cout << endl;
	cout << "============================" << endl;
}

void BigNumber::ConvertToString(char* _result_buf, int & _result_buf_Length, CONVERT_TYPES _type)
{
	cout << __FUNCTION__ << endl;
	ConversionInterface *conv_ptr = new ConvertStringToNumberArray();

	conv_ptr->ConvertToString( internal_data , internal_data_length, _result_buf, _result_buf_Length, _type);
}

void BigNumber::ConvertToInternal(const char* _str, int & _str_length, int* & _result_buf, int& _buf_Length, CONVERT_TYPES _type)
{
	cout << __FUNCTION__ << endl;
	ConversionInterface *conv_inter_ptr = new ConvertStringToNumberArray();
	conv_inter_ptr->ConvertToInternal( _str ,_str_length , _result_buf , _buf_Length, _type);
	delete conv_inter_ptr;
}

