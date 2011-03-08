#ifndef GMPERL_MPF_H
#define GMPERL_MPF_H

#include "gmperl_nifs.h"

{% for f in mpf %}{% include "priv/templates/fun.h" %}{% endfor %}
#endif // GMPERL_MPF_H
