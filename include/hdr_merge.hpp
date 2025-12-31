#ifndef HDR_MERGE_HPP
#define HDR_MERGE_HPP

#include <opencv2/opencv.hpp>
#include <vector>

enum class WeightType {
    UNIFORM,
    TENT,
    GAUSSIAN,
    PHOTON
};

cv::Mat mergeHDR(
    const std::vector<cv::Mat>& images,
    const std::vector<float>& exposureTimes,
    WeightType weightType
);

#endif
