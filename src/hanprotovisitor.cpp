#include "hanprotovisitor.h"

#include <stdio.h>


HanProtoVisitor::HanProtoVisitor()
{

}

antlrcpp::Any HanProtoVisitor::visitProgram(hp::hanprotoParser::ProgramContext *context)
{
    context->identity()->accept(this);
    for (const auto &dataLine : context->dataline()) {
        dataLine->accept(this);
    }
    std::cout << "Data" << std::endl;
    std::cout << "  T : " << m_pendingData.totalPower << std::endl;
    std::cout << "  L1: " << m_pendingData.power.l1 << std::endl;
    std::cout << "  L2: " << m_pendingData.power.l2 << std::endl;
    std::cout << "  L3: " << m_pendingData.power.l3 << std::endl;
    context->crc()->accept(this);
    return true;
}

antlrcpp::Any HanProtoVisitor::visitIdentity(hp::hanprotoParser::IdentityContext *context)
{
    std::cout << "ID " << context->HEX()->toString() << " " << context->NUMBER()->toString() << std::endl;
    return true;
}

antlrcpp::Any HanProtoVisitor::visitDataline(hp::hanprotoParser::DatalineContext *context)
{
    m_pendingDataType = DataType(context->TYPE()->getText());
    context->data()->accept(this);

    return true;
}

antlrcpp::Any HanProtoVisitor::visitData(hp::hanprotoParser::DataContext *context)
{
    if (context->time() != nullptr)
        context->time()->accept(this);
    else if (context->value() != nullptr)
        context->value()->accept(this);

    return true;
}

antlrcpp::Any HanProtoVisitor::visitTime(hp::hanprotoParser::TimeContext *context)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return true;
}

antlrcpp::Any HanProtoVisitor::visitValue(hp::hanprotoParser::ValueContext *context)
{
    auto value = std::stof(context->FLOAT()->getText());

    switch (m_pendingDataType.property()) {
    case DataType::Property::ThreePhaseInPower:
        m_pendingData.totalPower = value * 1000;
        break;
    case DataType::Property::Phase1InPower:
        m_pendingData.power.l1 = value * 1000;
        break;
    case DataType::Property::Phase2InPower:
        m_pendingData.power.l2 = value * 1000;
        break;
    case DataType::Property::Phase3InPower:
        m_pendingData.power.l3 = value * 1000;
        break;
    }

    return true;
}

antlrcpp::Any HanProtoVisitor::visitCrc(hp::hanprotoParser::CrcContext *context)
{
    std::cout << __PRETTY_FUNCTION__ << " " << context->HEX()->toString() << std::endl;
    return true;
}
