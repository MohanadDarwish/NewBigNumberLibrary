// NewBigNumberLibrary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "ConversionInterface.h"
#include "ConvertStringToNumberArray.h"
#include "ConvertStringToByteArray.h"
#include "BigNumber.h"

using namespace std;

int main()
{
	cout << __FUNCTION__ << endl;
	system("Color 0B");		//light cyan F Black B
	//
	char str_bin[] = "101010101010101010101010101010101010101010101010101010101010101";
	char str_dec[] = "6148914691236517205";
	char str_hex[] = "5555555555555555";
	//
	int str_bin_length = strlen("101010101010101010101010101010101010101010101010101010101010101");
	int str_dec_length = strlen("6148914691236517205");
	int str_hex_length = strlen("5555555555555555");
	//
	BigNumber bn_bin(str_bin, str_bin_length, TYPE_BINARY);
	bn_bin.Print_Internal_data();
	BigNumber bn_dec(str_dec, str_dec_length, TYPE_DECIMAL);
	bn_dec.Print_Internal_data();
	BigNumber bn_hex(str_hex, str_hex_length, TYPE_HEX);
	bn_hex.Print_Internal_data();
	//
	char* conversion_buffer = NULL;
	int conversion_buffer_length=0;
	//
	bn_bin.ConvertToStringFromNumberArray(conversion_buffer, conversion_buffer_length, TYPE_BINARY);
	conversion_buffer = new char[conversion_buffer_length];
	bn_bin.ConvertToStringFromNumberArray(conversion_buffer, conversion_buffer_length, TYPE_BINARY);
	if (conversion_buffer_length)
	{
		cout << "conversion success. buffer size = "<<conversion_buffer_length << endl;
	}
	for (int i = 0; i < conversion_buffer_length; i++) 
	{
		cout <<static_cast<int>(conversion_buffer[i]);
	}
	cout << endl;
	//
	char* conversion_buffer2 = NULL;
	int conversion_buffer_length2 = 0;
	//
	bn_dec.ConvertToStringFromNumberArray(conversion_buffer2, conversion_buffer_length2, TYPE_DECIMAL);
	conversion_buffer2 = new char[conversion_buffer_length2];
	//
	bn_dec.ConvertToStringFromNumberArray(conversion_buffer2, conversion_buffer_length2, TYPE_DECIMAL);
	if (conversion_buffer_length2)
	{
		cout << "conversion success. buffer size = " << conversion_buffer_length2 << endl;
	}
	printf("conversion_buffer2 : = %s \n", conversion_buffer2);
	//	
	char* conversion_buffer3 = NULL;
	int conversion_buffer_length3 = 0;
	//
	bn_hex.ConvertToStringFromNumberArray(conversion_buffer3, conversion_buffer_length3, TYPE_HEX);
	conversion_buffer3 = new char[conversion_buffer_length3];
	//
	bn_hex.ConvertToStringFromNumberArray(conversion_buffer3, conversion_buffer_length3, TYPE_HEX);
	if (conversion_buffer_length3)
	{
		cout << "conversion success. buffer size = " << conversion_buffer_length3 << endl;
	}
	printf("conversion_buffer3 : = %s \n", conversion_buffer3 );

	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	//============================== main() =======================================//
	char* byte_conversion_buffer = NULL;
	int byte_conversion_buffer_length = 0;
	//
	bn_bin.ConvertToStringFromByteArray(byte_conversion_buffer, byte_conversion_buffer_length, TYPE_BINARY);
	byte_conversion_buffer = new char[byte_conversion_buffer_length];

	bn_bin.ConvertToStringFromByteArray(byte_conversion_buffer, byte_conversion_buffer_length, TYPE_BINARY);
	if (byte_conversion_buffer_length)
	{
		cout << "conversion success. buffer size = " << byte_conversion_buffer_length << endl;
	}
	for (int i = 0; i < byte_conversion_buffer_length; i++)
	{
		cout <<(byte_conversion_buffer[i]);
	}
	cout << endl;
	//
	char* byte_conversion_buffer2 = NULL;
	int byte_conversion_buffer_length2 = 0;
	//
	bn_dec.ConvertToStringFromByteArray(byte_conversion_buffer2, byte_conversion_buffer_length2, TYPE_DECIMAL);
	byte_conversion_buffer2 = new char[byte_conversion_buffer_length2];
	//
	bn_dec.ConvertToStringFromByteArray(byte_conversion_buffer2, byte_conversion_buffer_length2, TYPE_DECIMAL);
	if (byte_conversion_buffer_length2)
	{
		cout << "conversion success. buffer size = " << byte_conversion_buffer_length2 << endl;
	}
	printf("conversion_buffer2 : = %s \n", byte_conversion_buffer2);
	//
	char* byte_conversion_buffer3 = NULL;
	int byte_conversion_buffer_length3 = 0;
	//
	bn_hex.ConvertToStringFromByteArray(byte_conversion_buffer3, byte_conversion_buffer_length3, TYPE_HEX);
	byte_conversion_buffer3 = new char[byte_conversion_buffer_length3];
	//
	bn_hex.ConvertToStringFromByteArray(byte_conversion_buffer3, byte_conversion_buffer_length3, TYPE_HEX);
	if (byte_conversion_buffer_length3)
	{
		cout << "conversion success. buffer size = " << byte_conversion_buffer_length3 << endl;
	}
	printf("conversion_buffer3 : = %s \n", byte_conversion_buffer3);

    return 0;
}

