#include <atomic>

#include "test.hpp"
#include "cppa/cppa.hpp"

using namespace cppa;

namespace { std::atomic<size_t> s_error_count{0}; }

size_t cppa_error_count() {
    return s_error_count;
}

void cppa_inc_error_count() {
    ++s_error_count;
}

std::string cppa_fill4(int value) {
    std::string result = std::to_string(value);
    while (result.size() < 4) result.insert(result.begin(), '0');
    return std::move(result);
}

const char* cppa_strip_path(const char* fname) {
    auto res = fname;
    auto i = fname;
    for (char c = *i; c != '\0'; c = *++i) {
        if (c == '/') {
            res = i + 1;
        }
    }
    return res;
}

void cppa_unexpected_message(const char* fname, size_t line_num) {
    CPPA_FORMAT_STR(std::cerr, fname, line_num,
                    "ERROR: unexpected message: "
                    << to_string(self->last_dequeued()));
}

void cppa_unexpected_timeout(const char* fname, size_t line_num) {
    CPPA_FORMAT_STR(std::cerr, fname, line_num, "ERROR: unexpected timeout");
}

std::vector<std::string> split(const std::string& str, char delim) {
    std::vector<std::string> result;
    std::stringstream strs{str};
    std::string tmp;
    while (std::getline(strs, tmp, delim)) result.push_back(tmp);
    return result;
}
