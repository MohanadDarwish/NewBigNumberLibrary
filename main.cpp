// BigNumLib.cpp : Defines the entry point for the console application.
//
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
	//endianness for this computer is -> little endian <- checked it myself
	cout << __FUNCTION__ << endl;
	system("Color 0B");		//light cyan F Black B
							//
	char str_bin[] = "1000100100010001100110100010001010101011001100111011110001000";  //1234605616436508552 base10 //0001000100100010001100110100010001010101011001100111011110001000 base2
	char str_dec[] = "1234605616436508552";
	char str_hex[] = "1122334455667788";
	//
	int str_bin_length = strlen("1000100100010001100110100010001010101011001100111011110001000");
	int str_dec_length = strlen("1234605616436508552");
	int str_hex_length = strlen("1122334455667788");
	//
	BigNumber bn_bin(str_bin, str_bin_length, TYPE_BINARY);
	//bn_bin.Print_Internal_data();
	cout << "Data is put in the memory in little endian and it is presented \n in the little endian order least byte in smallest address:-" << endl << endl;
	bn_bin.Print_Internal_byte_data(); //( 11223344 )16 == ( 287454020 )10
									   //( 55667788 )16 == ( 1432778632 )10

	BigNumber bn_dec(str_dec, str_dec_length, TYPE_DECIMAL);
	//bn_dec.Print_Internal_data();
	bn_dec.Print_Internal_byte_data();

	BigNumber bn_hex(str_hex, str_hex_length, TYPE_HEX);
	//bn_hex.Print_Internal_data();
	bn_hex.Print_Internal_byte_data();

	//char* conversion_buffer = NULL;
	//int conversion_buffer_length=0;
	//
	//bn_bin.ConvertToStringFromNumberArray(conversion_buffer, conversion_buffer_length, TYPE_BINARY);
	//conversion_buffer = new char[conversion_buffer_length];
	//bn_bin.ConvertToStringFromNumberArray(conversion_buffer, conversion_buffer_length, TYPE_BINARY);
	//if (conversion_buffer_length)
	//{
	//	cout << "conversion success. buffer size = "<<conversion_buffer_length << endl;
	//}
	//for (int i = 0; i < conversion_buffer_length; i++) 
	//{
	//	cout <<static_cast<int>(conversion_buffer[i]);
	//}
	//cout << endl;
	////
	////
	////char* conversion_buffer2 = NULL;
	////int conversion_buffer_length2 = 0;
	////
	////bn_dec.ConvertToStringFromNumberArray(conversion_buffer2, conversion_buffer_length2, TYPE_DECIMAL);
	////conversion_buffer2 = new char[conversion_buffer_length2];
	////
	////bn_dec.ConvertToStringFromNumberArray(conversion_buffer2, conversion_buffer_length2, TYPE_DECIMAL);
	////if (conversion_buffer_length2)
	////{
	////	cout << "conversion success. buffer size = " << conversion_buffer_length2 << endl;
	////}
	////printf("conversion_buffer2 : = %s \n", conversion_buffer2);
	////
	////
	////char* conversion_buffer3 = NULL;
	////int conversion_buffer_length3 = 0;
	//////
	////bn_hex.ConvertToStringFromNumberArray(conversion_buffer3, conversion_buffer_length3, TYPE_HEX);
	////conversion_buffer3 = new char[conversion_buffer_length3];
	//////
	////bn_hex.ConvertToStringFromNumberArray(conversion_buffer3, conversion_buffer_length3, TYPE_HEX);
	////if (conversion_buffer_length3)
	////{
	////	cout << "conversion success. buffer size = " << conversion_buffer_length3 << endl;
	////}
	////printf("conversion_buffer3 : = %s \n", conversion_buffer3 );

	cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Byte Array @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl;
	//============================== main() =======================================//
	char* byte_conversion_buffer = NULL;
	int byte_conversion_buffer_length = 0;
	//
	bn_bin.ConvertToStringFromByteArray(byte_conversion_buffer, byte_conversion_buffer_length, TYPE_BINARY);
	byte_conversion_buffer = new char[byte_conversion_buffer_length]();

	bn_bin.ConvertToStringFromByteArray(byte_conversion_buffer, byte_conversion_buffer_length, TYPE_BINARY);
	if (byte_conversion_buffer_length)
	{
		cout << "conversion success. buffer size = " << byte_conversion_buffer_length << endl;
	}
	for (int i = 0; i < byte_conversion_buffer_length; i++)
	{
		cout << (byte_conversion_buffer[i]);
	}
	cout << endl;

	////

	char* byte_conversion_buffer2 = NULL;
	int byte_conversion_buffer_length2 = 0;
	//
	bn_dec.ConvertToStringFromByteArray(byte_conversion_buffer2, byte_conversion_buffer_length2, TYPE_DECIMAL);
	byte_conversion_buffer2 = new char[byte_conversion_buffer_length2]();
	//
	bn_dec.ConvertToStringFromByteArray(byte_conversion_buffer2, byte_conversion_buffer_length2, TYPE_DECIMAL);
	if (byte_conversion_buffer_length2)
	{
		cout << "conversion success. buffer size = " << byte_conversion_buffer_length2 << endl;
	}
	//printf("conversion_buffer2 : = %s \n", byte_conversion_buffer2);
	for (int i = 0; i < byte_conversion_buffer_length2; i++)
	{
		cout << (byte_conversion_buffer2[i]);
	}
	cout << endl;

	////

	char* byte_conversion_buffer3 = NULL;
	int byte_conversion_buffer_length3 = 0;
	//
	bn_hex.ConvertToStringFromByteArray(byte_conversion_buffer3, byte_conversion_buffer_length3, TYPE_HEX);
	byte_conversion_buffer3 = new char[byte_conversion_buffer_length3]();
	//
	bn_hex.ConvertToStringFromByteArray(byte_conversion_buffer3, byte_conversion_buffer_length3, TYPE_HEX);
	if (byte_conversion_buffer_length3)
	{
		cout << "conversion success. buffer size = " << byte_conversion_buffer_length3 << endl;
	}
	printf("conversion_buffer3 : = %s \n", byte_conversion_buffer3);
	
	//BigNumber result = bn_dec + bn_bin ;
	char b1[] = "12ffffffff";
	int b1_size = strlen("12ffffffff");
	char b2[] = "2ffffffff";
	int b2_size = strlen("2ffffffff");
	//BigNumber bn1(b1, b1_size, TYPE_HEX);
	//BigNumber bn2(b2, b2_size, TYPE_HEX);
	//BigNumber result = bn1 + bn2;
	//result.Print_Internal_byte_data();//expected result is 12FFFFFFFF+2FFFFFFFF=15FFFFFFFE

	return 0;
}

