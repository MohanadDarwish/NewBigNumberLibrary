#include "stdafx.h"
#include "ConvertStringToByteArray.h"

using namespace std;

ConvertStringToByteArray::ConvertStringToByteArray()
{

}

ConvertStringToByteArray::~ConvertStringToByteArray()
{

}

/////////////////////////////////////////////////////////////////////

void ConvertStringToByteArray::ConvertToInternal(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length, CONVERT_TYPES _type)
{
	cout << __FUNCTION__ << endl;
	//need to change from string to binary(internal type) and put it in internal_data* of BigNumber
	switch (_type)
	{
	case TYPE_BINARY:
		ToInternalFromBin(_str, _str_num_length, _result_buf, _result_buf_length);
		break;
	case TYPE_DECIMAL:
		ToInternalFromDecimal(_str, _str_num_length, _result_buf, _result_buf_length);
		break;
	case TYPE_HEX:
		ToInternalFromHex(_str, _str_num_length, _result_buf, _result_buf_length);
		break;
	}
}

char ConvertStringToByteArray::ToInternalFromBin(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length)
{
	cout << __FUNCTION__ << endl;
	vector<int> int_vector;
	int temp = 0;
	int result = 0;
	int no_of_ints = 1;
	int no_of_bits = 0;

	for (int i = _str_num_length; i > 0; i--)
	{
		cout << _str[i - 1];
		temp = ((_str[i - 1] - '0') << no_of_bits);
		result |= temp;
		no_of_bits++;
		if ((no_of_bits == 32) && (no_of_bits != 0) || i == 1)
		{
			int_vector.push_back(result);
			no_of_ints++;
			no_of_bits = 0;
			result = 0;
		}
	}

	cout << endl;

	_result_buf = new int[int_vector.size()];
	memmove(_result_buf, int_vector.data(), int_vector.size() * sizeof(int));
	_result_buf_length = static_cast<int>(int_vector.size());

	return SUCCESS;
}

char ConvertStringToByteArray::ToInternalFromDecimal(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length)
{
	cout << __FUNCTION__ << endl;
	vector<int> decimal_vector;
	// need to check if the current digit is a vaiable decimal digit
	for (size_t str_pos = 0; str_pos < _str_num_length; str_pos++)
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
	vector<int> dividend(decimal_vector);
	vector<int> quotient;
	vector<unsigned char> byte_vector;
	unsigned char remainder = 0;
	while ((dividend.size() >= 1) && (dividend[0] != 0))
	{
		remainder = LongDivsion(dividend, quotient, 256);
		byte_vector.push_back(remainder);
		dividend = quotient;
		quotient.clear();
	}
	vector<int>internal_int_vector;
	int single_int = 0;
	int No_of_Bytes = 0;
	for (int i = 0; i < byte_vector.size(); i++)
	{
		single_int = single_int | byte_vector[i];
		No_of_Bytes++;
		if (No_of_Bytes == 4)
		{
			internal_int_vector.push_back(single_int);
			No_of_Bytes = 0;
			single_int = 0;
		}
		if (i == byte_vector.size() - 1)
		{
			break;
		}
		single_int = single_int << 8;
	}

	cout << "result of ConvertStringToNumberArray::ConvertToInternal: " << endl;

	_result_buf = new int[internal_int_vector.size()];
	memmove(_result_buf, internal_int_vector.data(), internal_int_vector.size() * sizeof(int));
	_result_buf_length = static_cast<int>(internal_int_vector.size());

	return SUCCESS;
}

char ConvertStringToByteArray::ToInternalFromHex(const char * _str, int _str_num_length, int *& _result_buf, int & _result_buf_length)
{
	cout << __FUNCTION__ << endl;
	vector<int> hex_vector;
	vector<unsigned char> byte_vector;
	bool least_nibble = true;
	unsigned char single_byte = 0;
	int single_int = 0;
	int no_of_bytes = 0;
	unsigned  char character_range_start = 0;
	// need to check if the current digit is a vaiable hex digit
	for (int str_pos = _str_num_length; str_pos > 0; str_pos--)
	{
		if (_str[str_pos - 1] >= '0' && _str[str_pos - 1] <= '9')
		{
			character_range_start = '0';
		}
		else if ((_str[str_pos - 1] >= 'A' && _str[str_pos - 1] <= 'F'))
		{
			character_range_start = 'A';
		}
		else if (_str[str_pos - 1] >= 'a' && _str[str_pos - 1] <= 'f')
		{
			character_range_start = 'a';
		}
		else 
		{
			return CONVERSION_ERROR;
		}

		single_int |= _str[str_pos - 1]- character_range_start;
		cout << single_int<<endl;
		no_of_bytes++;
		if (no_of_bytes == 8)
		{
			hex_vector.push_back(single_int);
			single_int = 0;
			no_of_bytes = 0;
		}
		single_int <<= 4;
		//if (_str[str_pos - 1] >= '0' && _str[str_pos - 1] <= '9')
		//{
		//	if (least_nibble) 
		//	{
		//		single_byte |= (_str[str_pos - 1] - '0') ;
		//		least_nibble = !least_nibble;
		//		if (str_pos - 1 == 0) 
		//		{
		//			byte_vector.push_back(single_byte);
		//		}
		//	}
		//	else
		//	{
		//		single_byte |= ( (_str[str_pos - 1] - '0') << 4 );
		//		least_nibble = !least_nibble;
		//		byte_vector.push_back(single_byte);
		//		single_byte = 0;
		//	}	
		//}
		//else if ((_str[str_pos - 1] >= 'A' && _str[str_pos - 1] <= 'F'))
		//{
		//	if (least_nibble)
		//	{
		//		single_byte |= (_str[str_pos - 1] - 'A');
		//		least_nibble = !least_nibble;
		//		if (str_pos - 1 == 0)
		//		{
		//			byte_vector.push_back(single_byte);
		//		}
		//	}
		//	else
		//	{
		//		single_byte |= ((_str[str_pos - 1] - 'A') << 4);
		//		least_nibble = !least_nibble;
		//		byte_vector.push_back(single_byte);
		//		single_byte = 0;
		//	}
		//}
		//else if (_str[str_pos - 1] >= 'a' && _str[str_pos - 1] <= 'f')
		//{
		//	if (least_nibble)
		//	{
		//		single_byte |= (_str[str_pos - 1] - 'a');
		//		least_nibble = !least_nibble;
		//		if (str_pos - 1 == 0)
		//		{
		//			byte_vector.push_back(single_byte);
		//		}
		//	}
		//	else
		//	{
		//		single_byte |= ((_str[str_pos - 1] - 'a') << 4);
		//		least_nibble = !least_nibble;
		//		byte_vector.push_back(single_byte);
		//		single_byte = 0;
		//	}
		//}
		//else
		//{
		//	cout << "Error: Wrong Hex Digit." << endl;
		//	return CONVERSION_ERROR;
		//}
	}

	//removing extra zeroes generated on the left of the number 0011 -> 11 
	for (size_t i = hex_vector.size(); i > 1; i--)
	{
		if (hex_vector[i - 1] == 0)
		{
			hex_vector.pop_back();
		}
		else
		{
			break;
		}
	}
	
	_result_buf = new int[hex_vector.size()];
	memmove(_result_buf, hex_vector.data(), hex_vector.size() * sizeof(int));
	_result_buf_length = static_cast<int>(hex_vector.size());
	return SUCCESS;
}

/////////////////////////////////////////////////////////////////////

void ConvertStringToByteArray::ConvertToString(int* _num, int& _num_length, char* _result_buf, int& _result_buf_Length, CONVERT_TYPES _type)
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

// convert from big number's internal type to binary
char ConvertStringToByteArray::ConvertToBin(int* _internal_num, int& _internal_num_length, char* _result_buf, int& _result_buf_Length)
{
	cout << __FUNCTION__ << endl;
	if (_result_buf_Length == NULL)
	{
		_result_buf_Length = _internal_num_length*32;
		return CONVERSION_ERROR;
	}
	else if (_result_buf_Length < _internal_num_length)
	{
		_result_buf_Length = _internal_num_length;
		return CONVERSION_ERROR;
	}
	else
	{
		string temp,result_buf;
		for (int i = _internal_num_length; i > 0; i--)
		{
			temp = bitset<32> ( _internal_num[i - 1] ).to_string();
			result_buf.append(temp);
		}
		int pos = 0;
		//loop to remove leading zeros
		while ((result_buf[0] == '0') && (pos < result_buf.size() - 1))
		{
			if (result_buf[0] == '1') break;
			result_buf.erase(result_buf.begin());
			pos++;
		}
		//for (int j = 0; j < result_buf.size(); j++)
		//{
		//	_result_buf[j] = result_buf[j];
		//}
		memmove( _result_buf , result_buf.data() , result_buf.size()*sizeof(char) );
		_result_buf_Length = result_buf.size();
		return SUCCESS;
	}
}

//Divide a big uint number by 2 takes int vector and quotient vector to be filled and returns the result remainder
int ConvertStringToByteArray::Divide_Decimal_vector_by_Two(vector<int>& decimal_array/*divisor*/, vector<int>& quotient)
{
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

/////////////////////////////////////////////////////////////////////

// convert from big number's internal type to decimal
char ConvertStringToByteArray::ConvertToDecimal(int* _internal_num, int& _internal_num_length, char*& _result_buf, int& _result_buf_Length)
{
	cout << __FUNCTION__ << endl;
	int conversion_length = ToDecimal(_internal_num, _internal_num_length, _result_buf, _result_buf_Length);
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
		ToDecimal(_internal_num, _internal_num_length, _result_buf, _result_buf_Length);
	}
	return SUCCESS;
}

size_t ConvertStringToByteArray::Convert_String_to_Decimal_vector(int* _str, int& _str_length, char* _result_buf, int& _result_buf_Length)
{
	vector<int> bignumberstr;
	bignumberstr.assign(&_str[0], &_str[_str_length]);
	vector<int> decimal_vector;
	decimal_vector.assign(&_result_buf[0], &_result_buf[_result_buf_Length]);

	size_t str_pos = 0;
	for (str_pos = 0; str_pos < bignumberstr.size(); str_pos++)
	{
		decimal_vector.push_back(bignumberstr[str_pos] - '0');
	}
	return str_pos;
}

int ConvertStringToByteArray::ToDecimal(int* _internal_num, int& _internal_num_length, char*& _result_buf, int& _result_buf_Length)
{
	string temp, result_buf;
	for (int i = _internal_num_length; i > 0; i--)
	{
		temp = bitset<32>(_internal_num[i - 1]).to_string();
		result_buf.append(temp);
	}
	//
	int pos = 0;
	//loop to remove leading zeros
	while ((result_buf[0] == '0') && (pos < result_buf.size() - 1))
	{
		if (result_buf[0] == '1') break;
		result_buf.erase(result_buf.begin());
		pos++;
	}
	//
	for (int j = 0; j < result_buf.size(); j++) 
	{
		result_buf[j] -= '0';
	}
	//////////////////////////////////////////////////////////////////////
	vector<int> binary_vector;
	binary_vector.assign( & result_buf[0], &result_buf[result_buf.size()] );
	//local variables
	char temp_hex_char = 0;
	int shift_counter = 0;
	string converted_string = "";
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
	_result_buf_Length = static_cast<int>(converted_string.size());
	return _result_buf_Length;
}

void ConvertStringToByteArray::update_bcd_digit_value_coressponding_to_its_current_value(vector< vector<char> >& whole_num_bcd_vector)
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

void ConvertStringToByteArray::shift_whole_num_bcd_vector_left(vector< vector<char> >& whole_num_bcd_vector)
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
char ConvertStringToByteArray::ConvertToHex(int*_internal_num, int& _internal_num_length, char* _result_buf, int& _result_buf_Length)
 {
	cout << __FUNCTION__ << endl;
	int conversion_length = ToHex(_internal_num, _internal_num_length, _result_buf, _result_buf_Length);
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

int ConvertStringToByteArray::ToHex(int*_internal_num, int& _internal_num_length, char* _result_buf, int& _result_buf_Length)
{
	string temp, result_buf;
	for (int i = _internal_num_length; i > 0; i--)
	{
		temp = bitset<32>(_internal_num[i - 1]).to_string();
		result_buf.append(temp);
	}
	//
	int pos = 0;
	//loop to remove leading zeros
	while ((result_buf[0] == '0') && (pos < result_buf.size() - 1))
	{
		if (result_buf[0] == '1') break;
		result_buf.erase(result_buf.begin());
		pos++;
	}
	//
	for (int j = 0; j < result_buf.size(); j++)
	{
		result_buf[j] -= '0';
	}
	//
	vector<int> binary_vector;
	binary_vector.assign(&result_buf[0], &result_buf[result_buf.size()]);
	//binary_vector.assign(&_internal_num[0], &_internal_num[_internal_num_length]);
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
			temp_hex_char =
				(binary_vector[vector_pos + 0]	  ) +
				(binary_vector[vector_pos + 1] * 2) +
				(binary_vector[vector_pos + 2] * 4) +
				(binary_vector[vector_pos + 3] * 8) ;
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
	//adding the null character '\0' to the end of the char array
	converted_string.push_back(0);

	if (_result_buf != NULL)
	{
		memmove(_result_buf, converted_string.data(), (converted_string.size() * sizeof(char)));
	}
	_result_buf_Length = static_cast<int>(converted_string.size());
	return _result_buf_Length;
}

//this function only implements diving a big int on normal int
int ConvertStringToByteArray::LongDivsion(vector<int>& int_array, vector<int>& quotient, int divisor)
{
	int digit_pos = 0;
	int temp_dividend = int_array[digit_pos];
	int remainder;

	//handling the case when diving 0 on anything
	if( (int_array.size() == 1) && (int_array[0] == 0) )// (!Check_vector_all_zeros(int_array))
	{
		return -1;//-1 here means infinity 0/anything = infinity
	}
	//handling the case when diving anything on 0
	if (!divisor)
	{
		return -1;//-1 here means infinity anything/0 = infinity
	}
	//looping on the dividend till we get a number that is fit to be divided on the divisor starting from the Most Significant Digit
	while ((temp_dividend < divisor) && (digit_pos < int_array.size() - 1))
	{
		temp_dividend = temp_dividend * 10 + int_array[++digit_pos];
	}

	//looping on the dividend number starting from the digit position that we got from the above loop
	//diving the temp_sub_dividend and getting a new digit from the original dividend
	while (digit_pos < int_array.size())
	{
		//put new digit to the result
		quotient.push_back(temp_dividend / divisor);

		//handling the case of when we reach the end of our dividend and we don't need to get a new temp_dividend
		//and also we have no more vector elements in int_array to refrence
		if (digit_pos == int_array.size() - 1)
		{
			break;
		}
		//get the new remainder and concat a new digit from our int_array
		temp_dividend = ( (temp_dividend % divisor) * 10 ) + int_array[++digit_pos];
	}
	remainder = temp_dividend % divisor;
	return remainder;
}