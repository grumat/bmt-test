# AGENTS.md — bmt-test

## What this repo is

Embedded STM32 bare-metal example projects for the **bmt** C++20 template library. Produces `.elf` firmware images (not host executables). No tests, no CI, no lint — building is the verification step.

**Shared knowledge base**: `.kb/` — coding guidelines, bmt library design notes, implementation reviews, and test migration status. Consult this directory when making changes to examples or the bmt submodule.

**Shared knowledge base**: `.kb/` — coding guidelines, bmt library design notes, implementation reviews, and test migration status. Consult this directory when making changes to examples or the bmt submodule.

## Setup

```bash
git submodule update --init   # bmt library lives at ./bmt
```

The project requires an `arm-none-eabi` toolchain. The default toolchain path on Windows is `C:/SysGCC/arm-eabi` (SysProgs distribution, GCC 15.2). The toolchain file: `cmake/arm-eabi.cmake`.

BSP files are read from one of two sources (selected via `OPT_USE_VISUALGDB` in root `CMakeLists.txt`):
- **VisualGDB** (`false` by default): CubeMX HAL at `%USERPROFILE%/STM32Cube/Repository/<CUBE_MX>/Drivers`
- **VisualGDB** (`true`): BSP at `%LOCALAPPDATA%/VisualGDB/EmbeddedBSPs/arm-eabi/com.sysprogs.arm.stm32/`

Each CubeMX FW version is pinned per target in `cmake-variants.yaml`.

## Build

**You must select a target MCU variant before building.** Three variants are defined in `cmake-variants.yaml`:

| Variant | MCU define         | CPU core  | Linker script              |
|---------|--------------------|-----------|----------------------------|
| F103    | `STM32F103xB`      | Cortex-M3 | `STM32F103C8_flash.lds`    |
| L432    | `STM32L432xx`      | Cortex-M4 | `STM32L432KC_flash.lds`    |
| G431    | `STM32G431xx`      | Cortex-M4 | `STM32G431KB_flash.lds`    |

The VSCode config uses Ninja generator:

```bash
# Example: configure for F103 Debug
cmake -B build -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE=cmake/arm-eabi.cmake \
  -DCMAKE_BUILD_TYPE=Debug \
  -DTARGET_MCU=STM32F103xB -DDEVICE_SUPPORT=STM32F1xx \
  -DCPU_FLAG=cortex-m3 -DCUBE_MX=STM32Cube_FW_F1_V1.8.4 \
  -DLINKER_SCRIPT=STM32F103C8_flash.lds

cmake --build build
```

Build outputs per example: `<example>-<TARGET_MCU>.elf` and `.lst` (disassembly). All six examples are built together.

## Code conventions

- **Tabs** for indentation (not spaces) — set in `.vscode/settings.json`
- **C++20** (`-std=c++20`)
- **Allman-style braces** (opening brace on new line for functions, types, namespaces)
- Every example compiles for all three MCUs via `#ifdef STM32F103xB` / `#elif defined(STM32L432xx)` / `#elif defined(STM32G431xx)`. The variant define is injected by `add_compile_definitions(${TARGET_MCU})` in root CMake.
- Startup file format varies by BSP source: `.c` (VisualGDB) vs `.s` assembly (CubeMX)
- Hardware configuration is expressed as `constexpr` template types, not runtime structs. See `bmt/docs/README.md` for the pattern.
- `extern "C" void SystemInit()` is the pre-main init hook. `main()` is the entry after that.

## Debugging

Cortex-Debug VSCode extension with BMP, J-Link, or ST-Link probes. Configs in `.vscode/launch.json`. SVD peripheral description files in `SVD/`.

## Key files

| Path | Purpose |
|------|---------|
| `CMakeLists.txt` | Root build — sets BSP paths, include dirs, adds all 6 examples |
| `cmake-variants.yaml` | MCU variant definitions (VSCode CMake Tools) |
| `cmake/arm-eabi.cmake` | Cross-compilation toolchain file |
| `LDS/` | Linker scripts (one per target MCU) |
| `SVD/` | SVD files for debug peripheral view |
| `bmt/` | Git submodule — the bmt template library headers |
| `bmt/docs/` | Library documentation (CONCEPTS.md, INSTALL.md, peripheral docs) |
| `.kb/` | Shared knowledge base — coding guidelines, bmt design notes, test migration status |
| `.kb/` | Shared knowledge base — coding guidelines, bmt design notes, test migration status |
