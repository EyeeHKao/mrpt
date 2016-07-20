/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2016, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

#include "base-precomp.h"  // Precompiled headers


#include <mrpt/utils/core_defs.h>
#include <mrpt/utils/bits.h>
#include <mrpt/utils/mrpt_stdint.h>
#include <cstring>

template <typename T>
void reverseBytesInPlace_2b(T& v_in_out)
{
	const uint16_t org = *reinterpret_cast<uint16_t*>(&v_in_out);
	const uint16_t val_rev = ((org & 0xff00) >> 8) | ((org & 0x00ff) << 8);
	::memcpy(&v_in_out, &val_rev, sizeof(T)); // This avoid deref. puned pointer warning with:   *reinterpret_cast<const T*>(&val_rev);
}

template <typename T>
void reverseBytesInPlace_4b(T& v_in_out)
{
	const uint32_t org = *reinterpret_cast<uint32_t*>(&v_in_out);
	const uint32_t val_rev = ((org & 0xff000000) >> (3*8)) | ((org & 0x00ff0000) >> (1*8)) | ((org & 0x0000ff00) << (1*8)) | ((org & 0x000000ff) << (3*8));
	::memcpy(&v_in_out, &val_rev, sizeof(T)); // This avoid deref. puned pointer warning with:   *reinterpret_cast<const T*>(&val_rev);
}

template <typename T>
void reverseBytesInPlace_8b(T& v_in_out)
{
	const uint64_t org = *reinterpret_cast<uint64_t*>(&v_in_out);
	uint64_t val_rev = 0;
	int i,j;
	for (i=7,j=7;i>=4;i--,j-=2)
		val_rev |= ((org & ( UINT64_C(0xff) << (i*8))) >> (j*8));
	for (i=3,j=1;i>=0;i--,j+=2)
		val_rev |= ((org & ( UINT64_C(0xff) << (i*8))) << (j*8));

	::memcpy(&v_in_out, &val_rev, sizeof(T)); // This avoid deref. puned pointer warning with:   *reinterpret_cast<const T*>(&val_rev);
}

void mrpt::utils::reverseBytesInPlace(bool& ) {
	// Nothing to do.
}

void mrpt::utils::reverseBytesInPlace(uint8_t& v_in_out) {
	// Nothing to do.
}
void mrpt::utils::reverseBytesInPlace(int8_t& v_in_out) {
	// Nothing to do.
}

void mrpt::utils::reverseBytesInPlace(uint16_t& v_in_out) {
	reverseBytesInPlace_2b(v_in_out);
}

void mrpt::utils::reverseBytesInPlace(int16_t& v_in_out) {
	reverseBytesInPlace_2b(v_in_out);
}

void mrpt::utils::reverseBytesInPlace(uint32_t& v_in_out) {
	reverseBytesInPlace_4b(v_in_out);
}

void mrpt::utils::reverseBytesInPlace(int32_t& v_in_out) {
	reverseBytesInPlace_4b(v_in_out);
}

void mrpt::utils::reverseBytesInPlace(uint64_t& v_in_out) {
	reverseBytesInPlace_8b(v_in_out);
}

void mrpt::utils::reverseBytesInPlace(int64_t& v_in_out)  {
	reverseBytesInPlace_8b(v_in_out);
}

void mrpt::utils::reverseBytesInPlace(float& v_in_out)  {
	reverseBytesInPlace_4b(v_in_out);
}

void mrpt::utils::reverseBytesInPlace(double& v_in_out) {
	reverseBytesInPlace_8b(v_in_out);
}

#ifdef HAVE_LONG_DOUBLE
void mrpt::utils::reverseBytesInPlace(long double& v_in_out) {
	uint64_t dat[2];
	::memcpy(&dat[0], &v_in_out, sizeof(long double)); // This avoid deref. puned pointer warning with:   *reinterpret_cast<const T*>(&val_rev);
	std::swap(dat[0],dat[1]);
	reverseBytesInPlace(dat[0]);
	reverseBytesInPlace(dat[1]);
	::memcpy(&v_in_out, &dat[0], sizeof(long double)); // This avoid deref. puned pointer warning with:   *reinterpret_cast<const T*>(&val_rev);
}
#endif
