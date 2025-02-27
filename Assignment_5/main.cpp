#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "pixel.h"

// Function to parse the input file and populate the pixel_list
void read_pixels(const std::string& filename, std::vector<Pixel>& pixel_list) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        std::cerr << "Please ensure the file is in the same directory as the executable." << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        Pixel pixel;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);

        pixel.x = std::stoi(line.substr(0, pos1));
        pixel.y = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        pixel.r = std::stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
        pixel.g = std::stof(line.substr(pos3 + 1, pos4 - pos3 - 1));
        pixel.b = std::stof(line.substr(pos4 + 1));

        pixel_list.push_back(pixel);
    }
    file.close();
}

// Function to calculate the average of r, g, and b values
void average_colors(const std::vector<Pixel>& pixel_list) {
    float r_sum = 0.0f, g_sum = 0.0f, b_sum = 0.0f;
    for (const auto& pixel : pixel_list) {
        r_sum += pixel.r;
        g_sum += pixel.g;
        b_sum += pixel.b;
    }
    size_t total_pixels = pixel_list.size();
    std::cout << "Average R: " << r_sum / total_pixels << std::endl;
    std::cout << "Average G: " << g_sum / total_pixels << std::endl;
    std::cout << "Average B: " << b_sum / total_pixels << std::endl;
}

// Function to flip the pixels vertically
void flip_vertically(std::vector<Pixel>& pixel_list) {
    int max_y = 255; // Assuming y ranges from 0 to 255
    for (auto& pixel : pixel_list) {
        pixel.y = max_y - pixel.y;
    }
}

// Function to write the pixel list to a file
void write_pixels(const std::string& filename, const std::vector<Pixel>& pixel_list) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }

    for (const auto& pixel : pixel_list) {
        file << pixel.x << "," << pixel.y << "," << pixel.r << "," << pixel.g << "," << pixel.b << std::endl;
    }
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::vector<Pixel> pixel_list;
    std::string input_file = argv[1];

    // Step 3: Read pixels from the input file
    read_pixels(input_file, pixel_list);

    // Step 4: Calculate and print average colors
    average_colors(pixel_list);

    // Step 4: Flip the pixels vertically
    flip_vertically(pixel_list);

    // Step 5: Write the flipped pixels to a new file
    write_pixels("flipped.dat", pixel_list);

    std::cout << "Flipped pixels saved to flipped.dat" << std::endl;

    return 0;
}