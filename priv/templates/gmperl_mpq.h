#ifndef GMPERL_MPQ_H
#define GMPERL_MPQ_H

#include "gmperl_nifs.h"

{{#mpq}}{{#version}}
#if _GNU_MP_VERSION >= {{major}}
#if _GNU_MP_VERSION_MINOR >= {{minor}}
#if _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}GMPERL_NIF_PROTOTYPE(gmperl_{{name}});{{#version}}
#endif // _GNU_MP_VERSION >= {{major}}
#endif // _GNU_MP_VERSION_MINOR >= {{minor}}
#endif // _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}{{/mpq}}
#endif // GMPERL_MPQ_H
