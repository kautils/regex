#ifndef _KAUTIL_WSTD_WREGEX_EXTERN_H
#define _KAUTIL_WSTD_WREGEX_EXTERN_H

#include <stdint.h>


#define KAUTIL_REGEX_ICASE 1
#define KAUTIL_REGEX_NOSUBS 2
#define KAUTIL_REGEX_OPTIMIZE 4
#define KAUTIL_REGEX_COLLATE 8
#define KAUTIL_REGEX_ECMASCRIPT 16
#define KAUTIL_REGEX_BASIC 32
#define KAUTIL_REGEX_EXTENDED 64
#define KAUTIL_REGEX_AWK 128
#define KAUTIL_REGEX_GREP 256
#define KAUTIL_REGEX_EGREP 256


struct kautil_smatch;
struct kautil_smatch_prv;
struct kautil_regex_extern{
    void (*assign)(void * hdl,const char * match,unsigned int  option)=0;
    bool (*search)(void * hdl,const char * input)=0;
    bool (*exists)(void * hdl,const char * input) =0;
    void * (*itr_initialize)(void * hdl)=0;
    int (*itr_set)(void * itr, const char * input)=0;
    uint64_t (*itr_length_found)(void * itr)=0;
    const char * (*replace)(void * hdl,const char * input,const char * replacement)=0;
    bool (*itr_next)(void * itr)=0;
    uint64_t (*itr_str)(void * itr,char ** res)=0;
    void (*itr_free)(void * hdl)=0;
    void * (*initialize)()=0;
    void (*free)(void *hdl)=0;

    kautil_smatch* (*smatch_initialize)(void *hdl)=0;
    void (*smatch_free)(kautil_smatch *hdl)=0;
    uint64_t (*smatch_current_length)(kautil_smatch *hdl)=0;
    uint64_t (*smatch_current_item)(kautil_smatch* hdl,char ** item,int const& i)=0;
    char * (*smatch_search)(kautil_smatch* hdl,const char * b,const char * e)=0;
    kautil_smatch_prv * prv = 0;
};

struct kautil_wsmatch;
struct kautil_wsmatch_prv;
struct kautil_wregex_extern{
    void (*assign)(void * hdl,const wchar_t * match,unsigned int  option)=0;
    bool (*search)(void * hdl,const wchar_t * input)=0;
    void * (*itr_initialize)(void * hdl)=0;
    int (*itr_set)(void * itr, const wchar_t * input)=0;
    bool (*exists)(void * hdl,const wchar_t * input) =0;
    uint64_t (*itr_length_found)(void * itr)=0;
    const wchar_t * (*replace)(void * hdl,const wchar_t * input,const wchar_t * replacement)=0;
    bool (*itr_next)(void * itr)=0;
    uint64_t (*itr_str)(void * itr,wchar_t ** res)=0;
    void (*itr_free)(void * hdl)=0;
    void (*free)(void *hdl)=0;
    void * (*initialize)()=0;

    uint64_t (*smatch_current_length)(kautil_wsmatch *hdl)=0;
    kautil_wsmatch * (*smatch_initialize)(void *hdl)=0;
    void (*smatch_free)(kautil_wsmatch *hdl)=0;
    uint64_t (*smatch_currentlength)(kautil_wsmatch *hdl)=0;
    uint64_t (*smatch_current_item)(kautil_wsmatch* hdl,wchar_t ** item,int const& i)=0;
    wchar_t * (*smatch_search)(kautil_wsmatch* hdl,const wchar_t * b,const wchar_t * e)=0;
    kautil_wsmatch_prv * prv = 0;
};


kautil_regex_extern * kautil_regex_extern_initialize(
        void *(*dlopen)(const char * ,int flags)
        ,void *(*dlsym)(void * ,const char *)
        ,int (*dlclose)(void*)
        ,int flags);
void kautil_regex_extern_free(kautil_regex_extern *m);
kautil_regex_extern * kautil_regex_extern_auto(); 


kautil_wregex_extern * kautil_wregex_extern_initialize(
        void *(*dlopen)(const char * ,int flags)
        ,void *(*dlsym)(void * ,const char *)
        ,int (*dlclose)(void*)
        ,int flags);
void kautil_wregex_extern_free(kautil_wregex_extern *m);
kautil_wregex_extern * kautil_wregex_extern_auto(); 




#endif