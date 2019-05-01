
#include <rtc/canvas.hpp>

#include <fstream>

void rtc::write_bmp_to_file(const char* filename, const rtc::bitmap_t& bitmap)
{
    std::ofstream output(filename, std::ios::binary);

    if (output) {
        output.write(reinterpret_cast<const char*>(&bitmap.file_header),
                     sizeof(bitmap.file_header));
        output.write(reinterpret_cast<const char*>(&bitmap.header),
                     sizeof(bitmap.header));
        output.write(reinterpret_cast<const char*>(bitmap.data.data()),
                     bitmap.data.size());
    }
    // else handle an error condition here
}
