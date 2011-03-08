#include "gmperl_nifs.h"
{% for f in mpq %}{% include "priv/templates/fun.c" %}{% endfor %}
