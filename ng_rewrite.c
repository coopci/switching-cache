#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

#include "ng_rewrite.h"

SWITHCING_CACHE_IMPLEMENT(ng_rewrite)

int ng_rewrite_init(){
    SWITHCING_CACHE_INIT(ng_rewrite)
    return 0;
}
int ng_rewrite_load(){
    sqlite3 *db;
    sqlite3_stmt *pStmt;
    sqlite3_stmt *pStmtCount;
    sqlite3_stmt *pStmtRows;
    int rewrites_count = 0; 
    int rc = 0;
    int i = 0;
    rc = sqlite3_open( "/home/dp/var/database/dpdispatcher.sqlite3" , &db);
    if ( rc != SQLITE_OK )
        return -1;
    rc = sqlite3_prepare( db , "select count(*) from proxy_rewritengbyuidjudged; " , -1 , &pStmtCount , NULL);
    if ( rc != SQLITE_OK )
        return -2;
    
    sqlite3_step(pStmtCount);
    rewrites_count = sqlite3_column_int( pStmtCount, 0);
    printf("rewrites_count is %d\n" , rewrites_count);
    
    ng_rewrite_t * cache = calloc( rewrites_count , sizeof(ng_rewrite_t)) ;
    
    if ( !cache )
        return -3;
    sqlite3_finalize(pStmtCount);
    
    rc = sqlite3_prepare( db , "select uid , ng , mode from proxy_rewritengbyuidjudged order by uid; " , -1 , &pStmtRows , NULL);
    
    printf("get rows \n" );
    while( sqlite3_step(pStmtRows) == SQLITE_ROW){
        ng_rewrite_t * nr = cache + i;
        nr->uid = sqlite3_column_int64( pStmtRows, 0);
        nr->ng = sqlite3_column_int( pStmtRows, 1);
        nr->mode = sqlite3_column_int( pStmtRows, 2);
        ++i;
        if ( i >= rewrites_count)
            break;
    }
    ng_rewrite_cache_t * _cache = calloc( 1 , sizeof(ng_rewrite_cache_t) );
    _cache->count = rewrites_count;
    _cache->data = cache;
    printf("loaded , refreshing ... \n" );
    ng_rewrite_refresh_cache( _cache , (_cache_free_func)ng_rewrite_free_cache);
    sqlite3_close(db);
    return 0;
}

void ng_rewrite_free_cache(ng_rewrite_cache_t * cache){
    if ( !cache)
        return;
    if ( cache->data )
        free(cache->data);
    free(cache);
}

/*
  binary search for a 
  typedef struct _ng_rewrite{
    int64_t uid ;
    int ng ;
    int mode ;
  } ng_rewrite_t;
  in 
  typedef struct _ng_rewrite_cache{
    int count;
    ng_rewrite_t * data;
   } ng_rewrite_cache_t;
 
*/
ng_rewrite_t *  ng_rewrite_lookup(ng_rewrite_cache_t * _cache, int64_t uid){
    int middle = 0;
    int head = 0;
    int tail = 0;
    ng_rewrite_t * cur = NULL;
    
    if ( ! _cache )
        return NULL;
    if ( _cache->count <= 0)
        return NULL;
    tail = _cache->count - 1;
    
    cur = _cache->data + tail;
    if ( cur->uid == uid ){
        return cur;
    }
    middle = _cache->count / 2;
    while( middle > head ){
        cur = _cache->data + middle;
        if ( cur->uid == uid )
            return cur;
        if ( cur->uid > uid ){
            tail = middle;
        }
        if ( cur->uid < uid ){
            head = middle;
        }
        
        middle = head + (tail - head) / 2;
    }
    cur = _cache->data + middle;
    if ( cur->uid == uid ){
        return cur;
    }
    
    return NULL;
}