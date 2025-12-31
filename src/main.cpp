#include <opencv2/opencv.hpp>
#include <iostream>
#include "hdr_merge.hpp"
#include "tonemap.hpp"

int main() {
    std::vector<std::string> filenames = {
        "e10.PNG",
        "e12.PNG",
        "e13.PNG",
        "e14.PNG",
        "e16.PNG"
    };

    std::vector<float> exposureTimes = {
        2.0f/1000.0f,
        8.0f/1000.0f,
        1.0f/60.0f,
        2.0f/60.0f,
        125.0f/1000.0f

    };

    std::vector<cv::Mat> images;
    for (const auto& file : filenames) {
        cv::Mat img = cv::imread(file, cv::IMREAD_UNCHANGED);
        if (img.empty()) {
            std::cerr << "Failed to load image: " << file << std::endl;
            return -1;
        }
        images.push_back(img);
    }

    cv::Mat hdr = mergeHDR(images, exposureTimes, WeightType::GAUSSIAN);
    cv::Mat ldr = reinhardToneMap(hdr);

    cv::imwrite("result_hdr.png", ldr);

    std::cout << "HDR processing complete." << std::endl;
    return 0;
}
