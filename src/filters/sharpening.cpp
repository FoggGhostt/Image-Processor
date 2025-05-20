#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
#include "image/color.h"
#include "image/image.h"
#include "filters/matrix_filter.h"

#include <filters/filter.h>
#include <filters/registry.h>

namespace image_processor::filters {

namespace {

const float FILTER_MATRIX_POS_11 = 0.0f;
const float FILTER_MATRIX_POS_12 = -1.0f;
const float FILTER_MATRIX_POS_13 = 0.0f;
const float FILTER_MATRIX_POS_21 = -1.0f;
const float FILTER_MATRIX_POS_22 = 5.0f;
const float FILTER_MATRIX_POS_23 = -1.0f;
const float FILTER_MATRIX_POS_31 = 0.0f;
const float FILTER_MATRIX_POS_32 = -1.0f;
const float FILTER_MATRIX_POS_33 = 0.0f;
const std::vector<float> FILTER_VECTOR{FILTER_MATRIX_POS_11, FILTER_MATRIX_POS_12, FILTER_MATRIX_POS_13,
                                       FILTER_MATRIX_POS_21, FILTER_MATRIX_POS_22, FILTER_MATRIX_POS_23,
                                       FILTER_MATRIX_POS_31, FILTER_MATRIX_POS_32, FILTER_MATRIX_POS_33};
const utils::Matrix<float> FILTER_MATRIX{3, 3, FILTER_VECTOR};

}  // namespace

class Sharpening : public MatrixFilter {

public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            return std::make_unique<Sharpening>();
        }
    };

public:
    Sharpening() {
    }

    image::Image Apply(const image::Image& image) override {
        SetMatrix(FILTER_MATRIX);
        return MatrixApply(image);
    }

    ~Sharpening() override = default;
};

REGISTER_FILTER("sharp", Sharpening::Factory)

}  // namespace image_processor::filters
