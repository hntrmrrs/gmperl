-spec {{ f.name }}({% if f.head_arg %}{{ f.head_arg.type }}{% endif %}{% if f.tail_args %}{% for t in f.tail_args %}, {{ t.type }}{% endfor %}{% endif %}) -> {{ f.ret_type }}.
