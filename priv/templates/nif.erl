{{ f.name }}({% if f.head_arg %}_{% endif %}{% if f.tail_args %}{% for t in f.tail_args %}, _{% endfor %}{% endif %}) -> ?ERR.
