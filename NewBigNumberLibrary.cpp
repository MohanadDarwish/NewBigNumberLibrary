// NewBigNumberLibrary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "ConversionInterface.h"
#include "ConvertStringToNumberArray.h"

#include "BigNumber.h"

using namespace std;

int main()
{
	cout << __FUNCTION__ << endl;
	system("Color 0B");		//light cyan F Black B

    //BigNumber b(LPSTR("123"));
	char str_bin[] = "1100001111";
	char str_dec[] = "783";
	char str_hex[] = "30F";

	int str_bin_length = strlen("1100001111");
	int str_dec_length = strlen("783");
	int str_hex_length = strlen("30F");

	BigNumber bn_bin(str_bin, str_bin_length, TYPE_BINARY);
	bn_bin.Print_Internal_data();
	BigNumber bn_dec(str_dec, str_dec_length, TYPE_DECIMAL);
	bn_dec.Print_Internal_data();
	BigNumber bn_hex(str_hex, str_hex_length, TYPE_HEX);
	bn_hex.Print_Internal_data();
	//
	char* conversion_buffer = NULL;
	int conversion_buffer_length=0;
	
	bn_bin.ConvertToString(conversion_buffer, conversion_buffer_length, TYPE_BINARY);
	conversion_buffer = new char[conversion_buffer_length];
	bn_bin.ConvertToString(conversion_buffer, conversion_buffer_length, TYPE_BINARY);
	if (conversion_buffer_length)
	{
		cout << "conversion success. buffer size = "<<conversion_buffer_length << endl;
	}
	for (int i = 0; i < conversion_buffer_length; i++) 
	{
		cout << "conversion_buffer : = " <<static_cast<int>(conversion_buffer[i]) << endl;
	}
	
	char* conversion_buffer2 = NULL;
	int conversion_buffer_length2 = 0;

	bn_dec.ConvertToString(conversion_buffer2, conversion_buffer_length2, TYPE_DECIMAL);
	conversion_buffer2 = new char[conversion_buffer_length2];

	bn_dec.ConvertToString(conversion_buffer2, conversion_buffer_length2, TYPE_DECIMAL);
	if (conversion_buffer_length2)
	{
		cout << "conversion success. buffer size = " << conversion_buffer_length2 << endl;
	}

	//for (int i = 0; i < conversion_buffer_length; i++)
	//{
	//	cout << "conversion_buffer2 : = " << static_cast<int>(conversion_buffer2[i]) << endl;
	//}
	printf("conversion_buffer2 : = %s \n", conversion_buffer2);

	//bn_hex.ConvertToString(conversion_buffer, conversion_buffer_length, TYPE_HEX);
	
    return 0;
}

