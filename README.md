# Combine Files

## 1. 개요

`Combine Files`는 여러 개의 파일을 하나로 병합하는 C++ 기반의 CLI(명령줄 인터페이스) 프로그램입니다. 특정 디렉터리 내에서 지정한 파일 패턴(`*.cpp`, `*.h` 등)에 맞는 파일들을 찾아 병합할 수 있습니다.

## 2. 설치 및 빌드 방법

### 2.1. Git 클론 및 빌드

다음 명령어를 실행하여 프로젝트를 클론하고 빌드합니다.

```bash
git clone https://github.com/username/combine_files.git
cd combine_files
make
```

### 2.2. 빌드 완료 후 실행 파일 확인

빌드가 완료되면 `combine_files` 실행 파일이 생성됩니다.

```bash
ls -l combine_files
```

## 3. 사용법

프로그램을 실행하여 여러 파일을 하나의 출력 파일로 병합할 수 있습니다.

```bash
./combine_files -p ./src -o merged.txt --pattern "*.cpp" "*.h" -v
```

### 3.1. 전체 옵션
| 옵션 | 설명 |
|------|------|
| `-p, --path <directory>` | 탐색할 디렉터리 지정 (기본값: `.`) |
| `-o, --output <file>` | 병합된 내용을 저장할 출력 파일 |
| `--pattern "<wildcard>"` | 병합할 파일 패턴 지정 (`*.cpp`, `*.h` 등) |
| `-x, --exclude <directory>` | 제외할 디렉터리 지정 (예: `.git`, `build`) |
| `-v, --verbose` | 자세한 로그 출력 |
| `-h, --help` | 사용법 및 옵션 설명 출력 |

### 3.2. 실행 예시

```bash
./combine_files -p ./src -o merged_output.txt --pattern "*.cpp" "*.h"
```

위 명령어는 `./src` 디렉터리에서 `.cpp`와 `.h` 파일을 찾아 `merged_output.txt` 파일로 병합합니다.

```bash
./combine_files -p . -o result.txt --pattern "*.md" -v
```

위 명령어는 현재 디렉터리에서 `.md` 파일을 찾아 `result.txt`로 병합하며, 자세한 로그를 출력합니다.

## 4. Doxygen 문서 보기 📄 

프로젝트의 Doxygen 문서는 GitHub Pages에서 볼 수 있습니다.  

🔗 **[문서 보기](https://seungwoo7050.github.io/combine_files/)**

## 5. 라이선스

이 프로젝트는 MIT 라이선스를 따르며, 자유롭게 사용, 수정, 배포할 수 있습니다.

## 6. 기여 방법

프로젝트 개선을 위해 PR(Pull Request) 환영합니다. 버그 리포트 또는 기능 요청은 Issues에 등록해주세요.

```bash
git checkout -b feature-branch
make
./combine_files --help
```

## 7. 문의 및 지원

이 프로젝트와 관련된 문의는 `seungwoo7050 [at] gmail [dot] com` 또는 GitHub Issues를 통해 문의해주세요.
