#include "tonemap.hpp"
#include <cmath>

cv::Mat reinhardToneMap(
    const cv::Mat& hdr,
    float key,
    float burn
) {
    cv::Mat luminance;
    cv::cvtColor(hdr, luminance, cv::COLOR_BGR2GRAY);

    cv::Mat logLum;
    cv::log(luminance + 1e-6f, logLum);

    float logAvgLum = std::exp(cv::mean(logLum)[0]);

    cv::Mat scaled = (key / logAvgLum) * hdr;

    double maxVal;
    cv::minMaxLoc(scaled, nullptr, &maxVal);
    float white = burn * static_cast<float>(maxVal);

    cv::Mat tonemapped = scaled.mul(1.0f + scaled / (white * white));
    tonemapped /= (1.0f + scaled);

    cv::Mat ldr;
    tonemapped.convertTo(ldr, CV_8UC3, 255.0);

    return ldr;
}
