#ifndef GMPERL_MPF_H
#define GMPERL_MPF_H

#include "gmperl_nifs.h"

{{#mpf}}{{#version}}
#if _GNU_MP_VERSION >= {{major}}
#if _GNU_MP_VERSION_MINOR >= {{minor}}
#if _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}GMPERL_NIF_PROTOTYPE(gmperl_{{name}});{{#version}}
#endif // _GNU_MP_VERSION >= {{major}}
#endif // _GNU_MP_VERSION_MINOR >= {{minor}}
#endif // _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}{{/mpf}}
#endif // GMPERL_MPF_H
