{% if f.version %}#if _GNU_MP_VERSION >= {{ f.version.major }}
#if _GNU_MP_VERSION_MINOR >= {{ f.version.minor }}
#if _GNU_MP_VERSION_PATCHLEVEL >= {{ f.version.patchlevel }}
{% endif %}{"{{ f.name }}", {{ f.arity }}, gmperl_{{ f.name }}},{% if f.version %}
#endif // _GNU_MP_VERSION >= {{ f.version.major }}
#endif // _GNU_MP_VERSION_MINOR >= {{ f.version.minor }}
#endif // _GNU_MP_VERSION_PATCHLEVEL >= {{ f.version.patchlevel }}{% endif %}
