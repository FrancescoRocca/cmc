project('cmc', 'c', version: '0.1.0')

inc_dir = include_directories('include')

sources = []
headers = []

subdir('src')
subdir('include')

yyjson_dep = dependency('yyjson')
toml_dep = dependency('libtomlc17')
deps = [yyjson_dep, toml_dep]

executable('cmc', sources, include_directories: inc_dir, dependencies: deps)
