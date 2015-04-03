import os
Import('*')

lib = "util"
# these modules will compiled in to library
lib_modules = """
              logger.cpp 
              record.cpp
              recordreader.cpp
              paramTemplate.cpp
              cmdParser.cpp
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
