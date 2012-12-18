#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include "ng_rewrite.h"

/*
SWITHCING_CACHE_DECLARE(ng_rewrite)
SWITHCING_CACHE_IMPLEMENT(ng_rewrite)

typedef struct _ng_rewrite{
    int64_t uid ;
    int ng ;
    int mode ;
} ng_rewrite_t;


typedef struct _ng_rewrite_cache{
    int count;
    ng_rewrite_t * data;
} ng_rewrite_cache_t;


void ng_rewrite_free_cache(ng_rewrite_cache_t * cache){
    if ( !cache)
        return;
    if ( cache->data )
        free(cache->data);
    free(cache);
}
*/

int main( int argc , char** args){
    int i;
    ng_rewrite_cache_t * cache = NULL;
    pthread_rwlock_t l;
    printf("hello , example.\n");
    printf("%d \n" , ng_rewrite_cache0  );
    
    ng_rewrite_init();//SWITHCING_CACHE_INIT(ng_rewrite)
    
    
    ng_rewrite_load();
    printf("ng_rewrite_lock_cache ... \n" );
    cache = (ng_rewrite_cache_t*) ng_rewrite_lock_cache();
    printf( "%d , %d , %d\n" , ng_rewrite_cache , ng_rewrite_cache0 , ng_rewrite_cache1 );
    printf( "ng_rewrite_unlock_cache: %d \n \n" , cache);
    ng_rewrite_unlock_cache(cache);
    
    
    ng_rewrite_load();
    printf("ng_rewrite_lock_cache ... \n" );
    cache = (ng_rewrite_cache_t*) ng_rewrite_lock_cache();
    printf( "%d , %d , %d\n" , ng_rewrite_cache , ng_rewrite_cache0 , ng_rewrite_cache1 );
    printf( "ng_rewrite_unlock_cache: %d \n\n" , cache);
    ng_rewrite_unlock_cache(cache);
    
    ng_rewrite_load();
    printf("ng_rewrite_lock_cache ... \n" );
    cache = (ng_rewrite_cache_t*) ng_rewrite_lock_cache();
    printf( "%d , %d , %d\n" , ng_rewrite_cache , ng_rewrite_cache0 , ng_rewrite_cache1 );
    printf( "ng_rewrite_unlock_cache: %d \n \n" , cache);
    ng_rewrite_unlock_cache(cache);
    
    ng_rewrite_load();
    printf("ng_rewrite_lock_cache ... \n" );
    cache = (ng_rewrite_cache_t*) ng_rewrite_lock_cache();
    printf( "%d , %d , %d\n" , ng_rewrite_cache , ng_rewrite_cache0 , ng_rewrite_cache1 );
    printf( "ng_rewrite_unlock_cache: %d \n \n" , cache);
    ng_rewrite_unlock_cache(cache);
    
    ng_rewrite_load();
    printf("ng_rewrite_lock_cache ... \n" );
    cache = (ng_rewrite_cache_t*) ng_rewrite_lock_cache();
    printf( "%d , %d , %d\n" , ng_rewrite_cache , ng_rewrite_cache0 , ng_rewrite_cache1 );
    printf( "ng_rewrite_unlock_cache: %d \n \n" , cache);
    ng_rewrite_unlock_cache(cache);
    
    ng_rewrite_load();
    printf("ng_rewrite_lock_cache ... \n" );
    cache = (ng_rewrite_cache_t*) ng_rewrite_lock_cache();
    printf( "%d , %d , %d\n" , ng_rewrite_cache , ng_rewrite_cache0 , ng_rewrite_cache1 );
    printf( "ng_rewrite_unlock_cache: %d \n \n" , cache);
    ng_rewrite_unlock_cache(cache);
    
    int nulls = 0;
    printf("using ... \n" );
    for (i = 0 ; i < cache->count ; ++i){
        ng_rewrite_t * nr = cache->data + i;
        ng_rewrite_t * rule = ng_rewrite_lookup( cache, nr->uid);
        if ( !rule )
            ++nulls ;
        //printf ("nr:%d , %d , %d\n"  , nr->uid , nr->ng , nr->mode);
    }
    printf ("nulls is %d \n"  , nulls);
}



