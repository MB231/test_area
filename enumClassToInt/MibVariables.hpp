#pragma once

#include "SnmpTypes.hpp"
#include <map>

namespace OID {
enum class Name {
    Unknown,  // Should be kept as first element.
    sysUpTime,
    snmpTrapOid,
    f3SwRevision,
    reportPhoneNumber,
    rfcomSnmpTraphostAddr,
    gpsTimestamp,
    gpsLatitude,
    gpsLongitude,
    activeFreqProfId,
    freqProfId,
    getReportType,
    wfProfileName,
    wfRegStatus,
    wfCellId,
    wfSbcIndex,
    wfStatusReportNotif,
    rssiValue,
    rssiCpichSir,
    rssiStatus,
    rssiReportNotif,
    txPowerValue,
    txPowerStatus,
    txPowerReportNotif,
    groupBler,
    groupBlerStatus,
    svc1Bler,
    svc1Session,
    svc1BlerStatus,
    svc2Bler,
    svc2Session,
    svc2BlerStatus,
    blerReportNotif,
    f3TemperatureInfo,
    f3PaTemp,
    f3DigTemp,
    f3DigTemp2,
    redNetIpv4Qbr,
    redNetIpv4Mbr,
    redNetIpv4Traffic,
    voiceQualPref,
    redPtnPrecedence,
    redPtnNetwork,
    redPtnSession,
    redPtnTrigger,
    redPtnRespSession,
    redPtnRespReason,
    redPtnRespNotif,
    redActivatedSession,
    redActivatedNotif,
    redActivatedMbr,
    redActivatedQbr,
    redDeactSession,
    redServiceEvent,
    redServiceNotif,
    redServiceStatus,
    redServiceSession,
    redIndicationNotif,
    redStatusInd,
    redReleasedNotif,
    redReleasedSession,
    redRsrcMbr,
    redResrcAllocNotif,
    redRscrcSession,
    ptpPrecedence,
    ptpIoPort,
    ptpPhoneNumber,
    ptpSession,
    ptpRespSession,
    ptpRespReason,
    ptpRespNotif,
    ptpTrigger,
    groupJoinId,
    groupUnjoinCmd,
    goCfg,
    goOper,
    redNetIpv4CtAddrType,
    groupKeySetSet,
    blackStatusInd,
    blkIndicationNotif,
    remConnSession,
    remConnNotif
};

#define LIST_OF_MIB_DATA \
    MIBDef(.1.3.6.1.2.1.1.3.0,                       sysUptime,             SnmpTypes::OidDataType::TIMETICKS, u_int32_t,   OID::Name::sysUpTime) \
    MIBDef(.1.3.6.1.6.3.1.1.4.1.0,                   snmpTrapOid,           SnmpTypes::OidDataType::OID,       std::string, OID::Name::snmpTrapOid) \
    MIBDef(.1.3.6.1.4.1.28095.1.6.1.2.2.1.1.5.0,     f3SwRevision,          SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::f3SwRevision) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.3.2.0,     redPtnPrecedence,      SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redPtnPrecedence) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.3.1.0,     redPtnNetwork,         SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redPtnNetwork) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.3.3.0,     redPtnSession,         SnmpTypes::OidDataType::UNSIGNED,  uint32_t,    OID::Name::redPtnSession) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.3.4.0,     redPtnTrigger,         SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redPtnTrigger) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.5.3.0,     ptpPrecedence,         SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::ptpPrecedence) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.5.2.0,     ptpIoPort,             SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::ptpIoPort) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.5.1.0,     ptpPhoneNumber,        SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::ptpPhoneNumber) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.5.4.0,     ptpSession,            SnmpTypes::OidDataType::UNSIGNED,  uint32_t,    OID::Name::ptpSession) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.5.5.0,     ptpTrigger,            SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::ptpTrigger) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.4.1.1.0,     groupJoinId,           SnmpTypes::OidDataType::UNSIGNED,  uint32_t,    OID::Name::groupJoinId) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.3.2.4.1.2.0, redNetIpv4Qbr,         SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redNetIpv4Qbr) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.3.2.4.1.1.0, redNetIpv4Mbr,         SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redNetIpv4Mbr) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.3.2.4.1.1.0, redNetIpv4Traffic,     SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redNetIpv4Traffic) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.9.3.2.3.0,   redActivatedSession,   SnmpTypes::OidDataType::UNSIGNED,  uint32_t,    OID::Name::redActivatedSession) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.9.3.1.1.0,   redDeactSession,       SnmpTypes::OidDataType::UNSIGNED,  uint32_t,    OID::Name::redDeactSession) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.11.12.1.0,   redServiceEvent,       SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redServiceEvent) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.11.1.1.0,    blackStatusInd,        SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::blackStatusInd) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.11.1.2.0,    blkIndicationNotif,    SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::blkIndicationNotif) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.1.0,       getReportType,         SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::getReportType) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.7.7.9.0,     reportPhoneNumber,     SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::reportPhoneNumber) \
    MIBDef(.1.3.6.1.4.1.290.3.5.3.4.2.1.1.2.0,       rfcomSnmpTraphostAddr, SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::rfcomSnmpTraphostAddr) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.3.1.16.0,          gpsTimestamp,          SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::gpsTimestamp) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.3.1.4.0,           gpsLatitude,           SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::gpsLatitude) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.3.1.5.0,           gpsLongitude,          SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::gpsLongitude) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.7.3.5.1.0,   activeFreqProfId,      SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::activeFreqProfId) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.7.11.1.0,    freqProfId,            SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::freqProfId) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.5.1.0,     wfProfileName,         SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::wfProfileName) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.5.2.0,     wfRegStatus,           SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::wfRegStatus) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.5.3.0,     wfCellId,              SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::wfCellId) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.5.4.0,     wfSbcIndex,            SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::wfSbcIndex) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.5.5.0,     wfStatusReportNotif,   SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::wfStatusReportNotif) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.3.1.0,     rssiValue,             SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::rssiValue) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.3.2.0,     rssiCpichSir,          SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::rssiCpichSir) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.3.3.0,     rssiStatus,            SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::rssiStatus) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.3.4.0,     rssiReportNotif,       SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::rssiReportNotif) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.4.1.0,     txPowerValue,          SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::txPowerValue) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.4.2.0,     txPowerStatus,         SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::txPowerStatus) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.4.3.0,     txPowerReportNotif,    SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::txPowerReportNotif) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.2.1.0,     groupBler,             SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::groupBler) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.2.2.0,     groupBlerStatus,       SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::groupBlerStatus) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.2.3.0,     svc1Bler,              SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::svc1Bler) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.2.4.0,     svc1Session,           SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::svc1Session) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.2.5.0,     svc1BlerStatus,        SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::svc1BlerStatus) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.2.6.0,     svc2Bler,              SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::svc2Bler) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.2.7.0,     svc2Session,           SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::svc2Session) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.2.8.0,     svc2BlerStatus,        SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::svc2BlerStatus) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.8.2.9.0,     blerReportNotif,       SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::blerReportNotif) \
    MIBDef(.1.3.6.1.4.1.28095.1.6.1.6.0,             f3TemperatureInfo,     SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::f3TemperatureInfo) \
    MIBDef(.1.3.6.1.4.1.28095.1.6.1.6.1.0,           f3PaTemp,              SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::f3PaTemp) \
    MIBDef(.1.3.6.1.4.1.28095.1.6.1.6.2.0,           f3DigTemp,             SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::f3DigTemp) \
    MIBDef(.1.3.6.1.4.1.28095.1.6.1.6.3.0,           f3DigTemp2,            SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::f3DigTemp2) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.3.2.8.2.0,   voiceQualPref,         SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::voiceQualPref) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.5.6.1.0,   ptpRespSession,        SnmpTypes::OidDataType::UNSIGNED,  uint32_t,    OID::Name::ptpRespSession) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.5.6.2.0,   ptpRespReason,         SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::ptpRespReason) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.5.6.3.0,   ptpRespNotif,          SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::ptpRespNotif) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.4.2.1.0,     groupUnjoinCmd,        SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::groupUnjoinCmd) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.10.1.1.0,    goCfg,                 SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::goCfg) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.10.1.3.0,    goOper,                SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::goOper) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.3.2.4.1.4.0, redNetIpv4CtAddrType,  SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redNetIpv4CtAddrType) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.4.3.1.2.0,   groupKeySetSet,        SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::groupKeySetSet) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.3.5.1.0,   redPtnRespSession,     SnmpTypes::OidDataType::UNSIGNED,  uint32_t,    OID::Name::redPtnRespSession) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.3.5.2.0,   redPtnRespReason,      SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redPtnRespReason) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.3.5.3.0,   redPtnRespNotif,       SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::redPtnRespNotif) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.11.10.2.0,   redIndicationNotif,    SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::redIndicationNotif) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.11.10.1.0,   redStatusInd,          SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redStatusInd) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.9.3.2.4.0,   redActivatedNotif,     SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::redActivatedNotif) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.9.3.2.1.0,   redActivatedMbr,       SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redActivatedMbr) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.9.3.2.2.0,   redActivatedQbr,       SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redActivatedQbr) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.11.12.4.0,   redServiceNotif,       SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::redServiceNotif) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.11.12.2.0,   redServiceStatus,      SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redServiceStatus) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.11.12.3.0,   redServiceSession,     SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redServiceSession) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.9.3.7.3.0,   redReleasedNotif,      SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::redReleasedNotif) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.9.3.7.2.0,   redReleasedSession,    SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redReleasedSession) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.9.3.8.1.0,   redRscrcSession,       SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redRscrcSession) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.9.3.8.2.0,   redRsrcMbr,            SnmpTypes::OidDataType::INTEGER,   int,         OID::Name::redRsrcMbr) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.9.3.8.3.0,   redResrcAllocNotif,    SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::redResrcAllocNotif) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.5.7.1.0,   remConnSession,        SnmpTypes::OidDataType::UNSIGNED,  uint32_t,    OID::Name::remConnSession) \
    MIBDef(.1.3.6.1.4.1.290.3.5.1.2.2.4.2.5.7.2.0,   remConnNotif,          SnmpTypes::OidDataType::OCTET_STR, std::string, OID::Name::remConnNotif) \

// Using xmacro to initialize map
std::map<std::string_view, std::string_view> oidToNameMap{
#define MIBDef(oidVal, oidN, oidT, TYPE, enumVal) { #oidVal, #oidN },
LIST_OF_MIB_DATA
#undef MIBDef
};

std::map<std::string_view, Name> oidToEnumVal{
#define MIBDef(oidVal, oidN, oidT, TYPE, enumVal) {#oidVal, enumVal},
LIST_OF_MIB_DATA
#undef MIBDef
};

std::map<Name, std::string_view> enumValtoString{
#define MIBDef(oidVal, oidN, oidT, TYPE, enumVal) {enumVal, #oidN},
LIST_OF_MIB_DATA
#undef MIBDef
};

template <Name OidNameEnumValue>
struct MIBentry;

#define MIBDef(oidVal, oidN, oidT, TYPE, enumVal)               \
    template <>                                                 \
    struct MIBentry<enumVal>                                    \
    {                                                           \
        static constexpr SnmpTypes::OidDataType oidType = oidT; \
        static constexpr std::string_view oidValue = #oidVal;    \
        static constexpr std::string_view oidName = #oidN;       \
        using type = TYPE;                                      \
    };
LIST_OF_MIB_DATA
#undef MIBDef
// "Syntactic Sugar" macros to access MIBentry fields
// pull OID value from MIBentry
#define OID_v(NAME) std::string(OID::MIBentry<OID::Name::NAME>::oidValue)
// pull OID type from MIBentry
#define OID_t(NAME) OID::MIBentry<OID::Name::NAME>::oidType
// pull C++ type from MIBentry
#define OID_cpp_t(NAME) OID::MIBentry<OID::Name::NAME>::type
// convert from OID value to name
#define OID_n(OIDVAL) OID::OID_n_utility(OIDVAL)
std::string_view OID_n_utility(std::string_view oidVal){
    if (const auto it = OID::oidToNameMap.find(oidVal); it != oidToNameMap.cend()) {
        return it->second;
    }
    return "Unknown";
}
Name OID_enum(std::string_view oidVal) {
    if (const auto it = OID::oidToEnumVal.find(oidVal); it != OID::oidToEnumVal.cend()) {
        return it->second;
    }
    return Name::Unknown;
}
std::string_view enumToName(Name name) {
    if (const auto it = OID::enumValtoString.find(name); it != OID::enumValtoString.cend()) {
        return it->second;
    }
    return "unknown";
}
// This function is necessary due to limitations of current preprocessor use
void pushOidToNameMap(std::string_view oidVal, std::string_view oidName){
    OID::oidToNameMap.insert(std::pair<std::string_view, std::string_view>(oidVal, oidName));
}

}  // namespace OID
