#pragma once

#include <vector>
#include <regex>
#include <string>

#include "Logger.hpp"
#include "IFileCombiner.hpp"

/**
 * @brief 텍스트 파일 병합을 위한 구체적 구현 클래스
 */
class TextFileCombiner : public IFilecombiner {
public:
    /**
     * @brief TextFileCombiner 생성자
     * @param searchPath 검색할 디렉터리
     * @param excludeDirs 제외할 디렉터리 이름 목록
     * @param patterns 파일 매칭을 위한 와일드카드 패턴 목록
     * @param outputFileName 결과 출력 파일 이름
     * @param logger Logger 인스턴스
     */
    TextFileCombiner(const std::string& searchPath,
                     const std::vector<std::string>& excludeDirs,
                     const std::vector<std::string>&  patterns,
                     const std::string& outputFileName,
                     Logger& logger);

    /**
     * @brief 텍스트 파일들을 병합하여 출력 파일에 기록
     * @return 성공 시 true, 실패 시 false
     */
    bool combineFiles() override;

private:
    std::string m_searchPath;
    std::vector<std::string> m_excludeDirs;
    std::vector<std::regex> m_regexPatterns;
    std::string m_outputFileName;
    Logger& m_logger;

    /**
     * @brief 와일드카드 패턴을 정규표현식으로 변환
     * @param pattern 변환할 와일드카드 패턴
     * @return 변환된 std::regex
     */
    std::regex wildcardToRegex(const std::string& pattern);

    /**
     * @brief 파일명이 정규표현식 패턴 중 하나와 매칭되는지 확인
     * @param filename 확인할 파일명
     * @return 매칭되면 true, 아니면 false
     */
    bool matchesAnyPattern(const std::string& filename);
};