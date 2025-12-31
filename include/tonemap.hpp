#ifndef TONEMAP_HPP
#define TONEMAP_HPP

#include <opencv2/opencv.hpp>

cv::Mat reinhardToneMap(
    const cv::Mat& hdr,
    float key = 0.15f,
    float burn = 0.95f
);

#endif
