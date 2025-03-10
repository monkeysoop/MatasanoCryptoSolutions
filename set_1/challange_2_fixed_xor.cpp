#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>


uint8_t HexCharToUint(char c) {
    switch (c) {
        case '0' : return 0b00000000;
        case '1' : return 0b00000001;
        case '2' : return 0b00000010;
        case '3' : return 0b00000011;
        case '4' : return 0b00000100;
        case '5' : return 0b00000101;
        case '6' : return 0b00000110;
        case '7' : return 0b00000111;
        case '8' : return 0b00001000;
        case '9' : return 0b00001001;
        case 'a' : return 0b00001010;
        case 'b' : return 0b00001011;
        case 'c' : return 0b00001100;
        case 'd' : return 0b00001101;
        case 'e' : return 0b00001110;
        case 'f' : return 0b00001111;
        default: std::exit(1);
    }
}

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

std::string FixedXOR(const std::string& hex_string_1, const std::string& hex_string_2) {
    size_t length_1 = hex_string_1.length();
    size_t length_2 = hex_string_2.length();

    if (length_1 != length_2) {
        std::exit(1);
    }

    std::string res{};

    res.reserve(length_1);

    for (size_t i = 0; i < length_1; i++) {
        uint8_t u_1 = HexCharToUint(hex_string_1[i]);
        uint8_t u_2 = HexCharToUint(hex_string_2[i]);

        res.push_back(UintToHexChar(u_1 ^ u_2));
    }

    return res;
}

int main() {
    std::string hex_string_1{"1c0111001f010100061a024b53535009181c"};
    std::string hex_string_2{"686974207468652062756c6c277320657965"};

    std::cout << FixedXOR(hex_string_1, hex_string_2) << std::endl;

    return 0;
}