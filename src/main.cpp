#include <iostream>
#include "Logger.hpp"
#include "cxxopts.hpp"
#include "IFileCombiner.hpp"
#include "TextFileCombiner.hpp"

/**
 * @brief 프로그램의 시작점
 */
int main(int argc, char* argv[]) {
    try {
        cxxopts::Options options("combine_files", "Utility to combine files based on wildcard patterns");
        options.add_options()
            ("p,path", "Directory to search (default: current directory)", cxxopts::value<std::string>()->default_value("."))
            ("x,exclude", "Directories to exclude (multiple values allowed)", cxxopts::value<std::vector<std::string>>())
            ("pattern", "Wildcard patterns for file matching (e.g. \"*.cpp\", \"*.h\")", cxxopts::value<std::vector<std::string>>()->default_value({}))
            ("o,output", "Output file name", cxxopts::value<std::string>()->default_value(""))
            ("l,log", "Optional log file path", cxxopts::value<std::string>()->default_value(""))
            ("v,verbose", "Enable verbose logging", cxxopts::value<bool>()->default_value("false"))
            ("h,help", "Display help");
        
        options.parse_positional({"pattern", "output"});

        auto result = options.parse(argc, argv);
        
        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }
            
        if (!result.count("pattern") || !result.count("output")) {
            std::cerr << "Error: Missing required arguments: pattern and output" << std::endl;
            std::cout << options.help() << std::endl;
            return 1;
        }

        std::string searchPath = result["path"].as<std::string>();
        auto patternsInput = result["pattern"].as<std::vector<std::string>>();
        std::string outputFileName = result["output"].as<std::string>();
        bool verbose = result["verbose"].as<bool>();
        std::string logFilePath = result["log"].as<std::string>();

        std::vector<std::string> excludeDirs;
        if (result.count("exclude")) {
            excludeDirs = result["exclude"].as<std::vector<std::string>>();
        }

        Logger logger(verbose, logFilePath);
        IFilecombiner* combiner = new TextFileCombiner(searchPath, excludeDirs, patternsInput, outputFileName, logger);

        if (!combiner->combineFiles()) {
            logger.error("File combination failed.");
            delete combiner;
            return 1;
        }
        delete combiner;
    } catch (const cxxopts::exceptions::exception& e) {
        std::cerr << "Option parsing error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}