#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>


char UintToHexChar(uint8_t u) {
    switch (u) {
        case 0b00000000: return '0';
        case 0b00000001: return '1';
        case 0b00000010: return '2';
        case 0b00000011: return '3';
        case 0b00000100: return '4';
        case 0b00000101: return '5';
        case 0b00000110: return '6';
        case 0b00000111: return '7';
        case 0b00001000: return '8';
        case 0b00001001: return '9';
        case 0b00001010: return 'a';
        case 0b00001011: return 'b';
        case 0b00001100: return 'c';
        case 0b00001101: return 'd';
        case 0b00001110: return 'e';
        case 0b00001111: return 'f';
        default: std::exit(1);
    }
}

std::string XOREncrypt(const std::string& s, const std::string& key) {
    size_t s_length = s.length();
    size_t key_length = key.length();

    if (key_length <= 0) {
        std::exit(1);
    }

    std::string res{};

    res.reserve(2 * s_length);

    for (size_t i = 0; i < s_length; i++) {
        uint8_t encrypted_character = static_cast<uint8_t>(s[i]) ^ static_cast<uint8_t>(key[i % key_length]);

        uint8_t high = encrypted_character >> 4;
        uint8_t low = encrypted_character & 0b00001111;

        res.push_back(UintToHexChar(high));
        res.push_back(UintToHexChar(low));
    }

    return res;
}

int main() {
    std::string s{"Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"};

    std::string key{"ICE"};

    std::cout << XOREncrypt(s, key) << std::endl;

    return 0;
}