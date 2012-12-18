#include <stdlib.h>


#include "switching_cache.h"


typedef struct _ng_rewrite{
    int64_t uid ;
    int ng ;
    int mode ;
} ng_rewrite_t;


typedef struct _ng_rewrite_cache{
    int count;
    ng_rewrite_t * data;
} ng_rewrite_cache_t;


void            ng_rewrite_free_cache(ng_rewrite_cache_t *);
int             ng_rewrite_init();
int             ng_rewrite_load();
ng_rewrite_t *  ng_rewrite_lookup(ng_rewrite_cache_t * , int64_t uid);

SWITHCING_CACHE_DECLARE(ng_rewrite)
