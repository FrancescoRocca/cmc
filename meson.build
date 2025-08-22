project('cmc', 'c')

inc_dir = include_directories('include')

subdir('src')

lib_jansson = dependency('jansson')
deps = [lib_jansson]

executable('cmc', sources, include_directories : inc_dir, dependencies : deps)
