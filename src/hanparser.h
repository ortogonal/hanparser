#pragma once

#include <chrono>
#include <functional>
#include <string>
#include <vector>

struct Power {
    uint32_t l1;
    uint32_t l2;
    uint32_t l3;
};

struct HanData
{
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    uint32_t totalInPower;
    uint32_t totalOutPower;
    Power inPower;
    Power outPower;
};


class HanParser
{
public:
    using HanDataCallback = std::function<void(const HanData &)>;

    HanParser();

    void appendLine(const std::string &data);

    void onData(HanDataCallback &&cb);

private:
    void parseLines(const std::vector<std::string> &lines) const;
    std::chrono::time_point<std::chrono::system_clock> parseTimestamp(const std::string &value) const;
    uint32_t parsePower(const std::string &value) const;

    std::vector<HanDataCallback> m_callbacks;
    std::vector<std::string> m_lines;

    bool foundStart = false;
};
