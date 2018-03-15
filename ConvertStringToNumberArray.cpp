#include "stdafx.h"
#include "ConvertStringToNumberArray.h"
#include "BigNumber.h"

using namespace std;

ConvertStringToNumberArray::ConvertStringToNumberArray()
{
	cout << __FUNCTION__ << endl;
}

ConvertStringToNumberArray::~ConvertStringToNumberArray()
{
	cout << __FUNCTION__ << endl;
}

void ConvertStringToNumberArray::ConvertToString(int* _num, int& _num_length, char* _result_buf, int& _result_buf_Length, CONVERT_TYPES _type)
{
	cout << __FUNCTION__ << endl;
	switch (_type)
	{
	case TYPE_BINARY:
		ConvertToBin(_num, _num_length, _result_buf, _result_buf_Length);
		break;
	case TYPE_DECIMAL:
		ConvertToDecimal(_num, _num_length, _result_buf, _result_buf_Length);
		break;
	case TYPE_HEX:
		ConvertToHex(_num, _num_length, _result_buf, _result_buf_Length);
		break;
	default:
		cout << "Error: Wrong conversion base type. " << endl;
	}
}

void ConvertStringToNumberArray::ConvertToInternal(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length , CONVERT_TYPES _type)
{
	cout << __FUNCTION__ << endl;
	//need to change from string to binary(internal type) and put it in internal_data* of BigNumber
	switch (_type)
	{
	case TYPE_BINARY:
		ToInternalFromBin( _str , _str_num_length , _result_buf , _result_buf_length);
		break;
	case TYPE_DECIMAL:
		ToInternalFromDecimal( _str , _str_num_length , _result_buf , _result_buf_length);
		break;
	case TYPE_HEX:
		ToInternalFromHex( _str , _str_num_length , _result_buf , _result_buf_length);
		break;
	}
}

char ConvertStringToNumberArray::ToInternalFromBin(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length)
{
	cout << __FUNCTION__ << endl;
	vector<int> binary_vector;
	// need to check if the current digit is a vaiable decimal digit
	for (int str_pos = _str_num_length; str_pos > 0; str_pos--)
	{
		if (_str[str_pos - 1] == '0' || _str[str_pos - 1] == '1')
		{
			binary_vector.push_back(_str[str_pos - 1] - '0');
		}
		else
		{
			cout << "Error: Wrong Binary Digit." << endl;
		}
	}

	_result_buf = new int[binary_vector.size()];
	memmove(_result_buf, binary_vector.data(), binary_vector.size() * sizeof(int));
	_result_buf_length = static_cast<int>(binary_vector.size());
	return SUCCESS;
}

char ConvertStringToNumberArray::ToInternalFromDecimal(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length)
{
	cout << __FUNCTION__ << endl;
	vector<int> decimal_vector;
	// need to check if the current digit is a vaiable decimal digit
	for (size_t str_pos = 0; str_pos < strlen(_str); str_pos++)
	{
		if (_str[str_pos] >= '0'  && _str[str_pos] <= '9')
		{
			decimal_vector.push_back(_str[str_pos] - '0');
		}
		else
		{
			cout << "Error: Wrong Decimal Digit." << endl;
		}
	}
	//
	vector<int> divisor(decimal_vector);
	vector<int> quotient;
	vector<int> binary_vector;
	int remainder = 0;
	while (divisor.size() >= 1)
	{
		remainder = Divide_Decimal_vector_by_Two(divisor, quotient);
		if (remainder)
		{
			binary_vector.push_back(1);//Least in Least
		}
		else
		{
			binary_vector.push_back(0);//Least in Least
		}
		divisor = quotient;
		quotient.clear();
	}
	cout << "result of ConvertStringToNumberArray::ConvertToInternal: " << endl;
	cout << "Internal_data :=  ";

	_result_buf = new int[binary_vector.size()];
	memmove(_result_buf, binary_vector.data(), binary_vector.size()*sizeof(int));
	_result_buf_length = static_cast<int>(binary_vector.size());
	return SUCCESS;
}

char ConvertStringToNumberArray::ToInternalFromHex(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length)
{
	cout << __FUNCTION__<<endl;
	vector<int> hex_vector;
	char hex_digit_values[16][4] ={ 
		{ 0,0,0,0 },/*0*/ { 0,0,0,1 },/*1*/ { 0,0,1,0 },/*2*/ { 0,0,1,1 },/*3*/
		{ 0,1,0,0 },/*4*/ { 0,1,0,1 },/*5*/	{ 0,1,1,0 },/*6*/ { 0,1,1,1 },/*7*/
		{ 1,0,0,0 },/*8*/ { 1,0,0,1 },/*9*/	{ 1,0,1,0 },/*A*/ { 1,0,1,1 },/*B*/
		{ 1,1,0,0 },/*C*/ { 1,1,0,1 },/*D*/	{ 1,1,1,0 },/*E*/ { 1,1,1,1 } /*F*/
	};

	// need to check if the current digit is a vaiable hex digit
	for (int str_pos = _str_num_length; str_pos > 0 ; str_pos--)
	{
		if (_str[str_pos-1] >= '0' && _str[str_pos-1] <= '9')
		{
			hex_vector.push_back(hex_digit_values[_str[str_pos - 1] - '0'][3]);
			hex_vector.push_back(hex_digit_values[_str[str_pos - 1] - '0'][2]);
			hex_vector.push_back(hex_digit_values[_str[str_pos - 1] - '0'][1]);
			hex_vector.push_back(hex_digit_values[_str[str_pos - 1] - '0'][0]);
			
		}
		else if ((_str[str_pos-1] >= 'A' && _str[str_pos-1] <= 'F') )
		{
			hex_vector.push_back(hex_digit_values[_str[str_pos - 1] - 'A' + 10][3]);
			hex_vector.push_back(hex_digit_values[_str[str_pos - 1] - 'A' + 10][2]);
			hex_vector.push_back(hex_digit_values[_str[str_pos - 1] - 'A' + 10][1]);
			hex_vector.push_back(hex_digit_values[_str[str_pos - 1] - 'A' + 10][0]);
			
			
		}
		else if (_str[str_pos-1] >= 'a' && _str[str_pos-1] <= 'f')
		{
			hex_vector.push_back(hex_digit_values[_str[str_pos - 1] - 'a' + 10][3]);
			hex_vector.push_back(hex_digit_values[_str[str_pos - 1] - 'a' + 10][2]);
			hex_vector.push_back(hex_digit_values[_str[str_pos - 1] - 'a' + 10][1]);
			hex_vector.push_back(hex_digit_values[_str[str_pos - 1] - 'a' + 10][0]);			
		}
		else 
		{
			cout << "Error: Wrong Hex Digit." << endl;
			return CONVERSION_ERROR;
		}
	}
	//removing extra zeroes generated on the left of the number 0011 -> 11 
	for (size_t i = hex_vector.size(); i > 1; i--) 
	{
		if (hex_vector[i-1] == 0)
		{
			hex_vector.pop_back();
		}
		else 
		{
			break;
		}
	}
	_result_buf = new int[hex_vector.size()];
	memmove(_result_buf , hex_vector.data() , hex_vector.size() * sizeof(int));
	_result_buf_length = static_cast<int>(hex_vector.size());
	return SUCCESS;
}

// convert from big number's internal type to binary
char ConvertStringToNumberArray::ConvertToBin(int* _internal_num, int& _internal_num_length, char* _result_buf, int& _result_buf_Length)
{
	cout << __FUNCTION__ << endl;
	if (_result_buf_Length == NULL) 
	{
		_result_buf_Length = _internal_num_length;
		return CONVERSION_ERROR;
	}
	else if (_result_buf_Length < _internal_num_length)
	{
		_result_buf_Length = _internal_num_length;
		return CONVERSION_ERROR;
	}
	else
	{
		for (int i = _internal_num_length; i > 0; i--)
		{
			_result_buf[_internal_num_length - i] = _internal_num[i-1];
		}
		_result_buf_Length = _internal_num_length;
		return SUCCESS;
	}
	
}

// convert from big number's internal type to decimal
char ConvertStringToNumberArray::ConvertToDecimal(int* _internal_num, int& _internal_num_length, char*& _result_buf, int& _result_buf_Length)
{
	cout << __FUNCTION__ << endl;
	int conversion_length  = ToDecimal(_internal_num, _internal_num_length, _result_buf, _result_buf_Length);
	if (_result_buf_Length == NULL)
	{
		_result_buf_Length = conversion_length;
	}
	else if (_result_buf_Length < conversion_length )
	{
		_result_buf_Length = conversion_length;
		return CONVERSION_ERROR;
	}
	else
	{
		ToDecimal(_internal_num, _internal_num_length, _result_buf, _result_buf_Length);
	}	
	return SUCCESS;
}

size_t ConvertStringToNumberArray::Convert_String_to_Decimal_vector(int* _str, int& _str_length, char* _result_buf, int& _result_buf_Length)
{
	vector<int> bignumberstr;
	bignumberstr.assign(&_str[0], &_str[_str_length]);
	vector<int> decimal_vector;
	decimal_vector.assign(&_result_buf[0], &_result_buf[_result_buf_Length]);

	size_t str_pos = 0;
	for (str_pos = 0 ; str_pos < bignumberstr.size() ; str_pos++)
	{
		decimal_vector.push_back(bignumberstr[str_pos] - '0');
	}
	return str_pos;
}

int ConvertStringToNumberArray::ToDecimal(int* _internal_num, int& _internal_num_length, char*& _result_buf, int& _result_buf_Length)
{
	vector<int> binary_vector;
	binary_vector.assign(&_internal_num[0], &_internal_num[_internal_num_length]);
	//local variables
	char temp_hex_char = 0;
	int shift_counter = 0;
	string converted_string= "";
	size_t decimal_digit_place = 0;
	//a copy of the this->binary_vector so we don't alter the binary_vector of the calling object.
	vector<int> num_binary_vector_copy(binary_vector);
	//4 element char vector used to initialize the whole vectors a muliplte of push_back(digit_bcd_vector)
	vector<char> digit_bcd_vector(4, 0);
	//whole num bcd vector should hold the bdc representation of the inputed binary vector
	vector< vector<char> > whole_num_bcd_vector;
	//double dabble alg.
	//take the last bit in binary_vector to last pos in whole_num_bcd_vector  
	whole_num_bcd_vector.push_back(digit_bcd_vector);
	size_t bin_vec_copy_pos = num_binary_vector_copy.size() + 1;
	while (num_binary_vector_copy.size())
	{
		//shift whole_num_bcd_vector to left aka [0]<-..[n-1]<-[n]
		shift_whole_num_bcd_vector_left(whole_num_bcd_vector);
		//new bit
		whole_num_bcd_vector[0][3] = num_binary_vector_copy[num_binary_vector_copy.size() - 1];
		shift_counter++;
		num_binary_vector_copy.pop_back();
		if (shift_counter < binary_vector.size())
		{
			//check the current digit if >4 ? add 3 : move on()
			update_bcd_digit_value_coressponding_to_its_current_value(whole_num_bcd_vector);
		}
		//
		if (whole_num_bcd_vector[decimal_digit_place].front())
		{
			//pushing back zeros in packs of 4 corresponding to the expected bcd decimals outputed
			whole_num_bcd_vector.push_back(digit_bcd_vector);
			decimal_digit_place++;
		}
	}
	//checking if there are a leading zeroes (an inner vector extra full of zeroes not needed)
	if (!(whole_num_bcd_vector[whole_num_bcd_vector.size() - 1][0] + whole_num_bcd_vector[whole_num_bcd_vector.size() - 1][1] +
		whole_num_bcd_vector[whole_num_bcd_vector.size() - 1][2] + whole_num_bcd_vector[whole_num_bcd_vector.size() - 1][3])) {
		whole_num_bcd_vector.pop_back();
	}
	///////////////////////////////////	
	for (size_t vector_pos = whole_num_bcd_vector.size(); vector_pos > 0; vector_pos--)
	{
		temp_hex_char = (whole_num_bcd_vector[vector_pos - 1][0] * 8) +
			(whole_num_bcd_vector[vector_pos - 1][1] * 4) +
			(whole_num_bcd_vector[vector_pos - 1][2] * 2) +
			(whole_num_bcd_vector[vector_pos - 1][3] * 1);
		//
		if (temp_hex_char >= 0 && temp_hex_char < 10)
		{
			temp_hex_char += '0';
		}
		converted_string.push_back(temp_hex_char);
		temp_hex_char = 0;
	}
	//adding the null character '\0' to the end of the char array
	converted_string.push_back(0);

	if (_result_buf != NULL) 
	{
		memmove(_result_buf, converted_string.data(), (converted_string.size() * sizeof(char)));
	}
	_result_buf_Length = static_cast<int>( converted_string.size() );
	return _result_buf_Length;
}

void ConvertStringToNumberArray::update_bcd_digit_value_coressponding_to_its_current_value(vector< vector<char> >& whole_num_bcd_vector)
{
	for (size_t whole_size = 0; whole_size < whole_num_bcd_vector.size(); whole_size++)
	{
		char temp_hex_char = 0;
		//check the current digit if >4 ? add 3 : move on()
		temp_hex_char = (whole_num_bcd_vector[whole_size][3]) +
						(whole_num_bcd_vector[whole_size][2] * 2) +
						(whole_num_bcd_vector[whole_size][1] * 4) +
						(whole_num_bcd_vector[whole_size][0] * 8);
		if (temp_hex_char > 4)
		{
			//	temp_hex_char += 3;
			switch (temp_hex_char)
			{
			case 5://0101 + 11 = 1000
				whole_num_bcd_vector[whole_size][0] = 1; whole_num_bcd_vector[whole_size][1] = 0;
				whole_num_bcd_vector[whole_size][2] = 0; whole_num_bcd_vector[whole_size][3] = 0;
				break;
			case 6://0110 + 11 = 1001
				whole_num_bcd_vector[whole_size][0] = 1; whole_num_bcd_vector[whole_size][1] = 0;
				whole_num_bcd_vector[whole_size][2] = 0; whole_num_bcd_vector[whole_size][3] = 1;
				break;
			case 7://0111 + 11 = 1010
				whole_num_bcd_vector[whole_size][0] = 1; whole_num_bcd_vector[whole_size][1] = 0;
				whole_num_bcd_vector[whole_size][2] = 1; whole_num_bcd_vector[whole_size][3] = 0;
				break;
			case 8://1000 + 11 = 1011
				whole_num_bcd_vector[whole_size][0] = 1; whole_num_bcd_vector[whole_size][1] = 0;
				whole_num_bcd_vector[whole_size][2] = 1; whole_num_bcd_vector[whole_size][3] = 1;
				break;
			case 9://1001 + 11 = 1100
				whole_num_bcd_vector[whole_size][0] = 1; whole_num_bcd_vector[whole_size][1] = 1;
				whole_num_bcd_vector[whole_size][2] = 0; whole_num_bcd_vector[whole_size][3] = 0;
				break;
			}
		}
		temp_hex_char = 0;
	}
}

void ConvertStringToNumberArray::shift_whole_num_bcd_vector_left(vector< vector<char> >& whole_num_bcd_vector)
{
	size_t number_of_bcd_digits = whole_num_bcd_vector.size();
	size_t number_of_transitions_between_inner_vectors = whole_num_bcd_vector.size() - 1;
	//loop from the end of whole_num_bcd_vector to first element
	for (size_t whole_pos = number_of_bcd_digits; whole_pos > 0; whole_pos--)//size-1 --> size-2 --> size-3 ..-->0
	{
		//three small shifting arrows
		whole_num_bcd_vector[whole_pos - 1][0] = whole_num_bcd_vector[whole_pos - 1][1];
		whole_num_bcd_vector[whole_pos - 1][1] = whole_num_bcd_vector[whole_pos - 1][2];
		whole_num_bcd_vector[whole_pos - 1][2] = whole_num_bcd_vector[whole_pos - 1][3];
		whole_num_bcd_vector[whole_pos - 1][3] = 0;
		//
		if ((number_of_transitions_between_inner_vectors > 0))
		{
			//the big shifting arrow from an inner vector[0] to the next inner vector[3]
			whole_num_bcd_vector[whole_pos - 1][3] = whole_num_bcd_vector[whole_pos - 2][0];
			whole_num_bcd_vector[whole_pos - 2][0] = 0;
			number_of_transitions_between_inner_vectors--;
		}
	}
}
/////////////////////////////////////////////////////////////////////

// convert from big number's internal type to hex
char ConvertStringToNumberArray::ConvertToHex(int*_internal_num, int& _internal_num_length, char* _result_buf, int& _result_buf_Length)
{
	cout << __FUNCTION__ << endl;

	int conversion_length = ToHex( _internal_num, _internal_num_length, _result_buf, _result_buf_Length);

	if (_result_buf_Length == NULL)
	{
		_result_buf_Length = conversion_length;
	}
	else if (_result_buf_Length < conversion_length)
	{
		_result_buf_Length = conversion_length;
		return CONVERSION_ERROR;
	}
	else
	{
		ToHex(_internal_num, _internal_num_length, _result_buf, _result_buf_Length);
	}
	return SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ConvertStringToNumberArray::ToHex(int*_internal_num, int& _internal_num_length, char* _result_buf, int& _result_buf_Length)
{
	vector<int> binary_vector;
	binary_vector.assign(&_internal_num[0], &_internal_num[_internal_num_length]);
	//
	string converted_string;
	size_t remaining_vector_elements;//must be >=4
	char temp_hex_char = 0;
	//
	for (size_t vector_pos = 0; vector_pos < binary_vector.size(); vector_pos += 4)
	{
		remaining_vector_elements = binary_vector.size() - vector_pos;
		if (remaining_vector_elements < 4)
		{
			for (size_t i = 0; i < remaining_vector_elements; i++)
			{
				if (i == 0)
				{
					temp_hex_char += (binary_vector[vector_pos]);
				}
				else
				{
					temp_hex_char += (binary_vector[vector_pos + i] * (i * 2));
				}

			}
			vector_pos = binary_vector.size();
		}
		else
		{
			temp_hex_char = (binary_vector[vector_pos + 0]) +
				(binary_vector[vector_pos + 1] * 2) +
				(binary_vector[vector_pos + 2] * 4) +
				(binary_vector[vector_pos + 3] * 8);
		}
		//
		if (temp_hex_char >= 0 && temp_hex_char < 10)
		{
			temp_hex_char += '0';
		}
		else
		{
			temp_hex_char = (temp_hex_char - 10) + 'A';
		}
		//
		converted_string.insert(converted_string.begin(), temp_hex_char);
		temp_hex_char = 0;
	}

	//return converted_string;
	//adding the null character '\0' to the end of the char array
	converted_string.push_back(0);

	if (_result_buf != NULL)
	{
		memmove(_result_buf, converted_string.data(), (converted_string.size() * sizeof(char)));
	}
	_result_buf_Length = static_cast<int>(converted_string.size());
	return _result_buf_Length;
}

//Divide a big uint number by 2 takes int vector and quotient vector to be filled and returns the result remainder
int ConvertStringToNumberArray::Divide_Decimal_vector_by_Two(vector<int>& decimal_array/*divisor*/, vector<int>& quotient)
{
	//cout << __FUNCTION__ << endl;

	//converting a decimal number having each digit in a different vector element
	//to another binary vector having each bit from the binary representation of the int vector 
	//in a different element
	//consider it divide by 2
	int digit_pos = 0;
	int temp_dividend = 0;

	for (digit_pos = 0; digit_pos < decimal_array.size(); digit_pos++)
	{
		//get the new remainder and concat a new digit from our int_array
		temp_dividend = (temp_dividend % 2) * 10 + decimal_array[digit_pos];
		//put new digit to the result
		if (digit_pos != 0 || (temp_dividend / 2) != 0)
		{
			quotient.push_back(temp_dividend / 2);
		}
	}
	return (temp_dividend % 2);
}