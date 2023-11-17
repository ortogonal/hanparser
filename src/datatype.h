#pragma once

#include <string>

class DataType
{
public:
    enum class Type : uint8_t {
        None = 0,
        Electricity = 1,
    };

    enum class Property : uint8_t {
        TimeStamp = 1,
        ThreePhaseInPower = 1,
        ThreePhaseOutPower = 2,
        Phase1InPower = 21,
        Phase1OutPower = 22,
        Phase2InPower = 41,
        Phase2OutPower = 42,
        Phase3InPower = 61,
        Phase3OutPower = 62,
    };

    enum class MeasurementValue : uint8_t {
        None = 0,
        Momentary = 7,
        Cumulative = 8,
    };

    DataType() = default;
    DataType(const std::string &str);

    bool matched(const Type &type, const Property &property, const MeasurementValue &measurementValue) const;
    bool valid() const;
    Type type() const;
    uint8_t channel() const;
    Property property() const;
    MeasurementValue measurement() const;

private:
    bool m_valid = false;

    uint8_t m_channel;
    Type m_type;
    Property m_property;
    MeasurementValue m_measurementValue;
};

