#include "hdr_merge.hpp"
#include <cmath>

static float computeWeight(float z, WeightType type) {
    //z /= 255.0f;

    switch (type) {
        case WeightType::UNIFORM:
            return 1.0f;

        case WeightType::TENT:
            return (z <= 0.5f) ? z : (1.0f - z);

        case WeightType::GAUSSIAN:
            return std::exp(-std::pow(z - 0.5f, 2) / (2.0f * 0.2f * 0.2f));

        case WeightType::PHOTON:
            return std::max(z, 1e-3f);

        default:
            return 1.0f;
    }
}

cv::Mat mergeHDR(
    const std::vector<cv::Mat>& images,
    const std::vector<float>& exposureTimes,
    WeightType weightType
) {
    CV_Assert(images.size() == exposureTimes.size());

    cv::Mat hdr = cv::Mat::zeros(images[0].size(), CV_32FC3);
    cv::Mat weightSum = cv::Mat::zeros(images[0].size(), CV_32FC3);

    for (size_t k = 0; k < images.size(); ++k) {
        cv::Mat img;
        double maxVal = (images[k].depth() == CV_16U) ? 65535.0 : 255.0;
        images[k].convertTo(img, CV_32FC3, 1.0 / maxVal);

        for (int y = 0; y < img.rows; ++y) {
            for (int x = 0; x < img.cols; ++x) {
                cv::Vec3f pixel = img.at<cv::Vec3f>(y, x);

                for (int c = 0; c < 3; ++c) {
                    float w = computeWeight(pixel[c], weightType);
                    hdr.at<cv::Vec3f>(y, x)[c] +=
                        w * pixel[c] / exposureTimes[k];
                    weightSum.at<cv::Vec3f>(y, x)[c] += w;
                }
            }
        }
    }

    hdr /= (weightSum + 1e-6f);
    return hdr;
}
