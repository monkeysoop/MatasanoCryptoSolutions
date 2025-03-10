#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <map>
#include <vector>
#include <iterator>
#include <utility>
#include <algorithm>
	

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

std::string XORDecrypt(const std::string& hex_string, uint8_t key) {
    size_t length = hex_string.length();
    if ((length % 2) != 0) {
        std::exit(1);
    }


    std::string res{};

    size_t half_length = static_cast<size_t>(hex_string.length() / 2);
    res.reserve(half_length);

    for (size_t i = 0; i < half_length; i++) {
        uint8_t high = HexCharToUint(hex_string[2 * i]);
        uint8_t low = HexCharToUint(hex_string[2 * i + 1]);

        uint8_t encoded = (high << 4) | low;

        uint8_t decoded = encoded ^ key;

        res.push_back(static_cast<char>(decoded));
    }

    return res;
}

std::vector<std::pair<char, unsigned>> CharacterFrequenciesOrderedDescending(const std::string& s) {
    std::map<char, unsigned> character_frequencies{};

    for (char c : s) {
        character_frequencies[c] += 1;
    }

    std::vector<std::pair<char, unsigned>> res{std::make_move_iterator(character_frequencies.begin()), std::make_move_iterator(character_frequencies.end())};
 
    std::sort(
        res.begin(), 
        res.end(), 
        [](const std::pair<char, unsigned>& a, const std::pair<char, unsigned>& b) { 
            return a.second > b.second;
        }
    );

    return res;
}

bool CommonCharacter(char c) {
    return (c == ' ' || c == 'e' || c == 'E' || c == 't' || c == 'T' || c == 'a' || c == 'A' || c == 'o' || c == 'O' || c == 'i' || c == 'I' || c == 'n' || c == 'N');
}

int main() {
    std::string hex_string{"1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"};

    for (uint8_t key = 0; key < 0xFF; key++) {
        std::string decrypted = XORDecrypt(hex_string, key);

        std::vector<std::pair<char, unsigned>> character_frequencies = CharacterFrequenciesOrderedDescending(decrypted);

        if (character_frequencies.size() > 2) {
            char c_1 = character_frequencies[0].first;
            char c_2 = character_frequencies[1].first;
            
            bool c_1_common = CommonCharacter(c_1);
            bool c_2_common = CommonCharacter(c_2);
            
            if (c_1_common && c_2_common) {
                std::cout << "key: " << static_cast<unsigned>(key) << " decrypted: " << decrypted << std::endl;
            }
        }
    } 

    return 0;
}