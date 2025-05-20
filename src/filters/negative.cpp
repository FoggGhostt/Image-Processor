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

class Negative : public Filter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            return std::make_unique<Negative>();
        }
    };

public:
    Negative() {
    }

    image::Image Apply(const image::Image& image) override {
        image::Image new_image = image;
        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < image.GetWidth(); ++col) {
                new_image(row, col).r = 1 - new_image(row, col).r;
                new_image(row, col).g = 1 - new_image(row, col).g;
                new_image(row, col).b = 1 - new_image(row, col).b;
            }
        }
        return new_image;
    }
};

REGISTER_FILTER("neg", Negative::Factory)

}  // namespace image_processor::filters
