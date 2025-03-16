#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <bitset>
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

std::string XORDecrypt(const std::string& hex_string, uint8_t key) {
    size_t length = hex_string.length();

    std::string res{};

    size_t half_length = static_cast<size_t>(length / 2);
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

std::string XORDecrypt(const std::string& hex_string, const std::vector<uint8_t>& keys) {
    size_t length = hex_string.length();

    std::string res{};

    size_t half_length = static_cast<size_t>(length / 2);
    res.reserve(half_length);

    for (size_t i = 0; i < half_length; i++) {
        uint8_t high = HexCharToUint(hex_string[2 * i]);
        uint8_t low = HexCharToUint(hex_string[2 * i + 1]);

        uint8_t encoded = (high << 4) | low;

        uint8_t decoded = encoded ^ keys[i % keys.size()];

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

bool PrintableCharacter(char c) {
    uint8_t u = static_cast<uint8_t>(c);
    return (u >= 32 && u < 127) || u == 8 || u == 9 || u == 10 || u == 0 || u == 13;
}

bool Character(char c) {
    uint8_t u = static_cast<uint8_t>(c);
    return (u >= 65 && u < 91) || (u >= 96 && u < 123) || (u >= 48 && u < 58) || c == '.' || c == ',';
}

bool CommonCharacter(char c) {
    return (
        c == ' ' || c == ',' ||
        c == 'e' || c == 'E' || 
        c == 't' || c == 'T' || 
        c == 'a' || c == 'A' || 
        c == 'o' || c == 'O' || 
        c == 'i' || c == 'I' || 
        c == 'n' || c == 'N' ||
        c == 's' || c == 'S' ||
        c == 'h' || c == 'H' ||
        c == 'r' || c == 'R' ||
        c == 'd' || c == 'D' ||
        c == 'l' || c == 'L' ||
        c == 'u' || c == 'U'
    );
}

bool VeryCommonCharacter(char c) {
    return (
        c == ' ' || 
        c == 'e' || c == 'E' || 
        c == 't' || c == 'T' || 
        c == 'a' || c == 'A' || 
        c == 'o' || c == 'O' || 
        c == 'i' || c == 'I' || 
        c == 'n' || c == 'N'
    );
}

std::string Base64ToHex(const std::string& base64_string) {
    const std::map<char, uint8_t> lookup_table{{ 
        {'A', 0b00000000}, {'B', 0b00000001}, {'C', 0b00000010}, {'D', 0b00000011}, {'E', 0b00000100}, {'F', 0b00000101}, {'G', 0b00000110}, {'H', 0b00000111}, 
        {'I', 0b00001000}, {'J', 0b00001001}, {'K', 0b00001010}, {'L', 0b00001011}, {'M', 0b00001100}, {'N', 0b00001101}, {'O', 0b00001110}, {'P', 0b00001111},
        {'Q', 0b00010000}, {'R', 0b00010001}, {'S', 0b00010010}, {'T', 0b00010011}, {'U', 0b00010100}, {'V', 0b00010101}, {'W', 0b00010110}, {'X', 0b00010111}, 
        {'Y', 0b00011000}, {'Z', 0b00011001}, {'a', 0b00011010}, {'b', 0b00011011}, {'c', 0b00011100}, {'d', 0b00011101}, {'e', 0b00011110}, {'f', 0b00011111},
        {'g', 0b00100000}, {'h', 0b00100001}, {'i', 0b00100010}, {'j', 0b00100011}, {'k', 0b00100100}, {'l', 0b00100101}, {'m', 0b00100110}, {'n', 0b00100111}, 
        {'o', 0b00101000}, {'p', 0b00101001}, {'q', 0b00101010}, {'r', 0b00101011}, {'s', 0b00101100}, {'t', 0b00101101}, {'u', 0b00101110}, {'v', 0b00101111},
        {'w', 0b00110000}, {'x', 0b00110001}, {'y', 0b00110010}, {'z', 0b00110011}, {'0', 0b00110100}, {'1', 0b00110101}, {'2', 0b00110110}, {'3', 0b00110111}, 
        {'4', 0b00111000}, {'5', 0b00111001}, {'6', 0b00111010}, {'7', 0b00111011}, {'8', 0b00111100}, {'9', 0b00111101}, {'+', 0b00111110}, {'/', 0b00111111}
    }};

    std::string res{};
    res.reserve((3 * base64_string.length() + 1) / 2);

    bool flip_flop = true;;
    uint8_t remainder = 0;

    for (char c : base64_string) {
        if (c == '=') {
            if (flip_flop && base64_string.back() == '=') {
                res.pop_back();
            }

            break;
        }

        std::map<char, uint8_t>::const_iterator iter = lookup_table.find(c);
        if (iter == lookup_table.end()) {
            std::exit(1);
        }

        uint8_t u = iter->second;

        if (flip_flop) {
            res.push_back(UintToHexChar((u & 0b00111100) >> 2));
            remainder = u & 0b00000011;
        } else {
            res.push_back(UintToHexChar(((u & 0b00110000) >> 4) | (remainder << 2)));
            res.push_back(UintToHexChar(u & 0b00001111));
        }

        flip_flop = !flip_flop;
    }

    return res;
}

size_t HammingDistance(const std::string& s_1, const std::string& s_2) {
    size_t length_1 = s_1.length();
    size_t length_2 = s_2.length();

    if (length_1 != length_2) {
        std::exit(1);
    }

    size_t sum = 0;

    for (size_t i = 0; i < length_1; i++) {
        uint8_t u = static_cast<uint8_t>(s_1[i]) ^ static_cast<uint8_t>(s_2[i]);

        sum += std::bitset<8>{u}.count();
    }

    return sum;
}

void DisplayCombination(const std::vector<std::vector<std::string>>& decrypted_bolcks, const std::vector<size_t>& is) {
    size_t size1 = decrypted_bolcks.size();
    size_t size2 = is.size();

    if (size1 != size2 || size1 == 0) {
        std::cout << "size 1: " << size1 << " size 2: " << size2 << std::endl; 
        std::exit(1);
    }
    
    std::vector<std::string> blocks{};
    blocks.resize(size1);
    
    for (size_t i = 0; i < size1; i++) {
        size_t decrypt_index = is[i];
        
        if (decrypt_index >= decrypted_bolcks[i].size()) {
            std::exit(1);
        }
        
        blocks[i] = decrypted_bolcks[i][decrypt_index];
    }

    for (size_t i = 0; i < blocks[0].length(); i++) {
        for (size_t j = 0; j < size1; j++) {
            if (i < blocks[j].length()) {
                char c = blocks[j][i];
                if (PrintableCharacter(c)) {
                    std::cout << c;
                }
            }
        }
    }
    
    std::cout << std::endl;

}

int main() {
    std::string s{Base64ToHex("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")};

    std::cout << "len: " << s.size() << std::endl;

    std::cout << Base64ToHex("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t") << std::endl;
    std::cout << Base64ToHex("TWFu") << std::endl;
    std::cout << Base64ToHex("TWE=") << std::endl;
    std::cout << Base64ToHex("TQ==") << std::endl;

    size_t length_s = s.length();

    std::cout << HammingDistance("this is a test", "wokka wokka!!!") << std::endl;

    size_t probable_key_size = 0;
    float best_average_hamming_distance = static_cast<float>(8 * length_s + 1);

    for (size_t key_size = 2; key_size <= 40; key_size++) {
    
        size_t sum_of_distances = 0;

        size_t first_substring_start = 0;
        while ((first_substring_start + 4 * key_size) < length_s) {
            size_t d = HammingDistance(s.substr(first_substring_start, 2 * key_size), s.substr(first_substring_start + 2 * key_size, 2 * key_size));
            sum_of_distances += d;
            first_substring_start += key_size;
        }

        float average_hamming_distance = static_cast<float>(sum_of_distances) / static_cast<float>(first_substring_start);


        if (first_substring_start != 0 && average_hamming_distance < best_average_hamming_distance) {
            probable_key_size = key_size;
            best_average_hamming_distance = average_hamming_distance;
        } 
    }

    std::cout << "probable key size: " << probable_key_size << std::endl;
    std::cout << "average hamming distance: " << best_average_hamming_distance << std::endl;
    
    std::vector<std::vector<std::string>> decrypted_bolcks{};
    decrypted_bolcks.resize(probable_key_size);

    for (size_t i = 0; i < probable_key_size; i++) {
        std::string ith_blocks{};
        ith_blocks.reserve(static_cast<size_t>((length_s + probable_key_size - 1) / probable_key_size));
            
        for (size_t j = 2 * i; (j + 1) < length_s; j += (2 * probable_key_size)) {
            ith_blocks.push_back(s[j]);
            ith_blocks.push_back(s[j + 1]);
        }

        std::vector<std::string> decrypts{};
            
        for (unsigned key = 0; key <= 256; key++) {
            std::string decrypted = XORDecrypt(ith_blocks, static_cast<uint8_t>(key));
                
            std::vector<std::pair<char, unsigned>> character_frequencies = CharacterFrequenciesOrderedDescending(decrypted);
                
            if (character_frequencies.size() > 5) {
                char c_1 = character_frequencies[0].first;
                char c_2 = character_frequencies[1].first;
                char c_3 = character_frequencies[2].first;
                char c_4 = character_frequencies[3].first;
                char c_5 = character_frequencies[4].first;
                char c_6 = character_frequencies[5].first;
                    
                bool c_1_char = Character(c_1);
                bool c_2_char = Character(c_2);
                bool c_3_char = Character(c_3);
                bool c_4_char = Character(c_4);
                bool c_5_char = Character(c_5);
                bool c_6_char = Character(c_6);

                bool c_1_common = CommonCharacter(c_1);
                bool c_2_common = CommonCharacter(c_2);
                bool c_3_common = CommonCharacter(c_3);
                bool c_4_common = CommonCharacter(c_4);
                bool c_5_common = CommonCharacter(c_5);
                bool c_6_common = CommonCharacter(c_6);

                bool c_1_very = VeryCommonCharacter(c_1);
                bool c_2_very = VeryCommonCharacter(c_2);
                bool c_3_very = VeryCommonCharacter(c_3);
                bool c_4_very = VeryCommonCharacter(c_4);
                bool c_5_very = VeryCommonCharacter(c_5);
                bool c_6_very = VeryCommonCharacter(c_6);

                unsigned chars = c_1_char + c_2_char + c_3_char + c_4_char + c_5_char + c_6_char;
                unsigned commons = c_1_common + c_2_common + c_3_common + c_4_common + c_5_common + c_6_common;
                unsigned very_commons = c_1_very + c_2_very + c_3_very + c_4_very + c_5_very + c_6_very;
                    
                if (commons >= 4 && very_commons >= 2 && chars >= 4) {
                    decrypts.push_back(decrypted);
                }
            }
        }
    
        decrypted_bolcks[i] = std::move(decrypts);
    }

    std::vector<size_t> is{};
    is.resize(probable_key_size);
    std::fill(is.begin(), is.end(), 0);

        
    size_t combinations = 1;
        
    for (size_t i = 0; i < probable_key_size; i++) {
        combinations *= decrypted_bolcks[i].size();
    }

    bool good = (combinations != 0);

    good = false; // I already got the solution and this one tends to get stuck in very big loops

    while (good) {
        
        DisplayCombination(decrypted_bolcks, is);

        size_t i;
                
        for (i = probable_key_size - 1; i > 0 && (is[i] == (decrypted_bolcks[i].size() - 1)); i--) {
            is[i] = 0;
        }

        if (i == 0 && is[i] == (decrypted_bolcks[i].size() - 1)) {
            std::cout << "done" << std::endl;
            good = false;
        } else {
            is[i]++;
        }
    }



    std::vector<uint8_t> keys{84, 101, 114, 109, 105, 110, 97, 116, 111, 114, 32, 88, 58, 32, 66, 114, 105, 110, 103, 32, 116, 104, 101, 32, 110, 111, 105, 115, 101};

    std::cout << XORDecrypt(s, keys) << std::endl;

    return 0;
}