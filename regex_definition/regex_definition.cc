//#include "./internal.h"

#include <memory>
#include <regex>
#include <string>

#ifdef KAUTIL_REGEX_WSINGLE_STRING

using char_type=wchar_t;
using regex_type =std::wregex;
using string_type =std::wstring;
using sv_string_type =std::wstring_view;
using smach_type = std::wsmatch;
using sregex_itr_type = std::wsregex_iterator;
#define kautil_regex_(name) kautil_wregex_##name
#define kautil_smatch_t kautil_wsmatch
#define kautil_extern_type kautil_wregex_extern
#define extern_initialize extern_initialize_w
#define extern_finalize extern_finalize_w

#else

using char_type=char;
using regex_type =std::regex;
using string_type =std::string;
using sv_string_type =std::string_view;
using smach_type = std::smatch;
using sregex_itr_type = std::sregex_iterator;
#define kautil_regex_(name) kautil_regex_##name
#define kautil_smatch_t kautil_smatch
#define extern_initialize extern_initialize
#define extern_finalize extern_finalize
#define kautil_extern_type kautil_regex_extern
#endif

struct handle{
    std::unique_ptr<regex_type> regex;
    string_type buffer;
};
#define __h(hdl) reinterpret_cast<handle*>(hdl)


const char_type * kautil_regex_(replace)(void * hdl,const char_type * input,const char_type * replacement){
    return (__h(hdl)->buffer = std::regex_replace(input, *__h(hdl)->regex, replacement)).c_str();
}

void kautil_regex_(assign)(void * hdl,const char_type * match,unsigned int  option){
    __h(hdl)->regex->assign(match, static_cast<std::regex_constants::syntax_option_type>(option));
}

bool kautil_regex_(exists)(void * hdl,const char_type * input){
    return std::regex_search(input, *__h(hdl)->regex);
}

void *kautil_regex_(initialize)() {
    auto res =  new handle;
    res->regex= std::make_unique<regex_type>();
    return res;
}

void kautil_regex_(finalize)(void *hdl) {
    delete reinterpret_cast<handle*>(hdl);
}


struct kautil_smatch_t{
    // ref:
    // iterate smatch smatch::suffix : https://stackoverflow.com/questions/21667295/how-to-match-multiple-results-using-stdregex
    //    https://stackoverflow.com/questions/29321249/regex-grouping-matches-with-c-11-regex-library
    smach_type matches;
    regex_type * rgx=nullptr;
};


kautil_smatch_t * kautil_regex_(smatch_initialize)(void * regex_hdl){
    auto res= new kautil_smatch_t;
    res->rgx=__h(regex_hdl)->regex.get();
    return res;
}


void kautil_regex_(smatch_finalize)(kautil_smatch_t* hdl){
    delete hdl;
}


uint64_t kautil_regex_(smatch_current_length)(kautil_smatch_t* hdl){ return  hdl->matches.size(); }
uint64_t kautil_regex_(smatch_current_item)(kautil_smatch_t* hdl,char_type ** item,int const& i){
    *item=const_cast<char_type*>(hdl->matches[i].first.base());
    return hdl->matches[i].second-hdl->matches[i].first;
}


char_type * kautil_regex_(smatch_search)(kautil_smatch_t* hdl,const char_type * b,const char_type * e) {
    if (std::regex_search(string_type::const_iterator{b}, string_type::const_iterator{e}, hdl->matches, *hdl->rgx)) {
        return const_cast<char_type*>( hdl->matches.suffix().first.base());
    } else return nullptr;
}



struct iterator{
    sv_string_type s;
    sregex_itr_type beg;
    sregex_itr_type end;
    sregex_itr_type cur;
    regex_type * regex;
    string_type buffer;
};

#define __i(hdl) reinterpret_cast<iterator*>(hdl)


void * kautil_regex_(itr_initialize)(void * hdl){
    auto res = new iterator{};
    res->regex=__h(hdl)->regex.get();
    return res;
}

int kautil_regex_(itr_set)(void * itr, const char_type * input){
    __i(itr)->s = input;
    __i(itr)->beg = sregex_itr_type(
            string_type::const_iterator(__i(itr)->s.begin())
            , string_type::const_iterator(__i(itr)->s.end()), *__i(itr)->regex);
    __i(itr)->end = sregex_itr_type();
    __i(itr)->cur = __i(itr)->beg;
    return 0;
}

uint64_t kautil_regex_(itr_length_found)(void * itr){
    return static_cast<uint64_t>(std::distance(__i(itr)->beg,__i(itr)->end));
}


bool kautil_regex_(itr_next)(void * itr){ return (++(__i(itr)->cur) == (__i(itr)->end)) ? false : true; }
void kautil_regex_(itr_finalize)(void * hdl){ delete __i(hdl); }

uint64_t kautil_regex_(itr_str)(void * itr,char_type ** res){
    *res=const_cast<char_type*>(__i(itr)->cur->operator[](0).first.base());
    return __i(itr)->cur->length();
}



#include "../regex.h"
extern "C" kautil_extern_type * extern_initialize(){
    auto m = new kautil_extern_type{};
    m->initialize = kautil_regex_(initialize);
    m->free = kautil_regex_(finalize);
    m->assign = kautil_regex_(assign);
    m->exists = kautil_regex_(exists);
    m->replace = kautil_regex_(replace);
    m->itr_initialize = kautil_regex_(itr_initialize);
    m->itr_free = kautil_regex_(itr_finalize);
    m->itr_next = kautil_regex_(itr_next);
    m->itr_set = kautil_regex_(itr_set);
    m->itr_length_found = kautil_regex_(itr_length_found);
    m->itr_str = kautil_regex_(itr_str);
    m->smatch_initialize = kautil_regex_(smatch_initialize);
    m->smatch_free = kautil_regex_(smatch_finalize);
    m->smatch_current_length = kautil_regex_(smatch_current_length);
    m->smatch_current_item = kautil_regex_(smatch_current_item);
    m->smatch_search = kautil_regex_(smatch_search);
    return m;
}

extern "C" void extern_finalize(kautil_regex_extern * m){ delete m; }

