#include "TextFileCombiner.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

namespace fs = std::filesystem;

TextFileCombiner::TextFileCombiner(const std::string& searchPath,
                                   const std::vector<std::string>& excludeDirs,
                                   const std::vector<std::string>& patterns,
                                   const std::string& outputFileName,
                                   Logger& logger)
    : m_searchPath(searchPath),
      m_excludeDirs(excludeDirs),
      m_outputFileName(outputFileName),
      m_logger(logger) 
{
    for (const auto& pat : patterns) {
        m_regexPatterns.push_back(wildcardToRegex(pat));
        m_logger.debug("Converted pattern: " + pat + " to regex.");
    }
}

std::regex TextFileCombiner::wildcardToRegex(const std::string& pattern) {
    std::string regexPattern = "^";
    for (char ch : pattern) {
        switch (ch) {
            case '*':
                regexPattern.append(".*");
                break;
            case '?':
                regexPattern.push_back('.');
                break;
            case '.':
                regexPattern.append("\\.");
                break;
            default:
                regexPattern.push_back(ch);
                break;
        }
    }
    regexPattern.push_back('$');
    return std::regex(regexPattern, std::regex::icase);
}

bool TextFileCombiner::matchesAnyPattern(const std::string& filename) {
    for (const auto& reg : m_regexPatterns) {
        if (std::regex_match(filename, reg))
            return true;
    }
    return false;
}

bool TextFileCombiner::combineFiles() {
    try {
        std::vector<fs::path> matchingFiles;
        try {
            if (!fs::exists(m_searchPath) || !fs::is_directory(m_searchPath)) {
                m_logger.error("Search path '" + m_searchPath + "' does not exist or is not a directory.");
                return false;
            }
            m_logger.info("Searching in directory: " + m_searchPath);

            for (auto it = fs::recursive_directory_iterator(m_searchPath); it != fs::recursive_directory_iterator(); ++it) {
                const auto& entry = *it;
                if (fs::is_directory(entry.path())) {
                    std::string dirName = entry.path().filename().string();
                    if (std::find(m_excludeDirs.begin(), m_excludeDirs.end(), dirName) != m_excludeDirs.end()) {
                        m_logger.debug("Excluding directory: " + entry.path().string());
                        it.disable_recursion_pending();
                    }
                }
                else if (fs::is_regular_file(entry.path())) {
                    std::string filename = entry.path().filename().string();
                    if (matchesAnyPattern(filename)) {
                        matchingFiles.push_back(entry.path());
                        m_logger.debug("Matched file: " + entry.path().string());
                    }
                }
            }
        } catch (const fs::filesystem_error& e) {
            m_logger.error(std::string("Filesystem error: ") + e.what());
            return false;
        }

        if (matchingFiles.empty()) {
            m_logger.error("No files matching the given patterns were found in '" + m_searchPath + "'.");
            return false;
        }

        // 파일 확장자 및 이름 순으로 정렬
        std::sort(matchingFiles.begin(), matchingFiles.end(), [](const fs::path& a, const fs::path& b) {
            std::string extA = a.extension().string();
            std::string extB = b.extension().string();
            if (extA == extB)
                return a.filename().string() < b.filename().string();
            return extA < extB;
        });

        std::ofstream outputFile(m_outputFileName);
        if (!outputFile) {
            m_logger.error("Cannot open output file: " + m_outputFileName);
            return false;
        }

        for (const auto& file : matchingFiles) {
            m_logger.info("Processing file: " + file.string());
            outputFile << "// ===== File: " << file << " =====" << std::endl;
            std::ifstream inputFile(file);
            if (!inputFile) {
                m_logger.error("Cannot read file: " + file.string());
                return false;
            }
            outputFile << inputFile.rdbuf() << std::endl;
        }
        m_logger.info("Successfully combined " + std::to_string(matchingFiles.size()) + 
                    " files into " + m_outputFileName);
        return true;
    } catch (const std::bad_alloc& e){
        m_logger.error("Critical memory allocation failure: " + std::string(e.what()));
        return false;
    }
}