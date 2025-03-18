#pragma once

#include <string>

/**
 * @brief 파일 병합을 위한 인터페이스
 * 
 * 텍스트, PDF, 이미지 등 다양한 파일 형식에 대한 병합 기능 확장 가능을 위한 인터페이스 설계
 */
class IFilecombiner {
public:
    virtual ~IFilecombiner() = default;

    /**
     * @brief 파일 병합을 수행하는 함수
     * @return 성공 시 true, 실패 시 false
     */
    virtual bool combineFiles() = 0;
};

