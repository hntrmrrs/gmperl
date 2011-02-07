gmperl
======

gmperl is a low-level Erlang NIF language binding for the GNU MP
Bignum (multiple precision arithmetic library). Tha main goal is to
augment Erlang's native bignum support with fast rational and mixed
precision floating point numbers.


## Requirements

* Erlang R14B1 or greater
* GMP (tested with 4.3.2 and 5.0.1; `mpz_powm_sec` requires 5.x)


## Source

gmperl's Git repo is available on Github at:

    http://github.com/skarab/gmperl


### Development

Clone the repo with:

    git clone git://github.com/skarab/gmperl.git


### Building

    # Run bootstrap to generate sources
    $ ./bootstrap
    # Run EUnit tests
    $ ./rebar eunit

### Contributing

1. Fork it, clone your fork, and create a new branch
1. Add code
1. Make sure new code has test that pass
1. Push your branch and send a pull request


## Usage

gmperl makes use of Erlang's NIF functionality. Note that long-running
NIF calls will block other NIF operations (due to the way they are
implemented in the Erlang scheduler).


### Integers

Integer functions are prefixed with `mpz_`.

    1> I = gmperl_nifs:mpz_init().
    <<>>
    2> ok = gmperl_nifs:mpz_set_ui(I, 10000000).
    ok
    3> J = gmperl_nifs:mpz_init().
    <<>>
    4> ok = gmperl_nifs:mpz_set_ui(J, 3).
    ok
    5> Result = gmperl_nifs:mpz_init().
    <<>>
    6> ok = gmperl_nifs:mpz_add(Result, I, J).
    ok
    7> gmperl_nifs:mpz_get_str(Result, 10).
    "10000003"


### Rational numbers

Functions for rational numbers are prefixed with `mpq_`.

    8> Q = gmperl_nifs:mpq_init().
    <<>>
    9> ok = gmperl_nifs:mpq_set_num(Q, I).
    ok
    10> ok = gmperl_nifs:mpq_set_den(Q, J).
    ok
    11> gmperl_nifs:mpq_get_str(Q, 10).
    "10000000/3"


### Floating-point numbers

Functions for floating-point numbers are prefixed with `mpf_`.

    12> F = gmperl_nifs:mpf_init_set_str("1234.0000001", 10).
    <<>>
    13> gmperl_nifs:mpf_get_str(F, 10, 100).
    {"12340000001",4}
    14> gmperl_nifs:mpf_get_prec(F).
    64


## TODO


* Batch allocation for speed
* `gmperl` module with more Erlang/FP-friendly methods
* Serialization/deserialization of GMP terms


## Additional documentation

See the GMP documentation at <http://gmplib.org>.


Copyright
---------

Copyright (c) 2011 Hunter Morris. See LICENSE for details.
