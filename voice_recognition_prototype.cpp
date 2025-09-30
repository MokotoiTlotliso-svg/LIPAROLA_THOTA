#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <cmath>

class VoiceRecognitionSim {
private:
    std::vector<std::vector<float>> keywordModels;
    std::vector<float> audioBuffer;
    const int BUFFER_SIZE = 1024;
    const float RESPONSE_THRESHOLD = 0.85f;
    
public:
    VoiceRecognitionSim() {
        initializeKeywordModels();
    }
    
    void initializeKeywordModels() {
        // Simulate 3 keyword models for Sesotho commands
        std::cout << "Initializing Sesotho keyword models..." << std::endl;
        std::vector<std::string> keywords = {"Feta"}; // Call
        keywords.push_back("Romela"); // Send
        keywords.push_back("Thusa"); // Help
        
        for(int i = 0; i < 3; i++) {
            std::vector<float> model(256, 0.1f * (i + 1));
            keywordModels.push_back(model);
            std::cout << "  - Model " << (i+1) << ": " << keywords[i] << std::endl;
        }
    }
    
    void testRealTimeProcessing() {
        std::cout << "\n=== Real-time Audio Processing Test ===" << std::endl;
        std::cout << "Testing latency requirements (<100ms)..." << std::endl;
        
        int totalFrames = 8;
        int latencyViolations = 0;
        
        for(int frame = 0; frame < totalFrames; frame++) {
            auto start = std::chrono::high_resolution_clock::now();
            
            // Simulate audio processing pipeline
            simulateAudioCapture();
            std::vector<float> features = extractFeatures();
            bool keywordDetected = matchKeywords(features);
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            
            std::cout << "Frame " << frame << ": " << duration.count() << "ms, "
                      << "Keyword: " << (keywordDetected ? "DETECTED" : "none");
            
            if(duration.count() > 100) {
                std::cout << " ⚠️ LATENCY WARNING";
                latencyViolations++;
            }
            std::cout << std::endl;
            
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
        std::cout << "\nResults: " << latencyViolations << "/" << totalFrames
                  << " frames exceeded 100ms limit" << std::endl;
    }
    
    void testKeywordDetection() {
        std::cout << "\n=== Keyword Detection Accuracy Test ===" << std::endl;
        std::cout << "Testing Sesotho command recognition..." << std::endl;
        
        std::vector<std::string> testCommands = {"Feta", "Romela", "Thusa", "Unknown"};
        int tests = 10;
        int detections = 0;
        
        for(int i = 0; i < tests; i++) {
            simulateAudioCapture();
            std::vector<float> features = extractFeatures();
            bool detected = matchKeywords(features);
            
            if(detected) {
                detections++;
                std::cout << "Test " << i << ": ✅ Keyword detected" << std::endl;
            } else {
                std::cout << "Test " << i << ": ❌ No keyword" << std::endl;
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        
        std::cout << "\nDetection Rate: " << detections << "/" << tests
                  << " (" << (detections * 100 / tests) << "%)" << std::endl;
    }
    
    void showWorkloadInfo() {
        std::cout << "\n=== Voice Recognition Workload Characteristics ===" << std::endl;
        std::cout << "• Real-time processing (<100ms latency)" << std::endl;
        std::cout << "• Matrix operations for neural network inference" << std::endl;
        std::cout << "• Continuous audio stream processing" << std::endl;
        std::cout << "• Sesotho language support" << std::endl;
        std::cout << "• Compute-intensive workload" << std::endl;
    }

private:
    void simulateAudioCapture() {
        audioBuffer.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
        
        for(int i = 0; i < BUFFER_SIZE; i++) {
            audioBuffer.push_back(dis(gen));
        }
    }
    
    std::vector<float> extractFeatures() {
        // Simulate MFCC feature extraction
        std::vector<float> features(256);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<float> dis(0.0f, 1.0f);
        
        for(int i = 0; i < 256; i++) {
            features[i] = dis(gen);
        }
        return features;
    }
    
    bool matchKeywords(const std::vector<float>& features) {
        // Simulate neural network inference
        for(const auto& model : keywordModels) {
            float confidence = computeSimilarity(features, model);
            if(confidence > RESPONSE_THRESHOLD) {
                return true;
            }
        }
        return false;
    }
    
    float computeSimilarity(const std::vector<float>& a, const std::vector<float>& b) {
        float similarity = 0.0f;
        for(size_t i = 0; i < std::min(a.size(), b.size()); i++) {
            similarity += a[i] * b[i]; // Simulate dot product
        }
        return std::abs(similarity) / std::min(a.size(), b.size());
    }
};

void displayMenu() {
    std::cout << "\n==========================================" << std::endl;
    std::cout << "    VOICE RECOGNITION WORKLOAD TEST" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "1. Test Real-time Processing" << std::endl;
    std::cout << "2. Test Keyword Detection" << std::endl;
    std::cout << "3. Show Workload Information" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "Choose an option (1-4): ";
}

int main() {
    VoiceRecognitionSim voiceSim;
    int choice;
    
    std::cout << "Initializing Voice Recognition Simulator..." << std::endl;
    std::cout << "Focus: Low-latency Sesotho speech processing" << std::endl;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                voiceSim.testRealTimeProcessing();
                break;
            case 2:
                voiceSim.testKeywordDetection();
                break;
            case 3:
                voiceSim.showWorkloadInfo();
                break;
            case 4:
                std::cout << "Exiting Voice Recognition Simulator. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option! Please choose 1-4." << std::endl;
        }
    } while(choice != 4);
    
    return 0;
}
