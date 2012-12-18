typedef void ( * _cache_free_func ) ( void * ptr ); \

#define SWITHCING_CACHE_DECLARE(X) \
    extern void * X##_cache0; \
    extern void * X##_cache1; \
    extern void * X##_cache; \
    extern pthread_rwlock_t X##_cache_rwlock0; \
    extern pthread_rwlock_t X##_cache_rwlock1; \
    void * X##_lock_cache(); \
    void X##_unlock_cache(void * c); \
    void X##_refresh_cache(void * ptr , _cache_free_func free_func);
    
    
#define SWITHCING_CACHE_IMPLEMENT(X) \
void * X##_cache0 = NULL; \
void * X##_cache1 = NULL; \
void * X##_cache = NULL; \
pthread_rwlock_t X##_cache_rwlock0; \
pthread_rwlock_t X##_cache_rwlock1; \
 \
void * X##_lock_cache(){ \
    void * ret = X##_cache; \
    if (ret == NULL) \
        return; \
    if ( ret == X##_cache0){ \
        pthread_rwlock_rdlock(& X##_cache_rwlock0); \
        return ret; \
    } \
    if ( ret == X##_cache1){ \
        pthread_rwlock_rdlock(& X##_cache_rwlock1); \
        return ret; \
    } \
} \
 \
void X##_unlock_cache(void * c){ \
    if ( c ==NULL ) \
        return; \
    if ( c == X##_cache0){ \
        pthread_rwlock_unlock(& X##_cache_rwlock0); \
    } \
    if ( c == X##_cache1){ \
        pthread_rwlock_unlock( & X##_cache_rwlock1); \
    } \
} \
 \
void X##_refresh_cache(void * ptr , _cache_free_func free_func){ \
    void * old = NULL; \
    if ( X##_cache == X##_cache0 ){ \
        pthread_rwlock_wrlock( & X##_cache_rwlock1); \
        old = X##_cache1; \
        X##_cache1 = ptr; \
        X##_cache = X##_cache1; \
        free_func(old); \
        pthread_rwlock_unlock( & X##_cache_rwlock1); \
        return ; \
    } \
    if ( X##_cache == X##_cache1 ){ \
        pthread_rwlock_wrlock( & X##_cache_rwlock0); \
        old = X##_cache0; \
        X##_cache0 = ptr; \
        X##_cache = X##_cache0; \
        free_func(old); \
        pthread_rwlock_unlock( & X##_cache_rwlock0); \
        return ; \
    } \
} \


#define SWITHCING_CACHE_INIT(X) \
    pthread_rwlock_init( & X##_cache_rwlock0 , NULL); \
    pthread_rwlock_init( & X##_cache_rwlock1 , NULL); \
    