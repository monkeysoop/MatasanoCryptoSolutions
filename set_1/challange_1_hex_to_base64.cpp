#include <iostream>
#include <string>
#include <array>
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

std::string HexToBase64(const std::string& hex_string) {
    std::array<char, 64> lookup_table{{ 
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3', 
        '4', '5', '6', '7', '8', '9', '+', '/'
    }};

    std::string res{};

    size_t base_64_size = static_cast<size_t>((2 * hex_string.length() + 2) / 3) + (3 - (2 * hex_string.length() % 3)) % 3;
    res.reserve(base_64_size);

    uint8_t base_64_index = 0;
    unsigned offset = 0;

    for (char c : hex_string) {
        uint8_t hex_value = HexCharToUint(c);
        switch (offset) {
            case 0: 
                base_64_index = hex_value << 2;                
                break;
            case 2: 
                base_64_index |= hex_value;                
                res.push_back(lookup_table[base_64_index & 0b00111111]);
                break;
            case 4: 
                base_64_index |= hex_value >> 2;                
                res.push_back(lookup_table[base_64_index & 0b00111111]);
                base_64_index = (hex_value & 0b00000011) << 4;
                break;
        }

        offset = (offset + 4) % 6;
    }

    switch (offset) {
        case 2: 
            res.push_back(lookup_table[base_64_index & 0b00111111]);
            res.push_back('=');
            res.push_back('=');
            break;
            case 4: 
            res.push_back(lookup_table[base_64_index & 0b00111111]);
            res.push_back('=');
            break;
    }


    return res;
}

int main() {
    std::string hex_string{"49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"};
    
    std::string hex_string_1{"4d616e"};
    std::string hex_string_2{"4d61"};
    std::string hex_string_3{"4d"};



    std::cout << HexToBase64(hex_string) << std::endl;
    std::cout << HexToBase64(hex_string_1) << std::endl;
    std::cout << HexToBase64(hex_string_2) << std::endl;
    std::cout << HexToBase64(hex_string_3) << std::endl;

    return 0;
}