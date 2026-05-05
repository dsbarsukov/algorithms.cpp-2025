#include <gtest/gtest.h>

#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string.h>

#include "base85ed.h"

const std::vector<std::pair<const char *, const char * >> short_cases =
{
    { "",     ""     },
    { "F#",   "1"    },
    { "F){",  "12"   },
    { "F)}j", "123"  },
    { "F)}kW","1234" }
};

static std::vector<uint8_t> cstr2v(const char *s)
{
    return std::vector<uint8_t>(
               s,
               s + std::string(s).size()
           );
}

// Тесты encode
TEST(Base85ShortsEncode, TrivialShortEncodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

// Тесты decode
TEST(Base85ShortsDecode, TrivialShortDecodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

TEST(Base85Encode, SeveralBlocks)
{
    EXPECT_EQ(base85::encode(cstr2v("12345678")), cstr2v("F)}kWH8wXm"));
    EXPECT_EQ(base85::encode(cstr2v("Hello")), cstr2v("NM&qnZv"));
}

TEST(Base85Decode, SeveralBlocks)
{
    EXPECT_EQ(base85::decode(cstr2v("F)}kWH8wXm")), cstr2v("12345678"));
    EXPECT_EQ(base85::decode(cstr2v("NM&qnZv")), cstr2v("Hello"));
}

TEST(Base85Roundtrip, TextData)
{
    const std::vector<uint8_t> data = cstr2v("Hello, Base85! This is a longer test string.");

    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85Roundtrip, DifferentLengths)
{
    for (size_t size = 0; size <= 32; ++size)
    {
        std::vector<uint8_t> data;

        for (size_t i = 0; i < size; ++i)
        {
            data.push_back(static_cast<uint8_t>(i));
        }

        EXPECT_EQ(base85::decode(base85::encode(data)), data);
    }
}

TEST(Base85Roundtrip, BinaryData)
{
    const std::vector<uint8_t> data = {0x00, 0x01, 0x02, 0x03, 0x7F, 0x80, 0xFE, 0xFF, 0x10, 0x20, 0x30, 0x40};

    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}
