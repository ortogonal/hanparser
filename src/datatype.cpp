#include "datatype.h"

DataType::DataType(const std::string &str)
{
    bool valid = true;

    auto typeStop = str.find("-");
    if (typeStop != std::string::npos) {
        auto type = str.substr(0, typeStop);
        m_type = (Type)std::stoi(type);
        typeStop++;
    } else {
        valid = false;
    }

    auto channelStop = str.find(":", typeStop);
    if (channelStop != std::string::npos) {
        auto channel = str.substr(typeStop, channelStop - typeStop);
        m_channel = std::stoi(channel);
        channelStop++;
    } else {
        valid = false;
    }

    auto propertyStop = str.find(".", channelStop);
    if (propertyStop != std::string::npos) {
        auto property = str.substr(channelStop, propertyStop - channelStop);
        m_property = (Property)std::stoi(property);
        propertyStop++;
    } else {
        valid = false;
    }

    auto measurmentStop = str.find(".", propertyStop);
    if (measurmentStop != std::string::npos) {
        auto measurement = str.substr(propertyStop, measurmentStop - propertyStop);
        m_measurementValue = (MeasurementValue)std::stoi(measurement);
    } else {
        valid = false;
    }

    m_valid = valid;
}

bool DataType::matched(const Type &type, const Property &property, const MeasurementValue &measurementValue) const
{
    return m_type == type /*&& m_property == property && m_measurementValue == measurementValue*/;
}

bool DataType::valid() const
{
    return m_valid;
}

DataType::Type DataType::type() const
{
    return m_type;
}

uint8_t DataType::channel() const
{
    return m_channel;
}

DataType::Property DataType::property() const
{
    return m_property;
}

DataType::MeasurementValue DataType::measurement() const
{
    return m_measurementValue;
}
