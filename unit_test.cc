
#ifdef TMAIN_KAUTIL_WSTD_REGEX_STATIC

#include "regex.h"

int tmain_regex_extern(
        int __printf(const char *,...)){

    {
        /* regex is not possible to use \\uff10-\\uff19 (not \uff10-\uff19) but
         wregex is possible to use \\uff10-\\uff19.
         this can be significant in some case such as rececive request from some other text orient language such as html's textarea . */

        {
            auto m = kautil_regex_extern_auto();
            auto reg = m->initialize();
            m->assign(reg,"[\\uff10-\\uff19]",KAUTIL_REGEX_ECMASCRIPT|KAUTIL_REGEX_ICASE);
            __printf("%s\n",m->exists(reg,"++０－９++")?"true":"false");
            m->free(reg);
        }


        {
            auto m = kautil_wregex_extern_auto();
            auto reg = m->initialize();
            m->assign(reg,L"[\\uff10-\\uff19]",KAUTIL_REGEX_ECMASCRIPT|KAUTIL_REGEX_ICASE);
            __printf("%s\n",m->exists(reg,L"++０－９++")?"true":"false");
            m->free(reg);
        }
    }


    {
        auto m = kautil_regex_extern_auto();
        auto reg = m->initialize();
        m->assign(reg,"(ura)(si)(ma)",KAUTIL_REGEX_ECMASCRIPT|KAUTIL_REGEX_ICASE);
        auto res = m->replace(reg,"urasima","$1th$3");
        __printf("%s\n",res);
        m->free(reg);
    }

    {
        auto m = kautil_wregex_extern_auto();
        auto reg = m->initialize();
        m->assign(reg,L"(ura)(si)(ma)(_wstr)",KAUTIL_REGEX_ECMASCRIPT|KAUTIL_REGEX_ICASE);
        auto res = m->replace(reg,L"urasima_wstr",L"$1th$3$4");
        __printf("%ls\n",res);
        m->free(reg);
    }

    {
        auto m = kautil_wregex_extern_auto();
        auto hreg = m->initialize();
        auto s = L"Some people, when confronted with a problem, think "
        "\"I know, I'll use regular expressions.\" "
        "Now they have two problems. 08:00~16:00  22:00-5:00  10時00~15時00分   => ABC=ＡＢＣ"
        "Now they have two problems. with wregex, could not replace unicode. but std::regex can => ABC=ＡＢＣ"
        "Now they have two problems. with wregex, could not replace unicode. but std::regex can => ABC=ＡＢＣ";
        
        {
            // i couldn't solve the problem ofslight deviation (e.g 10時00~15時00分, can not get 10 the return value includes 1 extra character)
            auto expr = L"([０-９|0-9]{2,6})[:|時]{1,3}([０-９|0-9]{1,6})[^０-９|^0-9|^\\s]+([０-９|0-9]{1,6})[:|時]{1,3}([０-９|0-9]{2,6})";
            m->assign(hreg,expr,KAUTIL_REGEX_ECMASCRIPT|KAUTIL_REGEX_ICASE);
            auto hsmat  = m->smatch_initialize(hreg);
            auto _beg = s;
            auto _cur = s;
            auto _end = s+256;// becouse wanted to omit wcslen
            for(;(_cur=m->smatch_search(hsmat,_cur,_end));){
                __printf("%lx",_cur);
                auto max = m->smatch_current_length(hsmat);
                auto res = (wchar_t *) 0;
                for(auto i =1; i < max;++i){
                    auto len =  m->smatch_current_item(hsmat,&res,i);
                    __printf("%.*ls\n",len,res);
                }
            }
            m->smatch_finalize(hsmat);
        }
        
        m->free(hreg);
        
    }
    return 0;
}

#include <stdio.h>

int main(){
//    while(true)
//    for(auto i = 0; i < 10000; ++i)
    tmain_regex_extern(printf);
}


#endif