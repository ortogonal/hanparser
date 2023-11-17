#include <gtest/gtest.h>

#include <datatype.h>

namespace test {

TEST(tst_datatype, init)
{
    DataType d1("0-0:1.0.0");
    EXPECT_TRUE(d1.valid());
    EXPECT_TRUE(d1.matched(DataType::Type::None,
                           DataType::Property::TimeStamp,
                           DataType::MeasurementValue::Momentary));
    EXPECT_EQ(d1.channel(), 0);

    DataType d2("1-0:1.7.0");
    EXPECT_TRUE(d2.valid());
    EXPECT_TRUE(d2.matched(DataType::Type::Electricity,
                           DataType::Property::ThreePhaseInPower,
                           DataType::MeasurementValue::Momentary));
    EXPECT_EQ(d2.channel(), 0);

    DataType d3("1-0:21.7.0");
    EXPECT_TRUE(d3.valid());
    EXPECT_TRUE(d3.matched(DataType::Type::Electricity,
                           DataType::Property::Phase1InPower,
                           DataType::MeasurementValue::Momentary));
    EXPECT_EQ(d3.channel(), 0);

    DataType d4("1-0:41.7.0");
    EXPECT_TRUE(d4.valid());
    EXPECT_TRUE(d4.matched(DataType::Type::Electricity,
                           DataType::Property::Phase2InPower,
                           DataType::MeasurementValue::Momentary));
    EXPECT_EQ(d4.channel(), 0);

    DataType d5("1-0:61.7.0");
    EXPECT_TRUE(d5.valid());
    EXPECT_TRUE(d5.matched(DataType::Type::Electricity,
                           DataType::Property::Phase3InPower,
                           DataType::MeasurementValue::Momentary));
    EXPECT_EQ(d5.channel(), 0);
}

} // namespace test
