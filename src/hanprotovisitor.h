#pragma once

#include <hanprotoBaseVisitor.h>

#include "datatype.h"


class HanProtoVisitor : public hp::hanprotoBaseVisitor
{
public:
    HanProtoVisitor();

    antlrcpp::Any visitProgram(hp::hanprotoParser::ProgramContext *context) override;
    antlrcpp::Any visitIdentity(hp::hanprotoParser::IdentityContext *context) override;
    antlrcpp::Any visitDataline(hp::hanprotoParser::DatalineContext *context) override;
    antlrcpp::Any visitData(hp::hanprotoParser::DataContext *context) override;
    antlrcpp::Any visitTime(hp::hanprotoParser::TimeContext *context) override;
    antlrcpp::Any visitValue(hp::hanprotoParser::ValueContext *context) override;
    antlrcpp::Any visitCrc(hp::hanprotoParser::CrcContext *context) override;

private:
    std::string id;
    DataType m_pendingDataType;
    HanData m_pendingData;


};

