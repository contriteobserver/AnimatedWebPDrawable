# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        webp-lib

        # Sets the library as a shared library.
        STATIC

        # Provides a relative path to your source file(s).
        libwebp/src/dec/alpha_dec.c
        libwebp/src/dec/buffer_dec.c
        libwebp/src/dec/buffer_dec.c
        libwebp/src/dec/frame_dec.c
        libwebp/src/dec/idec_dec.c
        libwebp/src/dec/io_dec.c
        libwebp/src/dec/quant_dec.c
        libwebp/src/dec/tree_dec.c
        libwebp/src/dec/vp8_dec.c
        libwebp/src/dec/vp8l_dec.c
        libwebp/src/dec/webp_dec.c

        libwebp/src/demux/demux.c
        libwebp/src/demux/anim_decode.c

        libwebp/src/dsp/alpha_processing.c
        libwebp/src/dsp/alpha_processing_mips_dsp_r2.c
        libwebp/src/dsp/alpha_processing_neon.c
        libwebp/src/dsp/alpha_processing_sse2.c
        libwebp/src/dsp/alpha_processing_sse41.c
        libwebp/src/dsp/cost.c
        libwebp/src/dsp/cost_mips32.c
        libwebp/src/dsp/cost_mips_dsp_r2.c
        libwebp/src/dsp/cost_neon.c
        libwebp/src/dsp/cost_sse2.c
        libwebp/src/dsp/cpu.c
        libwebp/src/dsp/dec.c
        libwebp/src/dsp/dec_clip_tables.c
        libwebp/src/dsp/dec_mips32.c
        libwebp/src/dsp/dec_mips_dsp_r2.c
        libwebp/src/dsp/dec_msa.c
        libwebp/src/dsp/dec_neon.c
        libwebp/src/dsp/dec_sse2.c
        libwebp/src/dsp/dec_sse41.c
        libwebp/src/dsp/enc.c
        libwebp/src/dsp/enc_mips32.c
        libwebp/src/dsp/enc_mips_dsp_r2.c
        libwebp/src/dsp/enc_msa.c
        libwebp/src/dsp/enc_neon.c
        libwebp/src/dsp/enc_sse2.c
        libwebp/src/dsp/enc_sse41.c
        libwebp/src/dsp/filters.c
        libwebp/src/dsp/filters_mips_dsp_r2.c
        libwebp/src/dsp/filters_msa.c
        libwebp/src/dsp/filters_neon.c
        libwebp/src/dsp/filters_sse2.c
        libwebp/src/dsp/lossless.c
        libwebp/src/dsp/lossless_enc.c
        libwebp/src/dsp/lossless_enc_mips32.c
        libwebp/src/dsp/lossless_enc_mips_dsp_r2.c
        libwebp/src/dsp/lossless_enc_msa.c
        libwebp/src/dsp/lossless_enc_neon.c
        libwebp/src/dsp/lossless_enc_sse2.c
        libwebp/src/dsp/lossless_enc_sse41.c
        libwebp/src/dsp/lossless_mips_dsp_r2.c
        libwebp/src/dsp/lossless_msa.c
        libwebp/src/dsp/lossless_neon.c
        libwebp/src/dsp/lossless_sse2.c
        libwebp/src/dsp/rescaler.c
        libwebp/src/dsp/rescaler_mips32.c
        libwebp/src/dsp/rescaler_mips_dsp_r2.c
        libwebp/src/dsp/rescaler_msa.c
        libwebp/src/dsp/rescaler_neon.c
        libwebp/src/dsp/rescaler_sse2.c
        libwebp/src/dsp/ssim.c
        libwebp/src/dsp/ssim_sse2.c
        libwebp/src/dsp/upsampling.c
        libwebp/src/dsp/upsampling_mips_dsp_r2.c
        libwebp/src/dsp/upsampling_msa.c
        libwebp/src/dsp/upsampling_neon.c
        libwebp/src/dsp/upsampling_sse2.c
        libwebp/src/dsp/upsampling_sse41.c
        libwebp/src/dsp/yuv.c
        libwebp/src/dsp/yuv_mips32.c
        libwebp/src/dsp/yuv_mips_dsp_r2.c
        libwebp/src/dsp/yuv_neon.c
        libwebp/src/dsp/yuv_sse2.c
        libwebp/src/dsp/yuv_sse41.c

        libwebp/src/utils/bit_reader_utils.c
        libwebp/src/utils/bit_writer_utils.c
        libwebp/src/utils/color_cache_utils.c
        libwebp/src/utils/filters_utils.c
        libwebp/src/utils/huffman_encode_utils.c
        libwebp/src/utils/huffman_utils.c
        libwebp/src/utils/quant_levels_dec_utils.c
        libwebp/src/utils/quant_levels_utils.c
        libwebp/src/utils/random_utils.c
        libwebp/src/utils/rescaler_utils.c
        libwebp/src/utils/thread_utils.c
        libwebp/src/utils/utils.c

        )

include_directories(
        libwebp/src/
)

add_library( # Sets the name of the library.
        webp-jni-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        webpJNI.c
        )

include_directories(
        libwebp/
)


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        webp-jni-lib
        -ljnigraphics

        webp-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})
