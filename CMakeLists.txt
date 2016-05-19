# ======================================================================
#  arisana main build file
#
#  cd .../path/to/build/directory
#  source .../path/to/arisana/ups/setup_for_development
#  buildtool
# ======================================================================


# use cmake 2.8 or later
cmake_minimum_required (VERSION 2.8)

# cetbuildtools contains our cmake modules
SET ( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} )
IF (NOT CETBUILDTOOLS_VERSION)
    MESSAGE (FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules")
ENDIF()

set(CMAKE_MODULE_PATH 
        $ENV{ART_DIR}/Modules
        $ENV{CETBUILDTOOLS_DIR}/Modules
        ${CMAKE_MODULE_PATH})


include(CetCMakeEnv)
cet_cmake_env()

cet_set_compiler_flags(DIAGS VIGILANT
 WERROR
 NO_UNDEFINED
 EXTRA_FLAGS -pedantic
 )

cet_report_compiler_flags()

# these are minimum required versions, not the actual product versions
find_ups_product( cetbuildtools v4_02_01 )
find_ups_product( darksidecore v1_00_00 )
find_ups_product( art v1_10_00 )
find_ups_product( fhiclcpp v2_16_00 )
find_ups_product( pqxx v4_0_1 )
find_ups_product( messagefacility v1_10_00 )
find_ups_product( cpp0x v1_03_00 )
find_ups_product( cetlib v1_03_00 )
find_ups_root( v5_34_00 )
find_ups_boost( v1_50_0 filesystem
                        program_options
                        unit_test_framework
 )

# Needed if using old art with new cetbuildtools / CMake.
check_ups_version(art "$ENV{ART_VERSION}" v1_11_00 PRODUCT_OLDER_VAR have_old_art)
if (have_old_art)
  cmake_policy(SET CMP0046 OLD)
endif()
unset(have_old_art)

# have to make sure cmake doesn't select the system libraries
# define libsigc
find_library( PQXX          NAMES pqxx          PATHS $ENV{PQXX_LIB} )

# macros for art_dictionary and simple_plugin
include(ArtDictionary)
include(ArtMake)
include(BuildPlugins)

# source
add_subdirectory (arisana)

# testing
#add_subdirectory(test)

# ups - table and config files
add_subdirectory(ups)

#add_subdirectory(fcl)
#add_subdirectory(aux)

# packaging utility
include(UseCPack)
