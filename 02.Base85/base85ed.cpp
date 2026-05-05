#include <cstddef>
#include <cstdint>
#include <vector>

#include "base85ed.h"

const uint8_t ALPHABET[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

static uint32_t base85_digit(uint8_t symbol)
{
    for (uint32_t i = 0; i < 85; ++i)
    {
        if (ALPHABET[i] == symbol)
        {
            return i;
        }
    }

    return 0;
}

std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> result;

    if (bytes.empty())
    {
        return result;
    }

    result.reserve((bytes.size() + 3) / 4 * 5);

    for (size_t i = 0; i < bytes.size(); i += 4)
    {
        const size_t remaining = bytes.size() - i;
        const size_t chunk_size = remaining < 4 ? remaining : 4;

        uint32_t value = 0;

        for (size_t j = 0; j < 4; ++j)
        {
            value <<= 8;

            if (j < chunk_size)
            {
                value |= bytes[i + j];
            }
        }

        uint8_t encoded[5];

        for (int j = 4; j >= 0; --j)
        {
            encoded[j] = ALPHABET[value % 85];
            value /= 85;
        }

        const size_t output_size = chunk_size + 1;

        for (size_t j = 0; j < output_size; ++j)
        {
            result.push_back(encoded[j]);
        }
    }

    return result;
}

std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    std::vector<uint8_t> result;

    if (b85str.empty())
    {
        return result;
    }

    result.reserve((b85str.size() + 4) / 5 * 4);

    for (size_t i = 0; i < b85str.size(); i += 5)
    {
        const size_t remaining = b85str.size() - i;
        const size_t chunk_size = remaining < 5 ? remaining : 5;

        uint32_t value = 0;

        for (size_t j = 0; j < 5; ++j)
        {
            uint8_t symbol = ALPHABET[84];

            if (j < chunk_size)
            {
                symbol = b85str[i + j];
            }

            value = value * 85 + base85_digit(symbol);
        }

        uint8_t decoded[4];

        decoded[0] = static_cast<uint8_t>((value >> 24) & 0xFF);
        decoded[1] = static_cast<uint8_t>((value >> 16) & 0xFF);
        decoded[2] = static_cast<uint8_t>((value >> 8) & 0xFF);
        decoded[3] = static_cast<uint8_t>(value & 0xFF);

        const size_t output_size = chunk_size - 1;

        for (size_t j = 0; j < output_size; ++j)
        {
            result.push_back(decoded[j]);
        }
    }

    return result;
}