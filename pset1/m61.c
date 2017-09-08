#define M61_DISABLE 1
#include "m61.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>



//number of allocations
int num_allocations = 0;

//number of fails
int num_fails = 0;

//number of frees
int num_frees = 0;

//number of bytes allocated
int alloc_bytes = 0;

//number of bytes freed
int freed_bytes = 0;

//number of bytes failed
int fail_bytes = 0;

//minimum address allocated
char* min_adrs = NULL;

//maximum address allocated
char* max_adrs = NULL;

/// m61_malloc(sz, file, line)
///    Return a pointer to `sz` bytes of newly-allocated dynamic memory.
///    The memory is not initialized. If `sz == 0`, then m61_malloc may
///    either return NULL or a unique, newly-allocated pointer value.
///    The allocation request was at location `file`:`line`.

void* m61_malloc(size_t sz, const char* file, int line) {
    (void) file, (void) line;   // avoid uninitialized variable warnings
    
    // return request located at file: line 
    if (malloc(sizeof(sz)) == NULL){
    	num_fails += 1;
        fail_bytes += sz;
    	abort();
    }
   
    else {
    
    	num_allocations += 1;
    	alloc_bytes += sz;
        void* mal = malloc(sizeof(sz));
        if (min_adrs == NULL) {
            min_adrs = mal;
            max_adrs = mal;
        }
        else if (mal - min_adrs < 0) {
            min_adrs = mal;
        }
        else if (max_adrs - mal < 0) {
            max_adrs = mal;
        }
        
    	return mal;
    }
    
    //printf("Pointer name: %s, file name:%s, line number:%s \n", ptr, file, line);
    
    
   
}

/// m61_free(ptr, file, line)
///    Free the memory space pointed to by `ptr`, which must have been
///    returned by a previous call to m61_malloc and friends. If
///    `ptr == NULL`, does nothing. The free was called at location
///    `file`:`line`.

void m61_free(void *ptr, const char *file, int line) {
    (void) file, (void) line;   // avoid uninitialized variable warnings
    // Your code here.
    
    	
	alloc_bytes -= sizeof(ptr);
	freed_bytes -= sizeof(ptr);
	num_allocations -= 1;
	num_frees += 1;
    	free(ptr);
    
    //printf("The free was called at location- %s : %d", file, line );
    
    
}

/// m61_realloc(ptr, sz, file, line)
///    Reallocate the dynamic memory pointed to by `ptr` to hold at least
///    `sz` bytes, returning a pointer to the new block. If `ptr` is NULL,
///    behaves like `m61_malloc(sz, file, line)`. If `sz` is 0, behaves
///    like `m61_free(ptr, file, line)`. The allocation request was at
///    location `file`:`line`.

void* m61_realloc(void* ptr, size_t sz, const char* file, int line) {
    void* new_ptr = NULL;
    if (sz) {
        new_ptr = m61_malloc(sz, file, line);
    }
    if (ptr && new_ptr) {
        // Copy the data from `ptr` into `new_ptr`.
        // To do that, we must figure out the size of allocation `ptr`.
        // Your code here (to fix test014).
    }
    m61_free(ptr, file, line);
    return new_ptr;
}

/// m61_calloc(nmemb, sz, file, line)
///    Return a pointer to newly-allocated dynamic memory big enough to
///    hold an array of `nmemb` elements of `sz` bytes each. The memory
///    is initialized to zero. If `sz == 0`, then m61_malloc may
///    either return NULL or a unique, newly-allocated pointer value.
///    The allocation request was at location `file`:`line`.

void* m61_calloc(size_t nmemb, size_t sz, const char* file, int line) {
    // Your code here (to fix test016).
    void* ptr = m61_malloc(nmemb * sz, file, line);
    if (ptr) {
        memset(ptr, 0, nmemb * sz);
    }
    return ptr;
}

/// m61_getstatistics(stats)
///    Store the current memory statistics in `*stats`.



void m61_getstatistics(struct m61_statistics* stats) {
    // Stub: set all statistics to enormous numbers
    memset(stats, 255, sizeof(struct m61_statistics));
    // Your code here.


    stats->nactive = num_allocations;
    stats->nactive = num_allocations - num_frees;

    stats->active_size = alloc_bytes - freed_bytes;

    stats->ntotal = alloc_bytes;
    stats->ntotal = num_allocations;

    stats->total_size = alloc_bytes;

    stats->nfail = num_fails;

    stats->fail_size = fail_bytes;
	
    stats->heap_min = min_adrs;
    
    stats->heap_max = max_adrs;
    
    // unsigned long long nactive;           // number of active allocations [#malloc - #free]
    // unsigned long long active_size;       // number of bytes in active allocations
    // unsigned long long ntotal;            // number of allocations, total
    // unsigned long long total_size;        // number of bytes in allocations, total
    // unsigned long long nfail;             // number of failed allocation attempts
    // unsigned long long fail_size;         // number of bytes in failed allocation attempts
    // char* heap_min;                       // smallest address in any region ever allocated
    // char* heap_max;                       // largest address in any region ever allocated
}

/// m61_printstatistics()
///    Print the current memory statistics.

    
void m61_printstatistics(void) {
    struct m61_statistics stats;
    m61_getstatistics(&stats);
	stats.nactive = num_allocations;
	stats.ntotal = alloc_bytes;
	stats.nfail = num_fails;
	stats.active_size = alloc_bytes - freed_bytes; 
	stats.total_size = alloc_bytes;
	stats.fail_size = fail_bytes;
	
    printf("malloc count: active %10llu   total %10llu   fail %10llu\n",
           stats.nactive, stats.ntotal, stats.nfail);
    
    printf("malloc size:  active %10llu   total %10llu   fail %10llu\n",
           stats.active_size, stats.total_size, stats.fail_size);
}


/// m61_printleakreport()
///    Print a report of all currently-active allocated blocks of dynamic
///    memory.

void m61_printleakreport(void) {
    // Your code here.
}
