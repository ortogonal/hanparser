#include "hanparser.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "datatype.h"

HanParser::HanParser() {}

void HanParser::appendLine(const std::string &line)
{
    if (foundStart) {
        m_lines.push_back(line);
    }

    if (!line.empty()) {
        if (line[0] == '/') {
            foundStart = true;
        } else if (line[0] == '!') {
            parseLines(m_lines);
            foundStart = false;
            m_lines.clear();
        }
    }
}

void HanParser::onData(HanDataCallback &&cb)
{
    m_callbacks.push_back(std::move(cb));
}

void HanParser::parseLines(const std::vector<std::string> &lines) const
{
    std::cout << "Start parsing" << std::endl;

    HanData data;

    for (const auto &line : lines) {
        auto splitPos = line.find('(');
        if (splitPos != std::string::npos) {
            auto type = line.substr(0, splitPos);
            DataType dt(type);

            auto value = line.substr(splitPos + 1);

            switch (dt.type()) {
            case DataType::Type::None:
                if (dt.property() == DataType::Property::TimeStamp) {
                    data.timestamp = parseTimestamp(value);
                }
                break;
            case DataType::Type::Electricity:
                if (dt.measurement() == DataType::MeasurementValue::Momentary) {
                    switch (dt.property()) {
                    case DataType::Property::ThreePhaseInPower:
                        data.totalInPower = parsePower(value);
                        break;
                    case DataType::Property::ThreePhaseOutPower:
                        data.totalOutPower = parsePower(value);
                        break;
                    case DataType::Property::Phase1InPower:
                        data.inPower.l1 = parsePower(value);
                        break;
                    case DataType::Property::Phase2InPower:
                        data.inPower.l2 = parsePower(value);
                        break;
                    case DataType::Property::Phase3InPower:
                        data.inPower.l3 = parsePower(value);
                        break;
                    case DataType::Property::Phase1OutPower:
                        data.outPower.l1 = parsePower(value);
                        break;
                    case DataType::Property::Phase2OutPower:
                        data.outPower.l2 = parsePower(value);
                        break;
                    case DataType::Property::Phase3OutPower:
                        data.outPower.l3 = parsePower(value);
                        break;
                    }
                }
            }
        }
    }

    std::cout << "Data " << data.timestamp.time_since_epoch().count()/1000000000 << std::endl;
    std::cout << "  T : " << data.totalInPower << " (" << data.totalOutPower
              << " diff: " << data.totalInPower - data.totalOutPower << ")" << std::endl;
    std::cout << "  L1: " << data.inPower.l1 << " (" << data.outPower.l1
              << " diff: " << data.inPower.l1 - data.outPower.l1 << ")" << std::endl;
    std::cout << "  L2: " << data.inPower.l2 << " (" << data.outPower.l2
              << " diff: " << data.inPower.l2 - data.outPower.l2 << ")" << std::endl;
    std::cout << "  L3: " << data.inPower.l3 << " (" << data.outPower.l3
              << " diff: " << data.inPower.l3 - data.outPower.l3 << ")" << std::endl;
}

std::chrono::time_point<std::chrono::system_clock> HanParser::parseTimestamp(
    const std::string &value) const
{
    std::tm tm = {};
    auto v = value.substr(0,12);
    for (int i = 0; i<6; i++) {
        v.insert(i*3+2, " ");
    }
    std::stringstream ss(v);
    ss >> std::get_time(&tm, "%y %m %d %H %M %S");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

uint32_t HanParser::parsePower(const std::string &value) const
{
    auto stopPos = value.find('*');
    if (stopPos != std::string::npos) {
        auto v = value.substr(0, stopPos);
        return std::stof(v) * 1000;
    } else {
        return 0;
    }
}
