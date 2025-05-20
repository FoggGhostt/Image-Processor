#include <cstddef>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
#include <algorithm>
#include "image/color.h"
#include "image/image.h"
#include "utils/matrix.h"

#include <filters/filter.h>
#include <filters/registry.h>

namespace image_processor::filters {

class MatrixFilter : public Filter {
public:
    MatrixFilter() {
    }

    void SetMatrix(utils::Matrix<float> matrix) {
        matrix_ = matrix;
    }

    void MatrixFilterApplication(const image::Image& image, image::Image& answer_image, size_t row, size_t col);

    image::Image MatrixApply(const image::Image& image);

    ~MatrixFilter() override = default;

private:
    utils::Matrix<float> matrix_;
};

}  // namespace image_processor::filters
