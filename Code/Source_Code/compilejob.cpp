//
// Created by Devon Coates on 9/7/23.
//

#include "compilejob.h"
#include <iostream>
#include <string>
#include <array>
#include <fstream>


void CompileJob::Execute(){
    std::array <char, 128> buffer;
    std::string command = "make testCompileError"; //TYPE THE COMMAND TO RUN WHICH RULE YOU WANT HERE

    //redirect cerr to cout
    command.append(" 2>&1");

    //open pipe and run command
    FILE* pipe = popen(command.c_str(), "r");
    if(!pipe){
        std::cout << "popen Failed: Failed to open pipe" << std::endl;
        return;
    }

    //read till end of process:
    while(fgets(buffer.data(), 128, pipe) != NULL){
        this->output.append(buffer.data());
    }

    //close pipe and get return code
    this->returnCode = pclose(pipe);

    std::cout << "Compile Job " << this->GetUniqueID() << " has been executed." << std::endl;
}

void CompileJob::JobCompleteCallback() {
    std::ofstream rawout("Data/rawOutput.txt", std::ios::out);

    if(rawout.is_open()){

    }else{
        std::cout << "FILE DID NOT OPEN" << std::endl;
        perror("Error: ");
    }

    rawout << this->output << std::endl;
    rawout << this->returnCode << std::endl;

    rawout.close();


    std::string errorDescription, filePath, buffer, code, oldFile;
    int lineNumber, columnNumber;
    std::ifstream in("Data/rawOutput.txt");
    std::ofstream out("Data/output.json", std::ios::out);
    std::getline(in, buffer);
    int fileNum = 1;
    out << "{\n\t\"File" << fileNum << "_Errors_and_Warnings\": [\n";
    int count = 0;
    int i = 1;
    while(!in.eof()) {
        std::getline(in, filePath, ':');
        std::getline(in, buffer, ':');
        try {
            lineNumber = std::stoi(buffer); // This could throw std::invalid_argument
        } catch (const std::invalid_argument& e) {
            // This block catches the exception
            continue;
        }
        std::getline(in, buffer, ':');
        try {
            columnNumber = std::stoi(buffer); // This could throw std::invalid_argument
        } catch (const std::invalid_argument& e) {
            // This block catches the exception
            continue;
        }
        std::getline(in, buffer, ':');
        if((buffer == " error" || buffer == " warning") && count == 0) {
            oldFile = filePath;
            std::getline(in, errorDescription);
            std::ifstream codeIn(filePath);
            code = "";
            while(!codeIn.eof()){
                getline(codeIn, buffer);
                if(i >= (lineNumber - 2) && i <= (lineNumber + 2)){
                    code += buffer;
                    code += "\\n";
                }
                i++;
            }
            out << "\t\t{\n"
                   "\t\t\t\"file_path\": \"" << filePath << "\",\n"
                << "\t\t\t\"line_number\": " << lineNumber << ", \n"
                << "\t\t\t\"column_number\": " << columnNumber << ", \n"
                << "\t\t\t\"error_description\": \"" << errorDescription << "\",\n"
                << "\t\t\t\"code\": \"" << code << "\"\n"
                << "\t\t}";
            count++;
        }
        else if((buffer == " error" || buffer == " warning") && count == 1){
            std::getline(in, errorDescription);
            filePath = "./" + filePath;
            std::ifstream codeIn(filePath);
            code = "";
            i = 1;
            while(!codeIn.eof()){
                getline(codeIn, buffer);
                if(i >= (lineNumber - 2) && i <= (lineNumber + 2)){
                    code += buffer;
                    code += "\\n";
                }
                i++;
            }
            if(filePath != oldFile){
                fileNum++;
                oldFile = filePath;
                out << "\n\t],\n\n\t\"File" << fileNum << "_Errors_and_Warnings\": [\n"
                    << "\t\t{\n"
                    << "\t\t\t\"file_path\": \"" << filePath << "\",\n"
                    << "\t\t\t\"line_number\": " << lineNumber << ", \n"
                    << "\t\t\t\"column_number\": " << columnNumber << ", \n"
                    << "\t\t\t\"error_description\": \"" << errorDescription << "\",\n"
                    << "\t\t\t\"code\": \"" << code << "\"\n"
                    << "\t\t}";
            }else
                out << ",\n"
                    << "\t\t{\n"
                    << "\t\t\t\"file_path\": \"" << filePath << "\",\n"
                    << "\t\t\t\"line_number\": " << lineNumber << ", \n"
                    << "\t\t\t\"column_number\": " << columnNumber << ", \n"
                    << "\t\t\t\"error_description\": \"" << errorDescription << "\",\n"
                    << "\t\t\t\"code\": \"" << code << "\"\n"
                    << "\t\t}";
        }
        std::getline(in, buffer, '/');
    }
    out << "\n\t]\n}" << std::endl;

    out.close();
    in.close();


    std::cout << "CompileJob " << this->GetUniqueID() << " return code" << this->returnCode << std::endl;
    std::cout << "CompileJob " << this->GetUniqueID() << " output \n" << this->output << std::endl;
}
