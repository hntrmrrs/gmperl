#ifndef GMPERL_NIFS_H
#define GMPERL_NIFS_H

#include "erl_nif.h"
#include <gmp.h>

typedef struct {
    mpz_t z;
    int   init;
} gmperl_mpz_t;

typedef struct {
    mpq_t q;
    int   init;
} gmperl_mpq_t;

typedef struct {
    mpf_t f;
    unsigned int rebits;
    int init;
} gmperl_mpf_t;

typedef struct {
    ErlNifResourceType *gmperl_mpz_rt;
    ErlNifResourceType *gmperl_mpq_rt;
    ErlNifResourceType *gmperl_mpf_rt;
    ERL_NIF_TERM atom_ok;
    ERL_NIF_TERM atom_true;
    ERL_NIF_TERM atom_false;
} gmperl_privdata_t;

ERL_NIF_TERM enif_get_boolean(ErlNifEnv *env, int n);
ERL_NIF_TERM enif_get_ok(ErlNifEnv *env);

#define GMPERL_NIF_PROTOTYPE(F) ERL_NIF_TERM F(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
#define BUF_SZ 4096

#include "gmperl_mpz.h"
#include "gmperl_mpq.h"
#include "gmperl_mpf.h"

#endif // GMPERL_NIFS_H
