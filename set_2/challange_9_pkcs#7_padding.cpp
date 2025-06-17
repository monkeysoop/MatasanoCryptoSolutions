#include <string>
#include <iostream>

std::string PKCS7Padding(const std::string& s, size_t padded_size) {
    if (s.size() >= padded_size) {
        return s.substr(0, padded_size);
    }

    std::string res{};
    res.reserve(padded_size);

    res = s;
    res.append((padded_size - s.size()), static_cast<decltype(res)::value_type>(padded_size - s.size()));

    return res;
}

int main() {
    std::string s{"YELLOW SUBMARINE"};

    std::cout << PKCS7Padding(s, 0) << std::endl;
    std::cout << PKCS7Padding(s, 1) << std::endl;
    std::cout << PKCS7Padding(s, 2) << std::endl;
    std::cout << PKCS7Padding(s, 20) << std::endl;
    std::cout << PKCS7Padding(s, 80) << std::endl;
    std::cout << PKCS7Padding(s, 28) << std::endl;

    return 0;
}