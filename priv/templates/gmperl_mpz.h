#ifndef GMPERL_MPZ_H
#define GMPERL_MPZ_H

#include "gmperl_nifs.h"

{{#mpz}}{{#version}}
#if _GNU_MP_VERSION >= {{major}}
#if _GNU_MP_VERSION_MINOR >= {{minor}}
#if _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}GMPERL_NIF_PROTOTYPE(gmperl_{{name}});{{#version}}
#endif // _GNU_MP_VERSION >= {{major}}
#endif // _GNU_MP_VERSION_MINOR >= {{minor}}
#endif // _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}{{/mpz}}
#endif // GMPERL_MPZ_H
