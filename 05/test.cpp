#include "serializer.hpp"
#include "gtest/gtest.h"

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
        
    template <class Deserializer> 
    Error deserialize(Deserializer& deserializer)
    {
		return deserializer(a, b, c);
	}
};


TEST(TestSerializer, TestFromHomework){
Data x { 1, true, 2};

std::stringstream stream;

Serializer serializer(stream);
serializer.save(x);

Data y { 0, false, 0 };
Deserializer deserializer(stream);
const Error err = deserializer.load(y);

ASSERT_TRUE(err == Error::NoError);

ASSERT_TRUE(x.a == y.a);
ASSERT_TRUE(x.b == y.b);
ASSERT_TRUE(x.c == y.c);
}


int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}