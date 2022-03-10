// #include </Users/swhit210/Downloads/protobuf-3.19.4/src/google/protobuf/text_format.h>
// namespace google::protobuf

// #include <iostream>
// #include <fstream>
// #include <filesystem>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <filesystem>
#include <stdint.h>
#include <fcntl.h>
#include <string>

const int kProtoReadBytesLimit = INT_MAX; 

namespace google::protobuf {

    int main() {

        // File Preparation
        std::string cwd = std::filesystem::current_path();
        std::string projectPath = "/tests";

        std::string inputFileCPU = "cpuprofile";

        // Read the Binary File
        std::ifstream file;
        
        file.open(inputFileCPU);

        if (file.fail()) {
            std::cout<<"Error opening file!"<<std::endl;
        }
        
        // Get Length of File
        file.seekg(0, file.end);
        int length = file.tellg();
        file.seekg(0, file.beg);

        // Read Into Buffer
        char* buffer = new char[length];
        file.read(buffer, length);

        // Convert Buffer to Byte Array
        google::protobuf::io::ArrayInputStream* bytes_input = new google::protobuf::io::ArrayInputStream(buffer, length);
        
        // Convert Byte Array to Coded Stream
        google::protobuf::io::CodedInputStream* coded_input = new google::protobuf::io::CodedInputStream(bytes_input);
        coded_input->SetTotalBytesLimit(536870912);

        // Parse Stream into Message
        google::protobuf::Message* proto;
        bool parseSuccess = proto->ParseFromCodedStream(coded_input);

        // If Successful, Print Message
        if (parseSuccess) {
            std::string* output;
            bool printSuccess = google::protobuf::TextFormat::PrintToString(*proto, output);

            if (printSuccess) {
                std::cout<<*output<<std::endl;
            }
        }

        return 0;
    }
}