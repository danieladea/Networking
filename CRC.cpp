#include <iostream>
#include "CRC.h"

const uint64_t CRC::m_polynomial = 0x42F0E1EBA9EA3693ull;

CRC::CRC()
{
	create_crc_table();
}

CRC::~CRC()
{}

void CRC::create_crc_table()
{
	uint64_t generator = m_polynomial;
	crctable = new uint64_t[256];
	/* iterate over all byte values 0 - 255 */
	for (int dividend = 0; dividend < 256; dividend++)
	{
		uint64_t crc = (uint64_t) dividend;
		/* calculate the CRC-8 value for current byte */
		for (uint64_t bit = 0; bit < 8; bit++)
		{
			if ((crc & 0x8000000000000) != 0)
			{
				crc <<= 1;
				crc ^= generator;
			}
			else
			{
				crc <<= 1;
			}
		}
		/* store CRC value in lookup table */
		crctable[dividend] = crc;
	}
}

uint64_t CRC::get_crc_code(uint8_t *stream, int length)
{
	uint64_t rem = 0;
	for (i = 0; i<length; i++)
	{
		rem = (rem << 8) ^ m_CRC_table[stream[i] ^ (rem >> 56)]
	}
}

