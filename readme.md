### kautil_regex
* wrapper of std::regex and std::wregex
* prepared to shorten compilation time

### note 
* kautil_regex_extern_initialize / kautil_wregex_extern_initialize : use when want to make detailed settings for dl options
* kautil_regex_extern_auto / kautil_wregex_extern_auto             : this is handire than kautil_(w)regex_extern_initialize, and perhaps compilation time is short, but dl options are fixed.

### example
```c++

#include "kautil/regex/regex.h"
#include <stdio.h>

int main{
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
    return 0;
}

```
