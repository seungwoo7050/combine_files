#pragma once

#include <fstream>
#include <string>
#include <iostream>

/**
 * @brief 간단한 Logger 클래스
 * 
 * 콘솔 및 (옵션에 따라) 파일에 로그 메시지를 기록
 */

class Logger {
public:
    /**
     * @brief Logger 생성자
     * @param verbose 콘솔에 상세 로그 출력 여부
     * @param logFilePath 로그 파일 경로 (비어있으면 파일 로그 미사용)
     */
    Logger(bool verbose, const std::string& logFilePath = "");

    /**
     * @brief 소멸자
     */
    ~Logger();

    /**
     * @brief 정보 메시지 출력
     * @param message 출력할 메시지
     */
    void info(const std::string& message);

    /**
     * @brief 디버그 메시지 출력
     * @param message 출력할 메시지
     */
    void debug(const std::string& message);

    /**
     * @brief 에러 메시지 출력
     * @param message 출력할 메시지
     */
    void error(const std::string& message);

private:
    bool m_verbose;
    std::ofstream m_logFile;
};