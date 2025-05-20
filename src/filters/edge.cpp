#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
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
const float FILTER_MATRIX_POS_22 = 4.0f;
const float FILTER_MATRIX_POS_23 = -1.0f;
const float FILTER_MATRIX_POS_31 = 0.0f;
const float FILTER_MATRIX_POS_32 = -1.0f;
const float FILTER_MATRIX_POS_33 = 0.0f;
const std::vector<float> FILTER_VECTOR{FILTER_MATRIX_POS_11, FILTER_MATRIX_POS_12, FILTER_MATRIX_POS_13,
                                       FILTER_MATRIX_POS_21, FILTER_MATRIX_POS_22, FILTER_MATRIX_POS_23,
                                       FILTER_MATRIX_POS_31, FILTER_MATRIX_POS_32, FILTER_MATRIX_POS_33};
const utils::Matrix<float> FILTER_MATRIX1{3, 3, FILTER_VECTOR};

}  // namespace

namespace {

float Cast(std::string_view s) {
    std::stringstream sstream(s.data());
    float result = 0;
    sstream >> result;
    return result;
}

}  // namespace

class Edge : public MatrixFilter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (parameters.size() != 1) {
                throw std::invalid_argument("");
            }

            const float threshold = Cast(parameters[0]);
            return std::make_unique<Edge>(threshold);
        }
    };

public:
    explicit Edge(float threshold) : threshold_(threshold) {
    }

    void ChangePixel(image::Image& image, const float threshold) {
        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < image.GetWidth(); ++col) {
                if (image(row, col).r > threshold) {
                    image(row, col).r = 1;
                    image(row, col).g = 1;
                    image(row, col).b = 1;
                } else {
                    image(row, col).r = 0;
                    image(row, col).g = 0;
                    image(row, col).b = 0;
                }
            }
        }
    }

    void GreyScale(image::Image& image) {
        const float red_figure = 0.299;
        const float green_figure = 0.587;
        const float blue_fugure = 0.114;
        image::Image new_image = image;
        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < image.GetWidth(); ++col) {
                image(row, col).r =
                    static_cast<float>(image(row, col).r * red_figure + image(row, col).g * green_figure +
                                       image(row, col).b * blue_fugure);
                image(row, col).g =
                    static_cast<float>(image(row, col).r * red_figure + image(row, col).g * green_figure +
                                       image(row, col).b * blue_fugure);
                image(row, col).b =
                    static_cast<float>(image(row, col).r * red_figure + image(row, col).g * green_figure +
                                       image(row, col).b * blue_fugure);
            }
        }
    }

    image::Image Apply(const image::Image& image) override {
        SetMatrix(FILTER_MATRIX1);
        image::Image new_image = image;
        GreyScale(new_image);
        new_image = MatrixApply(new_image);
        ChangePixel(new_image, threshold_);
        return new_image;
    }

    ~Edge() override = default;

private:
    [[maybe_unused]] float threshold_;
};

REGISTER_FILTER("edge", Edge::Factory)

}  // namespace image_processor::filters
