# ===========================================================================
#                  SeqAn - The Library for Sequence Analysis
# ===========================================================================
# File: /src/CMakeLists.txt
#
# CMakeLists.txt file for bam_bench.
# ===========================================================================

cmake_minimum_required (VERSION 3.0.0)
project (bam_bench_app CXX)
message (STATUS "Configuring src/bam_bench_app")

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------

# Update the cmake flags required for SeqAn.

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# Search SeqAn and select dependencies.
find_package (OpenMP)
find_package (ZLIB)
find_package (BZip2)

#set (TBB_INCLUDE_DIR "/opt/local/include/tbb/")
#set (TBB_LIBRARY "/opt/local/lib/")

#find_package (TBB)
find_package (SeqAn REQUIRED)

# Warn if TBB wasn't find.
if (NOT TBB_FOUND)
    message (STATUS "   TBB not found")
else(NOT TBB_FOUND)
    message (STATUS "   Using TBB Version ${TBB_VERSION}")
    list (APPEND SEQAN_DEFINITIONS "${TBB_DEFINITIONS}")
    list (APPEND SEQAN_LIBRARIES "${TBB_LIBRARIES}")
    list (APPEND SEQAN_INCLUDE_DIRS "${TBB_INCLUDE_DIRS}")
endif (NOT TBB_FOUND)

# Warn if OpenMP was not found.
# if (NOT OPENMP_FOUND)
#   message (STATUS "  OpenMP 3.0 not found: building yara without multi-threading.")
# endif (NOT OPENMP_FOUND)

# Warn if Zlib was not found.
if (NOT ZLIB_FOUND)
  message (STATUS "  Zlib not found: building yara without gzipped input and BAM output.")
endif (NOT ZLIB_FOUND)

# Warn if BZip2 was not found.
if (NOT BZIP2_FOUND)
  message (STATUS "  BZip2 not found: building yara without bzipped input.")
endif (NOT BZIP2_FOUND)

# ----------------------------------------------------------------------------
# App-Level Configuration
# ----------------------------------------------------------------------------

set (SEQAN_APP_VERSION "0.0.1")

# ----------------------------------------------------------------------------
# Build Setup
# ----------------------------------------------------------------------------

# Add include directories.
include_directories (${SEQAN_INCLUDE_DIRS})

# Add definitions set by find_package (SeqAn).
add_definitions (${SEQAN_DEFINITIONS})

# Add definitions set by the build system.
add_definitions (-DSEQAN_REVISION="${SEQAN_REVISION}")
add_definitions (-DSEQAN_DATE="${SEQAN_DATE}")
add_definitions (-DSEQAN_APP_VERSION="${SEQAN_APP_VERSION}")

# Add CXX flags found by find_package (SeqAn).
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SEQAN_CXX_FLAGS}")

# Update the list of file names below if you add source files to your application.
add_executable(bam_bench bam_bench.cpp)

# Add dependencies found by find_package (SeqAn).
target_link_libraries (bam_bench ${SEQAN_LIBRARIES})

# ----------------------------------------------------------------------------
# Installation - requires SeqAn build system.
# ----------------------------------------------------------------------------

# Set variables for installing, depending on the selected build type.
# if (NOT SEQAN_PREFIX_SHARE_DOC)
#   seqan_setup_install_vars (align_bench)
# endif (NOT SEQAN_PREFIX_SHARE_DOC)

# # Install yara in ${PREFIX}/bin directory
# install (TARGETS align_bench
#          DESTINATION bin)

# # Install non-binary files for the package to "." for app builds and
# # ${PREFIX}/share/doc/yara for SeqAn release builds.
# install (FILES LICENSE README.rst
#          DESTINATION ${SEQAN_PREFIX_SHARE_DOC})
