#include "filters/matrix_filter.h"
#include "image/image.h"

void image_processor::filters::MatrixFilter::MatrixFilterApplication(const image::Image &image,
                                                                     image::Image &answer_image, size_t row,
                                                                     size_t col) {
    const int64_t lower_row = 0;
    const int64_t upper_row = static_cast<int64_t>(image.GetHeight() - 1);
    const int64_t lower_col = 0;
    const int64_t upper_col = static_cast<int64_t>(image.GetWidth() - 1);
    for (int64_t i = 0; i < 3; ++i) {
        for (int64_t j = 0; j < 3; ++j) {
            const size_t modified_row_cord =
                static_cast<size_t>(std::clamp(static_cast<int64_t>(row) + 1 - i, lower_row, upper_row));
            const size_t modified_col_cord =
                static_cast<size_t>(std::clamp(static_cast<int64_t>(col) + 1 - j, lower_col, upper_col));
            answer_image(row, col) =
                answer_image(row, col) + image(modified_row_cord, modified_col_cord) * (matrix_(i, j));
        }
    }
}

image_processor::image::Image image_processor::filters::MatrixFilter::MatrixApply(
    const image_processor::image::Image &image) {
    utils::Matrix<image::Color> answer_image = image;
    for (size_t row = 0; row < answer_image.GetHeight(); ++row) {
        for (size_t col = 0; col < answer_image.GetWidth(); ++col) {
            answer_image(row, col) = answer_image(row, col) - answer_image(row, col);
            MatrixFilterApplication(image, answer_image, row, col);
            answer_image(row, col).r = std::fmin(1.0f, std::fmax(0.0f, answer_image(row, col).r));
            answer_image(row, col).g = std::fmin(1.0f, std::fmax(0.0f, answer_image(row, col).g));
            answer_image(row, col).b = std::fmin(1.0f, std::fmax(0.0f, answer_image(row, col).b));
        }
    }
    return answer_image;
}
