rapidcheck    = dependency('rapidcheck')
gtest         = dependency('gtest')
dependencies  = [cycles_dep, gtest, rapidcheck]

frequency = executable('test-frequency', 'test-frequency.cpp', dependencies: dependencies)
ratio     = executable(    'test-ratio',     'test-ratio.cpp', dependencies: dependencies)
cycle     = executable(    'test-cycle',     'test-cycle.cpp', dependencies: dependencies)

test('test-frequency', frequency)
test(    'test-ratio',     ratio)
test(    'test-cycle',     cycle)
