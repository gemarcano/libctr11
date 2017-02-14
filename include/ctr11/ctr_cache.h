/*******************************************************************************
 * Copyright (C) 2016, 2017 Gabriel Marcano
 *
 * Refer to the COPYING.txt file at the top of the project directory. If that is
 * missing, this file is licensed under the GPL version 2.0 or later.
 *
 ******************************************************************************/

/** @file */

#ifndef CTR_CACHE_H_
#define CTR_CACHE_H_

#ifdef __cplusplus
extern "C" {
#endif

/**	@brief Cleans and flushes all caches and write buffers.
 *
 *	@post All of the caches have been invalidated, and the data cache has been
 *		cleaned. Prefetch buffer has also been cleared.
 */
void ctr_cache_clean_and_flush_all(void);

/**	@brief Flushes (invalidates) all of the data cache.
 *
 *	@post The entire data cache is invalidated.
 */
void ctr_cache_flush_data_all(void);

/**	@brief Flushes (invalidates) the entry in the cache associated with the
 *		given address, if any exists.
 *
 *	The entry is associated with an address is the one specified by taking the
 *	address and ignoring the bottom 5 bits.
 *
 *	@param[in] address Address in memory to make sure to flush from cache.
 *
 *	@post The entry in the cache associated with the given address is
 *		invalidated.
 */
void ctr_cache_flush_data_entry(void *address);

/**	@brief Cleans but does not flush (invalidate) the entry in the cache
 *		associated with the given address, if any exists.
 *
 *	The entry is associated with an address is the one specified by taking the
 *	address and ignoring the bottom 5 bits.
 *
 *	@param[in] address Address in memory to make sure to clean in cache.
 *
 *	@post The entry in the cache associated with the given address is cleaned.
 */
void ctr_cache_data_clean_entry(void *address);

/**	@brief Cleans and flushes the entry in the cache associated with the given
 *		address, if any exists.
 *
 *	The entry is associated with an address is the one specified by taking the
 *	address and ignoring the bottom 5 bits.
 *
 *	@param[in] address Address in memory to make sure to clean and flush from
 *		cache.
 *
 *	@post The entry in the cache associated with the given address is cleaned
 *		and flushed.
 */
void ctr_cache_data_clean_and_flush_entry(void *address);

/**	@brief Flushes (invalidates) all instruction cache.
 *
 *	@post All of the instruction cache is invalidated.
 */
void ctr_cache_flush_instruction_all(void);

/**	@brief Flushes (invalidates) the instructions in the entry associated with
 *		the given address, if there is any.
 *
 *	The entry is associated with an address is the one specified by taking the
 *	address and ignoring the bottom 5 bits.
 *
 *	@param[in] address Address in memory to make sure to flush from cache.
 *
 *	@post The cache entry associated with the given address is invalidated.
 */
void ctr_cache_flush_instruction_entry(void *address);

/**	@brief Instruction Synchronization Barrier (ISB). Also referred to as Flush
 *		Prefetch Buffer.
 *
 *	@post Ensured instructions following this call were fetched only after this
 *		call.
 */
void ctr_isb(void);

/**	@brief Data Synchronization Barrier (DSB).
 *
 *	@post Ensures all memory accesses before this take place, all control
 *		register commands have completed, and prevented execution of
 *		instructions past it.
 */
void ctr_dsb(void);

/**	@brief Data Memory Barrier (DMB).
 *
 *	@post Ensured all memory accesses before this call took place before
 *		continuing.
 */
void ctr_dmb(void);

#ifdef __cplusplus
}
#endif

#endif//CTR_CACHE_H_

