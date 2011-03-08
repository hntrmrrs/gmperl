{% if f.version %}
#if _GNU_MP_VERSION >= {{ f.version.major }}
#if _GNU_MP_VERSION_MINOR >= {{ f.version.minor }}
#if _GNU_MP_VERSION_PATCHLEVEL >= {{ f.version.patchlevel }}{% endif %}
GMPERL_NIF_PROTOTYPE(gmperl_{{ f.name }})
{
    ERL_NIF_TERM ret;
    gmperl_privdata_t *priv = enif_priv_data(env);
    {% for l in f.locals %}
    {{ l.ctype }} val{{ l.index }}
    {% ifequal l.type "string" %}[BUF_SZ]{% endifequal %}
    {% ifequal l.type "char_ptr" %} = NULL{% endifequal %}
    {% ifequal l.type "new_mpz_t" %} = (gmperl_mpz_t *)enif_alloc_resource(priv->gmperl_mpz_rt, sizeof(gmperl_mpz_t)){% endifequal %}
    {% ifequal l.type "new_mpq_t" %} = (gmperl_mpq_t *)enif_alloc_resource(priv->gmperl_mpq_rt, sizeof(gmperl_mpq_t)){% endifequal %}
    {% ifequal l.type "new_mpf_t" %} = (gmperl_mpf_t *)enif_alloc_resource(priv->gmperl_mpf_rt, sizeof(gmperl_mpf_t)){% endifequal %};

    {% ifequal l.type "new_mpz_t" %}val{{ l.index }}->init = 0;{% endifequal %}
    {% ifequal l.type "new_mpq_t" %}val{{ l.index }}->init = 0;{% endifequal %}
    {% ifequal l.type "new_mpf_t" %}val{{ l.index }}->init = 0;{% endifequal %}

    {% ifequal l.type "mpz_t" %}
    if (!enif_get_resource(env, argv[{{ l.in_index }}], priv->gmperl_mpz_rt, (void**)&val{{ l.index }})) {
        goto badarg;
    }
    {% endifequal %}

    {% ifequal l.type "mpq_t" %}
    if (!enif_get_resource(env, argv[{{ l.in_index }}], priv->gmperl_mpq_rt, (void**)&val{{ l.index }})) {
        goto badarg;
    }
    {% endifequal %}

    {% ifequal l.type "mpf_t" %}
    if (!enif_get_resource(env, argv[{{ l.in_index }}], priv->gmperl_mpf_rt, (void**)&val{{ l.index }})) {
        goto badarg;
    }
    {% endifequal %}

    {% ifequal l.type "ulong" %}
    if (!enif_get_ulong(env, argv[{{ l.in_index }}], &val{{ l.index }})) {
        goto badarg;
    }
    {% endifequal %}

    {% ifequal l.type "long" %}
    if (!enif_get_long(env, argv[{{ l.in_index }}], &val{{ l.index }})) {
        goto badarg;
    }
    {% endifequal %}

    {% ifequal l.type "int" %}
    if (!enif_get_int(env, argv[{{ l.in_index }}], &val{{ l.index }})) {
        goto badarg;
    }
    {% endifequal %}

    {% ifequal l.type "uint" %}
    if (!enif_get_uint(env, argv[{{ l.in_index }}], &val{{ l.index }})) {
        goto badarg;
    }
    {% endifequal %}

    {% ifequal l.type "double" %}
    if (!enif_get_double(env, argv[{{ l.in_index }}], &val{{ l.index }})) {
        goto badarg;
    }
    {% endifequal %}

    {% ifequal l.type "num_base" %}
    if (!enif_get_uint(env, argv[{{ l.in_index }}], &val{{ l.index }})
        || (val{{ l.index }} != 0 && (val{{ l.index }} < 2 || val{{ l.index }} > 62))) {
        goto badarg;
    }
    {% endifequal %}

    {% ifequal l.type "string" %}
    if (!enif_get_string(env, argv[{{ l.in_index }}], val{{ l.index }}, sizeof(val{{ l.index }}), ERL_NIF_LATIN1)) {
        goto badarg;
    }
    {% endifequal %}
    {% endfor %}

    {% if f.ccall.retval %}
    {{ f.ccall.cretval }} val0 =
    {% endif %}
    {{ f.name }}(
        {% if f.ccall.head %}{% if f.ccall.head.reference %}&{% endif %}val{{ f.ccall.head.index }}{% if f.ccall.head.pointer %}->{{ f.ccall.head.pointer.target }}{% endif %}{% endif %}
        {% if f.ccall.tail %}{% for t in f.ccall.tail %}, {% if t.reference %}&{% endif %}val{{ t.index }}{% if t.pointer %}->{{ t.pointer.target }}{% endif %}{% endfor %}{% endif %}
    );

    {% ifequal f.ccall.retval "assert_zero" %}
    if (0 != val0) { goto badarg; }
    {% endifequal %}

    {% ifequal f.ccall.head.type "new_mpz_t" %}val{{ f.ccall.head.index }}->init = 1;{% endifequal %}
    {% ifequal f.ccall.head.type "new_mpq_t" %}val{{ f.ccall.head.index }}->init = 1;{% endifequal %}
    {% ifequal f.ccall.head.type "new_mpf_t" %}val{{ f.ccall.head.index }}->init = 1;{% endifequal %}
    {% if f.ccall.tail %}{% for t in f.ccall.tail %}
    {% ifequal t.type "new_mpz_t" %}val{{ t.index }}->init = 1;{% endifequal %}
    {% ifequal t.type "new_mpq_t" %}val{{ t.index }}->init = 1;{% endifequal %}
    {% ifequal t.type "new_mpf_t" %}val{{ t.index }}->init = 1;{% endifequal %}
    {% endfor %}{% endif %}

    {% ifequal f.return.type "ok" %}ret = enif_get_ok(env);{% endifequal %}
    {% ifequal f.return.type "long" %}ret = enif_make_long(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "int" %}ret = enif_make_int(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "uint" %}ret = enif_make_uint(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "long_out" %}ret = enif_make_long(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "ulong" %}ret = enif_make_ulong(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "ulong_out" %}ret = enif_make_ulong(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "int_out" %}ret = enif_make_int(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "uint_out" %}ret = enif_make_uint(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "double" %}ret = enif_make_double(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "double_out" %}ret = enif_make_double(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "string" %}ret = enif_make_string(env, val{{ f.return.index }}, ERL_NIF_LATIN1);{% endifequal %}
    {% ifequal f.return.type "mpz_t" %}ret = enif_make_resource(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "mpq_t" %}ret = enif_make_resource(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "mpf_t" %}ret = enif_make_resource(env, val{{ f.return.index }});{% endifequal %}
    {% ifequal f.return.type "boolean" %}ret = enif_get_boolean(env, val{{ f.return.index }});{% endifequal %}

    {% if f.return.tuple2 %}ret = enif_make_tuple2(env,
    {% ifequal f.return.tuple2.first.type "ok" %}enif_get_ok(env),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "long" %}enif_make_long(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "int" %}enif_make_int(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "uint" %}enif_make_uint(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "long_out" %}enif_make_long(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "ulong" %}enif_make_ulong(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "ulong_out" %}enif_make_ulong(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "int_out" %}enif_make_int(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "uint_out" %}enif_make_uint(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "double" %}enif_make_double(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "double_out" %}enif_make_double(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "string" %}enif_make_string(env, val{{ f.return.tuple2.first.index }}, ERL_NIF_LATIN1),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "mpz_t" %}enif_make_resource(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "mpq_t" %}enif_make_resource(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "mpf_t" %}enif_make_resource(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}
    {% ifequal f.return.tuple2.first.type "boolean" %}enif_get_boolean(env, val{{ f.return.tuple2.first.index }}),{% endifequal %}

    {% ifequal f.return.tuple2.second.type "ok" %}enif_get_ok(env){% endifequal %}
    {% ifequal f.return.tuple2.second.type "long" %}enif_make_long(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "int" %}enif_make_int(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "uint" %}enif_make_uint(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "long_out" %}enif_make_long(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "ulong" %}enif_make_ulong(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "ulong_out" %}enif_make_ulong(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "int_out" %}enif_make_int(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "uint_out" %}enif_make_uint(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "double" %}enif_make_double(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "double_out" %}enif_make_double(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "string" %}enif_make_string(env, val{{ f.return.tuple2.second.index }}, ERL_NIF_LATIN1){% endifequal %}
    {% ifequal f.return.tuple2.second.type "mpz_t" %}enif_make_resource(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "mpq_t" %}enif_make_resource(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "mpf_t" %}enif_make_resource(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    {% ifequal f.return.tuple2.second.type "boolean" %}enif_get_boolean(env, val{{ f.return.tuple2.second.index }}){% endifequal %}
    );{% endif %}

    {% ifequal f.ccall.retval "string" %}
    // Free string return values
    enif_free(val0);
    {% endifequal %}

    return ret;

    {% if f.needs_badarg %}
  badarg:
    {% if f.locals %}{% for l in f.locals %}
    {% ifequal l.type "new_mpz_t" %}if (NULL != val{{ l.index }}) enif_release_resource(val{{ l.index }});{% endifequal %}
    {% ifequal l.type "new_mpq_t" %}if (NULL != val{{ l.index }}) enif_release_resource(val{{ l.index }});{% endifequal %}
    {% ifequal l.type "new_mpf_t" %}if (NULL != val{{ l.index }}) enif_release_resource(val{{ l.index }});{% endifequal %}
    {% endfor %}{% endif %}
    return enif_make_badarg(env);
    {% endif %}
}
{% if f.version %}
#endif // _GNU_MP_VERSION >= {{ f.version.major }}
#endif // _GNU_MP_VERSION_MINOR >= {{ f.version.minor }}
#endif // _GNU_MP_VERSION_PATCHLEVEL >= {{ f.version.patchlevel }}
{% endif %}
