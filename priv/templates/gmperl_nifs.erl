%% -*- mode: erlang;erlang-indent-level: 4;indent-tabs-mode: nil -*-
%% ex: ft=erlang ts=4 sw=4 et
-module(gmperl_nifs).
-author('Hunter Morris <huntermorris@gmail.com>').

-on_load(init/0).

-export([info_lib/0]).

{{#mpz}}-export([{{name}}/{{arity}}]).
{{/mpz}}
{{#mpq}}-export([{{name}}/{{arity}}]).
{{/mpq}}
{{#mpf}}-export([{{name}}/{{arity}}]).
{{/mpf}}
-define(ERR, nif_stub_error(?LINE)).
-define(ERR(Line), erlang:nif_error({nif_not_loaded, module, ?MODULE, line, Line})).

-ifdef(TEST).
-compile(export_all).
-include_lib("eunit/include/eunit.hrl").
-endif.

-opaque mpz_t() :: binary().
-opaque mpq_t() :: binary().
-opaque mpf_t() :: binary().

-type num_base() :: 0 | 2..62.

-spec init() -> ok | {error, any()}.

-spec info_lib() -> [{binary(), binary()}].

{{#mpz}}-spec {{name}}({{#head_arg}}{{type}}{{/head_arg}}{{#tail_args}}, {{type}}{{/tail_args}}) -> {{ret_type}}.
{{/mpz}}
{{#mpq}}-spec {{name}}({{#head_arg}}{{type}}{{/head_arg}}{{#tail_args}}, {{type}}{{/tail_args}}) -> {{ret_type}}.
{{/mpq}}
{{#mpf}}-spec {{name}}({{#head_arg}}{{type}}{{/head_arg}}{{#tail_args}}, {{type}}{{/tail_args}}) -> {{ret_type}}.
{{/mpf}}
init() ->
    Dir = case code:priv_dir(gmperl) of
              {error, bad_name} -> "../priv";
              Priv              -> Priv
          end,
    erlang:load_nif(filename:join(Dir, "gmperl"), 0).

nif_stub_error(Line) -> erlang:nif_error({nif_not_loaded,module,?MODULE,line,Line}).

info_lib() -> ?ERR.

{{#mpz}}{{name}}({{#head_arg}}_{{/head_arg}}{{#tail_args}}, _{{/tail_args}}) -> ?ERR.
{{/mpz}}
{{#mpq}}{{name}}({{#head_arg}}_{{/head_arg}}{{#tail_args}}, _{{/tail_args}}) -> ?ERR.
{{/mpq}}
{{#mpf}}{{name}}({{#head_arg}}_{{/head_arg}}{{#tail_args}}, _{{/tail_args}}) -> ?ERR.
{{/mpf}}
-ifdef(TEST).

mpq_str_test() ->
    Ref = mpq_init(),
    ok = mpq_set_str(Ref, "9999999", 10),
    ?assertEqual("9999999", mpq_get_str(Ref, 10)).

mpz_test() ->
    _Ref0 = mpz_init(),
    Ref1 = mpz_init_set_str("1500", 10),
    ?assertEqual(1500, mpz_get_ui(Ref1)),
    ?assertEqual(1500, mpz_get_si(Ref1)),
    ?assertEqual(1500.0, mpz_get_d(Ref1)),
    ?assertEqual("1500", mpz_get_str(Ref1, 10)),
    _Ref2 = mpz_init_set(Ref1).

-endif.
