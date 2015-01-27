import os
Import('*')

bin_list = []

lib = "util"
# these modules will compiled in to library
lib_modules = """
              logger.cpp 
              """.split()

extra_include_dir = [
]

############################### for library ###########################
#######################################################################
# clone the environment from global env and make some modification of it
myenv    = env.Clone(CPPPATH = extra_include_dir)

# compile to object files
lib_objs = myenv.StaticObject(lib_modules)

# compile library
lib_ar   = myenv.StaticLibrary(target = lib, source = lib_objs)

# install
myenv.Install("#" + dirs['lib'], lib_ar)

############################### for binary ############################
#######################################################################
# compile each binary
for bin in bin_list:
  bin_obj = myenv.StaticObject(bin[1])
  bin_target = myenv.Program(target = bin[0], source = bin_obj + lib_ar)
  myenv.Install("#" + dirs['bin'], bin_target)
