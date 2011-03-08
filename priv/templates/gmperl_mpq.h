#ifndef GMPERL_MPQ_H
#define GMPERL_MPQ_H

#include "gmperl_nifs.h"

{% for f in mpq %}{% include "priv/templates/fun.h" %}{% endfor %}
#endif // GMPERL_MPQ_H
