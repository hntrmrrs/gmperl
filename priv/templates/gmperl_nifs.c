#include <string.h>

#include "gmperl_nifs.h"

static void
gmperl_mpz_t_dtor(ErlNifEnv *env, void *obj)
{
    mpz_clear(((gmperl_mpz_t *)obj)->z);
}

static void
gmperl_mpq_t_dtor(ErlNifEnv *env, void *obj)
{
    mpq_clear(((gmperl_mpq_t *)obj)->q);
}

static void
gmperl_mpf_t_dtor(ErlNifEnv *env, void *obj)
{
    mpf_clear(((gmperl_mpf_t *)obj)->f);
}

static void *
gmperl_allocate(size_t size)
{
    return enif_alloc(size);
}

static void *
gmperl_reallocate(void *ptr, size_t old_size, size_t new_size)
{
    return enif_realloc(ptr, new_size);
}

static void
gmperl_free(void *ptr, size_t size)
{
    return enif_free(ptr);
}

static int
on_load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM load_info)
{
    gmperl_privdata_t *priv;

    priv = (gmperl_privdata_t *)enif_alloc(sizeof(gmperl_privdata_t));
    priv->gmperl_mpz_rt = NULL;
    priv->gmperl_mpq_rt = NULL;
    priv->gmperl_mpf_rt = NULL;
    *priv_data = priv;

    /* Use Erlang NIF memory allocation/deallocation */
    mp_set_memory_functions(gmperl_allocate, gmperl_reallocate, gmperl_free);

    /* Create resource types */
    ErlNifResourceFlags flags = (ErlNifResourceFlags)(ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER);
    priv->gmperl_mpz_rt = enif_open_resource_type(env, "gmperl_nifs", "gmperl_mpz_resource", gmperl_mpz_t_dtor, flags, NULL);
    priv->gmperl_mpq_rt = enif_open_resource_type(env, "gmperl_nifs", "gmperl_mpq_resource", gmperl_mpq_t_dtor, flags, NULL);
    priv->gmperl_mpf_rt = enif_open_resource_type(env, "gmperl_nifs", "gmperl_mpf_resource", gmperl_mpf_t_dtor, flags, NULL);
    if (!enif_make_existing_atom(env, "ok", &priv->atom_ok, ERL_NIF_LATIN1)
        || !enif_make_existing_atom(env, "true", &priv->atom_true, ERL_NIF_LATIN1)
        || !enif_make_existing_atom(env, "false", &priv->atom_false, ERL_NIF_LATIN1)) {
        return -1;
    }
    return 0;
}

static int
on_reload(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM load_info)
{
    // Don't need to do anything here yet
    return 0;
}

static int
on_upgrade(ErlNifEnv *env, void **priv_data, void **old_priv_data, ERL_NIF_TERM load_info)
{
    // Don't need to do anything here yet
    *priv_data = *old_priv_data;
    return 0;
}

static void
on_unload(ErlNifEnv *env, void *priv_data)
{
    // Free the private data allocated earlier
    enif_free(priv_data);
}

ERL_NIF_TERM
enif_get_boolean(ErlNifEnv *env, int n)
{
    gmperl_privdata_t *priv = (gmperl_privdata_t *)enif_priv_data(env);
    return n ? priv->atom_true : priv->atom_false;
}

ERL_NIF_TERM
enif_get_ok(ErlNifEnv *env)
{
    return ((gmperl_privdata_t *)enif_priv_data(env))->atom_ok;
}

GMPERL_NIF_PROTOTYPE(gmperl_info_lib)
{
    static const char libname[] = "GMP";
    unsigned name_sz = strlen(libname);
    unsigned ver_sz  = strlen(gmp_version);
    ERL_NIF_TERM name_term, ver_term;

    memcpy(enif_make_new_binary(env, name_sz, &name_term), libname, name_sz);
    memcpy(enif_make_new_binary(env, ver_sz, &ver_term), gmp_version, ver_sz);

    return enif_make_list1(env, enif_make_tuple2(env, name_term, ver_term));
}

static ErlNifFunc nif_funcs[] =
{
    {"info_lib",         0, gmperl_info_lib},
{{#mpz}}{{#version}}
#if _GNU_MP_VERSION >= {{major}}
#if _GNU_MP_VERSION_MINOR >= {{minor}}
#if _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}{"{{name}}", {{arity}}, gmperl_{{name}}\},{{#version}}
#endif // _GNU_MP_VERSION >= {{major}}
#endif // _GNU_MP_VERSION_MINOR >= {{minor}}
#endif // _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}{{/mpz}}
{{#mpq}}{{#version}}
#if _GNU_MP_VERSION >= {{major}}
#if _GNU_MP_VERSION_MINOR >= {{minor}}
#if _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}{"{{name}}", {{arity}}, gmperl_{{name}}\},{{#version}}
#endif // _GNU_MP_VERSION >= {{major}}
#endif // _GNU_MP_VERSION_MINOR >= {{minor}}
#endif // _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}{{/mpq}}
{{#mpf}}{{#version}}
#if _GNU_MP_VERSION >= {{major}}
#if _GNU_MP_VERSION_MINOR >= {{minor}}
#if _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}{"{{name}}", {{arity}}, gmperl_{{name}}\},{{#version}}
#endif // _GNU_MP_VERSION >= {{major}}
#endif // _GNU_MP_VERSION_MINOR >= {{minor}}
#endif // _GNU_MP_VERSION_PATCHLEVEL >= {{patchlevel}}
{{/version}}{{/mpf}}\};

ERL_NIF_INIT(gmperl_nifs, nif_funcs, on_load, on_reload, on_upgrade, on_unload)
