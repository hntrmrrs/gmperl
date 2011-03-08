#include "gmperl_nifs.h"
{% for f in mpf %}{% include "priv/templates/fun.c" %}{% endfor %}
