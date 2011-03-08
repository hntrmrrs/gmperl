#include "gmperl_nifs.h"
{% for f in mpz %}{% include "priv/templates/fun.c" %}{% endfor %}
