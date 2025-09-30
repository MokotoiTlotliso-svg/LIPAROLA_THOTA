#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <chrono>
#include <thread>

class IntelligentConnectivitySim {
private:
    struct NetworkPolicy {
        std::string securityLevel;
        bool requirePIN;
        int dataLimit;
        std::string connectionType;
    };
    
    std::vector<std::string> trustedDevices;
    std::map<std::string, NetworkPolicy> policyRules;
    
public:
    IntelligentConnectivitySim() {
        initializePolicies();
        initializeTrustedDevices();
    }
    
    void initializePolicies() {
        std::cout << "Initializing Security Policies..." << std::endl;
        
        policyRules["home_trusted"] = {"LOW", false, 1000, "FULL_ACCESS"};
        policyRules["public_trusted"] = {"MEDIUM", true, 500, "LIMITED_ACCESS"};
        policyRules["untrusted"] = {"HIGH", true, 100, "RESTRICTED"};
        policyRules["emergency"] = {"CRITICAL", true, 50, "EMERGENCY_ONLY"};
        
        std::cout << "• 4 security levels configured" << std::endl;
        std::cout << "• Context-aware rules active" << std::endl;
    }
    
    void initializeTrustedDevices() {
        trustedDevices = {"home_wifi", "office_bt", "car_system", "personal_tablet"};
    }
    
    void testEnvironment(const std::string& location) {
        std::cout << "\n=== Testing Environment: " << location << " ===" << std::endl;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        std::vector<std::string> availableNetworks = scanNetworks(location);
        std::vector<std::string> nearbyDevices = scanDevices(location);
        
        std::cout << "Available networks: ";
        for(const auto& network : availableNetworks) {
            std::cout << network << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Nearby devices: ";
        for(const auto& device : nearbyDevices) {
            std::cout << device << " ";
        }
        std::cout << std::endl;
        
        std::string trustLevel = evaluateTrustLevel(nearbyDevices, location);
        NetworkPolicy policy = applyPolicy(trustLevel, location);
        
        makeConnectivityDecisions(availableNetworks, policy);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "⏱️  Context decision time: " << duration.count() << "μs" << std::endl;
        
        // Check if decision was fast enough
        if(duration.count() > 5000) { // 5ms threshold
            std::cout << "⚠️  Slow decision making detected" << std::endl;
        }
    }
    
    void testMultipleScenarios() {
        std::cout << "\n=== Multiple Scenario Test ===" << std::endl;
        std::cout << "Testing connectivity across different environments..." << std::endl;
        
        std::vector<std::string> scenarios = {
            "Home",
            "Office",
            "Public Cafe",
            "Shopping Mall",
            "Airport",
            "Rural Area"
        };
        
        for(const auto& scenario : scenarios) {
            testEnvironment(scenario);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    
    void testBatteryOptimization() {
        std::cout << "\n=== Battery Optimization Test ===" << std::endl;
        std::cout << "Testing power-efficient scanning strategies..." << std::endl;
        
        std::vector<std::string> powerModes = {"HIGH_POWER", "BALANCED", "LOW_POWER", "ULTRA_SAVE"};
        
        for(const auto& mode : powerModes) {
            std::cout << "\n--- Power Mode: " << mode << " ---" << std::endl;
            
            auto start = std::chrono::high_resolution_clock::now();
            
            // Simulate different scanning intensities
            int scanIntensity = 1;
            if(mode == "HIGH_POWER") scanIntensity = 4;
            else if(mode == "BALANCED") scanIntensity = 2;
            else if(mode == "LOW_POWER") scanIntensity = 1;
            else scanIntensity = 0; // ULTRA_SAVE
            
            std::vector<std::string> networks;
            std::vector<std::string> devices;
            
            for(int i = 0; i < scanIntensity; i++) {
                if(!networks.empty()) networks.clear();
                if(!devices.empty()) devices.clear();
                
                networks = scanNetworks("Test");
                devices = scanDevices("Test");
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            
            std::cout << "Networks found: " << networks.size() << std::endl;
            std::cout << "Devices found: " << devices.size() << std::endl;
            std::cout << "Scan time: " << duration.count() << "ms" << std::endl;
            std::cout << "Estimated battery impact: " << (scanIntensity * 10) << "%" << std::endl;
        }
    }
    
    void showWorkloadInfo() {
        std::cout << "\n=== Intelligent Connectivity Workload Characteristics ===" << std::endl;
        std::cout << "• Lightweight conditional logic" << std::endl;
        std::cout << "• Rule-based decision making" << std::endl;
        std::cout << "• Environment scanning and evaluation" << std::endl;
        std::cout << "• Low computational requirements" << std::endl;
        std::cout << "• Fast response times (<5ms decisions)" << std::endl;
        std::cout << "• Battery-efficient operations" << std::endl;
    }

private:
    std::vector<std::string> scanNetworks(const std::string& location) {
        std::vector<std::string> networks;
        
        if(location == "Home") {
            networks = {"Home_WiFi_5G", "Home_WiFi_2G", "Neighbor_WiFi"};
        } else if(location == "Office") {
            networks = {"Office_Secure", "Office_Guest", "Conference_Room"};
        } else if(location == "Public Cafe") {
            networks = {"Cafe_Free_WiFi", "Cafe_Premium", "Public_Hotspot"};
        } else if(location == "Shopping Mall") {
            networks = {"Mall_Free", "Store_WiFi", "FoodCourt_Network"};
        } else if(location == "Airport") {
            networks = {"Airport_Free", "Airport_Premium", "Airline_Lounge"};
        } else {
            networks = {"Cellular_4G", "Cellular_3G"}; // Rural area
        }
        
        // Add cellular as backup
        networks.push_back("Cellular_Data");
        
        return networks;
    }
    
    std::vector<std::string> scanDevices(const std::string& location) {
        std::vector<std::string> devices;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 3);
        
        // Always include some trusted devices based on location
        if(location == "Home") {
            devices.push_back("home_wifi");
            devices.push_back("smart_tv");
            if(dis(gen) > 1) devices.push_back("car_system");
        } else if(location == "Office") {
            devices.push_back("office_bt");
            if(dis(gen) > 1) devices.push_back("printer_01");
        }
        
        // Add some random unknown devices
        if(dis(gen) > 0) devices.push_back("unknown_device_1");
        if(dis(gen) > 1) devices.push_back("strange_bt_device");
        
        return devices;
    }
    
    std::string evaluateTrustLevel(const std::vector<std::string>& devices,
                                  const std::string& location) {
        int trustedCount = 0;
        for(const auto& device : devices) {
            for(const auto& trusted : trustedDevices) {
                if(device == trusted) {
                    trustedCount++;
                    break;
                }
            }
        }
        
        // Decision logic based on context and trusted devices
        if(location == "Home" && trustedCount >= 2) {
            return "home_trusted";
        } else if(location == "Office" && trustedCount >= 1) {
            return "public_trusted";
        } else if(trustedCount >= 1) {
            return "public_trusted";
        } else if(location == "Rural Area") {
            return "emergency";
        } else {
            return "untrusted";
        }
    }
    
    NetworkPolicy applyPolicy(const std::string& trustLevel, const std::string& location) {
        NetworkPolicy policy = policyRules[trustLevel];
        std::cout << "🔒 Security Policy Applied: " << std::endl;
        std::cout << "   • Level: " << policy.securityLevel << std::endl;
        std::cout << "   • PIN Required: " << (policy.requirePIN ? "YES" : "NO") << std::endl;
        std::cout << "   • Data Limit: " << policy.dataLimit << "MB" << std::endl;
        std::cout << "   • Connection: " << policy.connectionType << std::endl;
        return policy;
    }
    
    void makeConnectivityDecisions(const std::vector<std::string>& networks,
                                  const NetworkPolicy& policy) {
        std::cout << "📡 Connectivity Decisions:" << std::endl;
        
        for(const auto& network : networks) {
            if(policy.securityLevel == "LOW") {
                std::cout << "   ✅ FULL: " << network << " (trusted)" << std::endl;
            } else if(policy.securityLevel == "MEDIUM") {
                if(network.find("Secure") != std::string::npos ||
                   network.find("Office") != std::string::npos) {
                    std::cout << "   ✅ LIMITED: " << network << " (secured)" << std::endl;
                } else {
                    std::cout << "   ➖ AVOID: " << network << " (unsecured)" << std::endl;
                }
            } else if(policy.securityLevel == "HIGH") {
                if(network == "Cellular_Data") {
                    std::cout << "   ✅ RESTRICTED: " << network << " (cellular)" << std::endl;
                } else {
                    std::cout << "   ❌ BLOCKED: " << network << " (untrusted)" << std::endl;
                }
            } else { // EMERGENCY
                if(network == "Cellular_Data") {
                    std::cout << "   🆘 EMERGENCY: " << network << " (minimal)" << std::endl;
                } else {
                    std::cout << "   ❌ BLOCKED: " << network << std::endl;
                }
            }
        }
    }
};

void displayMenu() {
    std::cout << "\n==========================================" << std::endl;
    std::cout << " INTELLIGENT CONNECTIVITY WORKLOAD TEST" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "1. Test Home Environment" << std::endl;
    std::cout << "2. Test Office Environment" << std::endl;
    std::cout << "3. Test Public Environment" << std::endl;
    std::cout << "4. Test Multiple Scenarios" << std::endl;
    std::cout << "5. Test Battery Optimization" << std::endl;
    std::cout << "6. Show Workload Information" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "Choose an option (1-7): ";
}

int main() {
    IntelligentConnectivitySim connectivitySim;
    int choice;
    
    std::cout << "Initializing Intelligent Connectivity Simulator..." << std::endl;
    std::cout << "Focus: Context-aware network decisions for African markets" << std::endl;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                connectivitySim.testEnvironment("Home");
                break;
            case 2:
                connectivitySim.testEnvironment("Office");
                break;
            case 3:
                connectivitySim.testEnvironment("Public Cafe");
                break;
            case 4:
                connectivitySim.testMultipleScenarios();
                break;
            case 5:
                connectivitySim.testBatteryOptimization();
                break;
            case 6:
                connectivitySim.showWorkloadInfo();
                break;
            case 7:
                std::cout << "Exiting Intelligent Connectivity Simulator. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option! Please choose 1-7." << std::endl;
        }
    } while(choice != 7);
    
    return 0;
}
