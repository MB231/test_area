#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using JSON = nlohmann::json;
using StringPair = std::pair<std::string, std::string>;

template <typename T>
bool safeJsonRead(const JSON& json, const std::string& key, T& value) {
    try {
        if (json.contains(key)){
            std::cout << key << ": " << json.at(key) << std::endl;
            json.at(key).get_to(value);
        } else {
            std::cout << key << " not found" << std::endl;
            return false;
        }
    } catch (const JSON::exception& e) {
        std::cout << "Error getting: " << key << " Message: " << e.what() << '\n' << "exception id: " << e.id << std::endl;
        return false;
    }
    return true;
}

// used to keep data togeter
struct ScanResult {
    int idNum;
    float begMhz;
    float endMhz;
    float powerDb;
};


// I/Q data from SDR. Main status back, may be changed to raw and processed signal data instead for generality
struct ScanCmd {
    bool valid = false;
    struct Data {
        int idStartNum = 0;
        std::vector<ScanResult> scanV;
        float recChanEndMhz;
        float recChanStartMhz;
    };
    Data data;
    ScanCmd(std::string response, unsigned int startNumber, unsigned int idStartNum) {
        this->data.idStartNum = idStartNum;
        bool retVal = JSON::accept(response);
        if (retVal){JSON json = JSON::parse(response); // single array returned that needs unwrapping
        for (auto& el : json.items()) {
            JSON j = el.value(); // for easier parsing and ensuring right json structure/object
            if (j.contains("rec_start") || j.contains("rec_end")) {
                retVal = safeJsonRead(j, "rec_end", this->data.recChanEndMhz);
                retVal = safeJsonRead(j, "rec_start", this->data.recChanStartMhz);
            } else {
                ScanResult c;
                c.idNum = startNumber++;
                retVal = safeJsonRead(j, "chan_start", c.begMhz);
                retVal = safeJsonRead(j, "chan_end", c.endMhz);
                retVal = safeJsonRead(j, "powerDb", c.powerDb);
                this->data.scanV.push_back(c);
            }
        }
        }
        if (retVal) { 
            valid = true;
            std::cout << "successful scan response return";
        } else {
            valid = false;
            std::cout << "failed to parse scan response return";
        }
    }
    std::vector<StringPair> getParsed() {
        std::vector<StringPair> outV;
        // TODO gotta be a better way to do this
        std::string name = "rec_end_";
        name.append(std::to_string(this->data.idStartNum));
        outV.emplace_back(std::make_pair(name, std::to_string(this->data.recChanStartMhz)));
        name = "rec_start_";
        name.append(std::to_string(this->data.idStartNum));
        outV.emplace_back(std::make_pair(name, std::to_string(this->data.recChanEndMhz)));
        for (auto& i : this->data.scanV) {
            name = "chan_start_";
            name.append(std::to_string(i.idNum));
            outV.emplace_back(std::make_pair(name, std::to_string(i.begMhz)));
            name = "chan_end_";
            name.append(std::to_string(i.idNum));
            outV.emplace_back(std::make_pair(name, std::to_string(i.endMhz)));
            // 2 fields should not be parsed "other_invalid_field" and "invalid_field";
            name = "powerDb_";
            name.append(std::to_string(i.idNum));
            outV.emplace_back(std::make_pair(name, std::to_string(i.powerDb)));
        }
        return outV;
    }
};


struct VersionResp {
    bool valid = false;
    struct Data {
        std::string daemonVersion;
    };
    Data data;
    VersionResp(std::string response) {
        bool retVal = JSON::accept(response);
        if (retVal){JSON json = JSON::parse(response); // single array returned that needs unwrapping
        retVal = safeJsonRead(JSON::parse(response), "version", this->data.daemonVersion);
        }
        if (retVal) { 
            valid = true;
            std::cout << "successful version return";
        } else {
            valid = false;
            std::cout << "failed to parse daemon version return";
        }
    }
    std::vector<StringPair> getParsed() {
        std::vector<StringPair> outV;
        outV.emplace_back(std::make_pair("version", this->data.daemonVersion));
        return outV;
    }
};

struct EmptyResp {
    EmptyResp(std::string response) {}
};


//void from_json(const json& j, person& p) {
//    j.at("name").get_to(p.name);
//    j.at("address").get_to(p.address);
//    j.at("age").get_to(p.age);
//}
std::string version_test_string = "{\"version\": \"test_version\"}";
std::string scan_test_string = R"("[{\"chan_start\": 89.990234375, \"chan_end\": 94.990234375, \"other_invalid_field\": 100.0, \"invalid_field\": 0, \"powerDb\": -24.695461090527335}, {\"chan_start\": 99.98046875, \"chan_end\": 104.98046875, \"other_invalid_field\": 100.0, \"invalid_field\": 0, \"powerDb\": -24.34532265091265}, {\"chan_start\": 94.9853515625, \"chan_end\": 99.9853515625, \"other_invalid_field\": 100.0, \"invalid_field\": 0, \"powerDb\": -24.072625310805815}, {\"chan_start\": 84.9951171875, \"chan_end\": 89.9951171875, \"other_invalid_field\": 100.0, \"invalid_field\": 0, \"powerDb\": -24.061277308135345}, {\"chan_start\": 109.970703125, \"chan_end\": 114.970703125, \"other_invalid_field\": 100.0, \"invalid_field\": 0, \"powerDb\": -23.484578328193127}, {\"chan_start\": 104.9755859375, \"chan_end\": 109.9755859375, \"other_invalid_field\": 100.0, \"invalid_field\": 0, \"powerDb\": -23.459873099502815}, {\"rec_start\": 90.009765625, \"rec_end\": 94.990234375}]")";

int main() {
    VersionResp versionResp(version_test_string);
    std::cout << "Version Return: \n";
    for (auto& [key, val] : versionResp.getParsed()) {
        std::cout << "field: " << key << " value: " << val << "\n";
    }

    ScanCmd scan(scan_test_string, 0, 128);
    std::cout << "Scan Return: \n";
    for (auto& [key, val] : scan.getParsed()) {
        std::cout << "field: " << key << " value: " << val << "\n";
    }
    return 0;
}
