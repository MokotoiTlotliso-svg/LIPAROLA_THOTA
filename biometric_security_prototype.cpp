#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <chrono>
#include <thread> 

class BiometricSecuritySim {
private:
    struct UserProfile {
        std::string voicePrintHash;
        std::string pin;
        std::vector<std::string> trustedDevices;
    };
    
    std::map<std::string, UserProfile> userDatabase;
    std::vector<std::string> nearbyDevices;
    
public:
    BiometricSecuritySim() {
        initializeUserDatabase();
    }
    
    void initializeUserDatabase() {
        std::cout << "Initializing User Database..." << std::endl;
        
        UserProfile user1 = {"voice_hash_1234", "5678", {"home_bt", "car_bt"}};
        UserProfile user2 = {"voice_hash_5678", "1234", {"office_wifi"}};
        UserProfile user3 = {"voice_hash_9012", "4321", {"home_bt", "personal_device"}};
        
        userDatabase["thabo"] = user1;
        userDatabase["matseliso"] = user2;
        userDatabase["ntate_john"] = user3;
        
        std::cout << "• 3 user profiles loaded" << std::endl;
        std::cout << "• Multi-factor authentication enabled" << std::endl;
    }
    
    void testUserAuthentication() {
        std::cout << "\n=== User Authentication Test ===" << std::endl;
        
        scanNearbyDevices();
        std::cout << std::endl;
        
        // Test authentication for different users
        authenticateUser("thabo");
        authenticateUser("matseliso");
        authenticateUser("ntate_john");
        authenticateUser("unknown_user"); // Test non-existent user
    }
    
    void testContextAwareness() {
        std::cout << "\n=== Context-Aware Security Test ===" << std::endl;
        std::cout << "Testing security policy adaptation..." << std::endl;
        
        // Test different environments
        std::vector<std::string> environments = {"Home", "Office", "Public", "Unknown"};
        
        for(const auto& env : environments) {
            std::cout << "\n--- Testing " << env << " Environment ---" << std::endl;
            
            // Simulate different device scans for each environment
            if(env == "Home") {
                nearbyDevices = {"home_bt", "car_bt", "tv_system"};
            } else if(env == "Office") {
                nearbyDevices = {"office_wifi", "printer_bt"};
            } else if(env == "Public") {
                nearbyDevices = {"public_wifi", "unknown_device1"};
            } else {
                nearbyDevices = {"strange_device", "unknown_network"};
            }
            
            std::cout << "Nearby devices: ";
            for(const auto& device : nearbyDevices) {
                std::cout << device << " ";
            }
            std::cout << std::endl;
            
            // Test authentication in this context
            authenticateUser("thabo");
        }
    }
    
    void stressTest() {
        std::cout << "\n=== Stress Test: Multiple Authentication Attempts ===" << std::endl;
        std::cout << "Testing system under load..." << std::endl;
        
        scanNearbyDevices();
        int attempts = 5;
        int successCount = 0;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for(int i = 0; i < attempts; i++) {
            bool success = quickAuthTest();
            if(success) successCount++;
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // FIXED LINE
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "\nStress Test Results:" << std::endl;
        std::cout << "• Attempts: " << attempts << std::endl;
        std::cout << "• Successful: " << successCount << std::endl;
        std::cout << "• Total time: " << duration.count() << "ms" << std::endl;
        std::cout << "• Average time per auth: " << (duration.count() / attempts) << "ms" << std::endl;
    }
    
    void showWorkloadInfo() {
        std::cout << "\n=== Biometric Security Workload Characteristics ===" << std::endl;
        std::cout << "• Multi-factor authentication (voice + PIN)" << std::endl;
        std::cout << "• Context-aware security policies" << std::endl;
        std::cout << "• Moderate latency tolerance (1-2 seconds)" << std::endl;
        std::cout << "• Random memory access patterns" << std::endl;
        std::cout << "• Decision logic intensive" << std::endl;
    }

private:
    void scanNearbyDevices() {
        nearbyDevices = {"home_bt", "unknown_device", "office_wifi", "car_bt"};
        std::cout << "Scanning nearby devices... Found: ";
        for(const auto& device : nearbyDevices) {
            std::cout << device << " ";
        }
        std::cout << std::endl;
    }
    
    void authenticateUser(const std::string& userId) {
        auto start = std::chrono::high_resolution_clock::now();
        
        if(userDatabase.find(userId) == userDatabase.end()) {
            std::cout << "❌ User '" << userId << "' not found in database!" << std::endl;
            return;
        }
        
        const UserProfile& profile = userDatabase[userId];
        
        bool voiceAuth = authenticateVoice(profile.voicePrintHash);
        bool trustedEnvironment = isTrustedEnvironment(profile);
        
        bool authenticated = false;
        std::string authMethod = "";
        std::string contextInfo = "";
        
        if(voiceAuth && trustedEnvironment) {
            authenticated = true;
            authMethod = "Voice";
            contextInfo = " (Trusted Environment)";
        } else if(voiceAuth) {
            authenticated = true;
            authMethod = "Voice";
        } else {
            // Fallback to PIN verification
            authenticated = verifyPIN(profile.pin);
            authMethod = "PIN";
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "👤 " << userId << ": ";
        if(authenticated) {
            std::cout << "✅ AUTH_SUCCESS";
        } else {
            std::cout << "❌ AUTH_FAILED";
        }
        std::cout << " via " << authMethod << contextInfo;
        std::cout << " [" << duration.count() << "ms]" << std::endl;
        
        // Check if within acceptable latency
        if(duration.count() > 2000) {
            std::cout << "   ⚠️  Slow authentication (>2s)" << std::endl;
        }
    }
    
    bool quickAuthTest() {
        // Simplified version for stress testing
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);
        return dis(gen) > 0.4f; // 60% success rate
    }
    
    bool authenticateVoice(const std::string& storedVoicePrint) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);
        return dis(gen) > 0.3f; // 70% success rate
    }
    
    bool isTrustedEnvironment(const UserProfile& profile) {
        for(const auto& trustedDevice : profile.trustedDevices) {
            for(const auto& nearbyDevice : nearbyDevices) {
                if(trustedDevice == nearbyDevice) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool verifyPIN(const std::string& correctPIN) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);
        return dis(gen) > 0.2f; // 80% success rate
    }
};

void displayMenu() {
    std::cout << "\n==========================================" << std::endl;
    std::cout << "    BIOMETRIC SECURITY WORKLOAD TEST" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "1. Test User Authentication" << std::endl;
    std::cout << "2. Test Context Awareness" << std::endl;
    std::cout << "3. Stress Test" << std::endl;
    std::cout << "4. Show Workload Information" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "Choose an option (1-5): ";
}

int main() {
    BiometricSecuritySim securitySim;
    int choice;
    
    std::cout << "Initializing Biometric Security Simulator..." << std::endl;
    std::cout << "Focus: Multi-factor authentication with context awareness" << std::endl;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                securitySim.testUserAuthentication();
                break;
            case 2:
                securitySim.testContextAwareness();
                break;
            case 3:
                securitySim.stressTest();
                break;
            case 4:
                securitySim.showWorkloadInfo();
                break;
            case 5:
                std::cout << "Exiting Biometric Security Simulator. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option! Please choose 1-5." << std::endl;
        }
    } while(choice != 5);
    
    return 0;
}
