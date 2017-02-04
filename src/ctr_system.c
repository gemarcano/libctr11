/*******************************************************************************
 * Copyright (C) 2016, 2017 Gabriel Marcano
 *
 * Refer to the COPYING.txt file at the top of the project directory. If that is
 * missing, this file is licensed under the GPL version 2.0 or later.
 *
 ******************************************************************************/

/** @file */

#include <ctr11/ctr_system.h>

ctr_system_type ctr_get_system_type(void)
{
	//This is seemingly not confirmed on 3dbrew, but it seems PDN_MPCORE_CFG's
	//second and third bit are only set on the N3DS, while the first bit is
	//set for all systems. Use that to detect the type of system.
	return ctr_core_get_system_type();
}

bool ctr_detect_a9lh_entry(void)
{
	//Aurora determined that this register isn't yet set when a9lh launches.
	return ctr_core_detect_a9lh_entry();
}

void ctr_system_poweroff(void)
{
	ctr_core_system_poweroff();
}

void ctr_system_reset(void)
{
	ctr_core_system_reset();
}

