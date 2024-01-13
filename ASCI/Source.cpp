#include <iostream>
#include <opencv2/opencv.hpp>

void imageToAscii(const cv::Mat& image, std::ostream& output, int cols, int scale) {
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    int rows = gray.rows;
    int cols_in_char = 10;
    int rows_in_char = 10;

    for (int i = 0; i < rows; i += rows_in_char) {
        for (int j = 0; j < cols; j += cols_in_char) {
            cv::Mat roi = gray(cv::Range(i, std::min(i + rows_in_char, rows)),
                cv::Range(j, std::min(j + cols_in_char, cols)));

            int avg_intensity = static_cast<int>(cv::mean(roi)[0]);
           // @%#*+=-:.`//
            char ascii_char = "`.:-=+*#%@"[avg_intensity / 25];
            for (int k = 0; k < scale; ++k) {
                output << ascii_char;
            }
        }
        output << '\n';
    }
}

int main() {
    cv::Mat image = cv::imread("");// <-- enter yours file path//

    if (image.empty()) {
        std::cerr << "Error: Unable to load image." << std::endl;
        return -1;
    }

    int cols = image.cols;
    int scale = 2; 

    imageToAscii(image, std::cout, cols, scale);

    return 0;
}
