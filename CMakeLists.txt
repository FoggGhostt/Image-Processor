include_directories(src)

add_executable(
    image_processor

    bin/main.cpp

    src/args/args.cpp

    src/filters/crop.cpp
    src/filters/filter.cpp
    src/filters/registry.cpp
    src/filters/grayscale.cpp
    src/filters/negative.cpp
    src/filters/sharpening.cpp
    src/filters/matrix_filter.cpp
    src/filters/edge.cpp

    src/image/color.cpp
    src/image/image.cpp

    src/image_format/bmp.cpp
    src/image_format/format.cpp

    src/io/reader.cpp
    src/io/writer.cpp

    src/utils/matrix.cpp
)