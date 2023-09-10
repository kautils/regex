
#include "regex.h"

struct kautil_wsmatch_prv{
    void * dl=0;
    void (*destruct)(kautil_wregex_extern*)=0;
    int (*dlclose)(void*)=0;
};

kautil_wregex_extern * kautil_wregex_extern_initialize(
        void *(*dlopen)(const char * ,int flags)
        ,void *(*dlsym)(void * ,const char *)
        ,int (*dlclose)(void*)
        ,int flags){
    auto hdl = dlopen(KAUTIL_WSTD_REEGX_SO,flags);
    auto m = ((kautil_wregex_extern *(*)())dlsym(hdl,"extern_initialize_w"))();
    m->prv = new kautil_wsmatch_prv;
    m->prv->destruct=(void (*)(kautil_wregex_extern*))dlsym(hdl,"extern_finalize_w");
    m->prv->dl =hdl;
    m->prv->dlclose = dlclose;
    return m;
}

void kautil_wregex_extern_free(kautil_wregex_extern * m){
    if(0== (!m + !m->prv)){
        auto dlclose = m->prv->dlclose;
        auto prv = m->prv;
        auto dl = m->prv->dl;
        auto destruct = m->prv->destruct;
        delete prv;
        destruct(m);
        dlclose(dl);
    }
}


struct kautil_smatch_prv{
    void * dl=0;
    void (*destruct)(kautil_regex_extern*)=0;
    int (*dlclose)(void*)=0;
};

kautil_regex_extern * kautil_regex_extern_initialize(
        void *(*dlopen)(const char * ,int flags)
        ,void *(*dlsym)(void * ,const char *)
        ,int (*dlclose)(void*)
        ,int flags){
    auto hdl = dlopen(KAUTIL_WSTD_REEGX_SO,flags);
    auto m = ((kautil_regex_extern *(*)())dlsym(hdl,"extern_initialize"))();
    m->prv = new kautil_smatch_prv;
    m->prv->destruct=(void (*)(kautil_regex_extern*))dlsym(hdl,"extern_finalize");
    m->prv->dl =hdl;
    m->prv->dlclose = dlclose;
    return m;
}

void kautil_regex_extern_free(kautil_regex_extern * m){
    if(0== (!m + !m->prv)){
        auto dlclose = m->prv->dlclose;
        auto prv = m->prv;
        auto dl = m->prv->dl;
        auto destruct = m->prv->destruct;
        delete prv;
        destruct(m);
        dlclose(dl);
    }
}




#include "kautil/sharedlib/sharedlib.h"

struct auto_delete_w{
    kautil_wregex_extern * m=0;
    auto_delete_w(){ m=kautil_wregex_extern_initialize(kautil_dlopen,kautil_dlsym,kautil_dlclose,rtld_lazy|rtld_nodelete); }
    ~auto_delete_w(){ kautil_wregex_extern_free(m); }
};

kautil_wregex_extern * kautil_wregex_extern_auto(){ static auto kRes = auto_delete_w{};return kRes.m; }


struct auto_delete{
    kautil_regex_extern * m=0;
    auto_delete(){ m=kautil_regex_extern_initialize(kautil_dlopen,kautil_dlsym,kautil_dlclose,rtld_lazy|rtld_nodelete); }
    ~auto_delete(){ kautil_regex_extern_free(m); }
};

kautil_regex_extern * kautil_regex_extern_auto(){ static auto kRes = auto_delete{};return kRes.m; } 




