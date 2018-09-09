# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp )


add_library( native-logger
             SHARED
             src/main/cpp/logger.h
             src/main/cpp/logger.cpp)

add_library( native-transfer
             SHARED
             src/main/cpp/native_transfer.h
             src/main/cpp/native_transfer.cpp)

add_library( native-operate
             SHARED
             src/main/cpp/native_operate.h
             src/main/cpp/native_operate.cpp)

add_library( native-threads
             SHARED
             src/main/cpp/native_threads.h
             src/main/cpp/native_threads.cpp)

add_library( native-register
             SHARED
             src/main/cpp/native_register.h
             src/main/cpp/native_register.cpp)


add_library( native-costtime
             SHARED
             src/main/cpp/native_costtime.h
             src/main/cpp/native_costtime.cpp)

add_library( native-media
             SHARED
             src/main/cpp/native_media.h
             src/main/cpp/native_media.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )

target_link_libraries( native-logger
                       ${log-lib} )

target_link_libraries( native-transfer
                       native-logger )

target_link_libraries( native-operate
                       native-logger )

target_link_libraries( native-threads
                       native-logger )

target_link_libraries( native-register
                       native-logger )

target_link_libraries( native-costtime
                       native-logger )

target_link_libraries( native-media
                       native-logger )