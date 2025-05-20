#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
#include "image/color.h"
#include "image/image.h"

#include <filters/filter.h>
#include <filters/registry.h>

namespace image_processor::filters {

class GrayScale : public Filter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            return std::make_unique<GrayScale>();
        }
    };

public:
    GrayScale() {
    }

    image::Image Apply(const image::Image& image) override {
        const float red_figure = 0.299;
        const float green_figure = 0.587;
        const float blue_fugure = 0.114;
        image::Image new_image = image;
        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < image.GetWidth(); ++col) {
                new_image(row, col).r =
                    static_cast<float>(image(row, col).r * red_figure + image(row, col).g * green_figure +
                                       image(row, col).b * blue_fugure);
                new_image(row, col).g =
                    static_cast<float>(image(row, col).r * red_figure + image(row, col).g * green_figure +
                                       image(row, col).b * blue_fugure);
                new_image(row, col).b =
                    static_cast<float>(image(row, col).r * red_figure + image(row, col).g * green_figure +
                                       image(row, col).b * blue_fugure);
            }
        }
        return new_image;
    }
};

REGISTER_FILTER("gs", GrayScale::Factory)

}  // namespace image_processor::filters
