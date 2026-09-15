project('cmc', 'c')

inc_dir = include_directories('include')

sources = []
headers = []

subdir('src')
subdir('include')

yyjson_dep = dependency('yyjson')
deps = [yyjson_dep]

executable('cmc', sources, include_directories: inc_dir, dependencies: deps)
