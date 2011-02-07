#include "gmperl_nifs.h"
{{#mpq}}
{{#version}}
#if _GNU_MP_VERSION >= {{major}}
#if _GNU_MP_VERSION_MINOR >= {{minor}}
#if _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}GMPERL_NIF_PROTOTYPE(gmperl_{{name}})
{
    ERL_NIF_TERM ret;
    gmperl_privdata_t *priv = enif_priv_data(env);

    {{#locals}}

    {{#long}}long{{/long}}
    {{#int}}int{{/int}}
    {{#uint}}unsigned int{{/uint}}
    {{#int_out}}int{{/int_out}}
    {{#uint_out}}unsigned int{{/uint_out}}
    {{#long_out}}long{{/long_out}}
    {{#ulong}}unsigned long{{/ulong}}
    {{#double}}double{{/double}}
    {{#string}}char{{/string}}
    {{#num_base}}unsigned{{/num_base}}
    {{#mpz_t}}gmperl_mpz_t *{{/mpz_t}}
    {{#mpq_t}}gmperl_mpq_t *{{/mpq_t}}
    {{#mpf_t}}gmperl_mpf_t *{{/mpf_t}}
    {{#new_mpz_t}}gmperl_mpz_t *{{/new_mpz_t}}
    {{#new_mpq_t}}gmperl_mpq_t *{{/new_mpq_t}}
    {{#new_mpf_t}}gmperl_mpf_t *{{/new_mpf_t}}
    {{#char_ptr}}char *{{/char_ptr}}
    val{{index}}{{#string}}[4096]{{/string}}{{#char_ptr}} = NULL{{/char_ptr}}

    {{#new_mpz_t}} = (gmperl_mpz_t *)enif_alloc_resource(priv->gmperl_mpz_rt, sizeof(gmperl_mpz_t)){{/new_mpz_t}}
    {{#new_mpq_t}} = (gmperl_mpq_t *)enif_alloc_resource(priv->gmperl_mpq_rt, sizeof(gmperl_mpq_t)){{/new_mpq_t}}
    {{#new_mpf_t}} = (gmperl_mpf_t *)enif_alloc_resource(priv->gmperl_mpf_rt, sizeof(gmperl_mpf_t)){{/new_mpf_t}}

    ;

    {{#mpz_t}}
    if (!enif_get_resource(env, argv[{{in_index}}], priv->gmperl_mpz_rt, (void**)&val{{index}})) {
        goto badarg;
    }
    {{/mpz_t}}

    {{#mpq_t}}
    if (!enif_get_resource(env, argv[{{in_index}}], priv->gmperl_mpq_rt, (void**)&val{{index}})) {
        goto badarg;
    }
    {{/mpq_t}}

    {{#mpf_t}}
    if (!enif_get_resource(env, argv[{{in_index}}], priv->gmperl_mpf_rt, (void**)&val{{index}})) {
        goto badarg;
    }
    {{/mpf_t}}

    {{#ulong}}
    if (!enif_get_ulong(env, argv[{{in_index}}], &val{{index}})) {
        goto badarg;
    }
    {{/ulong}}

    {{#long}}
    if (!enif_get_long(env, argv[{{in_index}}], &val{{index}})) {
        goto badarg;
    }
    {{/long}}

    {{#int}}
    if (!enif_get_int(env, argv[{{in_index}}], &val{{index}})) {
        goto badarg;
    }
    {{/int}}

    {{#uint}}
    if (!enif_get_uint(env, argv[{{in_index}}], &val{{index}})) {
        goto badarg;
    }
    {{/uint}}

    {{#double}}
    if (!enif_get_double(env, argv[{{in_index}}], &val{{index}})) {
        goto badarg;
    }
    {{/double}}

    {{#num_base}}
    if (!enif_get_uint(env, argv[{{in_index}}], &val{{index}})
        || (val{{index}} != 0 && (val{{index}} < 2 || val{{index}} > 62))) {
        goto badarg;
    }
    {{/num_base}}

    {{#string}}
    if (!enif_get_string(env, argv[{{in_index}}], val{{index}}, sizeof(val{{index}}), ERL_NIF_LATIN1)) {
        goto badarg;
    }
    {{/string}}

    {{/locals}}

    {{#call}}

    {{#retval}}
    {{#long}}long{{/long}}
    {{#int}}int{{/int}}
    {{#uint}}unsigned int{{/uint}}
    {{#long_out}}long{{/long_out}}
    {{#int_out}}int{{/int_out}}
    {{#uint_out}}unsigned int{{/uint_out}}
    {{#ulong}}unsigned long{{/ulong}}
    {{#double}}double{{/double}}
    {{#string}}char *{{/string}}
    {{#num_base}}unsigned{{/num_base}}
    {{#assert_zero}}int{{/assert_zero}}
    {{#boolean}}int{{/boolean}}

    val0 =
    {{/retval}}

    {{name}}({{#head}}{{#reference}}&{{/reference}}val{{index}}{{#pointer}}->{{target}}{{/pointer}}{{/head}}{{#tail}}, {{#reference}}&{{/reference}}val{{index}}{{#pointer}}->{{target}}{{/pointer}}{{/tail}});

    {{#retval}}{{#assert_zero}}if (0 != val0) { goto badarg; }{{/assert_zero}}{{/retval}}
    {{/call}}

    {{#return}}

    {{#ok}}ret = enif_get_ok(env);{{/ok}}
    {{#long}}ret = enif_make_long(env, val{{index}});{{/long}}
    {{#int}}ret = enif_make_int(env, val{{index}});{{/int}}
    {{#uint}}ret = enif_make_uint(env, val{{index}});{{/uint}}
    {{#long_out}}ret = enif_make_long(env, val{{index}});{{/long_out}}
    {{#ulong}}ret = enif_make_ulong(env, val{{index}});{{/ulong}}
    {{#ulong_out}}ret = enif_make_ulong(env, val{{index}});{{/ulong_out}}
    {{#int_out}}ret = enif_make_int(env, val{{index}});{{/int_out}}
    {{#uint_out}}ret = enif_make_uint(env, val{{index}});{{/uint_out}}
    {{#double}}ret = enif_make_double(env, val{{index}});{{/double}}
    {{#double_out}}ret = enif_make_double(env, val{{index}});{{/double_out}}
    {{#string}}ret = enif_make_string(env, val{{index}}, ERL_NIF_LATIN1);{{/string}}
    {{#mpz_t}}ret = enif_make_resource(env, val{{index}});{{/mpz_t}}
    {{#mpq_t}}ret = enif_make_resource(env, val{{index}});{{/mpq_t}}
    {{#mpf_t}}ret = enif_make_resource(env, val{{index}});{{/mpf_t}}
    {{#boolean}}ret = enif_get_boolean(env, val{{index}});{{/boolean}}

    {{#tuple2}}ret = enif_make_tuple2(env,
    {{#first}}
    {{#long}}enif_make_long(env, val{{index}}){{/long}}
    {{#int}}enif_make_int(env, val{{index}}){{/int}}
    {{#uint}}enif_make_uint(env, val{{index}}){{/uint}}
    {{#long_out}}enif_make_long(env, val{{index}}){{/long_out}}
    {{#int_out}}enif_make_int(env, val{{index}}){{/int_out}}
    {{#uint_out}}enif_make_uint(env, val{{index}}){{/uint_out}}
    {{#ulong}}enif_make_ulong(env, val{{index}}){{/ulong}}
    {{#ulong_out}}enif_make_ulong(env, val{{index}}){{/ulong_out}}
    {{#double}}enif_make_double(env, val{{index}}){{/double}}
    {{#double_out}}enif_make_double(env, val{{index}}){{/double_out}}
    {{#string}}enif_make_string(env, val{{index}}, ERL_NIF_LATIN1){{/string}}
    {{/first}},
    {{#second}}
    {{#long}}enif_make_long(env, val{{index}}){{/long}}
    {{#int}}enif_make_int(env, val{{index}}){{/int}}
    {{#uint}}enif_make_uint(env, val{{index}}){{/uint}}
    {{#long_out}}enif_make_long(env, val{{index}}){{/long_out}}
    {{#int_out}}enif_make_int(env, val{{index}}){{/int_out}}
    {{#uint_out}}enif_make_uint(env, val{{index}}){{/uint_out}}
    {{#ulong}}enif_make_ulong(env, val{{index}}){{/ulong}}
    {{#ulong_out}}enif_make_ulong(env, val{{index}}){{/ulong_out}}
    {{#double}}enif_make_double(env, val{{index}}){{/double}}
    {{#double_out}}enif_make_double(env, val{{index}}){{/double_out}}
    {{#string}}enif_make_string(env, val{{index}}, ERL_NIF_LATIN1){{/string}}
    {{/second}}
    );{{/tuple2}}

    {{#mpz_t}}enif_release_resource(val{{index}});{{/mpz_t}}
    {{#mpq_t}}enif_release_resource(val{{index}});{{/mpq_t}}
    {{#mpf_t}}enif_release_resource(val{{index}});{{/mpf_t}}
    {{/return}}

    {{#call}}
    {{#retval}}
    {{#string}}enif_free(val0);{{/string}}
    {{/retval}}
    {{/call}}

    return ret;

    {{#needs_badarg}}badarg:{{/needs_badarg}}

    {{#locals}}

    {{#new_mpz_t}}
    if (NULL != val{{index}}) enif_release_resource(val{{index}});
    {{/new_mpz_t}}

    {{#new_mpq_t}}
    if (NULL != val{{index}}) enif_release_resource(val{{index}});
    {{/new_mpq_t}}

    {{#new_mpf_t}}
    if (NULL != val{{index}}) enif_release_resource(val{{index}});
    {{/new_mpf_t}}

    {{/locals}}

    {{#needs_badarg}}return enif_make_badarg(env);{{/needs_badarg}}
}{{#version}}
#endif // _GNU_MP_VERSION >= {{major}}
#endif // _GNU_MP_VERSION_MINOR >= {{minor}}
#endif // _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}{{/mpq}}
